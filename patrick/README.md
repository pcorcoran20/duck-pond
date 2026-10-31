# patrick/ — Everest / Duck Pond additions

Things that live alongside the firmware but aren't part of it. Upstream merges never
touch this folder.

| path | what |
| --- | --- |
| `homeassistant/irrigoto_43c89c_manual.yaml` | HA package: joystick scripts (on/off, throw ±, bearing ±), `input_text.oto_ip` |
| `homeassistant/irrigoto_43c89c_spots.yaml` | HA package: spot-water named trees, dry travel between them, optional schedule |
| `homeassistant/oto_joystick_card.yaml` | Lovelace manual card for the joystick |
| `tools/duck-pond-remote.html` | Keyboard remote. Open from disk, not through HA (HTTPS can't call the device over HTTP) |

Device: `irrigoto-43c89c`, 8 MB flash, TCA6408A LED expander. MAC kept out of the
repo (it's on the device page in HA) — upstream's `.gitignore` keeps per-user MACs
and LAN IPs local, so this folder follows the same rule.
Factory backup: `oto_factory_43c89c.bin` (8,388,608 bytes) — keep it off this repo.

UI reskin and charging sensor are in the main tree (`components/irrigoto/`), see the
two commits on top of upstream.
