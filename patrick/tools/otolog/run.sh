#!/bin/bash
# otolog launcher: activates the venv and streams the OtO's ESPHome log.
# Usage: export OTO_API_KEY='<base64 api key from secrets.yaml>'; ./run.sh [--host 192.168.4.1] [--port 6053] [--level LOG_LEVEL_VERBOSE]
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [ -z "$OTO_API_KEY" ] && ! printf '%s\n' "$@" | grep -q -- '^--key' && ! printf '%s\n' "$@" | grep -qE -- '^(--help|-h|--selftest|--plaintext)$'; then
  echo "usage: export OTO_API_KEY='<base64 api key>'; $0 [--host 192.168.4.1] [--port 6053] [--level LOG_LEVEL_VERBOSE]" >&2
  echo "  (or pass --key <base64 api key>)" >&2
  exit 2
fi
# shellcheck disable=SC1091
source "$HERE/venv/bin/activate"
exec python3 "$HERE/otolog.py" "$@"
