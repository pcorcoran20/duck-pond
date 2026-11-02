#!/bin/bash
# One-time setup on any Mac: creates a Python venv next to this script and
# installs aioesphomeapi. Then use ./run.sh.
# Add --with-ota to also install esphome so ./otaup.py can push a .ota.bin.
# Needs Python 3.11+. Picks the newest one it can find; override with
#   PYTHON=/path/to/python3.12 ./setup.sh
set -e
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PY="${PYTHON:-}"
if [ -z "$PY" ]; then
  for c in python3.14 python3.13 python3.12 python3.11 \
           /opt/homebrew/bin/python3 /usr/local/bin/python3 python3; do
    if command -v "$c" >/dev/null 2>&1 && "$c" -c 'import sys; sys.exit(0 if sys.version_info >= (3,11) else 1)' 2>/dev/null; then
      PY="$(command -v "$c")"; break
    fi
  done
fi
if [ -z "$PY" ]; then
  echo "No Python 3.11+ found. Install one, then re-run:" >&2
  echo "  brew install python@3.12      (Homebrew)" >&2
  echo "  or download from https://www.python.org/downloads/macos/" >&2
  exit 1
fi
echo "using $PY ($("$PY" --version 2>&1))"
rm -rf "$HERE/venv"
"$PY" -m venv "$HERE/venv"
"$HERE/venv/bin/pip" install --quiet --upgrade pip
"$HERE/venv/bin/pip" install --quiet 'aioesphomeapi==46.25.1'
if [ "${1:-}" = "--with-ota" ]; then
  echo "installing esphome (for otaup.py; a few minutes)..."
  "$HERE/venv/bin/pip" install --quiet 'esphome==2026.10.1'
fi
echo "ok: venv ready. Next: export OTO_API_KEY='<api encryption key>' ; $HERE/run.sh"
