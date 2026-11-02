#!/usr/bin/env python3
"""otolog - stream an ESPHome device's log over the native API (port 6053).

Built for reading the OtO sprinkler while joined to its fallback hotspot
(device at 192.168.4.1). Reconnects automatically when the device deep-sleeps.
"""
from __future__ import annotations

import argparse
import asyncio
import datetime as dt
import os
import re
import signal
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ANSI_RE = re.compile(r"\x1b\[[0-9;]*[A-Za-z]")
RETRY_SECONDS = 5.0


def strip_ansi(text: str) -> str:
    return ANSI_RE.sub("", text)


def decode_log_message(message: bytes | str) -> str:
    if isinstance(message, bytes):
        message = message.decode("utf-8", errors="replace")
    return strip_ansi(message).rstrip("\r\n")


def stamp(now: dt.datetime | None = None) -> str:
    now = now or dt.datetime.now()
    return now.strftime("%H:%M:%S.%f")[:-3]


def format_line(message: bytes | str, now: dt.datetime | None = None) -> str:
    return f"{stamp(now)} {decode_log_message(message)}"


class Sink:
    """Writes to stdout and appends to oto-<date>.log (rotates by date)."""

    def __init__(self, directory: Path) -> None:
        self.directory = directory
        self.directory.mkdir(parents=True, exist_ok=True)
        self._fh = None
        self._date = None

    def _file(self):
        today = dt.date.today().isoformat()
        if self._fh is None or self._date != today:
            if self._fh:
                self._fh.close()
            self._fh = open(self.directory / f"oto-{today}.log", "a", encoding="utf-8")
            self._date = today
        return self._fh

    def write(self, line: str) -> None:
        print(line, flush=True)
        fh = self._file()
        fh.write(line + "\n")
        fh.flush()

    def notice(self, text: str) -> None:
        self.write(f"{stamp()} [otolog] {text}")

    def close(self) -> None:
        if self._fh:
            self._fh.close()
            self._fh = None


async def run(host: str, port: int, key: str | None, sink: Sink, log_level_name: str) -> int:
    from importlib.metadata import version as _pkg_version
    from aioesphomeapi import APIClient, LogLevel
    from aioesphomeapi.core import (
        APIConnectionError,
        HandshakeAPIError,
        InvalidAuthAPIError,
        InvalidEncryptionKeyAPIError,
        RequiresEncryptionAPIError,
    )

    level = getattr(LogLevel, log_level_name, None)
    if level is None:
        level = getattr(LogLevel, "LOG_LEVEL_DEBUG")
        sink.notice(f"{log_level_name} not in this aioesphomeapi; using LOG_LEVEL_DEBUG")

    stop = asyncio.Event()
    disconnected = asyncio.Event()
    loop = asyncio.get_running_loop()
    for sig in (signal.SIGINT, signal.SIGTERM):
        loop.add_signal_handler(sig, stop.set)

    sink.notice(
        f"aioesphomeapi {_pkg_version('aioesphomeapi')} -> {host}:{port} "
        f"(log level {level.name}; {'PLAINTEXT, no encryption' if key is None else 'noise-encrypted'}); Ctrl-C to stop"
    )

    waiting_announced = False
    while not stop.is_set():
        disconnected.clear()
        client = APIClient(host, port, None, noise_psk=key, client_info="otolog", keepalive=15)

        async def on_stop(expected: bool) -> None:
            disconnected.set()

        try:
            await client.connect(on_stop=on_stop, login=True, log_errors=False)
        except (InvalidEncryptionKeyAPIError, RequiresEncryptionAPIError, InvalidAuthAPIError, HandshakeAPIError) as exc:
            sink.notice(f"ERROR: handshake/authentication failed: {exc!r}")
            sink.notice("Check OTO_API_KEY matches api: encryption: key: in secrets.yaml (base64, 32 bytes).")
            return 2
        except (APIConnectionError, OSError, asyncio.TimeoutError) as exc:
            if not waiting_announced:
                reason = str(exc).splitlines()[0] if str(exc) else type(exc).__name__
                if "Connect call failed" in reason or "Errno" in reason:
                    reason = reason[reason.rfind("[Errno"):] if "[Errno" in reason else reason
                sink.notice(f"could not connect to {host}:{port} ({reason[:120]}); waiting for device, retrying every {RETRY_SECONDS:.0f}s...")
                waiting_announced = True
            try:
                await asyncio.wait_for(stop.wait(), RETRY_SECONDS)
            except asyncio.TimeoutError:
                pass
            continue

        waiting_announced = False
        try:
            info = await client.device_info()
            sink.notice(
                f"connected: name={info.name} friendly={info.friendly_name!r} mac={info.mac_address} "
                f"esphome={info.esphome_version} compiled={info.compilation_time!r} "
                f"project={info.project_name} {info.project_version} model={info.model} "
                f"deep_sleep={info.has_deep_sleep}"
            )

            def on_log(msg) -> None:
                sink.write(format_line(msg.message))

            client.subscribe_logs(on_log, log_level=level, dump_config=False)
            sink.notice("log subscription active")

            stop_task = asyncio.ensure_future(stop.wait())
            disc_task = asyncio.ensure_future(disconnected.wait())
            done, pending = await asyncio.wait({stop_task, disc_task}, return_when=asyncio.FIRST_COMPLETED)
            for t in pending:
                t.cancel()
            if disc_task in done and not stop.is_set():
                sink.notice("connection dropped (device asleep or rebooting); waiting for device...")
                waiting_announced = True
                try:
                    await asyncio.wait_for(stop.wait(), RETRY_SECONDS)
                except asyncio.TimeoutError:
                    pass
        except APIConnectionError as exc:
            sink.notice(f"API error after connect: {type(exc).__name__}: {exc}; reconnecting...")
            await asyncio.sleep(RETRY_SECONDS)
        finally:
            try:
                await client.disconnect(force=True)
            except Exception:
                pass

    sink.notice("stopped")
    return 0


