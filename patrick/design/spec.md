# irrigoto -> Hearth component language: implementation spec

Files in this directory:

* `shared.css`   - the new shared prelude. Replaces the old prelude VERBATIM and IDENTICALLY in all five pages.
* `sprite.html`  - five per-page inline sprites. Each page gets ONLY its own block.
* `spec.md`      - this document.
* `blocks/*.css` - the five page-CSS blocks from sections 1b-5b as paste-ready files (byte-identical to the fenced
                   blocks in this document; use them instead of copying out of markdown).
* (build/orig/ is not kept here: the pre-Hearth baseline is commit 8084a3b, `git show 8084a3b:components/irrigoto/html/<page>.html`.)
* `build/*.html` - STALE: scratch builds of the FIRST draft of this spec, kept only because their measured sizes are the
                   basis of the budget arithmetic in 1f-5f. They predate the review revisions below; where they and this
                   document disagree, this document wins. Never copy them over the real files.

Pages: `<repo>/components/irrigoto/html/{landing,zone_setup,cal,schedule,fs}.html`

Hearth reference (read it if a judgement below needs grounding):
`Hearth Dashboard Studio` (https://claude.ai/code/artifact/5b6253f0-7ce1-4eb1-a490-7a0c87352c14, read it with the Artifact tool)

---------------------------------------------------------------------------------------------------

## 0. Global rules (apply to every page)

### 0.1 The shared prelude replacement

The shared prelude is byte-identical in all five files today (md5 `c0a40d71...` over the 118 lines from
`*{box-sizing...` to the `@media (prefers-reduced-motion:reduce)` rule) and is preceded by one comment line
`/* ---- Muscovy design system ---- */`. Replace **from that comment line through the reduced-motion rule, inclusive**
with the entire contents of `shared.css`. Exact current line ranges (comment line .. reduced-motion line):

| page | old prelude lines | first page-specific line after it (boundary selector; keep it and everything after) |
|---|---|---|
| landing.html | 38-156 | 158 `body{min-height:100dvh;display:flex;flex-direction:column;max-width:560px;margin:0 auto;}` |
| zone_setup.html | 55-173 | 175 `html,body{height:100%;overflow:hidden;}` |
| cal.html | 55-173 | 175 `body{max-width:560px;margin:0 auto;padding-bottom:24px;}` |
| schedule.html | 58-176 | 178 `body{max-width:560px;margin:0 auto;padding-bottom:24px;}` |
| fs.html | 55-173 | 175 `body{max-width:640px;margin:0 auto;padding-bottom:24px;}` |

Line 157 / 174 / 174 / 177 / 174 is a blank line in each file; keep one blank line between the prelude and the
page block. After the replacement, `diff` of the prelude region across the five files must be empty (check 10.1).

What changed in the prelude, in one paragraph: the two token blocks are copied unchanged, with ten tokens
**appended** to each (`--dot --tint --tint-2 --ok-ink --orange-ink --red-ink --scrim --knob --shadow-float --shadow-knob`;
the `*-ink` tokens are the text colour to use on a status tint: equal to `--ok/--orange/--red` in dark, darkened in light
so 11-12px status text passes in sunlight - use them wherever status-coloured TEXT sits on a tint or on white); body goes
to Hearth's 14px; `svg.i` is defined; the header becomes Hearth `.top` (panel background, 1px line, 40px `.back` icon
button, the duck inside an inverted 28px `.mark` tile via CSS on `.logo .duck`, the page name `.hdr-title/.header-mid`
at `.name-in` weight (15px/600, sentence case, `--text`; Hearth's top bar never carries an eyebrow), `#conn` as the
`.ha-chip` status pill, `.usage` as the plain mono `.stage-meta` read-out); `main` becomes a `.pane` (flex column, 16px
gap); `.sec-hdr` becomes a `.group` divider (1px rule above + 16px, suppressed on the first `section` of `main`
(`:first-of-type`, because cal's `main` starts with a callout div), on `main > .sec-hdr:first-child` and inside cards);
`.sec-btn/#refresh-btn` (the action beside a group title) is Hearth `.mini` at the 36px floor (recessed `--bg`, muted
text, 12.5px); `.card` loses its drop shadow and takes Hearth's chrome-card radius 12 (the `--radius` token keeps its
14px value for check 10.2; it is simply no longer used by cards); `.empty` becomes the dashed `.insp-empty` (quiet when
written inside a card, including fs's `#tree`); the `.btn` family becomes Hearth `.btn` at touch density (42px, radius 10,
danger = red text on the normal outline in EVERY state - no red fill on press, primary = accent fill with transparent
border, a `hover:hover`-gated Hearth hover for laptops); fields are recessed radius-9 inputs with accent-border focus
(range and checkbox inputs keep the global `:focus-visible` ring), range inputs get a 36px hit box; `.name-in` is
invisible-until-hover on desktop and shows its resting 1px border on touch (`hover:none`); `.theme-switch` becomes
Hearth `.switch` (44x26 visual, single 1px knob shadow `--shadow-knob`, knob on `.theme-slider:before`, `#theme-cb` stays
an invisible full-size checkbox, and the label's `:before` pads the hit box to ~56x44 with no markup change);
`.banner` becomes a `.rep` row (panel fill, `--border` line, status is a tint on the 22px icon circle only; warning =
orange, not red); small utilities are added (`.score .kv .val .field .name-in @keyframes pulse`; the first draft's
unused `.eyebrow .pill .btnrow .dotpulse .lbl2` were dropped to save bytes).
No selector that JS relies on was removed. `.sec-btn,#refresh-btn`, `.btn-primary/.btn-green/.btn-danger/.btn-red`,
`.card/.status-card/.upload-card`, `.hint/.note/.cal-desc`, `.throw-inp/.path-inp/.file-inp`, `#conn-dot.ok/.err`,
`body.winter-lock ...` all still exist with the same meaning.

Brand exception, stated once: the duck keeps its own `--pond`/`--red` fills inside the inverted `.mark` tile. Hearth's
mark glyph is monochrome, but the duck is the product mascot, not an icon; leave its fills alone.

### 0.2 The sprite

Paste the page's block from `sprite.html` on its own line **immediately after `<body>`** (before `<header>`).
Reference glyphs as `<svg class="i"><use href="#i-NAME"/></svg>`. Never add `class="i"` to the duck.
Never put the sprite inside `#entries` (schedule) or `#zone-list` (landing).

### 0.3 Density decisions (the "how touch-sized vs Hearth-dense" call)

Hearth's chrome is 7px-padding desktop density. These pages are used one-handed outdoors, so:

| control | Hearth | here | why |
|---|---|---|---|
| `.btn` | 7px 12px (~33px) | 10px 14px, `min-height:42px` | the guide's own touch adaptation |
| `.btn.icon`, `.back` | 34px | 40px square | touch floor |
| `.btn.sm` / `.sec-btn` / `#refresh-btn` | `.mini` 3px 8px | 6px 12px, `min-height:36px` | secondary actions get the 36px floor |
| inputs / selects | 8px 10px (~36px) | 10px 12px, `min-height:42px`, 15px text | same as before; 15px keeps iOS zoom behaviour unchanged |
| d-pad tiles | `.kp-pad` 50px | 56px, gap 6 (48px, gap 6 under 640px tall) | >= 44 rule everywhere; the gap and the short-viewport step give the radar height back |
| `.sbtn` toolbar cells | `.mnav` ~44px | 44px, 11px label | the 11px label is the guide's smallest size; 10.5 was unreadable in sun |
| `#btn-trim` | `.mini` 3px 8px | 36px, 12px | it is tapped standing in the spray; 36 is the secondary-action floor |
| day picker | `.seg` 5px 10px | 40px tall segments | 44 preferred, 40 is the floor; 7 across a 311px card |
| primary footer / sheet buttons | 7px | 46px | one-handed thumb targets |
| toggle | 38x22 | 44x26 visual, ~56x44 hit box | touch; the hit box comes from `.theme-switch:before`, no markup change |
| range input | native | 36px tall hit box | the thumb is the only real target otherwise |
| fs `dl` / `del` | `.mini` | 36px tall, min 44px wide, 8px apart | a wet-thumb miss on `dl` must not land on `del` |

Everything else (radius scale, font scale, weights, tracking, icon stroke, muted hierarchy, flat chrome) is
Hearth's exactly. Body copy is 14px; labels 12.5/500; eyebrows 11/600/.08em uppercase; hints 12.5/400; buttons
13/500; display face only on headings 16px+ and big numbers.

### 0.4 Glyph policy

* Every emoji / symbol glyph that lives in **markup** is replaced by a sprite `<use>`.
* Glyphs inside **JS `innerHTML` strings** (single-quoted or template literal) are replaced in place, keeping the
  JS string syntax valid. SVG attributes use double quotes, so inside a single-quoted or backtick string nothing
  needs escaping. Every such edit is listed per page with exact before/after. Do not touch anything else in `<script>`.
* Glyphs written via **`textContent`** cannot become SVG. They stay as text (`▶ Start`, `⊙ trim`, `✓`, `●/○`, `🐶 Chase`,
  `→`). Where the markup also carries the same glyph (landing `#start-btn`, zone_setup `#btn-trim`), the markup keeps
  the text glyph too, so the control looks the same before and after JS touches it.
* A leading `+` on "Add Zone" / "Add entry" is treated as a glyph (it stands for the plus icon); the label text
  after it is unchanged.
* With an `svg.i` leading the label, drop the single space that followed the old glyph (`.btn{gap:7px}` spaces it).
* The winter-lock banner built by the **head script** keeps its `&#10052;` text snowflake on every page (the head
  script is off-limits). It already reads `--green-dim --border --radius-sm --font`, so it inherits the new palette;
  leave it.

### 0.4a Order of work (line numbers)

Every line number in this document refers to the page **as it is today** (= `build/orig/`). Apply each page's
`<script>` string edits (1d, 2d, 5d) **first**, before the prelude replacement or any CSS/markup change, so the numbers
are still true; or ignore the numbers entirely and match on the quoted "before" text, which is unique in every case.
Never edit a `<script>` line by number after the CSS pass: the prelude alone shifts everything by ~46 lines.

### 0.5 Raw-string hazard

Before saving, grep each page for `)` followed by one or more uppercase letters and then `"` (check 10.3). Nothing
in `shared.css` or `sprite.html` trips it; keep it that way in your own edits (e.g. never let a `)` be followed directly by capital letters and a double quote).

---------------------------------------------------------------------------------------------------

## 1. landing.html

Current: 926 lines, 47,033 bytes. Budget ceiling 55,225 bytes. Markup 215-354, one `<script>` 356-924.

### 1a. Prelude

Replace lines 38-156 with `shared.css`. Boundary: keep line 158
`body{min-height:100dvh;display:flex;flex-direction:column;max-width:560px;margin:0 auto;}` as the first page rule.

### 1b. Page CSS

Replace the whole page block (old lines 158-213, from the `body{min-height:100dvh...` rule through
`input[type=range]{accent-color:var(--green);}`) with this block verbatim:

```css
body{min-height:100dvh;display:flex;flex-direction:column;max-width:560px;margin:0 auto;}
main{flex:1;overflow-y:auto;}
/* header: editable device name (.name-in). No pencil: touch gets the resting border from the prelude */
.hdr-name{display:flex;align-items:center;min-width:0;overflow:hidden;}
input.dev-name-inp{width:min(150px,34vw);font-size:13px;padding:6px 8px;}
.edit-icon{display:none;}
#winter-left{font-family:var(--mono);font-variant-numeric:tabular-nums;}
/* zone cards (JS: div.card#zcard-N > .zone-card); the radar disc is the card's icon tile */
#zone-list{display:flex;flex-direction:column;gap:8px;}
.zone-card{display:flex;gap:12px;align-items:flex-start;}
.zone-radar{flex:none;width:90px;height:90px;border-radius:50%;}
.zone-body{flex:1;min-width:0;}
.zone-name-wrap{display:flex;align-items:center;margin-left:-8px;}
input.zone-name{font-family:var(--display);font-size:18px;font-weight:700;letter-spacing:-.01em;width:100%;padding:4px 8px;}
.zone-meta{font-size:12.5px;color:var(--text-mid);line-height:1.45;margin-bottom:10px;}
.zone-actions{display:flex;gap:8px;flex-wrap:wrap;}
.zone-actions .btn{min-height:40px;padding:9px 12px;}
.zone-actions .btn:last-child{margin-left:auto;}
/* watering status row (Hearth .ai-status: muted text, only the dot is coloured); JS sets display flex/none */
.watering-bar{display:none;align-items:center;gap:8px;font-size:13px;font-weight:600;color:var(--text-mid);margin-bottom:4px;min-height:1.4em;}
.pulse-dot{width:8px;height:8px;border-radius:50%;background:var(--green);flex:none;animation:pulse 1s ease-in-out infinite;}
/* schedule summary rows; the dot colour is JS-owned (style.color), CSS turns the glyph into an 8px disc */
.sched-row{padding:7px 0;border-bottom:1px solid var(--border);}
.sched-row:last-child{border-bottom:0;}
.sched-dot{display:inline-block;width:8px;height:8px;border-radius:50%;background:currentColor;font-size:0;vertical-align:middle;margin-right:4px;transition:color .2s;}
.sched-row[data-enabled="0"] .sched-dot{background:transparent;border:1.5px solid currentColor;}
.sched-pulse{animation:pulse 1s ease-in-out infinite;}
.sched-dot.sched-pulse{box-shadow:0 0 6px currentColor;}
/* device rows (Hearth .holrow): muted label, 13px mono tabular value */
.dev-row{display:flex;justify-content:space-between;align-items:center;gap:12px;padding:9px 0;border-bottom:1px solid var(--border);font-size:13px;}
.dev-row:last-child{border-bottom:0;}
.dev-label{color:var(--text-mid);font-weight:500;}
.dev-val{color:var(--text);font-family:var(--mono);font-size:13px;text-align:right;font-variant-numeric:tabular-nums;}
.dev-val svg.i{width:14px;height:14px;vertical-align:-3px;}
/* water modal: Hearth .sheet (head / body / sticky foot), bottom-anchored; opened only by #modal-bg.open */
#modal-bg{display:none;position:fixed;inset:0;background:var(--scrim);z-index:100;align-items:flex-end;justify-content:center;}
#modal-bg.open{display:flex;}
#modal{background:var(--bg2);border:1px solid var(--border);border-bottom:0;border-radius:18px 18px 0 0;
width:100%;max-width:560px;max-height:88dvh;overflow-y:auto;box-shadow:var(--shadow-float);}
.sheet-head{display:flex;align-items:center;gap:12px;padding:14px 18px;border-bottom:1px solid var(--border);margin-bottom:14px;}
.sheet-head > div{flex:1;min-width:0;}
.modal-title{font-family:var(--display);font-size:20px;font-weight:700;letter-spacing:-.01em;}
.modal-sub{font-size:12.5px;color:var(--text-mid);margin-top:2px;}
.mode-grid{display:grid;grid-template-columns:1fr 1fr;gap:8px;padding:0 18px;margin-bottom:14px;}
.mode-btn{min-height:48px;padding:9px 12px;border-radius:12px;border:1px solid var(--border);background:var(--bg2);color:var(--text);font-size:14px;font-weight:600;text-align:left;line-height:1.35;}
.mode-btn svg.i{width:16px;height:16px;vertical-align:-3px;margin-right:2px;}
.mode-btn span{display:block;font-size:12px;font-weight:400;color:var(--text-mid);margin-top:2px;}
.mode-btn.sel{border-color:var(--green);box-shadow:0 0 0 2px var(--green-glow);}
#chase-row{margin:0 18px 14px;padding:12px;border:1px solid var(--border);border-radius:var(--radius-sm);background:var(--bg);font-size:12.5px;}
#chase-row .val{color:var(--text);font-weight:600;}
#modal-status{font-size:12.5px;color:var(--text-mid);text-align:center;margin:0 18px 10px;min-height:1.4em;}
.modal-actions{position:sticky;bottom:0;display:flex;gap:8px;justify-content:flex-end;padding:12px 18px calc(12px + env(safe-area-inset-bottom,0px));border-top:1px solid var(--border);background:var(--bg2);}
.modal-actions .btn{min-height:46px;font-size:14px;}
#start-btn{min-width:140px;}
```

Rule-by-rule rationale (old -> new):

| old rule | new treatment |
|---|---|
| `input.dev-name-inp` borderless + 2px outline focus | `.name-in` (shared) + `width:min(150px,34vw)` so the header never overflows at 351-400px while `#conn-txt` still reads "connecting"; markup adds `name-in` class |
| `.edit-icon` 12px text | `display:none`. Hearth's `.name-in` has no pencil; on touch the prelude's `hover:none` resting border is the affordance. The header span is deleted from markup; the JS-template span stays (class is referenced) and is hidden by this rule |
| `.zone-card/.zone-radar/.zone-body` | same layout, gap 12; radar kept as a circle (the canvas paints its own `--radar-bg` disc with transparent corners, so no tile behind it) |
| `input.zone-name` 17/700 + outline | display face 18/700 `.name-in`; wrap pulled left 8px so the text aligns with `.zone-meta` |
| `.zone-actions .btn` 9px 14px | 9px 12px, min-height 40 |
| `.watering-bar` 6px progress bar + `.watering-bar > div` + `.watering-fill` (dead, mismatched) | Hearth `.ai-status`: flex, 8px pulsing accent dot, 13/600 MUTED text (only the dot is coloured). Delete the three old rules. |
| `.pulse-dot` + `@keyframes sched-pulse-anim` | `currentColor` dot on the shared `pulse` keyframe; the old keyframe is deleted (no JS references it) |
| `.sched-row` 8px/14px | 7px 0, 13px (the JS inline style still sets flex/space-between/12px) |
| `.sched-dot` 10px glyph | `font-size:0` + 8px disc in `currentColor`; hollow when `data-enabled="0"`; `.sched-pulse` adds a 6px `currentColor` glow because `font-size:0` discards the JS-set `textShadow` |
| `.dev-row/.dev-label/.dev-val` | `.holrow` rhythm, 13px label AND 13px mono tabular value (glance text stays >= 13px) |
| `#modal-bg` hardcoded rgba scrim | `var(--scrim)` |
| `#modal` 22px radii, padding 14px 20px 28px | 18px top radii, zero padding (children carry 18px), `--shadow-float`. No grab handle: Hearth's `.sheet` has none; the head carries a close button instead |
| `.modal-title` 20/800 | display face 20/700 inside `.sheet-head` (title + sub on the left, `.btn.icon` X on the right, bottom rule) |
| `.modal-sub` | 12.5px muted, under the title inside `.sheet-head` |
| `.mode-btn.sel` accent-dim fill + accent text + inset ring | Hearth selection: accent border + 2px `--green-glow` halo, text stays `--text` |
| `#chase-row` | same box; inner markup becomes `.field > .kv + range` |
| `.modal-actions .btn` 13px pad | Hearth `.sheet-foot`: `position:sticky;bottom:0` inside the scrolling sheet (on a 667px phone the 9-tile grid + chase row overflow, and the Start button must never scroll out of reach), right-aligned, Cancel at natural width, Start last at `min-width:140px`, 46px tall, safe-area bottom padding |
| (new) `.zone-actions .btn:last-child{margin-left:auto}` | the trash button sits at the far right whether or not the row wraps; at 390px it used to wrap directly under Water Zone |

### 1c. Markup changes

1. Sprite: insert the `landing.html` block from `sprite.html` right after `<body>` (new line 216).

2. Header (old 216-226):
```html
<header>
  <a class="logo" href="/"><svg class="duck" ...unchanged...>...</svg>Irrigoto</a>
  <div class="hdr-name">
    <input class="dev-name-inp name-in" id="dev-name-inp" type="text" value="irrigoto"
      title="Tap to rename"
      onblur="saveDeviceName(this.value)"
      onkeydown="if(event.key==='Enter')this.blur()">
  </div>
  <div id="conn"><div id="conn-dot"></div><span id="conn-txt">connecting</span></div>
</header>
```
(The inline-styled wrapper `div` becomes `div.hdr-name`; the input gains `name-in`; the `<span class="edit-icon">`
pencil line is DELETED from the header - Hearth's `.name-in` carries no pencil. The pencil symbol stays in the sprite
only for the JS-template span, which `.edit-icon{display:none}` hides; if you need the bytes, drop `i-pencil` too.)

3. Winter banner (old 232-238). Root keeps id/class/inline `style="display:none"`; everything inside is wrapped:
```html
<div id="winter-banner" class="banner banner-info" style="display:none">
  <div class="banner-row">
    <span class="banner-i"><svg class="i"><use href="#i-snowflake"/></svg></span>
    <div class="banner-body">
      Winter sleep active &mdash; sleeping again in
      <span id="winter-left">&mdash;</span>
      <div>
        <button class="btn btn-primary"
                onclick="exitWinter()">Resume normal operation</button>
      </div>
    </div>
  </div>
</div>
```
(The inner `div` loses `style="margin-top:8px"`; `.banner .btn{margin-top:10px}` spaces it. The Resume button is
the page's primary while winterised, so it takes `btn-primary`. It is still a `<button>` inside `#winter-banner`,
which the lock rules require.)

4. Cal-incomplete banner (old 239-242):
```html
<div id="cal-incomplete" class="banner banner-warn" style="display:none">
  <div class="banner-row">
    <span class="banner-i"><svg class="i"><use href="#i-alert-triangle"/></svg></span>
    <div class="banner-body">Calibration incomplete &mdash; throw values were never entered, so the
    previous cal's throw scale is in use. Re-run the pressure calibration.</div>
  </div>
</div>
```

5. Section action pills and buttons (text unchanged, glyph -> icon, leading space dropped):

| old line | before | after |
|---|---|---|
| 248 | `<button class="sec-btn" onclick="location='/zone?id=new'">+ Add Zone</button>` | `<button class="sec-btn" onclick="location='/zone?id=new'"><svg class="i"><use href="#i-plus"/></svg>Add Zone</button>` |
| 264 | `<a class="btn" href="/cal">&#128200; Pressure cal</a>` | `<a class="btn" href="/cal"><svg class="i"><use href="#i-chart"/></svg>Pressure cal</a>` |
| 265 | `<a class="btn" href="/cal#speed">&#9992; Speed cal</a>` | `<a class="btn" href="/cal#speed"><svg class="i"><use href="#i-gauge"/></svg>Speed cal</a>` |
| 271 | `<a class="sec-btn" href="/fs">&#128193; Filesystem</a>` | `<a class="sec-btn" href="/fs"><svg class="i"><use href="#i-folder"/></svg>Filesystem</a>` |
| 293 | `...onclick="apMode()">&#128246; AP Setup Mode</button>` | `...onclick="apMode()"><svg class="i"><use href="#i-wifi"/></svg>AP Setup Mode</button>` |
| 294 | `...onclick="reconnectNet()">&#128268; Reconnect to network</button>` | `...onclick="reconnectNet()"><svg class="i"><use href="#i-plug"/></svg>Reconnect to network</button>` |
| 297 | `...onclick="enterWinter()">&#10052; Winter sleep</button>` | `...onclick="enterWinter()"><svg class="i"><use href="#i-snowflake"/></svg>Winter sleep</button>` |

Keep `style="display:none"` on `#reconnect-btn` and the two `style="margin-top:10px"` on the device-card `.zone-actions`.

6. Mode picker, Chase (old 334): `&#128054; Chase <span>play mode &middot; 1-10 min</span>` ->
`<svg class="i"><use href="#i-paw"/></svg>Chase <span>play mode &middot; 1-10 min</span>`
(`.mode-btn` stays `display:block`, so the icon sits inline before the title; the `<span>` is already block.)

7. Chase duration field (old 337-346) becomes Hearth's range field (label + mono read-out on one row, slider under):
```html
<div id="chase-row" style="display:none">
  <div class="field">
    <div class="kv"><label for="chase-dur">Chase duration</label><span class="val" id="chase-dur-val">3 min</span></div>
    <input type="range" id="chase-dur" min="1" max="10" step="1" value="3"
           oninput="document.getElementById('chase-dur-val').textContent=this.value+' min'">
  </div>
</div>
```
(`#chase-row` root unchanged; the `oninput` attribute is byte-identical; JS still toggles `style.display` block/none.)

8. Modal actions (old 348-351): leave `&#9654; Start` as text. `openModal()`/`startWater()` overwrite the button
with `textContent='▶ Start'`, so an SVG here would vanish on first open. Do not change the two button lines.

9. Sheet head and foot (Hearth `.sheet` anatomy). Old 305-307 are
```html
  <div id="modal">
    <div class="modal-title" id="modal-zone-name">Water Zone</div>
    <div class="modal-sub">Select depth and start watering</div>
```
   Replace the two inner lines with
```html
    <div class="sheet-head">
      <div>
        <div class="modal-title" id="modal-zone-name">Water Zone</div>
        <div class="modal-sub">Select depth and start watering</div>
      </div>
      <button class="btn icon" onclick="closeModal()" aria-label="Close"><svg class="i"><use href="#i-x"/></svg></button>
    </div>
```
   `#modal-zone-name` keeps its id (JS writes `textContent`); `closeModal()` already exists (the Cancel button calls
   it). Then move the status line ABOVE the foot so the sticky foot never covers it: old 352 `<div id="modal-status"></div>`
   is cut from after `</div>` of `.modal-actions` and pasted immediately before `<div class="modal-actions">`.
   Final order inside `#modal`: `.sheet-head`, `.mode-grid`, `#chase-row`, `#modal-status`, `.modal-actions`.
   Nothing else about `#modal-status` changes (JS sets `textContent` and `style.color` only).

### 1d. JS string edits (the only `<script>` lines you may touch)

| line | edit (apply as a text substitution on the quoted fragment; do not retype the line) |
|---|---|
| 472 | replace the glyph entity `&#9998;` with `<svg class="i"><use href="#i-pencil"/></svg>` (the span is hidden by CSS; this only keeps the markup glyph-free. Skipping this row is allowed if you also drop `i-pencil` from the sprite) |
| 468 | insert the text ` name-in` (space, then the word) immediately after `class="zone-name` so the attribute reads `class="zone-name name-in"`. **Change nothing else on the line**: the `value="${...}"` expression that follows contains the JS OR operator (two vertical bars) inside `${...}`; a backslash or any other stray character there is a syntax error that kills the whole script, and there is no node here to catch it. `querySelector('.zone-name')` still matches |
| 476 | replace `&#127783; Water Zone` with `<svg class="i"><use href="#i-cloud-rain"/></svg>Water Zone` |
| 477 | replace `&#9881; Setup` with `<svg class="i"><use href="#i-settings"/></svg>Setup` |
| 478 | replace the trailing `&#128465;` (just before `</button>`) with `<svg class="i"><use href="#i-trash"/></svg>`. Everything else on the line - the `onclick` with its `${...}` expression and the inline `style="border-color:rgba(248,113,113,.3);color:#e0614f;padding:8px 10px"` - stays byte-identical; with the 18px icon the button renders 40x40 (see section 6 for the remnant note) |
| 615 | `'<span style="color:var(--green)">&#9889; charging</span>'` | `'<span style="color:var(--green)"><svg class="i"><use href="#i-zap"/></svg> charging</span>'` (keep the space: this is inline text, not a flex button) |
| 687 | `btn.innerHTML='&#9632; Stop';` | `btn.innerHTML='<svg class="i"><use href="#i-square"/></svg>Stop';` |
| 693 | `btn.innerHTML='&#127783; Water Zone';` | `btn.innerHTML='<svg class="i"><use href="#i-cloud-rain"/></svg>Water Zone';` |
| 698 | `btn.innerHTML='&#127783; Water Zone';` | `btn.innerHTML='<svg class="i"><use href="#i-cloud-rain"/></svg>Water Zone';` |

Lines 468-481 are inside a backtick template literal; 615/687/693/698 are single-quoted strings. Double-quoted
SVG attributes are valid in both. After editing, re-read each line and confirm the quote that opened the string
is the one that closes it, and run check 10.8: the line-468 hunk must differ from `build/orig/` by exactly the eight
characters ` name-in` and nothing else.

Leave exactly as they are: 500/530/532 (`'▶ Start'` textContent), 748 (`'🐶 Chase · '` feeds textContent),
836/841/846 (`●`/`○` textContent; CSS re-skins them), 911 (`&#9679;` in innerHTML, immediately overwritten by
paintSchedDots, so pointless to change), every hardcoded colour in JS (`#e0614f`, `#7f2020`, `#60a5fa`, `#4ab8ff`,
`#ffd700`, canvas fallbacks).

### 1e. DO NOT TOUCH (landing)

jsHookIds: `dev-name-inp conn-dot conn-txt winter-banner winter-left winter-btn cal-incomplete zone-list
sched-summary d-fw d-wifi d-bat d-chg d-storage d-detail d-winter theme-cb ap-mode-btn reconnect-btn modal-bg
modal-zone-name chase-row chase-dur chase-dur-val start-btn modal-status`, plus dynamic `zcard-{id} wbar-{id}
wlabel-{id} wbtn-{id} zmeta-{id}`.

jsHookClasses: `zone-name mode-btn sel open winter-lock btn-primary btn card zone-radar sched-row sched-dot
sched-pulse ok empty zone-card zone-body watering-bar pulse-dot watering-label zone-name-wrap edit-icon zone-meta
zone-actions`; attributes `data-mode data-zone data-enabled data-winter-lock data-theme`; element selectors
`canvas`, `button,input,select,textarea`, `:focus`.

Also unchanged: viewport meta, head theme-bootstrap `<script>`, the font `<link>`, all labels and text, the
`setTheme`/`drawRadar` canvas code, `#conn-dot` must carry no class in markup (JS assigns `className` wholesale).

### 1f. Budget (estimated spare: ~400 B - run check 10.9 the moment the page is saved)

47,033 - 3,946 (old page CSS) + 4,618 (new page CSS) + 4,149 (prelude growth: 11,344 - 7,195) + 2,132 (sprite)
+ ~700 (markup: sheet head/close button, banners, wrappers) + ~330 (JS strings) ~= 54,800 bytes. Ceiling 55,225.
The first-draft scratch build measured 54,297 with a smaller prelude and no sheet head, so expect to be within
~400 B of the ceiling. Apply trims in this order until 10.9 says OK: (1) drop `i-paw` from the sprite and leave
`Chase` text-only (-330 B); (2) drop `i-pencil` and skip row 472 of 1d (-130 B); (3) remove the rationale comments in
the page CSS (-450 B). Never trim by removing blank lines inside `<script>`.

---------------------------------------------------------------------------------------------------

## 2. zone_setup.html

Current: 1140 lines, 57,150 bytes. Ceiling 65,342. `<style>` 54-236, markup 238-309, `<script>` 311-1138.
The head `<script>` (7-45, theme bootstrap + /api/time + winter-lock IIFE) stays byte-identical.

Layout reminder: body is a fixed-height flex column and `#map-wrap{flex:1}` gets the leftover, so every strip
pixel comes out of the radar. The numbers below trim strips where Hearth allows (header 52, readout tiles,
d-pad 56px cells, footer 46px buttons) and spend them on the 48px stacked toolbar.

### 2a. Prelude

Replace lines 55-173 with `shared.css`. Boundary: line 175 `html,body{height:100%;overflow:hidden;}` is the first
page rule and stays.

### 2b. Page CSS

Replace old lines 175-235 (from `html,body{height:100%;overflow:hidden;}` through the `#toast{...}` rule) with:

```css
html,body{height:100%;overflow:hidden;}
body{display:flex;flex-direction:column;height:100dvh;max-width:520px;margin:0 auto;
-webkit-user-select:none;user-select:none;-webkit-touch-callout:none;}
input,textarea{-webkit-user-select:text;user-select:text;}
header{padding:6px 12px;min-height:52px;}
.header-mid{text-align:center;}
/* stage: dotted canvas ground; the 12/16 padding is baked into resizeCanvas() */
#map-wrap{flex:1;display:flex;align-items:center;justify-content:center;padding:12px 16px;min-height:0;position:relative;
background-image:radial-gradient(var(--dot) 1px,transparent 1.5px);background-size:18px 18px;}
#map{border-radius:50%;display:block;touch-action:none;box-shadow:var(--shadow);}
#heat-legend{display:none;flex-direction:column;align-items:flex-start;gap:4px;position:absolute;right:12px;top:50%;transform:translateY(-50%);}
.hl-bar{width:14px;border-radius:7px;border:1px solid var(--border);
background:linear-gradient(to bottom,rgba(255,90,40,.95) 0%,rgba(255,195,40,.9) 28%,rgba(63,182,198,.95) 52%,rgba(90,157,124,.9) 76%,rgba(60,140,255,.95) 100%);}
.hl-ticks{display:flex;flex-direction:column;justify-content:space-between;font-family:var(--mono);font-size:10px;color:var(--text-mid);line-height:1.3;padding-left:4px;font-variant-numeric:tabular-nums;}
#hl-label{font-size:11px;font-weight:600;color:var(--text-mid);white-space:nowrap;margin-top:2px;padding:2px 7px;border-radius:99px;background:var(--bg2);border:1px solid var(--border);}
#hl-label:empty{display:none;}
/* control pane = panel on ground: #readout opens it with the 1px line, every strip below shares the fill */
#readout,#dpad-section,#secondary,#edit-bar,#name-row,#footer{background:var(--bg2);}
#readout{display:grid;grid-template-columns:repeat(3,1fr);gap:6px;flex-shrink:0;padding:8px 16px 0;border-top:1px solid var(--border);}
.rcel{text-align:center;padding:6px;background:var(--tint);border-radius:12px;}
.rlabel{font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;color:var(--text-mid);margin-bottom:4px;}
.rval{font-family:var(--display);font-size:22px;font-weight:600;letter-spacing:-.03em;line-height:1;color:var(--text);font-variant-numeric:tabular-nums;white-space:nowrap;}
/* d-pad = Hearth keypad tiles: press = darker tint, held = accent (the jogging "on" state), limit = orange tint. No scale. */
#dpad-section{flex-shrink:0;display:flex;align-items:center;justify-content:center;padding:8px 16px 6px;}
#dpad{display:grid;grid-template-columns:repeat(3,56px);grid-template-rows:repeat(3,56px);gap:6px;}
.dp{display:flex;align-items:center;justify-content:center;padding:0;background:var(--tint);border:1px solid transparent;
border-radius:14px;color:var(--text);cursor:pointer;touch-action:manipulation;-webkit-user-select:none;user-select:none;
transition:background .1s,color .1s;}
.dp svg.i{width:22px;height:22px;}
.dp:active{background:var(--tint-2);}
.dp.held{background:var(--green);color:var(--accent-ink);}
.dp-empty{background:transparent;border:0;pointer-events:none;}
#btn-add{background:var(--green);color:var(--accent-ink);}
#btn-add svg.i{width:26px;height:26px;}
#btn-add:active{filter:brightness(.92);}
.dp.at-limit{background:var(--orange-dim);color:var(--orange-ink);}
.dp.at-limit:active,.dp.at-limit.held{background:var(--orange);color:var(--accent-ink);}
@media (max-height:640px){#dpad{grid-template-columns:repeat(3,48px);grid-template-rows:repeat(3,48px);}.rcel{padding:5px 6px;}}
/* secondary row = Hearth .mnav: idle muted; on = accent text on the accent-tinted ground. The JS-inlined active
   state of #btn-path/#btn-heatmap (color + border-color accent) needs the 1px transparent border to stay. */
#secondary,#edit-bar{flex-shrink:0;display:flex;gap:4px;padding:0 12px 8px;}
.sbtn{flex:1;min-width:0;min-height:44px;padding:4px 2px 3px;display:flex;flex-direction:column;align-items:center;justify-content:center;gap:2px;
background:transparent;border:1px solid transparent;border-radius:var(--radius-sm);color:var(--text-mid);font-size:11px;font-weight:600;
cursor:pointer;white-space:nowrap;overflow:hidden;transition:background .15s,color .15s;}
.sbtn svg.i{width:20px;height:20px;}
.sbtn:active{background:var(--bg3);color:var(--text);}
#btn-water.on{background:var(--green-dim);color:var(--green);border-color:transparent;}
/* edit-mode toolbar: ordinary .btn shapes (danger / primary / plain); #edit-bar keeps its inline display:none */
#edit-bar .sbtn{flex-direction:row;gap:7px;min-height:42px;padding:8px 10px;font-size:13px;font-weight:500;color:var(--text);background:var(--bg2);border-color:var(--border);}
#edit-bar .sbtn svg.i{width:18px;height:18px;}
#edit-bar .sbtn:first-child{color:var(--red);}
#btn-edit-save{background:var(--green);color:var(--accent-ink);border-color:transparent;}
#btn-edit-save:disabled{opacity:.45;}
/* trim = Hearth .mini at the 36px floor; doTrim() rewrites textContent, so the glyph stays text */
#btn-trim{display:block;width:100%;margin-top:6px;min-height:36px;padding:6px 8px;font-size:12px;font-weight:500;background:var(--bg);
border:1px solid var(--border);border-radius:7px;color:var(--text-mid);cursor:pointer;white-space:nowrap;transition:background .15s,color .15s;}
#btn-trim:not(.water-off):active{color:var(--text);border-color:var(--text-mid);background:var(--bg3);}
#btn-trim.water-off{opacity:.45;cursor:default;}
#btn-trim.busy{opacity:.6;pointer-events:none;}
/* name row: eyebrow label + recessed field (a required input keeps the field look at rest) */
#name-row{flex-shrink:0;display:flex;align-items:center;gap:10px;padding:2px 16px;}
#name-row label{font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;color:var(--text-mid);white-space:nowrap;}
#zone-name{flex:1;width:auto;min-height:40px;padding:6px 10px;font-size:16px;font-weight:600;}
#zone-name::placeholder{color:var(--text-mid);}
/* footer: .btn + .btn.primary at touch height; Save stays flex:2 */
#footer{flex-shrink:0;display:flex;gap:8px;padding:6px 16px calc(8px + env(safe-area-inset-bottom,0px));}
#btn-cancel{flex:1;min-height:46px;background:var(--bg2);border:1px solid var(--border);border-radius:var(--radius-sm);color:var(--text);font-size:14px;font-weight:500;cursor:pointer;transition:background .15s;}
#btn-cancel:active{background:var(--bg3);}
#btn-save{flex:2;min-height:46px;background:var(--green);border:1px solid transparent;border-radius:var(--radius-sm);color:var(--accent-ink);font-size:14px;font-weight:600;cursor:pointer;transition:filter .15s;}
#btn-save:disabled{opacity:.45;cursor:default;}
#btn-save:not(:disabled):active{filter:brightness(.94);}
/* toast: inverted fg/bg, Hearth toast shadow; clears footer (60) + name row (44) + 20; JS drives opacity */
#toast{position:fixed;bottom:calc(124px + env(safe-area-inset-bottom,0px));left:50%;transform:translateX(-50%);background:var(--text);color:var(--bg);
padding:9px 16px;border-radius:var(--radius-sm);font-size:13px;font-weight:500;opacity:0;transition:opacity .3s;pointer-events:none;white-space:nowrap;box-shadow:var(--shadow);z-index:60;}
```

Judgement calls made here:

* **Panel-on-ground.** Hearth's depth model is a `--panel` pane on a `--bg` ground. `#map-wrap` stays on `--bg` with
  the dot grid (the canvas paints its own `--radar-bg` disc), and everything below it - `#readout #dpad-section
  #secondary #edit-bar #name-row #footer` - shares one `--bg2` fill, opened by a single 1px line on `#readout`. The
  readout tiles are `--tint` cells (Hearth `.fc`) inside that panel, so the per-tile borders are gone. `#readout` is
  NOT moved inside `#dpad-section` in markup: `_setEditUI()` hides `#dpad-section/#secondary/#footer` in edit mode and
  the readout must stay visible; the shared fill makes the strips read as one pane either way.
* **D-pad = Hearth keypad tiles, not `.d-btn` circles.** A 3x3 cluster of 56px borderless tinted squares (radius 14,
  `--tint` fill) is exactly `.kp-pad button`; circles would read as a media stepper. Press feedback is Hearth's keypad
  press: a darker tint (`--tint-2`), NOT an accent fill and NOT a scale - the first draft's `transform:scale(.97)` could
  move the tile edge out from under the pointer and fire the inline `onpointerleave="holdStop()"`, cutting a hold short.
  `.held` (set by JS while jogging) is the real "on" state and takes the accent fill; the centre "add point" tile is
  the one accent-filled tile at rest (`#btn-add:active` only dims it). At-limit = orange tint with `--orange-ink` glyph;
  held while at a limit = solid orange. No `!important` anywhere; `.held`/`.at-limit` win over base and `:active` by
  source order. Under 640px tall the tiles drop to 48px (still >= 44) and the readout tiles lose 1px of padding.
* **Readouts = `.fc` stat tiles + `.d-big`.** Three tinted 12px-radius cells with a 6px gap replace the single
  divided strip; values move from 800-weight mono to Bricolage 600/-.03em/tabular, as Hearth sets every big number.
  Units stay inside the value string (JS writes them with `textContent`).
* **Trim = Hearth `.mini`** (recessed `--bg`, `--border` line, muted text, radius 7) at the 36px floor with 12px text,
  because it is tapped standing in the spray. Accent is reserved for the primary and for selection, so trim no longer
  draws an accent outline at rest; `.water-off` is Hearth's `disabled{opacity:.45}` rather than a third grey. The 6px it
  gains are recovered by the d-pad gap (8 -> 6) and the name-row padding (4 -> 2). It keeps its `⊙` text glyph in
  markup and JS (textContent trap). Optional, outside constraint 4's letter: if you accept a two-string JS edit, change
  line 947 `"⊙ trimming..."` -> `"trimming..."` and 956 `"⊙ trim"` -> `"trim"`, delete `⊙ ` from markup line 259, and add
  `#btn-trim:before{content:"";display:inline-block;width:9px;height:9px;border:1.5px solid currentColor;border-radius:50%;margin-right:5px;vertical-align:-1px;}`
  for a CSS-drawn target ring. Default: leave JS alone.
* **Toolbar = stacked icon-over-label (Hearth `.mnav` / `.rail`).** Six cells at ~55px each cannot hold icon +
  "Predict" on one line, so `.sbtn` is icon above an 11px label (the guide's smallest size; "Predict" at 11/600 fits a
  58px cell), muted by default, transparent background, 44px tall. Idle `#btn-water` is muted like its neighbours (no
  accent at rest); `#btn-water.on` is Hearth's selected-nav treatment - accent text on the 13%-accent ground
  (`--green-dim`) - which sits between the JS-inlined accent-text + accent-border state of `#btn-path/#btn-heatmap`
  so the row reads as one family. Labels remain bare text nodes (btn-heatmap's innerHTML writes text);
  `overflow:hidden` clips instead of ellipsising.
* **Zone name = a real field.** Hearth's `.name-in` is for headings that already look editable; `#zone-name` is a
  required input with nothing else to signal it, and `:hover` never fires outdoors, so it keeps the shared recessed
  field look at rest (`--bg` fill, `--border` line via the prelude's `input[type=text]` rule) and raises its
  placeholder to `--text-mid`. The name row loses its own top rule (the panel fill makes it redundant).
* **Toast** sits at `bottom:124px` + safe area: footer (6+46+8 = 60) + name row (2+40+2 = 44) + 20px breathing room,
  so "point added" / "hold auto-stopped" / trim results never paint over the Zone name field. In edit mode the footer
  is hidden and `#edit-bar` (8+42+8 = 58) + name row = 102px, so 124 still clears it. Shadow is the ordinary
  `--shadow` (Hearth's toast weight); `--shadow-float` is reserved for sheets.
* **Height accounting at 375x667** (the first draft claimed the strips "give the radar height back"; here are the
  numbers): header 52 + readout 8+96 (the Throw cell carries the 36px trim button and the grid stretches all three
  cells to it) + d-pad 8+180+6 + toolbar 44+8 + name row 44 + footer 60 = 506px of chrome, leaving `#map-wrap` 161px
  and `resizeCanvas()` a 145px disc (first draft 130, original 112). At 320x568 the `max-height:640px` step makes it
  ~115px. With the winter banner prepended the radar is ~40px, but the page is locked then anyway.
* The winter banner injected by the head script is left as-is (it reads tokens).

### 2c. Markup changes

1. Sprite block (`zone_setup.html` set) right after `<body>` (old line 238).
2. Back (old 241): `<a class="back" href="/">&#8592;</a>` -> `<a class="back" href="/" aria-label="Back"><svg class="i"><use href="#i-chevron-left"/></svg></a>`
3. Readout (old 259): leave `⊙ trim` text (see 2b), nothing else changes in 257-261.
4. D-pad (old 263-281):

| old | before | after |
|---|---|---|
| 267 | `...onpointerleave="holdStop()">▲</button>` | `...onpointerleave="holdStop()"><svg class="i"><use href="#i-chevron-up"/></svg></button>` |
| 271 | `...onpointerleave="holdStop()">◀</button>` | `...onpointerleave="holdStop()"><svg class="i"><use href="#i-chevron-left"/></svg></button>` |
| 272 | `<button class="dp" id="btn-add" onclick="doAct('add_pt')">+</button>` | `<button class="dp" id="btn-add" onclick="doAct('add_pt')"><svg class="i"><use href="#i-plus"/></svg></button>` |
| 274 | `...onpointerleave="holdStop()">▶</button>` | `...onpointerleave="holdStop()"><svg class="i"><use href="#i-chevron-right"/></svg></button>` |
| 278 | `...onpointerleave="holdStop()">▼</button>` | `...onpointerleave="holdStop()"><svg class="i"><use href="#i-chevron-down"/></svg></button>` |

(The glyph-only buttons would ideally carry `aria-label="Pressure up"` / `"Nozzle counter-clockwise"` / `"Add point"` /
`"Nozzle clockwise"` / `"Pressure down"`; that is ~160 B and this page has the thinnest budget, so add them only if
check 10.9 leaves >= 300 B spare after everything else is in.)

5. Secondary toolbar (old 283-290):
```html
<div id="secondary">
  <button class="sbtn" id="btn-water" onclick="doAct('water_toggle')"><svg class="i"><use href="#i-droplet"/></svg>Water</button>
  <button class="sbtn" onclick="doAct('undo')"><svg class="i"><use href="#i-undo"/></svg>Undo</button>
  <button class="sbtn" onclick="doAct('clear')"><svg class="i"><use href="#i-x"/></svg>Clear</button>
  <button class="sbtn" id="btn-path" onclick="togglePath()"><svg class="i"><use href="#i-target"/></svg>Path</button>
  <button class="sbtn" id="btn-heatmap" onclick="toggleHeatmap()"><svg class="i"><use href="#i-thermometer"/></svg>Depth</button>
  <button class="sbtn" id="btn-edit" onclick="toggleEdit()"><svg class="i"><use href="#i-pencil"/></svg>Edit</button>
</div>
```
6. Edit bar (old 293-297), inline style attribute unchanged:
```html
<div id="edit-bar" style="display:none;gap:6px;padding:8px 16px;align-items:center;justify-content:center">
  <button class="sbtn" onclick="deleteSelPoint()"><svg class="i"><use href="#i-trash"/></svg>Delete pt</button>
  <button class="sbtn" id="btn-edit-save" onclick="saveEdits()"><svg class="i"><use href="#i-check"/></svg>Save edits</button>
  <button class="sbtn" onclick="cancelEdit()"><svg class="i"><use href="#i-x"/></svg>Done</button>
</div>
```
7. Name row, footer, toast (299-309): unchanged.

### 2d. JS string edits

| line | before | after |
|---|---|---|
| 370 | `btn.innerHTML = ['🌡 Depth','🌡 Predict','🌡 Actual'][heatPasses];` | `btn.innerHTML = ['<svg class="i"><use href="#i-thermometer"/></svg>Depth','<svg class="i"><use href="#i-thermometer"/></svg>Predict','<svg class="i"><use href="#i-thermometer"/></svg>Actual'][heatPasses];` |

Single-quoted array elements; double-quoted attributes inside; three elements, three commas unchanged.
Leave 947/956 (`⊙`, textContent), 953/971 (`✓` in toast), and the head script's line 37 alone.

### 2e. DO NOT TOUCH (zone_setup)

jsHookIds: `map map-wrap heat-legend hl-label v-bearing v-throw v-points btn-trim btn-up btn-dn btn-add btn-left
btn-right btn-water btn-path btn-heatmap btn-edit secondary edit-bar btn-edit-save dpad-section footer btn-cancel
btn-save zone-name conn-dot conn-label toast winter-lock`; attributes `data-theme` on `<html>`, `data-edited` on
`#zone-name`.

jsHookClasses: `held at-limit on water-off busy ok err winter-lock dp sbtn`; every control stays a real
`<button>`/`<input>` (the head script disables by tag).

Canvas coupling: `--radar-bg --radar-grid --text-mid --text-dim --green --orange --accent-ink` are read by
`draw()` and `--green`/`--orange` get 2-hex alpha suffixes appended, so they must remain 6-digit hex (they do).
`#map-wrap` padding must stay `12px 16px`. The `.hl-bar` gradient, the coverage ramp, cw/ccw colours and the
gold sprinkler are protected literals. `#edit-bar`'s inline `display:none`, `#dpad-section/#secondary/#footer`
restored with `style.display=''` (so their display must come from the stylesheet, as above), `#toast` opacity.

### 2f. Budget (estimated spare: ~450 B - the thinnest page; run check 10.9 the moment it is saved)

57,150 - ~5,700 (old page CSS) + 7,057 (new page CSS) + 4,149 (prelude growth) + 1,314 (sprite) + ~740 (markup,
without aria-labels) + ~170 (JS) ~= 64,880. Ceiling 65,342. The first-draft scratch build measured 64,847 with a
smaller prelude, a smaller page block and 161 B of aria-labels, so expect to land within ~450 B of the ceiling.
Trims in order: (1) remove the nine comment lines in the page CSS block (-~900 B; they are documentation, not style);
(2) drop the `@media (max-height:640px)` rule (-120 B, costs the short-viewport radar gain). Never trim inside `<script>`.

---------------------------------------------------------------------------------------------------

## 3. cal.html

Current: 664 lines, 33,015 bytes. Ceiling 41,207. Markup 204-307, `<script>` 309-662 (stays byte-identical:
no glyphs live in it). Head `<script>` 7-45 untouchable.

### 3a. Prelude

Replace lines 55-173 with `shared.css`. Boundary: line 175 `body{max-width:560px;margin:0 auto;padding-bottom:24px;}`.

### 3b. Page CSS

Replace old lines 175-201 (through `.spd-val{font-family:var(--mono);}`) with:

```css
body{max-width:560px;margin:0 auto;padding-bottom:24px;}
.callout{align-items:flex-start;}
.callout svg.i{color:var(--green);margin-top:1px;}
.callout b{font-family:inherit;}  /* .score b is mono for numbers; "Pressure -> Throw" is prose */
.btn-row{display:flex;gap:8px;flex-wrap:wrap;margin-top:12px;}
/* progress (Hearth .posbar): tint track, accent fill, width-driven by JS */
.prog-wrap{background:var(--tint-2);border-radius:6px;height:6px;margin:12px 0;overflow:hidden;}
.prog-fill{height:100%;background:var(--green);transition:width .4s;}
.status-msg{font-size:12.5px;color:var(--text-mid);min-height:1.4em;margin:6px 0;font-variant-numeric:tabular-nums;}
/* results table: eyebrow heads, mono tabular cells, # column muted */
table{width:100%;border-collapse:collapse;font-size:12.5px;margin-top:12px;}
th{color:var(--text-mid);font-weight:600;text-align:left;padding:6px 8px;border-bottom:1px solid var(--border);font-size:11px;letter-spacing:.08em;text-transform:uppercase;}
td{padding:8px;border-bottom:1px solid var(--border);font-family:var(--mono);font-size:12px;color:var(--text);font-variant-numeric:tabular-nums;}
td:first-child{color:var(--text-mid);}
tr:last-child td{border-bottom:none;}
.bar-wrap{background:var(--tint-2);border-radius:6px;height:6px;width:80px;overflow:hidden;}
.bar-fill{height:100%;background:var(--green);transition:width .4s;}
/* throw steps: recessed sub-panel with a 22px tinted step badge (Hearth .rep-i) */
.throw-input-block{display:none;margin-top:14px;padding:14px;background:var(--bg);border:1px solid var(--border);border-radius:12px;}
.throw-input-block.show{display:block;}
.throw-label{display:flex;gap:10px;align-items:flex-start;font-size:13px;color:var(--text);margin-bottom:10px;line-height:1.5;}
.step-i{width:22px;height:22px;border-radius:50%;display:grid;place-items:center;flex:none;background:var(--orange-dim);color:var(--orange-ink);}
.step-i svg.i{width:14px;height:14px;}
.throw-row{display:flex;gap:8px;align-items:center;flex-wrap:wrap;}
.throw-inp{flex:1;min-width:140px;background:var(--bg2);font-size:15px;font-family:var(--mono);}
/* encoder tiles: eyebrow + display-face numeral + floated verdict pill (JS assigns className enc-ok / enc-warn / '') */
.enc-grid{display:grid;grid-template-columns:1fr 1fr;gap:8px;}
.enc-box{background:var(--bg2);border-radius:12px;padding:12px;border:1px solid var(--border);}
.enc-name{font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;color:var(--text-mid);margin-bottom:6px;}
.enc-val{font-family:var(--display);font-size:26px;font-weight:600;letter-spacing:-.03em;line-height:1;color:var(--text);font-variant-numeric:tabular-nums;}
.enc-sub{font-size:12px;color:var(--text-mid);margin-top:8px;line-height:20px;font-variant-numeric:tabular-nums;}
.enc-ok,.enc-warn{float:right;font-size:11px;font-weight:700;line-height:16px;padding:2px 7px;border-radius:99px;}
.enc-ok{background:var(--ok-dim);color:var(--ok-ink);}
.enc-warn{background:var(--orange-dim);color:var(--orange-ink);}
```

Dropped as dead: `.spd-row .spd-label .spd-val`. Judgement calls:

* **One accent per view.** The three "Run ..." buttons and the Refresh button are plain `.btn` with a leading icon
  (Hearth fills exactly one `.primary` per view; section-level verbs are outlined). The two throw-step Save buttons
  keep `.btn-green`: only one step block is visible at a time and Save is that step's single primary. `btn-green` is
  not a JS hook on this page (the script only toggles `.show` on the throw blocks), so the class change is markup-only.
* **Step cards = `.group`-style recessed sub-panel + tinted step badge**, not the old orange-filled box. Hearth's
  "status is a tint, never a fill": the block is `--bg` inside the `--bg2` card with a 1px line, and the only
  orange is the 22px `.rep-i` circle (`--orange-dim` ground, `--orange-ink` glyph) holding droplet (step 1) / sparkle
  (step 2). The input inside is raised back to `--bg2` (as the old `.throw-inp` already did) so it reads as the control.
* **Encoder status = `.grade` pill.** `enc-ok`/`enc-warn` class names stay (JS writes them); they now render as the
  11px/700 tinted verdict pill in the `*-ink` colours, floated right, with the big degree value in Bricolage 26px.
  `.enc-sub` stays a block (not flex): its markup is `AGC: <span> &nbsp; <span>` and a flex container would turn the
  `&nbsp;` text node into an anonymous item the layout then depends on; a float keeps the markup non-load-bearing
  (`#enc-v-st` with an empty className simply floats nothing).
* **The intro callout** is a `.score` strip, but `.score b` is Hearth's mono rule for numeric values and
  "Pressure -> Throw" is prose, so the page adds `.callout b{font-family:inherit}`.
* **Progress = `.posbar`** on the existing `.prog-wrap/.prog-fill` and `.bar-wrap/.bar-fill` names (JS-templated).
* The intro paragraph becomes a `.score` strip with an accent info icon (see 3c).

### 3c. Markup changes

1. Sprite block (`cal.html` set) right after `<body>` (old line 204).
2. Back (old 206): `<a class="back" href="/" title="Back">&larr;</a>` -> `<a class="back" href="/" title="Back"><svg class="i"><use href="#i-chevron-left"/></svg></a>`
3. Intro callout (old 212):
`<div class="note card" style="margin:0 0 16px">Run <b>Pressure &rarr; Throw</b> first &mdash; ...dry).</div>` ->
`<div class="score callout"><svg class="i"><use href="#i-info"/></svg><span>Run <b>Pressure &rarr; Throw</b> first &mdash; complete it before speed cal, jog cal, or zone creation. The other calibrations use its pressure map to open the valve; until it completes they run with the valve closed (dry).</span></div>`
(Text identical, wrapped in a span; inline margin removed, `main`'s 16px gap spaces it.)
4. Buttons:

| old | before | after |
|---|---|---|
| 220 | `<button class="btn btn-green" id="pres-start-btn" onclick="presStart()">&#9654; Run scan</button>` | `<button class="btn" id="pres-start-btn" onclick="presStart()"><svg class="i"><use href="#i-play"/></svg>Run scan</button>` (class loses `btn-green`: one accent per view) |
| 221 | `...onclick="presCancel()">&#9632; Cancel</button>` | `...onclick="presCancel()"><svg class="i"><use href="#i-square"/></svg>Cancel</button>` (keep `style="display:none"`) |
| 222 | `...onclick="presClear()">&#10005; Clear cal</button>` | `...onclick="presClear()"><svg class="i"><use href="#i-x"/></svg>Clear cal</button>` |
| 262 | `<button class="btn btn-green" id="noz-start-btn" onclick="nozStart()">&#9654; Run speed cal</button>` | `<button class="btn" id="noz-start-btn" onclick="nozStart()"><svg class="i"><use href="#i-play"/></svg>Run speed cal</button>` |
| 278 | `<button class="btn btn-green" id="jog-start-btn" onclick="jogStart()">&#9654; Run jog cal</button>` | `<button class="btn" id="jog-start-btn" onclick="jogStart()"><svg class="i"><use href="#i-play"/></svg>Run jog cal</button>` |
| 279 | `...onclick="jogCancel()">&#9632; Cancel</button>` | `...onclick="jogCancel()"><svg class="i"><use href="#i-square"/></svg>Cancel</button>` (keep `style="display:none"`) |
| 292 | `<button class="btn" style="font-size:12px;padding:4px 10px" onclick="loadEncoder()">&#8635; Refresh</button>` | `<button class="btn sm" onclick="loadEncoder()"><svg class="i"><use href="#i-refresh"/></svg>Refresh</button>` |
| 233, 242 | `class="btn btn-green"` on `#throw-low-save-btn` / `#throw-save-btn` | unchanged (each is the single primary of its step block) |

5. Throw step labels (old 230 and 239):
`<div class="throw-label">&#128167; Step 1 of 2: ...</div>` ->
`<div class="throw-label"><span class="step-i"><svg class="i"><use href="#i-droplet"/></svg></span><span>Step 1 of 2: Valve is open a little (short throw). Go measure the distance to the outer edge of this short spray ellipse, then enter it below.</span></div>`
`<div class="throw-label">&#127775; Step 2 of 2: ...</div>` ->
`<div class="throw-label"><span class="step-i"><svg class="i"><use href="#i-sparkle"/></svg></span><span>Step 2 of 2: Valve is now open at full pressure. Go measure the distance to the outer edge of the spray ellipse, then enter it below.</span></div>`
6. Keep every `style="display:none"` (`#pres-cancel-btn #pres-prog-wrap #pres-table-wrap #noz-prog-wrap #noz-table-wrap
#jog-cancel-btn #jog-prog-wrap`), every `style="width:0%"`, and the `style="margin-top:6px"` on the two throw
`.status-msg` lines (harmless; or delete them, `.status-msg{margin:6px 0}` covers it).

### 3d. JS string edits

None. `<script>` 309-662 stays byte-identical. The head script's `&#10052;` (line 37) stays.

### 3e. DO NOT TOUCH (cal)

jsHookIds: `pres-start-btn pres-cancel-btn pres-clear-btn pres-prog-wrap pres-prog pres-msg pres-table-wrap
pres-tbody throw-low-block throw-low-inp throw-low-save-btn throw-low-msg throw-block throw-inp throw-save-btn
throw-msg noz-start-btn noz-prog-wrap noz-prog noz-msg jog-start-btn jog-cancel-btn jog-prog-wrap jog-prog jog-msg
enc-v-deg enc-v-agc enc-v-st enc-n-deg enc-n-agc enc-n-st speed winter-lock`.
jsHookClasses: `show enc-ok enc-warn winter-lock bar-wrap bar-fill`.
`#enc-v-st/#enc-n-st` get `className=` assigned wholesale: give them no other class. `#pres-tbody` must stay the only
thing inside `#pres-table-wrap` besides the table; thead keeps 5 `<th>`.

### 3f. Budget (estimated spare: ~1,800 B)

33,015 - ~2,500 + 3,023 + 4,149 + 914 + ~570 ~= 39,400 (first-draft scratch build: 39,188). Ceiling 41,207. Run 10.9.

---------------------------------------------------------------------------------------------------

## 4. schedule.html

Current: 35,469 bytes. Ceiling 43,661. Markup 217-267, `<script>` after. Head `<script>` 7-47 untouchable.

### 4a. Prelude

Replace lines 58-176 with `shared.css`. Boundary: line 178 `body{max-width:560px;margin:0 auto;padding-bottom:24px;}`.

### 4b. Page CSS

Replace old lines 178-215 (through `#delay-custom{flex:1;}`) with:

```css
body{max-width:560px;margin:0 auto;padding-bottom:24px;}
main{gap:12px;}
main > .sec-hdr{margin-top:4px;}
/* status readout: Hearth .holrow list inside a panel; 13px values (glance text), status inks for light theme */
.status-card{padding:2px 14px;}
.status-row{display:flex;justify-content:space-between;align-items:center;gap:12px;padding:9px 0;border-bottom:1px solid var(--border);font-size:13px;}
.status-row:last-child{border-bottom:0;}
.status-row .lbl{display:flex;align-items:center;gap:7px;color:var(--text-mid);font-weight:500;}
.status-row .lbl svg.i{width:16px;height:16px;}
.status-row .val{color:var(--text);font-family:var(--mono);font-size:13px;text-align:right;font-variant-numeric:tabular-nums;}
.status-row .val.warn{color:var(--orange-ink);}
.status-row .val.err{color:var(--red-ink);}
/* section counters as Hearth .pg pills (panel fill, 1px line) so the JS-written orange on #delay-state reads in sun */
#delay-state,#ent-count{letter-spacing:0;text-transform:none;font-size:11px;padding:3px 9px;border-radius:99px;background:var(--bg);border:1px solid var(--border);}
/* rain delay: .presets grid + a .field row */
.presets{display:grid;grid-template-columns:repeat(4,1fr);gap:6px;}
.presets .btn{padding:8px 4px;background:var(--bg);}
.delay-row{display:flex;gap:8px;margin-top:10px;align-items:center;}
.delay-row .btn{flex:none;}
#delay-custom{flex:1;}
#delay-status{margin-top:8px;min-height:1.4em;}
/* entries (DOM-order contract: only entry cards are direct children of #entries) */
#entries{display:flex;flex-direction:column;gap:8px;}
.entry{position:relative;}
.entry.disabled{opacity:.5;}
.entry-hdr{display:flex;align-items:center;gap:8px;margin-bottom:12px;}
.entry-num{flex:1;font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;color:var(--text-mid);}
.next-preview{padding:3px 8px;border-radius:99px;background:var(--bg3);white-space:nowrap;}
.entry-del{display:inline-flex;align-items:center;min-height:36px;padding:6px 12px;background:var(--bg2);border:1px solid var(--border);
border-radius:var(--radius-sm);color:var(--red);font-size:13px;font-weight:500;cursor:pointer;}
.entry-del:active{background:var(--btn-hover);border-color:var(--text-mid);}
.row{display:flex;gap:10px;margin-bottom:12px;flex-wrap:wrap;}
.row > .col{flex:1;min-width:0;}
/* form labels = Hearth .field label (12.5/500, sentence case); !important beats the JS-inlined Days label style; the Enabled label.theme-switch is excluded */
.col label,.entry label:not(.theme-switch){display:block;font-size:12.5px!important;font-weight:500;letter-spacing:0!important;text-transform:none!important;color:var(--text)!important;margin-bottom:6px;}
/* day picker: Hearth .seg track; selected = accent fill (outdoor legibility) */
.days{display:flex;gap:2px;background:var(--bg);border:1px solid var(--border);border-radius:var(--radius-sm);padding:3px;}
.day{flex:1;min-height:40px;padding:0;text-align:center;font-size:12.5px;font-weight:600;border:0;border-radius:7px;background:transparent;color:var(--text-mid);cursor:pointer;}
.day.sel{background:var(--green);color:var(--accent-ink);}
.day-presets{display:flex;gap:6px;margin-top:8px;flex-wrap:wrap;}
.day-preset{min-height:36px;padding:6px 11px;font-size:12.5px;color:var(--text-mid);background:var(--bg);border:1px solid var(--border);border-radius:99px;cursor:pointer;}
.day-preset:active{color:var(--text);border-color:var(--text-mid);}
.toggle-row{display:flex;justify-content:space-between;align-items:center;gap:12px;padding-top:12px;border-top:1px solid var(--border);}
.toggle-row .toggle-lbl{font-size:13px;font-weight:600;color:var(--text);}
/* add entry = Hearth .btn.block with the plus icon (dashed means "empty / drop here", never an action) */
.add-btn{display:flex;align-items:center;justify-content:center;gap:7px;width:100%;min-height:46px;padding:12px;background:var(--btn);
border:1px solid var(--border);border-radius:var(--radius-sm);color:var(--text);font-size:14px;font-weight:500;cursor:pointer;}
.add-btn:active{background:var(--btn-hover);border-color:var(--text-mid);}
.add-btn:disabled{opacity:.45;cursor:default;}
/* save bar = Hearth .sheet-foot idiom: Clear all pushed left, Save (the one primary) right at natural width */
.save-bar{display:flex;gap:8px;justify-content:flex-end;}
.save-bar .btn{min-height:46px;font-size:14px;}
.save-bar .btn:first-child{margin-right:auto;}
#save-btn{min-width:140px;}
#save-status{font-size:12.5px;color:var(--text-mid);text-align:center;min-height:1.4em;}
#save-status.ok{color:var(--ok-ink);}
#save-status.err{color:var(--red-ink);}
```

Judgement calls:

* **Form labels are Hearth `.field label`** (12.5px/500, sentence case, `--text`), not eyebrows: eyebrows are section
  headings only, and the first draft's uppercase labels were the Muscovy label re-tokened. The four `!important`s exist
  only to beat the inline `font-size:10px;letter-spacing:.12em;text-transform:uppercase;color:var(--text-mid)` the JS
  template writes on the Days label (line 512), so all five labels in a card share one spec. Keep them: the inline style
  is the wrong look, not just the wrong size.
* **Day picker = `.seg` track with accent-filled selections.** Hearth's seg thumb (panel + 1px shadow) is too quiet
  for a 7-way multi-select read in sunlight; the track/padding/7px-inside-10px geometry is Hearth's, the selected
  state borrows `.d-pbtn.on` (accent fill, `--accent-ink` text). Presets become `.ideas` chips (36px).
* **Add entry = Hearth `.btn.block`** with the plus icon. Dashed borders mean "nothing here yet / drop target" in
  Hearth and nothing else, so the old dashed button misread as an empty state; press = the ordinary `.btn:active`.
* `.entry-del` is Hearth `.btn.danger` (red text on the normal outline, 36px) in every state - press is the normal
  `--btn-hover` ground, never a red fill. No trash icon: adding one would be a JS template *addition*, not a glyph
  replacement (optional: line 488 `'...>Delete</button>'` -> `'...><svg class="i"><use href="#i-trash"/></svg>Delete</button>'`
  plus `i-trash` in the sprite).
* `#delay-state` / `#ent-count` become Hearth `.pg`-style pills (panel fill, 1px line) rather than `--bg3` tint: the
  JS-written orange `style.color` on `#delay-state` cannot change, and orange on white measures ~3.2:1 on `--bg3`,
  so it gets the stronger `--bg` + border ground instead.
* `.status-row .val` stays 13px (Hearth `.holrow` size; "Next run Sat 06:30" is glance text) and its `.warn/.err`
  states use `--orange-ink/--red-ink`; `#save-status.ok/.err` likewise use the ink tokens.
* **Save bar = Hearth `.sheet-foot` idiom**: Clear all pushed left with `margin-right:auto`, Save at the right as the
  page's one primary, natural width with a 140px floor (nothing stretches `flex:1` except `.block`). The guide's
  fixed `.mnav`-style bar was considered and rejected: it would cost body padding and a second sticky layer on a
  page that already scrolls past 32 entries.
* Native `confirm()` for Clear all stays.

### 4c. Markup changes

1. Sprite block (`schedule.html` set) right after `<body>` (old line 217).
2. Back (old 219): `&larr;` -> `<svg class="i"><use href="#i-chevron-left"/></svg>` (same pattern as cal).
3. Status card labels (old 225-227) gain a leading icon inside `.lbl` only (never inside `.val`):
```html
<div class="status-row"><span class="lbl"><svg class="i"><use href="#i-clock"/></svg>Device time</span><span class="val" id="st-time">&mdash;</span></div>
<div class="status-row"><span class="lbl"><svg class="i"><use href="#i-calendar"/></svg>Next run</span><span class="val" id="st-next">&mdash;</span></div>
<div class="status-row"><span class="lbl"><svg class="i"><use href="#i-refresh"/></svg>Last update</span><span class="val" id="st-last">&mdash;</span></div>
```
4. Rain delay card (old 234-248):
```html
<div class="card">
  <div class="presets">
    <button class="btn" onclick="setDelay(6)">6 h</button>
    <button class="btn" onclick="setDelay(12)">12 h</button>
    <button class="btn" onclick="setDelay(24)">24 h</button>
    <button class="btn" onclick="setDelay(48)">48 h</button>
  </div>
  <div class="delay-row">
    <input type="number" id="delay-custom" min="1" max="336" placeholder="hours">
    <button class="btn" onclick="setDelayCustom()">Set</button>
    <button class="btn btn-danger" id="delay-cancel-btn" onclick="setDelay(0)"
            style="display:none">Cancel</button>
  </div>
  <div id="delay-status" class="hint"></div>
</div>
```
(Inline grid/flex/`flex:0 0 auto`/margin styles move to the classes above. **`style="display:none"` on
`#delay-cancel-btn` must stay inline**: JS reveals it with `style.display=''`.)
5. Add entry (old 256): `<button class="add-btn" id="add-btn" onclick="addEntry()">+ Add entry</button>` ->
`<button class="add-btn" id="add-btn" onclick="addEntry()"><svg class="i"><use href="#i-plus"/></svg>Add entry</button>`
6. Footer hint (old 264): drop `style="margin-top:18px;"` (main gap spaces it). Text unchanged.
7. `#save-btn` gets no icon (JS swaps its textContent). `.save-bar` buttons unchanged otherwise.

### 4d. JS string edits

None by default. The only candidate is line 486 (`'&rarr; ' + nf.label` in the `.next-preview` chip), and line 597
rewrites the same chip with `textContent = '→ ' + ...` on every interaction, so an SVG there would be wiped after the
first tap. Leave the arrow as text in both places. (Optional trash icon on line 488, see 4b.)

### 4e. DO NOT TOUCH (schedule)

jsHookIds: `entries ent-count add-btn delay-state delay-cancel-btn delay-status st-time st-next st-last save-btn
save-status delay-custom winter-lock`.
jsHookClasses: `winter-lock warn err ok card entry disabled empty entry-hdr entry-num next-preview entry-del row col
days day sel day-presets day-preset toggle-row toggle-lbl theme-switch theme-slider`; attributes `data-k` (zone time
mode depth days enabled), `data-bit`, `data-preset`; globals `setDelay setDelayCustom addEntry clearAll saveAll
delEntry`. `#save-status` gets `className=` wholesale: no extra classes on it. `#entries` direct children must be
only entry cards, in order (`children[idx]`, `lastChild`).

### 4f. Budget (estimated spare: ~1,500 B)

35,469 - ~3,300 + 4,527 + 4,149 + 586 + ~450 ~= 42,100 (first-draft scratch build: 41,505). Ceiling 43,661. Run 10.9.

---------------------------------------------------------------------------------------------------

## 5. fs.html

Current: 339 lines, 17,830 bytes. Ceiling 26,022. Markup 200-235, `<script>` 236-337. Head `<script>` untouchable.

### 5a. Prelude

Replace lines 55-173 with `shared.css`. Boundary: line 175 `body{max-width:640px;margin:0 auto;padding-bottom:24px;}`.

### 5b. Page CSS

Replace old lines 175-197 (through `.act-btn.del:hover,.act-btn.del:active{...}`) with:

```css
body{max-width:640px;margin:0 auto;padding-bottom:24px;}
.hdr-title{flex:1 0 auto;}  /* the usage read-out ellipsises before the page title does */
/* upload panel: eyebrow title, stacked field rows */
.upload-title{font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;color:var(--text-mid);margin-bottom:12px;}
.upload-row{display:flex;gap:8px;align-items:center;}
.upload-row + .upload-row{margin-top:8px;}
.path-lbl{font-size:12.5px;font-weight:500;color:var(--text-mid);width:40px;flex:none;}
/* file input stays display:block (UA shadow layout; flex on the host is not portable to iOS Safari) */
.file-inp{flex:1;display:block;line-height:30px;color:var(--text-mid);font-size:13px;padding:4px 6px;cursor:pointer;}
.file-inp::file-selector-button{font:inherit;background:var(--bg2);border:1px solid var(--border);border-radius:7px;color:var(--text);
font-size:12.5px;font-weight:500;padding:6px 10px;cursor:pointer;margin-right:10px;}
.path-inp{flex:1;font-size:13px;font-family:var(--mono);}
.upload-status{font-size:12.5px;color:var(--text-mid);margin-top:10px;min-height:1.4em;}
/* file list: Hearth .pg-item rows; 30px/9 icon tile, mono name, mono-tabular size, 36x44 actions 8px apart */
.tree{font-size:13px;}
.dir-row{display:flex;align-items:center;gap:8px;padding:5px 6px;border-radius:var(--radius-sm);min-height:44px;}
.dir-row + .dir-row{margin-top:2px;}
.dir-row:hover{background:var(--bg);}
.indent{display:inline-block;flex-shrink:0;}
.dir-icon,.file-icon{display:inline-flex;align-items:center;justify-content:center;flex:none;width:30px;height:30px;border-radius:9px;background:var(--bg);}
.dir-icon{color:var(--green);}
.file-icon{color:var(--text-mid);}
.dir-icon svg.i,.file-icon svg.i{width:16px;height:16px;}
.dir-name{color:var(--text);font-weight:600;font-family:var(--mono);font-size:12.5px;}
.file-name{color:var(--text);flex:1;overflow:hidden;text-overflow:ellipsis;white-space:nowrap;font-family:var(--mono);font-size:12.5px;}
.file-size{color:var(--text-mid);font-family:var(--mono);font-size:11px;flex-shrink:0;font-variant-numeric:tabular-nums;}
.file-actions{display:flex;gap:8px;flex-shrink:0;}
.act-btn{display:inline-flex;align-items:center;justify-content:center;gap:5px;min-height:36px;min-width:44px;padding:6px 9px;border-radius:var(--radius-sm);border:1px solid var(--border);background:var(--bg2);
color:var(--text-mid);font-size:12px;font-weight:500;cursor:pointer;text-decoration:none;font-family:var(--font);}
.act-btn svg.i{width:15px;height:15px;}
.act-btn:active{color:var(--text);border-color:var(--text-mid);}
.act-btn.del{color:var(--red);}
```

Judgement calls:

* **File rows = Hearth `.pg-item` / `.lib-item` hybrid.** Each row is a radius-10 strip (hover `--bg`), with a 30px
  radius-9 recessed icon tile (Hearth `.lib-item .ic`; folder in accent, file in muted - Hearth has no orange for
  folders; orange is a status colour), the name in mono 600 (ids and paths are machine values), size in mono tabular,
  and the two actions as radius-10 outlined buttons 36px tall and at least 44px wide, 8px apart, so a wet-thumb miss on
  `dl` does not land on `del` (`del` is `.danger`: red text, normal ground on press - no red fill). The per-row 1px
  rules are gone in favour of 2px gaps. Labels `dl`/`del` stay verbatim.
* **The file input stays `display:block`.** A file input's layout is UA shadow DOM; `display:flex` on the host happens
  to work in Chromium but is not guaranteed on iOS Safari (the actual outdoor device), so the row relies on
  `::file-selector-button` plus `line-height:30px` only. Empty states written into `#tree` are quietened by the
  prelude's `.card .tree > .empty` rule (they sit one level below the card).
* `.indent` keeps no width in CSS (JS writes `style.width`).
* `#refresh-btn` is restyled by the shared `.sec-btn,#refresh-btn` rule (neutral 36px button, no green text, no pill).
* Native `confirm()`/`alert()` stay.

### 5c. Markup changes

1. Sprite block (`fs.html` set) right after `<body>` (old line 200).
2. Back (old 202): `&larr;` -> `<svg class="i"><use href="#i-chevron-left"/></svg>`.
3. Upload card (old 210-221):
```html
<div class="upload-card">
  <div class="upload-title">Upload File</div>
  <div class="upload-row">
    <input class="file-inp" type="file" id="upload-file">
  </div>
  <div class="upload-row">
    <span class="path-lbl">Path:</span>
    <input class="path-inp" id="upload-path" placeholder="/lfs/zones/zone_000.bin" value="/lfs/">
    <button class="btn btn-green" onclick="uploadFile()"><svg class="i"><use href="#i-upload"/></svg>Upload</button>
  </div>
  <div class="upload-status" id="upload-status"></div>
</div>
```
(`style="margin-bottom:8px"` and the inline-styled `Path:` span become classes.)
4. Refresh (old 227): `<button id="refresh-btn" onclick="loadTree()">&#8635; Refresh</button>` ->
`<button id="refresh-btn" onclick="loadTree()"><svg class="i"><use href="#i-refresh"/></svg>Refresh</button>`

### 5d. JS string edits

| line | before | after |
|---|---|---|
| 272 | `'<span class="dir-icon">&#128193;</span>'+` | `'<span class="dir-icon"><svg class="i"><use href="#i-folder"/></svg></span>'+` |
| 279 | `'<span class="file-icon">&#128196;</span>'+` | `'<span class="file-icon"><svg class="i"><use href="#i-file"/></svg></span>'+` |
| 283 | `...download="'+displayName(e.name)+'">&#8595; dl</a>'+` | `...download="'+displayName(e.name)+'"><svg class="i"><use href="#i-download"/></svg>dl</a>'+` |

Do not touch line 284 (`deleteFile(\''+e.path+'\')` escaping) or the head script's line 37.

### 5e. DO NOT TOUCH (fs)

jsHookIds: `tree usage upload-file upload-path upload-status winter-lock refresh-btn` (the last is the selector of
the shared `.sec-btn,#refresh-btn` rule).
jsHookClasses: `winter-lock empty dir-row indent dir-icon dir-name file-icon file-name file-size file-actions act-btn del`;
globals `uploadFile loadTree deleteFile`.

### 5f. Budget (estimated spare: ~2,300 B)

17,830 - ~2,450 + 2,619 + 4,149 + 734 + ~250 + ~220 ~= 23,700 (first-draft scratch build: 23,480). Ceiling 26,022. Run 10.9.

---------------------------------------------------------------------------------------------------

## 6. Cross-page notes

* **Winter-lock banner (JS-built, all pages but landing):** left untouched. It already reads `--green-dim --text
  --border --radius-sm --font`, so it inherits the palette; its `&#10052;` text snowflake stays because the head
  script is off-limits. The shared prelude adds `body.winter-lock button svg.i, body.winter-lock a svg.i{opacity:1}`
  so sprite icons inside already-dimmed buttons are not dimmed twice by the injected `svg{opacity:.45}` rule.
* **Hardcoded colours that remain** (all pre-existing and allowed): JS inline `#e0614f #7f2020 #60a5fa #4ab8ff
  rgba(248,113,113,.3) rgba(74,184,255,.85)` in landing, canvas fallbacks and `#ffd700`, the `.hl-bar` gradient and
  coverage ramp in zone_setup. The CSS-side hardcodes that existed (`#fff` knob, `rgba(13,22,19,.6)` scrim) are now
  tokens (`--knob`, `--scrim`).
* **`.theme-switch` is shared by landing (header theme toggle) and schedule (per-entry Enabled)**; both get the same
  Hearth switch from the prelude.
* **`.sec-hdr` divider logic**: a section header draws a 1px rule above itself with 16px padding, except the first
  `section` of `main` (`section:first-of-type`, so cal's `#pressure` header is suppressed even though the callout div
  precedes it), a `main > .sec-hdr:first-child`, and any `.card > .sec-hdr` (fs). Schedule's headers are direct
  children of `main` after a card, so they get the rule - that is intended.
* **Status text uses the ink tokens.** Anywhere status-coloured TEXT sits on a tint or on the page (cal `.enc-ok/.enc-warn`
  and `.step-i`, schedule `.status-row .val.warn/.err` and `#save-status`, the warn banner icon, the at-limit d-pad glyph)
  takes `--ok-ink/--orange-ink/--red-ink`, never the raw `--ok/--orange/--red`: on white the raw colours measure 2.8-3.6:1
  at 11-12px. Dots, borders, fills and glows keep the raw colours. JS-written colours (`#delay-state`, the landing
  sched dots, `btn.style.color='#e0614f'`) cannot change; where it matters they get a stronger ground instead.
* **Known remnant (needs explicit permission to touch): the landing zone-card trash button.** The JS template
  (line 478) carries `style="border-color:rgba(248,113,113,.3);color:#e0614f;padding:8px 10px"`, a pinkish non-token
  outline that is now the one Muscovy-shaped button left on any page. Constraint 4 allows only the glyph swap on that
  line, so it stays. The one-attribute follow-up, if permission is given, is: replace `class="btn" style="...padding:8px 10px"`
  with `class="btn btn-danger"` on that line and nothing else (`.zone-actions .btn:last-child{margin-left:auto}` already
  positions it). Record it as a follow-up; do not do it as part of this work.
* **The duck** keeps its own fills inside the inverted mark tile (brand exception, see 0.1).
* **Switch hit box**: both switches get the 44px-tall hit area from `.theme-switch:before` (an invisible pseudo-element
  on the `<label>`, so a tap 9px above or below the 26px track still activates `#theme-cb` / the entry's `data-k="enabled"`
  checkbox). No row became part of the label; markup is unchanged.

---------------------------------------------------------------------------------------------------

## 7. Verification checks (run all ten before finishing)

Run from `<repo>/components/irrigoto/html/`.
`$H` = this scratch directory (`.../scratchpad/hearth2`). The pages are inside a git repo (root `.../duck-pond/irrigoto`),
so the `git show HEAD:components/irrigoto/html/...` baselines below work from any cwd in the repo; `$H/build/orig/` holds
the same pre-edit files as a non-git baseline (swap `git show HEAD:components/irrigoto/html/$f` for `cat $H/build/orig/$f`
if HEAD has moved). The local `grep` is ugrep, so the `-P` patterns in 10.4 run as written. Run **10.9 immediately after
saving each page** and apply that page's trim list before moving on; the budgets on landing and zone_setup are a few
hundred bytes.

```bash
# 10.1 prelude is byte-identical in all five pages and equals shared.css
for f in landing zone_setup cal schedule fs; do
  s=$(grep -n '^/\* ---- Shared prelude' $f.html | cut -d: -f1); e=$(grep -n 'prefers-reduced-motion' $f.html | head -1 | cut -d: -f1)
  sed -n "${s},${e}p" $f.html | md5; done | sort -u | wc -l        # expect 1
md5 -q $H/shared.css                                                 # expect the same hash (shared.css ends with a newline; sed -n output does too)

# 10.2 token values unchanged (compare against git HEAD or the pre-edit copies)
for f in *.html; do diff <(git show HEAD:components/irrigoto/html/$f 2>/dev/null | grep -E '^\s+--(bg|green|pond|orange|red|ok|text|border|btn|radius|radar|shadow|font|display|mono)[-a-z0-9]*:' ) \
                        <(grep -E '^\s+--(bg|green|pond|orange|red|ok|text|border|btn|radius|radar|shadow|font|display|mono)[-a-z0-9]*:' $f); done   # expect empty

# 10.3 raw-string delimiter hazard
grep -nE '\)[A-Z]+"' *.html                                          # expect nothing

# 10.4 no emoji / symbol glyphs left in markup or innerHTML strings (textContent sites are allowed; listed below;
#      landing 472 `&#9998;` is also allowed to survive if you took the 1f trim that skips that row)
grep -nP '&#(9998|10052|9888|128193|128200|9992|128246|128268|127783|9881|128465|9889|9632|128054|9679|128167|127775|10005|8635|8593|8595|8592);' *.html
grep -nP '[💧⌫✕◎🌡✎🗑▲◀▶▼]|&larr;' *.html
# expected survivors only: landing 350 `&#9654; Start`, landing 911 `&#9679;` (overwritten by textContent),
# zone_setup 259/947/956 `⊙`, every head-script `&#10052;` (cal 37, schedule 40, fs 37, zone_setup 37),
# landing 500/530/532 `▶`, landing 748 🐶, landing 836/841/846 ●/○, toasts ✓ (zone_setup 953/971, schedule 677), schedule 366/486/597 arrows.

# 10.5 every <use> points at a symbol that exists in that page's sprite
for f in *.html; do for n in $(grep -o 'href="#i-[a-z-]*"' $f | sort -u | sed 's/href="#//;s/"//'); do
  grep -q "id=\"$n\"" $f || echo "$f: missing symbol $n"; done; done        # expect nothing

# 10.6 JS hook ids still exist exactly once in markup (static ones)
for id in dev-name-inp conn-dot conn-txt winter-banner winter-left winter-btn cal-incomplete zone-list sched-summary d-fw d-wifi d-bat d-chg d-storage d-detail d-winter theme-cb ap-mode-btn reconnect-btn modal-bg modal-zone-name chase-row chase-dur chase-dur-val start-btn modal-status; do [ $(grep -c "id=\"$id\"" landing.html) = 1 ] || echo "landing: $id"; done
for id in map map-wrap heat-legend hl-label v-bearing v-throw v-points btn-trim btn-up btn-dn btn-add btn-left btn-right btn-water btn-path btn-heatmap btn-edit secondary edit-bar btn-edit-save dpad-section footer btn-cancel btn-save zone-name conn-dot conn-label toast; do [ $(grep -c "id=\"$id\"" zone_setup.html) = 1 ] || echo "zone_setup: $id"; done
for id in pres-start-btn pres-cancel-btn pres-clear-btn pres-prog-wrap pres-prog pres-msg pres-table-wrap pres-tbody throw-low-block throw-low-inp throw-low-save-btn throw-low-msg throw-block throw-inp throw-save-btn throw-msg noz-start-btn noz-prog-wrap noz-prog noz-msg jog-start-btn jog-cancel-btn jog-prog-wrap jog-prog jog-msg enc-v-deg enc-v-agc enc-v-st enc-n-deg enc-n-agc enc-n-st speed; do [ $(grep -c "id=\"$id\"" cal.html) = 1 ] || echo "cal: $id"; done
for id in entries ent-count add-btn delay-state delay-cancel-btn delay-status st-time st-next st-last save-btn save-status delay-custom; do [ $(grep -c "id=\"$id\"" schedule.html) = 1 ] || echo "schedule: $id"; done
for id in tree usage upload-file upload-path upload-status refresh-btn; do [ $(grep -c "id=\"$id\"" fs.html) = 1 ] || echo "fs: $id"; done

# 10.7 inline display:none hooks that JS relies on are still inline
grep -c 'style="display:none' landing.html      # expect 5 (winter-banner, cal-incomplete, reconnect-btn, chase-row + the wbar in the JS template)
grep -c 'style="display:none' cal.html          # expect 7
grep -c 'style="display:none' schedule.html     # expect 1 (delay-cancel-btn)
grep -c 'style="display:none' zone_setup.html   # expect 1 (edit-bar)

# 10.8 <script> blocks: only the listed lines changed. Diff each page's script region against the pre-edit file
#      and confirm the hunks are exactly: landing 468,472,476-478,615,687,693,698 (472 optional); zone_setup 370; fs 272,279,283; cal/schedule none.
#      The landing line-468 hunk must differ ONLY by the inserted ` name-in` (8 characters); any other difference there is a script-killing typo.
for f in landing zone_setup cal schedule fs; do diff <(git show HEAD:components/irrigoto/html/$f.html | sed -n '/^<script>/,/^<\/script>/p') <(sed -n '/^<script>/,/^<\/script>/p' $f.html) | grep '^[<>]'; done
diff <(grep -o 'class="zone-name[^"]*" type="text" value="[^"]*"' $H/build/orig/landing.html) <(grep -o 'class="zone-name[^"]*" type="text" value="[^"]*"' landing.html)
#      expect exactly one changed pair whose only difference is `zone-name` -> `zone-name name-in`

# 10.9 size budget (run after EVERY page save; also prints the spare bytes so you can decide on the optional extras)
for f in landing:55225 zone_setup:65342 cal:41207 schedule:43661 fs:26022; do n=${f%%:*}; cap=${f##*:}; s=$(wc -c < $n.html); echo "$n $s / $cap spare $((cap-s)) $([ $s -le $cap ] && echo OK || echo OVER)"; done
file *.html | grep -i crlf   # expect nothing: CRLF would add one byte per line and blow every budget

# 10.10 no new colour literals outside the token blocks (allowed survivors: hl-bar gradient, JS inline hexes listed in section 6)
for f in *.html; do awk '/^<style>/{s=1} /^<\/style>/{s=0} s' $f | awk 'NR>48' | grep -nE '#[0-9a-fA-F]{3,6}\b|rgba?\(' | grep -v 'hl-bar\|linear-gradient' ; done   # expect nothing
# and the no-external-resources rule:
grep -nE 'src="http|href="http' *.html | grep -v 'fonts.googleapis\|fonts.gstatic'   # expect nothing
```

If 10.8 shows an unexpected hunk, revert that hunk: constraint 4 allows glyph-string replacement only.
If a browser is available, open each page from a local file (a `python3 -m http.server` in the html directory is
enough; the API calls fail harmlessly) and confirm: landing - toggle the theme, open the water sheet at 375x667 and
check the Cancel/Start foot is visible without scrolling and the X closes it; zone_setup - fire a toast (tap Water
with no connection gives "..." errors that toast) and confirm it clears the Zone name field, enter and leave edit mode,
check the d-pad does not shrink on press; schedule - the Days label matches the other labels; fs - the Loading/Empty
state inside the card has no dashed box; and that there is no console error about a missing element on any page.
