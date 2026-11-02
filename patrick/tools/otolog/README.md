# otolog — read the OtO's ESPHome log over its fallback hotspot

1. Join the Mac to the `irrigoto-<suffix> Fallback` WiFi (temporarily turn off
   Auto-Join for the house SSID so macOS doesn't jump back).
2. Once: `./setup.sh`
3. Each time: `export OTO_API_KEY='<value under api: encryption: key: in secrets.yaml>'`
   then `./run.sh`  (defaults: --host 192.168.4.1 --port 6053)
Ctrl-C stops it. A copy of everything is appended to oto-<date>.log next to the script.
The key is read from your shell only and never written to disk.