def selftest() -> int:
    raw = b"\x1b[0;36m[D][wifi:123]: Connecting to 'home'...\x1b[0m\r\n"
    out = decode_log_message(raw)
    assert out == "[D][wifi:123]: Connecting to 'home'...", out
    line = format_line(raw, dt.datetime(2026, 11, 1, 12, 34, 56, 789000))
    assert line == "12:34:56.789 [D][wifi:123]: Connecting to 'home'...", line
    assert strip_ansi("\x1b[1;31mred\x1b[0m plain") == "red plain"
    assert decode_log_message(b"\xff\xfebad") == "�￾bad".replace("￾", "�")
    print("selftest ok:", line)
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(
        prog="otolog",
        description="Stream an ESPHome device's log over the native API (noise-encrypted).",
        epilog="The API key is read from env OTO_API_KEY unless --key is given. "
        "Output goes to stdout and is appended to otolog/oto-<date>.log.",
    )
    ap.add_argument("--host", default="192.168.4.1", help="device address (default 192.168.4.1)")
    ap.add_argument("--port", type=int, default=6053, help="native API port (default 6053)")
    ap.add_argument("--key", help="noise PSK (base64); overrides OTO_API_KEY")
    ap.add_argument("--level", default="LOG_LEVEL_VERBOSE",
                    help="LogLevel enum name (default LOG_LEVEL_VERBOSE; falls back to DEBUG)")
    ap.add_argument("--logdir", default=str(HERE), help="directory for oto-<date>.log")
    ap.add_argument("--selftest", action="store_true", help="run ANSI/timestamp unit checks and exit")
    ap.add_argument("--plaintext", action="store_true",
                    help="connect WITHOUT encryption (for an image whose api: has no encryption key); no OTO_API_KEY needed")
    args = ap.parse_args()

    if args.selftest:
        return selftest()

    key = None if args.plaintext else (args.key or os.environ.get("OTO_API_KEY"))
    if not key and not args.plaintext:
        print("usage: export OTO_API_KEY=<base64 key from secrets.yaml>; otolog.py [--host 192.168.4.1] [--port 6053]",
              file=sys.stderr)
        print("error: no API key (set OTO_API_KEY or pass --key)", file=sys.stderr)
        return 2

    sink = Sink(Path(args.logdir))
    try:
        return asyncio.run(run(args.host, args.port, key, sink, args.level))
    except KeyboardInterrupt:
        return 0
    finally:
        sink.close()


if __name__ == "__main__":
    sys.exit(main())
