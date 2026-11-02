#!/usr/bin/env python3
"""otaup - push an ESPHome .ota.bin to a device over the ESPHome OTA port.

Built for flashing the OtO while joined to its fallback hotspot (192.168.4.1),
where the HA ESPHome Builder cannot reach it. Uses esphome's own espota2
uploader, so auth (SHA256 challenge with the ota: password) is the real thing.

  export OTO_OTA_PASSWORD='<ota: password: value from secrets.yaml>'
  ./otaup.py firmware.ota.bin [--host 192.168.4.1] [--port 3232]
"""
import argparse
import os
import sys
from pathlib import Path

# Re-exec under the sibling venv (where setup.sh installed esphome) when run
# with some other interpreter, e.g. ./otaup.py under the system python3.
_VENV = Path(__file__).resolve().parent / "venv"
_VENV_PY = _VENV / "bin" / "python"
# sys.prefix is the venv dir when running inside it; comparing executables
# does not work because venv/bin/python is a symlink to the real interpreter.
if _VENV_PY.is_file() and Path(sys.prefix).resolve() != _VENV.resolve():
    os.execv(str(_VENV_PY), [str(_VENV_PY), str(Path(__file__).resolve()), *sys.argv[1:]])


def main() -> int:
    ap = argparse.ArgumentParser(prog="otaup", description=__doc__.split("\n\n")[0])
    ap.add_argument("file", help="the .ota.bin downloaded from the ESPHome Builder (OTA format, not factory)")
    ap.add_argument("--host", default="192.168.4.1")
    ap.add_argument("--port", type=int, default=3232)
    ap.add_argument("--password", help="OTA password; overrides OTO_OTA_PASSWORD")
    args = ap.parse_args()

    path = Path(args.file)
    if not path.is_file():
        print(f"error: {path} is not a file", file=sys.stderr)
        return 2
    if path.name.endswith(".factory.bin"):
        print("error: that is a factory image; OTA needs the .ota.bin", file=sys.stderr)
        return 2
    password = args.password or os.environ.get("OTO_OTA_PASSWORD")
    if not password:
        print("usage: export OTO_OTA_PASSWORD='<ota password>'; otaup.py firmware.ota.bin", file=sys.stderr)
        return 2
    try:
        from esphome.espota2 import run_ota
    except ImportError:
        print("error: esphome not installed in this venv; run ./setup.sh --with-ota (needs internet)", file=sys.stderr)
        return 2
    import logging
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    print(f"otaup: {path.name} ({path.stat().st_size} bytes) -> {args.host}:{args.port}")
    rc, addr = run_ota(args.host, args.port, password, path)
    if rc == 0:
        print(f"otaup: upload accepted by {addr}; device is rebooting into the new image")
    else:
        print("otaup: upload FAILED (see messages above)", file=sys.stderr)
    return rc


if __name__ == "__main__":
    sys.exit(main())
