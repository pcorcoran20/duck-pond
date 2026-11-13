# patrick/ — Everest / Duck Pond additions

Things that live alongside the firmware but aren't part of it. Upstream merges never
touch this folder.

| path | what |
| --- | --- |
| `homeassistant/irrigoto_43c89c_manual.yaml` | HA package: joystick scripts (on/off, throw ±, bearing ±, mirror, sweep a sector around the aim, swing left/right), `input_text.oto_ip` |
| `homeassistant/oto_keypad_card.yaml` + `www/oto_keypad_card.js` | Custom card: arrow-key control of the joystick (M mirror, S sweep, W swing, Esc off) |
| `homeassistant/irrigoto_43c89c_spots.yaml` | HA package: spot-water named trees, dry travel between them, optional schedule |
| `homeassistant/oto_joystick_card.yaml` | Lovelace manual card for the joystick |
| `tools/duck-pond-remote.html` | Keyboard remote. Open from disk, not through HA (HTTPS can't call the device over HTTP) |
| `design/hearth-guide.md` | Exact-values style guide extracted from the Hearth Dashboard Studio artifact — the house look the device pages follow |
| `design/spec.md` + `shared.css`, `sprite.html`, `blocks/`, `hearth-icons.json` | The implementation spec that produced the Hearth component pass (b1c9013): shared CSS prelude, per-page CSS blocks, icon sprite + catalog |

Device: `irrigoto-43c89c`, 8 MB flash, TCA6408A LED expander. MAC kept out of the
repo (it's on the device page in HA) — upstream's `.gitignore` keeps per-user MACs
and LAN IPs local, so this folder follows the same rule.
Factory backup: `oto_factory_43c89c.bin` (8,388,608 bytes) — keep it off this repo.

UI reskin and charging sensor are in the main tree (`components/irrigoto/`), see the
two commits on top of upstream.
