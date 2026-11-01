# Hearth Dashboard Studio: component style guide

Purpose: re-skin another product so it looks like it was built by the same hand as Hearth.
Source of truth: `artifact-5b6253f0-1793079828-b67c.html` (4789 lines). Everything below is copied from
its `<style>` block (lines 29-957) and the markup / JS templates that compose those classes. Values are
EXACT; when Hearth writes `calc(13px * var(--d-fs,1))` the base value is 13px (`--d-fs` is the user's
text-size tweak, default 1, and you should read every `calc(Npx * var(--d-fs,1))` simply as `Npx`).

Hearth has TWO visual layers that both matter:

* **Editor chrome** - the app around the canvas (top bar, panes, inspector, sheets, toasts). Styled with
  `--bg --panel --line --fg --muted --accent --accent-ink --magic`. Flat, bordered, almost shadowless.
* **Dashboard preview** - the cards the user is designing (`.dash`, `.card`, `.d-*`, `.pill`, `.chip`,
  `.sw-toggle`, `.bri`). Styled with `--d-*` variables set inline by the current theme. Softer, bigger,
  tinted with `color-mix(... var(--d-text) 9%, transparent)` surfaces, allowed to have shadow/glow.

A product that is itself a *device UI* (not an editor) should borrow chrome rules for navigation, forms,
sheets and status, and preview-card rules for the "live" tiles that show device state.

---------------------------------------------------------------------------------------------------

## 0. Tokens, and how they map onto the irrigoto token names

Hearth editor tokens (exact):

```css
:root{
  --bg:#f3f4f7; --panel:#ffffff; --line:#e2e4ea; --fg:#15171c; --muted:#666c7a;
  --accent:#4352f0; --accent-ink:#ffffff; --stage:#e9ebf0; --dot:#d3d6de;
  --magic:#7b4dff;
  --f-display:"Bricolage Grotesque", "Geist", system-ui, sans-serif;
  --f-body:"Geist", system-ui, -apple-system, "Segoe UI", sans-serif;
  --f-mono:"Geist Mono", ui-monospace, "SF Mono", Menlo, monospace;
}
/* dark (both the system-pref path and the explicit toggle set the same values) */
:root[data-theme="dark"]{
  --bg:#0e1014; --panel:#15181e; --line:#252932; --fg:#eceef3; --muted:#8c92a1;
  --accent:#8a94ff; --accent-ink:#0e1014; --stage:#0a0c0f; --dot:#1c2028; --magic:#b49bff; color-scheme:dark}
```

Hearth never defines a success/warn/danger token; it hardcodes them and tints with `color-mix`:

| role | light | dark (preview) | how Hearth tints it |
|---|---|---|---|
| ok | `#1f9d63` | `#2fc77a` | `color-mix(in srgb, #1f9d63 18%, transparent)` bg, solid text |
| warn/mid | `#d07a12` bg / `#c87210` text | `#ff9f40` | `color-mix(in srgb, #d07a12 18%, transparent)` |
| danger | `#d23b3b` | `#ff5a5a` | `color-mix(in srgb, #d23b3b 18%, transparent)`; `.btn.danger{color:#d23b3b}` |

Mapping onto the irrigoto names (which must not change). Use the right-hand name in the new CSS:

| Hearth | irrigoto token | note |
|---|---|---|
| `--bg` (page ground) | `--bg` | |
| `--panel` (raised surface: top bar, panes, buttons, cards) | `--bg2` | also `--btn` |
| `--stage` / `--dot` (recessed canvas) | `--radar-bg` / `--bg3` | `--bg3` doubles as hover ground (`--btn-hover`) |
| `--line` | `--border` | |
| `--fg` | `--text` | |
| `--muted` | `--text-mid` | `--text-dim` has no Hearth equivalent; use for placeholder/disabled only |
| `--accent` / `--accent-ink` | `--green` / `--accent-ink` | |
| `color-mix(in srgb, var(--accent) 13%, var(--bg))` | `--green-dim` | selected-rail background, `.pg-item.cur` |
| `color-mix(in srgb, var(--accent) 30%, transparent)` | `--green-glow` | the 2px selection ring on `.th`, `.fxb`, `.flagbtn`, `.pg-menu-btn[aria-expanded]` |
| `--magic` | `--pond` | "AI / do it for me" colour: `.btn.magic`, `.newtag`, `.group h3 svg.i`, `.ai-status .dotpulse` |
| `color-mix(in srgb, var(--magic) 14%, transparent)` | `--pond-dim` | `.newtag` background |
| `#1f9d63` / `#2fc77a` | `--ok` ; 18-22% tint = `--ok-dim` | |
| `#d07a12` `#c87210` / `#ff9f40` | `--orange` ; tint = `--orange-dim` | |
| `#d23b3b` / `#ff5a5a` | `--red` ; tint = `--red-dim` | |
| `--f-body` / `--f-display` / `--f-mono` | `--font` / `--display` / `--mono` | |

Hearth's `box-shadow:0 1px 2px rgba(0,0,0,.08)` (seg thumb) and the sheet/popover shadows are the only
editor shadows; irrigoto's `--shadow` token is fine to keep for its cards but see section 9.

`color-mix()` is used everywhere in Hearth. It is fine on any phone browser from 2023 on; where a
`-dim` token already exists, prefer the token (shorter, and it is already tuned per theme).

---------------------------------------------------------------------------------------------------

## 1. Type

### Faces

* Body: `font-family:var(--f-body)` = Geist. `body{font-size:14px}`. Everything inherits
  (`button,input,select,textarea{font:inherit; color:inherit}`), so controls are 14px unless a class says otherwise.
* Display: `var(--f-display)` = Bricolage Grotesque. Used ONLY for: `.brand` (17px/700), pane `h2`
  (19px/700), `.insp-head h2` (18px/700), `.insp-empty h2` (16px), `.sheet-head h2` (20px, inherits 700 from h2 default),
  `.report h3` (18px), and in the preview `.d-big`, `.hd-greet`, `.hd-time`, `.hub-title`, `.hr-val`,
  `.ts-ring b`, `.v-bat b`, `.saver .t`, keypad digits. Rule: display face = headings and big numbers, never labels, never buttons.
* Mono: `var(--f-mono)` = Geist Mono. Used for: `code` (12px), `pre.code` (12px), `.val` (12px, range read-outs),
  `.score b` (contrast ratios), `.stage-meta` (12px), `.ent-summary span` (12px entity ids), `.mono` inputs
  (`font-family:var(--f-mono)!important; font-size:12.5px!important` - entity-id fields), `.cam .ts` timestamps.
  Rule: mono = machine values (ids, ratios, timestamps, code), not prose.

### Scale (all editor-chrome; base px, weight, tracking, face)

| px | weight | tracking | face | where |
|---|---|---|---|---|
| 10 | 700 | `.06em` uppercase | body | `.newtag`, `.pv` (dashed "Preview only" tag, 600) |
| 10.5 | 600 | - | body | `.wx-live` preview badge |
| 11 | 600 | `.08em` uppercase | body | `.eyebrow` (section label, `color:var(--muted)`) |
| 11 | 600/700 | - | body | `.libn` count pill, `.grade` (700), `.pill` (600), `.vis-badge` (500), `.mnav button`, `.tv-log` |
| 11.5 | 600 | - | body | `.rail button` labels; `.lib-item span` desc (normal, line-height 1.35); `.mini` (500); `.libg summary small`; `.pg-go small` |
| 12 | 400 | - | mono | `code`, `pre.code` (line-height 1.55), `.val`, `.stage-meta` |
| 12 | 400 | - | body | `.insp-head p`, `.switch span small`, `.hr-n span`, `.tb button` (600) |
| 12.5 | 400 | - | body | `.hint` (line-height 1.5), `.pane-title p` (1.45), `.insp-empty p` (1.45), `.wel small` (1.4), `.tips`, `.score`, `.pg-empty` |
| 12.5 | 500 | - | body | `.field label`, `.field .lbl2`, `.crow` (label rows), `.th b` (600), `.ha-chip`, `.ideas button` |
| 13 | 500 | - | body | `.btn`, `.seg button` (400), `.pg` page pills, `.leftout` |
| 13 | 600 | - | body | `.switch span b`, `.lib-item b`, `.ev b`, `.hub-chip`, `.scn button` (500) |
| 13.5 | 600 | - | body | `.libg summary b`, `.twg summary` (details headers) |
| 14 | 600 | - | body | `.group h3` (pane sub-heading, flex with icon) |
| 15 | 600/700 | - | body | `.wel b` (welcome card title), `.ht-l` (700) |
| 16 | 700 | - | display | `.insp-empty h2` |
| 17 | 700 | `-.01em` | display | `.brand` |
| 18 | 700 | - | display | `.insp-head h2` |
| 19 | 700 | `-.01em` | display | `.pane-title h2` |
| 20 | 700 | - | display | `.sheet-head h2` |

Preview-card scale (`--d-*` themed, base px):

| px | weight | tracking | face | class |
|---|---|---|---|---|
| 11 | 600 | - | body | `.pill` |
| 12.5 | 500 | `var(--d-lls,0)` | body | `.d-label` (muted, ellipsised), `.d-pbtn` (600), `.chip` (400), `.room-stats` |
| 14 | `var(--d-hw,600)` | - | body | `.d-name` (ellipsised) |
| 16 | 600 | - | body | `.d-name` when a widget wants it bigger (inline style) |
| 24 | 600 | `-.02em` | display | `.hub-title` (line-height 1.15) |
| 26 | 600 | - | display | `.v-bat b` |
| 30-44 | 600 | `-.03em` | display | `.d-big` (`line-height:1`, tabular) - sensors use 34, energy 32, plant 30, weather 44 via inline `font-size:calc(34px * var(--d-fs,1) * var(--d-num,1))` |
| clamp(26px,4.4cqi,40px) | 600 | `-.03em` | display | `.hd-greet` (line-height 1.05, `text-wrap:balance`) |
| clamp(30px,5cqi,48px) | 500 | `-.04em` | display | `.hd-time` (tabular) |

Rules:

* Tracking is only ever applied three ways: tight on display sizes (`-.01em` at 17-19px, `-.02em` at 24px,
  `-.03em`/`-.04em` at 30px+), loose on tiny uppercase (`.06em`-`.08em`), zero everywhere else.
* `font-variant-numeric:tabular-nums` on every number that changes: `.val`, `.score b`, `.d-big`,
  `.hd-time`, `.fc div b`, `.hr-val`, `.ts-bottom`, `.ts-vol span`, `.v-bat b`, `.pg-menu-btn small`, `.saver .t`.
  If a value can tick, it is tabular.
* Units ride inside the big number as `<span class="d-unit">` = `font-size:.5em; color:var(--d-muted); margin-left:3px; letter-spacing:0`.
* Line-heights: prose 1.45-1.55, big numbers 1 / 1.05, everything else browser default.
* Muted text is `var(--muted)` (chrome) or `var(--d-muted)` (preview). There is no third grey for body copy.

---------------------------------------------------------------------------------------------------

## 2. Spacing and radius scales

### Radius (observed, exact)

| px | used for |
|---|---|
| 4 | `.th-prev i`, `.flagbtn i`, drop indicators, `.prog`, `.ev i` bar |
| 5 | inline `code` |
| 7 | `.seg button` (thumb inside a 10px seg), `.mini`, `.tb button`, `.fxb i`, `.rz` handle |
| 8 | `.name-in`, `.th-prev`, `.hub-ed-dev input`, `.hub-ed-sc input` |
| 9 | `.mark` (brand tile), **`.field input/select/textarea`**, `.lib-item .ic`, `.pre`, `.flagbtn`, `.v-paints button` |
| 10 | **`.btn`**, `.seg`, `.search input`, `.score`, `.insp-head .ic`, `.pg-item`, `.tb` toolbar, `.toast`, `.egg`, `.rep`, `.hub-ed-dev`, `.fp-ed`, `.mnav button` |
| 11 | `.fxb` |
| 12 | **cards**: `.lib-item`, `.libg`, `.th`, `.twg`, `pre.code`, `.fp-room`, `.rail button`, `.fc div`, `.g-bay` |
| 13 | `.wel .wi` icon tile |
| 14 | `.pg-menu` popover, `.insp-empty .ic`, `.ts-menu button`, phone `.dash` |
| 16 | `.wel button`, `.insp-empty`, `.g-scene`, `.ts-art` |
| 18 | **`.sheet`** modal, `.dash` canvas |
| 20 | `.ts-menu` |
| 99 | pills, chips, tags, switches, swatch rings, `.pg` page tabs, `.pg-menu-btn`, `.ha-chip`, `.ideas button`, `.ent-summary span`, `.kiosk-x` |
| 50% | circular buttons `.d-btn`, `.sw`, `.ht-ico`, `.ts-ico`, `.av .face`, `.vc span`, `.rep-i`, dots |

The rule inside: **nested radius = outer minus padding**. Seg 10 with 3px padding -> thumb 7. Card 12 with
~3px inset -> 9 icon tile. Preview: `.d-ico{border-radius:calc(var(--d-radius) * .5 + 4px)}`,
`.d-pbtn{border-radius:calc(var(--d-radius) * .45 + 2px)}`, `.hub-tile{calc(var(--d-radius) * .8)}` - child radii are
derived from the card radius, never fixed.

### Spacing (exact)

* Top bar: `padding:10px 16px; gap:10px` (phone `gap:6px; padding:10px 12px`).
* Pane: `.pane{padding:16px; gap:18px}`. Group: `.group{gap:10px; padding-top:16px}`. Pane-title `p` sits `4px` under `h2`.
* Field: `.field{gap:6px}` label-to-control. Button row: `.btnrow{gap:8px}`. Row of label+value: `.row{gap:12px}`.
* Lists of cards: `.lib{gap:8px}`, `.lib-grid{gap:8px}`, `.themes{gap:10px}`, `.wel{gap:10px}`, `.tweaks{gap:8px}`.
* Card inner: `.lib-item{padding:12px 10px; gap:7px}`, `.th{padding:6px; gap:6px}`, `.wel button{padding:16px; gap:14px}`,
  `.insp-empty{padding:26px 8px 18px; gap:8px}`, `.score{padding:10px 12px; gap:10px}`.
* Details: `.twg summary{padding:11px 12px}`, `.twb{padding:4px 12px 14px; gap:14px}`, `.libg summary{padding:11px 12px; gap:10px}`.
* Sheet: head `16px 18px`, body `16px 18px; gap:14px`, foot `12px 18px; gap:8px`.
* Popover: `.pg-menu{padding:10px; gap:8px}`, items `padding:4px 6px; gap:6px`, list `gap:4px`.
* Preview: `.dash{padding:24px}` (phone 16), `.dgrid{gap:var(--d-gap)}` (default from `state.gap`), `.card{padding:16px; gap:10px}`,
  `.chips{gap:8px; margin-top:12px}`, `.d-row{gap:8px; margin-top:auto}` (action row pinned to card bottom).
* Icon-to-text gap: 5px (tabs), 6px (seg, chips, d-pbtn), 7px (btn), 8px (group h3, scn), 10px (brand, insp-head, libg summary).

Summary of the grid: 4 / 6 / 8 / 10 / 12 / 14 / 16 / 18. Hearth never uses 5px gaps except icon-to-text in tabs, and never 20/24 inside chrome.

---------------------------------------------------------------------------------------------------

## 3. App chrome

### `.top` bar

```css
.top{display:flex; align-items:center; gap:10px; padding:10px 16px; border-bottom:1px solid var(--line); background:var(--panel); min-width:0}
.spacer{flex:1}
@media (max-width:520px){ .btn .lbl{display:none} .top{gap:6px; padding:10px 12px} }
```

Composition (verbatim order): brand, editable name input, `.spacer`, icon buttons (undo/redo, `disabled`),
a `.seg` device switcher, a status chip, a plain `.btn` with label, then ONE `.btn.primary` at the far right.
On phones button labels (`.lbl`) hide and only icons stay. The bar is `--panel` on a `--bg` page, separated
by a 1px line, no shadow.

### `.brand` + `.mark`

```css
.brand{display:flex; align-items:center; gap:10px; font-family:var(--f-display); font-weight:700; font-size:17px; letter-spacing:-.01em; white-space:nowrap}
.mark{width:28px; height:28px; border-radius:9px; background:var(--fg); color:var(--bg); display:grid; place-items:center}
.mark svg{width:16px; height:16px}
```
```html
<div class="brand"><span class="mark"><svg class="i" viewBox="0 0 24 24"><path d="M3 11 12 4l9 7M5 10v10h14V10"/></svg></span><span class="txt">Dashboard Studio</span></div>
```
The mark is an *inverted* tile (foreground colour fill, background-colour glyph) - the only place in the
chrome where fg is used as a fill besides the toast, the floating toolbar and the active `.pg`. The brand
text hides on phones (`.brand .txt{display:none}` under 980px).

### Editable title `.name-in`

```css
.name-in{border:1px solid transparent; background:transparent; border-radius:8px; padding:6px 8px; min-width:0; width:160px; font-weight:500}
.name-in:hover{border-color:var(--line)}
.name-in:focus{border-color:var(--accent); outline:none}
```
Invisible until hover; a quiet way to make a heading editable.

### `.seg` segmented control

```css
.seg{display:flex; background:var(--bg); border:1px solid var(--line); border-radius:10px; padding:3px; gap:2px; flex-wrap:wrap}
.seg button{border:0; background:transparent; padding:5px 10px; border-radius:7px; color:var(--muted); display:flex; align-items:center; gap:6px; font-size:13px}
.seg button[aria-pressed="true"]{background:var(--panel); color:var(--fg); box-shadow:0 1px 2px rgba(0,0,0,.08)}
```
Recessed track (`--bg`) on a `--panel` surface; the selected segment is a raised `--panel` thumb with the
one tiny shadow in the chrome. State is `aria-pressed`, not a class. Used for: device size, °F/°C,
Day/Night, card width S/M/L/XL, any 2-5 option mutually exclusive choice inside a `.field` under a `.lbl2`.
Compact variant: `.stage-meta .seg button{padding:3px 9px; font-size:12px}`, `#unitSeg button{padding:3px 8px}`.

### `.btn` and variants

```css
.btn{border:1px solid var(--line); background:var(--panel); border-radius:10px; padding:7px 12px; display:inline-flex; align-items:center; gap:7px; font-weight:500; font-size:13px; white-space:nowrap}
.btn:hover:not(:disabled){border-color:var(--muted)}
a.btn{text-decoration:none}
.btn.primary{background:var(--accent); color:var(--accent-ink); border-color:transparent}
.btn.primary:hover{filter:brightness(1.06)}
.btn.magic{background:var(--magic); color:#fff; border-color:transparent}
.btn.danger{color:#d23b3b}
.btn.icon{padding:7px}
.btn.block{width:100%; justify-content:center}
button:disabled{opacity:.45; cursor:default}
```

* Default `.btn` is an outlined panel-coloured button; hover darkens only the *border* to `--muted`. No fill change, no lift.
* `.primary` = accent fill, transparent border, hover is `filter:brightness(1.06)`. One per view.
* `.magic` = violet fill, white text, used for "do it for me" actions (Surprise me, Build a page, Ask Claude).
  Carries the sparkle icon. Think of it as "primary, but the machine is doing the work".
* `.danger` is text-colour only (`#d23b3b` -> `--red`), still outlined, still panel-filled. Destructive
  actions never get a red fill. Two-step confirm pattern (`twoStep()`) lives in JS, not CSS.
* `.icon` = square 7px padding, so with an 18px icon it is 34px (with the 1px borders). Pair with `title` and `aria-label`.
* `.block` for full-width in sheets/panes.
* `.btn .dotpulse` - an 8px pulsing dot in currentColor shown inside a busy button.
* Icons inside buttons: leading for verbs (`${ic('left')}Earlier`), trailing only for "next"-type arrows (`Later${ic('right')}`).
* Rows of buttons: `.btnrow{display:flex; flex-wrap:wrap; gap:8px}`; never stretch buttons to fill unless `.block`.

Touch adaptation (for the device UI): keep every value above except `padding` -> `10px 14px` (so 13px text
+ 20px line + 20 + 2 border = 42px) and `.btn.icon{padding:11px}` (40px square). Nothing else changes.

### Rail (vertical tab strip, desktop) and `.mnav` (phone bottom nav)

```css
.rail button{border:0; background:none; border-radius:12px; padding:9px 4px 8px; display:flex; flex-direction:column; align-items:center; gap:4px; color:var(--muted); font-size:11.5px; font-weight:600}
.rail button svg.i{width:21px; height:21px}
.rail button:hover{color:var(--fg); background:var(--bg)}
.rail button[aria-selected="true"]{color:var(--fg); background:color-mix(in srgb, var(--accent) 13%, var(--bg))}
.rail button[aria-selected="true"] svg.i{color:var(--accent)}
.mnav{display:flex; position:fixed; left:0; right:0; bottom:0; background:var(--panel); border-top:1px solid var(--line); padding:6px 6px calc(6px + env(safe-area-inset-bottom,0px)); z-index:20; justify-content:space-around}
.mnav button{border:0; background:none; display:flex; flex-direction:column; align-items:center; gap:3px; font-size:11px; color:var(--muted); padding:6px 8px; border-radius:10px}
.mnav button[aria-pressed="true"]{color:var(--fg); background:var(--bg)}
```
Icon-over-label, muted by default, selected = fg text + accent icon + faint accent-tinted ground (`--green-dim`).
This is the pattern for a multi-page device UI's navigation.

---------------------------------------------------------------------------------------------------

## 4. Form controls

### `.field`

```css
.field{display:flex; flex-direction:column; gap:6px}
.field label,.field .lbl2{font-size:12.5px; font-weight:500}
.field input[type=text],.field select,.field textarea{border:1px solid var(--line); border-radius:9px; padding:8px 10px; background:var(--bg); min-width:0; width:100%}
.field textarea{resize:vertical; min-height:84px; line-height:1.45}
.field input[type=text]:focus,.field select:focus,.field textarea:focus{border-color:var(--accent); outline:none}
.mono{font-family:var(--f-mono) !important; font-size:12.5px !important}
.row{display:flex; align-items:center; justify-content:space-between; gap:12px}
```
```html
<div class="field"><label for="pgName">Page name</label><input type="text" id="pgName" value="..."></div>
<div class="field"><span class="lbl2">Width</span><div class="seg" role="group" aria-label="Width">...</div></div>
<div class="field"><div class="row"><label for="fxInt">Strength</label><span class="val" id="fxIntV"></span></div><input type="range" id="fxInt"></div>
<div class="field"><label>Light</label><input type="text" class="mono" placeholder="light.kitchen" spellcheck="false"></div>
```
* Label above control, 6px apart, 12.5/500, no colon, sentence case.
* Inputs are *recessed*: `--bg` fill inside a `--panel` pane, 1px `--line` border, radius 9. Focus = border turns accent, no ring, no glow.
* `.lbl2` is the label when the "control" is not a labelable element (a seg, a grid of presets).
* A range field puts the label and a mono `.val` read-out on one `.row`, slider underneath.
* Placeholders are real examples (`light.kitchen`, `HDS1:...`), machine-value fields get `.mono` + `spellcheck="false"`.
* Hints go directly under the control as `<p class="hint">`.
* Quick-edit grids reuse the same look at 8px radius: `.hub-ed-dev input,.hub-ed-dev select{border:1px solid var(--line); border-radius:8px; padding:6px 8px; background:var(--bg); font-size:12.5px}`.

Touch adaptation: `padding:11px 12px` on inputs/selects (44px tall at 14px text). Keep radius 9.

### `.search`

```css
.search{position:relative}
.search svg.i{position:absolute; left:10px; top:50%; transform:translateY(-50%); color:var(--muted); width:16px}
.search input{width:100%; border:1px solid var(--line); border-radius:10px; padding:8px 10px 8px 34px; background:var(--bg)}
.search input:focus{outline:none; border-color:var(--accent)}
```
Magnifier icon (16px, muted) absolutely placed at left 10px; input padded 34px. Radius 10, not 9 (search is a "button-ish" field).

### Range inputs

Chrome: `input[type=range]{accent-color:var(--accent); width:100%}` - native, just tinted. Read-out `.val{font-family:var(--f-mono); font-size:12px; color:var(--muted); font-variant-numeric:tabular-nums}`.

Preview `.bri` (brightness/volume slider, fully custom):
```css
.bri{-webkit-appearance:none; appearance:none; height:6px; border-radius:6px; background:color-mix(in srgb, var(--d-text) 14%, transparent); accent-color:var(--d-accent)}
.bri::-webkit-slider-thumb{-webkit-appearance:none; width:16px; height:16px; border-radius:50%; background:var(--d-text); border:0}
.bri::-moz-range-thumb{width:16px; height:16px; border-radius:50%; background:var(--d-text); border:0}
```
6px track in 14% text-tint, 16px round thumb in solid text colour. No fill-to-left highlight.

### `.switch` toggle (chrome)

```css
.switch{display:flex; align-items:center; justify-content:space-between; gap:12px; cursor:pointer}
.switch input{appearance:none; -webkit-appearance:none; width:38px; height:22px; border-radius:99px; background:var(--line); position:relative; flex:none; cursor:pointer; transition:background .2s}
.switch input::after{content:""; position:absolute; top:3px; left:3px; width:16px; height:16px; border-radius:50%; background:#fff; transition:transform .2s; box-shadow:0 1px 2px rgba(0,0,0,.2)}
.switch input:checked{background:var(--accent)}
.switch input:checked::after{transform:translateX(16px)}
.switch span b{display:block; font-weight:600; font-size:13px}
.switch span small{color:var(--muted); font-size:12px}
```
```html
<label class="switch"><span><b>Change theme at sunset</b><small>Exports an automation that swaps themes at sunset and sunrise</small></span><input type="checkbox" id="nightOn"></label>
```
The whole row is the `<label>`; text (bold title + muted one-line explanation) left, 38x22 track right.
Off track = `--line`, on = accent, knob always white with a 1px shadow.

Preview `.sw-toggle` (bigger, text-coloured knob):
```css
.sw-toggle{width:40px; height:24px; border-radius:99px; background:color-mix(in srgb, var(--d-text) 16%, transparent); border:0; position:relative; flex:none; padding:0}
.sw-toggle::after{content:""; position:absolute; top:3px; left:3px; width:18px; height:18px; border-radius:50%; background:var(--d-text); transition:transform .2s}
.is-on .sw-toggle{background:var(--d-active)}
.is-on .sw-toggle::after{transform:translateX(16px); background:var(--d-on)}
```
A `<button class="sw-toggle" data-act="toggle" aria-label="...">` with no inner content; the state class `.is-on` lives on the *card*, not the button.

Native checkbox (lists): `.holrow input{width:18px; height:18px; accent-color:var(--accent); margin:0}`.

### Colour swatches

```css
.swatches{display:flex; flex-wrap:wrap; gap:8px; align-items:center}
.sw{width:26px; height:26px; border-radius:50%; border:2px solid var(--panel); box-shadow:0 0 0 1px var(--line)}
.sw[aria-pressed="true"]{box-shadow:0 0 0 2px var(--fg)}
.sw.auto{background:conic-gradient(from 0deg,#ff6a9a,#ffb547,#5ee38a,#5bc8ff,#8a7bff,#ff6a9a)}
.colorpick{width:30px; height:30px; border:0; padding:0; background:none}
.crow{display:flex; align-items:center; justify-content:space-between; gap:10px; font-size:12.5px; font-weight:500}
.crow-r{display:flex; align-items:center; gap:6px}
```
26px circles, 2px panel-coloured gap ring then a 1px line ring; selected = 2px fg ring. A `.crow` is a label-left / colour-input-right row (with an optional `.mini` Reset).

### Preset / option tiles (chrome)

```css
.presets{display:grid; grid-template-columns:repeat(3,1fr); gap:6px}
.pre{border:1px solid var(--line); background:var(--bg); border-radius:9px; padding:7px 4px; font-size:12px; font-weight:500}
.pre:hover{border-color:var(--accent)}
.th{border:1px solid var(--line); border-radius:12px; padding:6px; background:var(--panel); text-align:left; display:flex; flex-direction:column; gap:6px; min-width:0}
.th[aria-pressed="true"]{border-color:var(--accent); box-shadow:0 0 0 2px color-mix(in srgb, var(--accent) 30%, transparent)}
.fxb[aria-pressed="true"]{border-color:var(--accent); box-shadow:0 0 0 2px color-mix(in srgb, var(--accent) 30%, transparent)}
```
Selected tiles = accent border + 2px 30% accent halo (`--green-glow`). This is THE selection treatment in Hearth; `.pg-menu-btn[aria-expanded="true"]` uses the same with 25%.

---------------------------------------------------------------------------------------------------

## 5. Grouping and hierarchy

```css
.pane{padding:16px; display:flex; flex-direction:column; gap:18px}
.pane-title h2{margin:0; font-family:var(--f-display); font-size:19px; font-weight:700; letter-spacing:-.01em}
.pane-title p{margin:4px 0 0; color:var(--muted); font-size:12.5px; line-height:1.45}
.pane-title + .group{border-top:0; padding-top:0}
.group{display:flex; flex-direction:column; gap:10px; padding-top:16px; border-top:1px solid var(--line)}
.group:first-child{border-top:0; padding-top:0}
.group h3{margin:0; font-size:14px; font-weight:600; display:flex; align-items:center; gap:8px}
.group h3 svg.i{color:var(--magic)}
.eyebrow{font-size:11px; text-transform:uppercase; letter-spacing:.08em; color:var(--muted); font-weight:600}
.hint{color:var(--muted); font-size:12.5px; line-height:1.5; margin:0}
.newtag{font-size:10px; font-weight:700; letter-spacing:.06em; color:var(--magic); background:color-mix(in srgb, var(--magic) 14%, transparent); padding:2px 6px; border-radius:99px; text-transform:uppercase}
.tips{margin:0; padding-left:18px; display:flex; flex-direction:column; gap:8px; color:var(--muted); font-size:12.5px; line-height:1.5}
.tips b{color:var(--fg); font-weight:600}
```
```html
<div class="pane-title"><h2>Style</h2><p>Pick a theme. Everything else is optional.</p></div>
<div class="group">
  <div class="eyebrow">Theme</div>
  ...controls...
</div>
<div class="group">
  <h3><svg class="i" viewBox="0 0 24 24">...</svg>Auto-build my home <span class="newtag">New</span></h3>
  <p class="hint">Makes a page for every room, filled with that room's devices.</p>
  <div class="btnrow"><button class="btn magic">Build a page for every room</button></div>
</div>
```
* A pane = title block, then `.group`s stacked. Groups separate with a **1px top border + 16px padding**,
  never with boxes. The first group (or the one right after the title) has no border.
* Two heading styles inside a group: `.eyebrow` (uppercase tracker, for "this is a settings section") or
  `h3` with a violet icon (for "this is a feature"). Pick one per group, never both.
* `.hint` under a heading/control: muted 12.5px, line-height 1.5, zero margin (the parent gap spaces it).
* `.newtag` is a tiny violet pill after the h3 text.
* Collapsible groups are `<details class="twg">`:

```css
.twg{border:1px solid var(--line); border-radius:12px; background:var(--panel)}
.twg summary{list-style:none; cursor:pointer; padding:11px 12px; font-weight:600; font-size:13.5px; display:flex; align-items:center; gap:8px}
.twg summary::-webkit-details-marker{display:none}
.twg summary::before{content:""; width:7px; height:7px; border-right:1.8px solid var(--muted); border-bottom:1.8px solid var(--muted); transform:rotate(-45deg); transition:transform .2s; margin:0 2px}
.twg[open] summary::before{transform:rotate(45deg)}
.twg summary .mini{margin-left:auto}
.twb{display:flex; flex-direction:column; gap:14px; padding:4px 12px 14px}
.twg.fold .twb{padding-top:0}
```
The disclosure chevron is a CSS-drawn 7px square rotated -45deg (pointing right), rotating to 45deg (down). It is drawn in `--muted` at 1.8px stroke, matching icon stroke weight. Same recipe on `.libg summary::before`.

### `.tabs`

```css
.tabs{display:flex; gap:4px; padding:12px 16px 0; position:sticky; top:0; background:var(--panel); z-index:2; border-bottom:1px solid var(--line)}
.tabs button{border:0; background:none; padding:8px 3px 10px; margin-right:5px; color:var(--muted); font-weight:600; border-bottom:2px solid transparent; display:flex; align-items:center; gap:5px}
.tabs button[aria-selected="true"]{color:var(--fg); border-color:var(--fg)}
.tabs svg.i{width:15px; height:15px}
```
Underline tabs; the active underline is **fg, not accent**. Accent is reserved for the thing being acted on.

---------------------------------------------------------------------------------------------------

## 6. Status

### `.pill` (preview; also used in chrome via same class)

```css
.pill{font-size:11px; font-weight:600; padding:3px 8px; border-radius:99px; background:color-mix(in srgb, var(--d-text) 9%, transparent); white-space:nowrap}
.pill.ok{background:color-mix(in srgb, #2fc77a 22%, transparent); color:color-mix(in srgb, #2fc77a 65%, var(--d-text))}
.pill.warn{background:color-mix(in srgb, #ff9f40 24%, transparent); color:color-mix(in srgb, #ff9f40 65%, var(--d-text))}
.pill.bad{background:color-mix(in srgb, #ff5a5a 24%, transparent); color:color-mix(in srgb, #ff5a5a 65%, var(--d-text))}
```
Usage: `<span class="pill ${b.locked?'ok':'warn'}">${b.locked?'Locked':'Unlocked'}</span>` - top-right of a
card in `.d-top`, opposite the `.d-ico`. Neutral pill (no modifier) for counts ("3 on", "Hourly", "2 of 4 home").
Text colour is the status colour mixed 65% into the text colour, so it stays readable on any theme. Map:
ok -> `--ok`/`--ok-dim`, warn -> `--orange`/`--orange-dim`, bad -> `--red`/`--red-dim`.

### `.chip` (preview summary chips)

```css
.chips{display:flex; flex-wrap:wrap; gap:8px; margin-top:12px}
.chip{display:inline-flex; align-items:center; gap:6px; padding:7px 12px; border-radius:99px; background:var(--d-card); border:1px solid var(--d-border); font-size:12.5px; -webkit-backdrop-filter:blur(var(--d-blur)); backdrop-filter:blur(var(--d-blur))}
.chip svg.i{width:14px; height:14px; color:var(--d-accent)}
.wx-chips .chip{padding:5px 10px}
```
```html
<span class="chip"><svg class="i">...</svg>3 lights on</span>
```
A chip = 14px accent-coloured icon + short fact, card-coloured, bordered, pill-shaped. Used in rows under a greeting / big value. Chrome equivalent:
`.ha-chip{display:inline-flex; align-items:center; gap:7px; font-size:12.5px; font-weight:500; color:var(--muted); border:1px solid var(--line); border-radius:99px; padding:5px 11px; white-space:nowrap}`
with a status dot `.ha-chip i{width:8px; height:8px; border-radius:50%; background:#1f9d63; box-shadow:0 0 0 3px color-mix(in srgb, #1f9d63 22%, transparent)}` (`.off i` -> `#d23b3b`).
That 8px dot with a 3px 22% halo is Hearth's "connected / live" indicator.

### `.score` + `.grade`

```css
.score{display:flex; align-items:center; gap:10px; padding:10px 12px; border-radius:10px; background:var(--bg); border:1px solid var(--line); font-size:12.5px}
.score b{font-family:var(--f-mono); font-variant-numeric:tabular-nums}
.grade{font-size:11px; font-weight:700; padding:2px 7px; border-radius:99px; margin-left:auto}
.grade.ok{background:color-mix(in srgb, #1f9d63 18%, transparent); color:#1f9d63}
.grade.mid{background:color-mix(in srgb, #d07a12 18%, transparent); color:#c87210}
.grade.bad{background:color-mix(in srgb, #d23b3b 18%, transparent); color:#d23b3b}
```
```html
<div class="score"><span>Text contrast <b>7.2:1</b> · labels <b>4.6:1</b></span><span class="grade ok">Very easy to read</span></div>
```
A recessed strip (bg-on-panel) with mono numbers and a verdict pill pushed right. This is the pattern for
"measurement + verdict" rows (battery / signal / flow rate etc.).

### `.ai-status` (busy line)

```css
.ai-status{font-size:13px; color:var(--muted); min-height:1.4em; display:flex; align-items:center; gap:8px}
.ai-status .dotpulse{width:8px; height:8px; border-radius:50%; background:var(--magic); animation:pulse 1s ease-in-out infinite}
@keyframes pulse{50%{opacity:.25; transform:scale(.7)}}
```
Reserved height (so the layout doesn't jump), pulsing violet dot + muted sentence. Use for "Calibrating...", "Saving...".

### Report rows (install results)

```css
.rep{display:flex; gap:10px; align-items:flex-start; padding:10px 12px; border:1px solid var(--line); border-radius:10px}
.rep-i{width:22px; height:22px; border-radius:50%; display:grid; place-items:center; font-weight:700; font-size:12px; flex:none; background:color-mix(in srgb, #1f9d63 18%, transparent); color:#1f9d63}
.rep.bad .rep-i{background:color-mix(in srgb, #d07a12 20%, transparent); color:#c87210}
.rep small{color:var(--muted); line-height:1.45}
```
22px tinted circle with a glyph, title + muted detail. Good for a log / step list.

### `.toast`

```css
.toast{position:fixed; bottom:calc(76px + env(safe-area-inset-bottom,0px)); left:50%; transform:translateX(-50%); background:var(--fg); color:var(--bg); padding:9px 16px; border-radius:10px; font-weight:500; z-index:60; box-shadow:0 10px 30px rgba(0,0,0,.25); white-space:nowrap}
@media (min-width:981px){ .toast{bottom:24px} }
```
```js
function toast(msg){ const t = $('toast'); t.textContent = msg; t.hidden = false; clearTimeout(toastT); toastT = setTimeout(() => t.hidden = true, 2200); }
```
Inverted (fg on bg), centred bottom, above the phone nav, 2.2s, text only ("Block removed. Ctrl+Z brings it back"). No icon, no colour coding, no close button.

### Inline error text

`<p class="hint" id="codeErr" role="alert"></p>` - errors are a hint paragraph that gets text; `.tv-err{color:#d23b3b; font-weight:500}` when red is warranted. `.kp-msg.err{color:#ff7a7a}` in the preview.

---------------------------------------------------------------------------------------------------

## 7. Containers

### `.lib-item` (the chrome card)

```css
.lib-item{border:1px solid var(--line); background:var(--panel); border-radius:12px; padding:12px 10px; text-align:left; display:flex; flex-direction:column; gap:7px; cursor:grab; transition:border-color .15s, transform .15s; position:relative}
.lib-item:hover{border-color:var(--accent); transform:translateY(-1px)}
.lib-item:active{cursor:grabbing}
.lib-item .ic{width:30px; height:30px; border-radius:9px; background:var(--bg); display:grid; place-items:center; color:var(--accent)}
.lib-item b{font-weight:600; font-size:13px}
.lib-item span{font-size:11.5px; color:var(--muted); line-height:1.35}
.lib-item span:not(.ic):not(.newtag){display:-webkit-box; -webkit-line-clamp:2; -webkit-box-orient:vertical; overflow:hidden}
.lib-item .newtag{position:absolute; top:10px; right:8px}
.lib-grid{display:grid; grid-template-columns:1fr 1fr; gap:8px}
```
```html
<button class="lib-item" draggable="true" data-type="light"><span class="ic"><svg class="i">...</svg></span><b>Light</b><span>Toggle and dim one light</span></button>
```
Anatomy top-to-bottom: 30px icon tile (bg-on-panel, accent glyph, radius 9) -> bold 13px name -> muted 11.5px
2-line description. 1px line border, radius 12, panel fill, **no shadow**. Hover = accent border + 1px lift.
Grouped in `<details class="libg">` with a count pill `.libn{font-size:11px; font-weight:600; color:var(--muted); background:var(--bg); border-radius:99px; padding:2px 8px}`.

### `.wel` welcome buttons

```css
.wel{display:grid; gap:10px}
.wel button{display:grid; grid-template-columns:auto 1fr auto; align-items:center; gap:14px; text-align:left; border:1px solid var(--line); background:var(--bg); border-radius:16px; padding:16px; color:var(--fg)}
.wel button:hover{border-color:var(--accent)}
.wel button.hero{background:color-mix(in srgb, var(--magic) 10%, var(--bg)); border-color:color-mix(in srgb, var(--magic) 40%, var(--line))}
.wel .wi{width:44px; height:44px; border-radius:13px; display:grid; place-items:center; background:var(--panel); color:var(--accent)}
.wel .hero .wi{background:var(--magic); color:#fff}
.wel b{display:block; font-size:15px}
.wel small{display:block; color:var(--muted); font-size:12.5px; margin-top:2px; line-height:1.4}
.wel .go{color:var(--muted)}
```
Big three-column row: 44px icon tile | title + one-line blurb | muted chevron (`.go`). Radius 16 (the
"large choice" radius). The `.hero` variant tints the whole row 10% violet and fills the tile violet.
Use for a landing / start screen's primary choices.

### `.insp-empty` empty state

```css
.insp-empty{display:flex; flex-direction:column; align-items:center; text-align:center; gap:8px; padding:26px 8px 18px; border:1.5px dashed var(--line); border-radius:16px}
.insp-empty .ic{width:46px; height:46px; border-radius:14px; background:var(--bg); display:grid; place-items:center; color:var(--accent)}
.insp-empty h2{margin:0; font-family:var(--f-display); font-size:16px}
.insp-empty p{margin:0; color:var(--muted); font-size:12.5px; line-height:1.45}
```
```html
<div class="insp-empty"><span class="ic">${ic('pencil')}</span><h2>Tap a block to change it</h2><p>Its settings show up here. Drag blocks to move them around.</p></div>
```
1.5px **dashed** line border, radius 16, centred 46px icon tile, display-face title, muted explanation.
Preview equivalent `.empty{border:2px dashed var(--d-border); border-radius:var(--d-radius); padding:48px 20px; text-align:center; color:var(--d-muted)}` with `.empty b{display:block; color:var(--d-text); font-size:16px; margin-bottom:6px}`.
Dashed = "nothing here yet / drop target". Never used for anything else.

### `.insp-head` (selected-item header)

```css
.insp-head{display:flex; align-items:center; gap:10px}
.insp-head .ic{width:36px; height:36px; border-radius:10px; background:var(--bg); display:grid; place-items:center; color:var(--accent); flex:none}
.insp-head h2{margin:0; font-family:var(--f-display); font-size:18px; font-weight:700}
.insp-head p{margin:2px 0 0; color:var(--muted); font-size:12px}
.ihead-acts{margin-left:auto; display:flex; gap:4px}
```
```html
<div class="insp-head"><span class="ic">...</span><div><h2>Light</h2><p>Toggle and dim one light</p></div>
  <div class="ihead-acts"><button class="btn icon" title="Duplicate">...</button><button class="btn icon danger" title="Delete">...</button></div></div>
```
Icon tile | title + subtitle | right-aligned icon buttons (4px apart). This is the header for any "edit one thing" view (a zone, a schedule entry).

### `.sheet` modal

```css
.modal{position:fixed; inset:0; background:rgba(8,10,14,.55); display:grid; place-items:center; z-index:50; padding:16px}
.sheet{background:var(--panel); border:1px solid var(--line); border-radius:18px; width:min(780px,100%); max-height:min(88vh, 900px); display:flex; flex-direction:column; overflow:hidden; box-shadow:0 30px 80px rgba(0,0,0,.35)}
.sheet-head{display:flex; align-items:center; gap:12px; padding:16px 18px; border-bottom:1px solid var(--line)}
.sheet-head h2{margin:0; font-family:var(--f-display); font-size:20px; flex:1}
.sheet .tabs{position:static; padding:8px 18px 0; flex-wrap:wrap}
.sheet-body{overflow:auto; padding:16px 18px; flex:1; min-height:0; display:flex; flex-direction:column; gap:14px}
.sheet-foot{display:flex; gap:8px; justify-content:flex-end; padding:12px 18px; border-top:1px solid var(--line); flex-wrap:wrap; align-items:center}
.sheet-foot .hint{margin-right:auto}
.steps{margin:0; padding-left:20px; display:flex; flex-direction:column; gap:12px; line-height:1.55}
.ideas{display:flex; flex-wrap:wrap; gap:6px}
.ideas button{border:1px solid var(--line); background:var(--bg); border-radius:99px; padding:5px 11px; font-size:12.5px; color:var(--muted)}
.ideas button:hover{color:var(--fg); border-color:var(--muted)}
```
```html
<div class="modal" id="modal" hidden>
  <div class="sheet" role="dialog" aria-modal="true" aria-labelledby="mTitle">
    <div class="sheet-head"><h2 id="mTitle"></h2><button class="btn icon" id="mClose" aria-label="Close"><svg class="i" viewBox="0 0 24 24"><path d="M6 6l12 12M18 6 6 18"/></svg></button></div>
    <div id="mTabs"></div>
    <div class="sheet-body" id="mBody"></div>
    <div class="sheet-foot" id="mFoot"></div>
  </div>
</div>
<!-- a typical foot -->
<span class="hint">Uses your Claude account.</span><button class="btn" id="aiStop" hidden>Stop</button><button class="btn magic" id="aiGo">...</button>
```
Scrim 55% near-black. Sheet radius 18, 1px line border AND the big shadow (the one place both appear).
Head: display-face title, close is a plain `.btn.icon` X at right. Foot: buttons right-aligned, optional
`.hint` pushed left; the primary/magic button is last. Body is a column with 14px gaps of `.field`s, `.hint`s, `<ol class="steps">`, `pre.code`.

### `.pg-menu` popover

```css
.pg-menu-btn{display:flex; align-items:center; gap:8px; border:1px solid var(--line); background:var(--panel); border-radius:99px; padding:6px 10px 6px 12px; font-weight:600; min-width:0; max-width:min(320px, 52vw)}
.pg-menu-btn:hover{border-color:var(--muted)}
.pg-menu-btn[aria-expanded="true"]{border-color:var(--accent); box-shadow:0 0 0 2px color-mix(in srgb, var(--accent) 25%, transparent)}
.pg-menu-btn svg.i{width:16px; height:16px; color:var(--muted)}
.pg-menu{position:absolute; top:calc(100% + 8px); left:0; z-index:25; width:min(340px, calc(100vw - 32px)); background:var(--panel); border:1px solid var(--line); border-radius:14px; box-shadow:0 18px 50px rgba(10,12,20,.22); padding:10px; display:flex; flex-direction:column; gap:8px}
.pg-list{list-style:none; margin:0; padding:0; display:flex; flex-direction:column; gap:4px; max-height:min(52vh, 420px); overflow:auto}
.pg-item{display:grid; grid-template-columns:auto minmax(0,1fr) auto auto; align-items:center; gap:6px; padding:4px 6px; border-radius:10px; border:1px solid transparent}
.pg-item:hover{background:var(--bg)}
.pg-item.cur{background:color-mix(in srgb, var(--accent) 10%, transparent); border-color:color-mix(in srgb, var(--accent) 35%, transparent)}
.pg-foot{display:flex; align-items:center; justify-content:space-between; gap:8px; flex-wrap:wrap; border-top:1px solid var(--line); padding-top:8px}
```
Trigger is a pill button (radius 99) with a muted chevron. The popover is radius 14, 8px below, with a
list of radius-10 rows; current row gets the 10%/35% accent tint. Footer separated by the same 1px top border rule as `.group`.

### Page pills `.pg`

```css
.pg{border:1px solid var(--line); background:var(--panel); color:var(--muted); border-radius:99px; padding:6px 13px; font-weight:500; font-size:13px}
.pg[aria-pressed="true"]{background:var(--fg); color:var(--bg); border-color:var(--fg)}
.pg.add{padding:6px 9px; display:grid; place-items:center}
```
Pill tabs where the selected one is **inverted fg** - same as the brand mark and toast. Use for page/zone switching.

### `pre.code` and `code`

```css
pre.code{margin:0; background:var(--bg); border:1px solid var(--line); border-radius:12px; padding:14px; font-family:var(--f-mono); font-size:12px; line-height:1.55; overflow:auto; white-space:pre; max-height:52vh}
code{font-family:var(--f-mono); font-size:12px; background:var(--bg); border:1px solid var(--line); padding:1px 5px; border-radius:5px}
```
Recessed, bordered, mono. Inline `code` gets a 1px border too - a chip, not a highlight.

### `.mini` (tiny inline action)

```css
.mini{border:1px solid var(--line); background:var(--bg); border-radius:7px; padding:3px 8px; font-size:11.5px; font-weight:500; color:var(--muted)}
.mini:hover{color:var(--fg)}
.pv{font-size:10px; font-weight:600; color:var(--muted); border:1px dashed var(--muted); border-radius:99px; padding:1px 6px; margin-left:6px; vertical-align:1px; white-space:nowrap}
```
"Reset" buttons inside rows; `.pv` is a dashed micro-tag for caveats ("Preview only").

### Floating toolbar `.tb`

```css
.tb{position:absolute; top:-18px; right:10px; display:flex; gap:2px; background:var(--fg); color:var(--bg); border-radius:10px; padding:3px; z-index:5; box-shadow:0 6px 20px rgba(0,0,0,.25)}
.tb button{border:0; background:transparent; color:inherit; height:28px; min-width:28px; padding:0 7px; border-radius:7px; display:grid; place-items:center; font-size:12px; font-weight:600}
.tb button:hover{background:color-mix(in srgb, var(--bg) 18%, transparent)}
```
Inverted mini-toolbar over a selected object. 10 outer / 7 inner radius with 3px padding, again.

---------------------------------------------------------------------------------------------------

## 8. The dashboard-preview card language

These classes render the *product* (the dashboard tiles). They are themed by inline `--d-*` vars set from the
theme object: `bg base card border text muted accent active on radius blur shadow font display gap fs num hw ls ltt lls bw pad isw dpad`.
Representative theme values (exact, from `THEMES`):

* Flat Black: `card:#101010 border:#1b1b1b text:#f4f4f4 muted:#8f8f8f accent:#ffb547 on:#1d1200 radius:18 blur:0 shadow:'none'`
* Porcelain: `card:#ffffff border:rgba(20,30,50,0.06) text:#131924 muted:#646b78 accent:#3a66f5 on:#ffffff radius:22 shadow:'0 1px 2px rgba(16,24,40,0.04), 0 8px 24px rgba(16,24,40,0.07)'`
* Liquid Glass: `card:rgba(255,255,255,0.10) border:rgba(255,255,255,0.20) radius:26 blur:22 shadow:'0 12px 40px rgba(0,0,0,0.22)'`

Card style presets (`CARD_STYLES`): `filled{cardOpacity:100, borderW:0, shadow:'soft'}`, `glass{14, blur:22, borderW:1, shadow:'medium'}`,
`outline{0, borderW:2, shadow:'none'}`, `floating{100, borderW:0, shadow:'strong'}`, `minimal{0, 0, none}`, `soft{70, 0, none, blur:8}`.
For a device UI on the irrigoto palette, "Flat Black / filled" semantics fit: `--d-card`=`--bg2`, `--d-border`=`--border`, `--d-text`=`--text`, `--d-muted`=`--text-mid`, `--d-accent`=`--green`, `--d-on`=`--accent-ink`, `--d-active`=`--green`, radius 14-18, no blur.

### Card shell (PREVIEW)

```css
.dash{background:var(--d-bg); color:var(--d-text); font-family:var(--d-font); font-size:14px; border-radius:18px; padding:var(--d-dpad,24px); min-height:520px; box-shadow:0 20px 60px rgba(10,12,20,.18); transition:background .5s, color .5s; position:relative}
.dgrid{display:grid; grid-template-columns:repeat(12,minmax(0,1fr)); gap:var(--d-gap)}
.card{grid-column:span 3; background:var(--d-card); border:var(--d-bw,1px) solid var(--d-border); border-radius:var(--d-radius); box-shadow:var(--d-shadow);
  -webkit-backdrop-filter:blur(var(--d-blur)) saturate(1.4); backdrop-filter:blur(var(--d-blur)) saturate(1.4);
  padding:var(--d-pad,16px); position:relative; min-width:0; display:flex; flex-direction:column; gap:10px; cursor:pointer; transition:background .25s, outline-color .15s, opacity .2s}
.card[data-size="m"]{grid-column:span 6}  .card[data-size="l"]{grid-column:span 9}  .card[data-size="xl"]{grid-column:span 12}
@container dash (max-width:700px){ .card[data-size="s"],.card[data-size="m"]{grid-column:span 6} .card[data-size="l"],.card[data-size="xl"]{grid-column:span 12} }
@container dash (max-width:440px){ .card[data-size="m"]{grid-column:span 12} }
.card.bare{background:transparent; border-color:transparent; box-shadow:none; -webkit-backdrop-filter:none; backdrop-filter:none}
```
12-column grid, card = column flex with 10px gap, padding 16. Selection/hover are **outlines**, not borders
(EDITOR chrome on top of the preview):
```css
.card:hover{outline:1.5px dashed color-mix(in srgb, var(--accent) 60%, transparent); outline-offset:3px}
.card.is-sel{outline:2px solid var(--accent); outline-offset:3px}
```
(`--accent` here is the *editor* accent, deliberately not the theme's, so the selection ring looks like UI, not content.)

### Card anatomy (PREVIEW)

```css
.d-top{display:flex; justify-content:space-between; align-items:center; gap:8px}
.d-ico{width:38px; height:38px; border-radius:var(--d-ico-r, calc(var(--d-radius) * .5 + 4px)); display:grid; place-items:center; background:var(--d-ico-bg, color-mix(in srgb, var(--d-text) 8%, transparent)); color:var(--d-text); flex:none}
.d-ico svg.i{width:19px; height:19px}
.d-name{font-weight:var(--d-hw,600); font-size:14px; white-space:nowrap; overflow:hidden; text-overflow:ellipsis}
.d-label{font-size:12.5px; color:var(--d-muted); font-weight:500; text-transform:var(--d-ltt,none); letter-spacing:var(--d-lls,0); white-space:nowrap; overflow:hidden; text-overflow:ellipsis}
.d-big{font-family:var(--d-display); font-weight:var(--d-hw,600); letter-spacing:calc(-.03em + var(--d-ls,0em)); line-height:1; font-variant-numeric:tabular-nums}
.d-unit{font-size:.5em; color:var(--d-muted); margin-left:3px; letter-spacing:0}
.d-row{display:flex; gap:8px; margin-top:auto}
```
Canonical compositions (from the renderers, verbatim shape):

```html
<!-- toggle device (light) -->
<div class="d-top"><span class="d-ico">${ic('bulb')}</span><button class="sw-toggle" data-act="toggle" aria-label="Toggle Kitchen"></button></div>
<div><div class="d-name">Kitchen</div><div class="d-label">On · 80%</div></div>
<input class="bri" type="range" min="1" max="100" value="80" aria-label="Brightness">

<!-- status device (lock) -->
<div class="d-top"><span class="d-ico">${ic('lock')}</span><span class="pill ok">Locked</span></div>
<div><div class="d-name">Front door</div><div class="d-label">Tap to unlock</div></div>
<div class="d-row"><button class="d-pbtn on" data-act="lock">Unlock</button></div>

<!-- reading (sensor) -->
<div class="d-label">Humidity</div>
<div class="d-big" style="font-size:34px">48<span class="d-unit">%</span></div>
<svg class="spark">...</svg>

<!-- chooser (alarm) -->
<div class="d-top"><span class="d-ico">${ic('shield')}</span><span class="pill ok">Armed home</span></div>
<div class="d-name">Alarm</div>
<div class="d-row"><button class="d-pbtn">Off</button><button class="d-pbtn on">Home</button><button class="d-pbtn">Away</button></div>

<!-- stepper (climate / cover) -->
<div class="dial-ctl"><button class="d-btn" data-act="tminus" aria-label="Lower">${ic('minus')}</button><button class="d-btn" data-act="tplus" aria-label="Raise">${ic('plus')}</button></div>
<div class="d-row"><button class="d-pbtn" aria-label="Open more">${ic('up')}</button><button class="d-pbtn" aria-label="Stop">${ic('stop')}</button><button class="d-pbtn" aria-label="Close more">${ic('down')}</button></div>
```
The grammar: **top row = icon tile left, state (toggle or pill) right -> name + muted label -> optional
visual -> action row pinned to the bottom with `margin-top:auto`.** Every card follows it.

### Card buttons (PREVIEW)

```css
.d-btn{border:0; background:color-mix(in srgb, var(--d-text) 9%, transparent); color:var(--d-text); width:34px; height:34px; border-radius:50%; display:grid; place-items:center; flex:none}
.d-btn:hover{background:color-mix(in srgb, var(--d-text) 16%, transparent)}
.d-btn.lg{width:44px; height:44px; background:var(--d-accent); color:var(--d-on)}
.d-pbtn{border:0; flex:1; min-width:0; height:36px; border-radius:calc(var(--d-radius) * .45 + 2px); background:color-mix(in srgb, var(--d-text) 9%, transparent); color:var(--d-text); font-weight:600; font-size:12.5px; display:flex; align-items:center; justify-content:center; gap:6px; white-space:nowrap}
.d-pbtn.on{background:var(--d-accent); color:var(--d-on)}
.d-pbtn svg.i{width:15px; height:15px}
.d-pbtn.sm{height:30px; font-size:12px}
```
* `.d-btn` = 34px circle, borderless, 9% text-tint fill, hover 16%. `.lg` = 44px accent-filled (the "play" button).
* `.d-pbtn` = 36px tall pill-ish button that *fills the row* (`flex:1`), 9% tint, `.on` = accent fill + `--d-on` text.
  A row of them is a radio group. Icon + label inside, 15px icon.
* No borders anywhere in the preview button set. Depth comes from tint percentages: 5-6% (surfaces),
  8-9% (icon tiles, buttons), 11-12% (hover tiles), 14-16% (tracks, hover buttons), 18% (pressed).

Touch adaptation: `.d-btn` -> 44px, `.d-pbtn` -> `height:44px; font-size:13px`. Keep the tint recipe.

### Lit state (PREVIEW)

```css
.w-light.is-on{background:color-mix(in srgb, var(--d-active) 20%, var(--d-card))}
.w-light.is-on .d-ico{background:var(--d-active); color:var(--d-on); box-shadow:0 0 22px color-mix(in srgb, var(--d-active) 55%, transparent)}
.hrow.is-on{background:color-mix(in srgb, var(--d-active) 16%, transparent)}
.hrow.is-on .d-ico{background:var(--d-active); color:var(--d-on)}
.hub-tile.on{background:color-mix(in srgb, var(--d-active) 22%, transparent); border-color:color-mix(in srgb, var(--d-active) 50%, transparent)}
.w-lock.is-open .d-ico, .w-garage.is-open .d-ico{background:color-mix(in srgb, #ff9f40 28%, transparent); color:#ffb066}
```
"On" = card tinted 16-22% accent, icon tile goes solid accent with a soft 22px glow. "Open/unsafe" = icon tile tinted orange. A zone that is watering should look exactly like `.w-light.is-on`.

### Row-list variant (PREVIEW, `.hrow`)

```css
.hrow{display:grid; grid-template-columns:auto minmax(0,1fr) auto; align-items:center; gap:10px 12px; padding:12px; border-radius:calc(var(--d-radius) * .55); background:color-mix(in srgb, var(--d-text) 6%, transparent); border:1px solid var(--d-border); transition:background .2s}
.hr-n{min-width:0; display:flex; flex-direction:column; gap:2px}
.hr-n b{font-weight:var(--d-hw,600); white-space:nowrap; overflow:hidden; text-overflow:ellipsis}
.hr-n span{font-size:12px; color:var(--d-muted); white-space:nowrap; overflow:hidden; text-overflow:ellipsis}
.hr-c{display:flex; align-items:center; gap:6px}
.hr-x{grid-column:1 / -1; min-width:0}
.hr-val{font-family:var(--d-display); font-weight:600; min-width:3ch; text-align:center; font-variant-numeric:tabular-nums}
.posbar{height:6px; border-radius:6px; background:color-mix(in srgb, var(--d-text) 12%, transparent); overflow:hidden}
.posbar i{display:block; height:100%; background:var(--d-active); transition:width .4s}
```
`icon tile | name + status | controls` on one line, optional full-width second line (slider or bar). This is the shape for a zone list.

### Big tiles (PREVIEW, `.hub-tile`)

```css
.hub-tile{aspect-ratio:1; border:1px solid var(--d-border); background:color-mix(in srgb, var(--d-text) 6%, transparent); color:var(--d-text); border-radius:calc(var(--d-radius) * .8); padding:16px; display:flex; flex-direction:column; align-items:flex-start; text-align:left; gap:3px; min-width:0; transition:transform .15s, background .2s}
.hub-tile:hover{transform:translateY(-2px); background:color-mix(in srgb, var(--d-text) 11%, transparent)}
.ht-ico{width:46px; height:46px; border-radius:50%; display:grid; place-items:center; background:color-mix(in srgb, var(--d-text) 10%, transparent); margin-bottom:auto}
.ht-ico svg.i{width:23px; height:23px}
.ht-l{font-weight:700; font-size:15px}
.ht-s{font-size:12.5px; color:var(--d-muted); white-space:nowrap; overflow:hidden; text-overflow:ellipsis; max-width:100%}
```
Square, icon circle top-left, label + sub bottom-left. Good for a 2x2 "mode" chooser on a phone.

### Progress / bars

`.prog{height:4px}` (media), `.posbar{height:6px}` (shade position), `.v-bar{height:10px; border-radius:99px}` (range). Track = 10-14% text tint, fill = solid text or `--d-active`. Hearth bars have NO gradient (except the charging shimmer) and NO border.

---------------------------------------------------------------------------------------------------

## 9. Shadows

Where Hearth uses them (exact):

| element | shadow | why |
|---|---|---|
| `.seg button[aria-pressed]` | `0 1px 2px rgba(0,0,0,.08)` | the raised thumb |
| `.switch input::after` | `0 1px 2px rgba(0,0,0,.2)` | knob |
| `.sw` swatch | `0 0 0 1px var(--line)` / selected `0 0 0 2px var(--fg)` | ring, not depth |
| `.th/.fxb/.flagbtn[aria-pressed]`, `.pg-menu-btn[aria-expanded]` | `0 0 0 2px color-mix(accent 30%/25%)` | selection halo |
| `.pg-menu` | `0 18px 50px rgba(10,12,20,.22)` | popover floats |
| `.sheet` | `0 30px 80px rgba(0,0,0,.35)` | modal floats |
| `.toast` | `0 10px 30px rgba(0,0,0,.25)` | floats |
| `.tb` | `0 6px 20px rgba(0,0,0,.25)` | floats |
| `.rz` | `0 2px 8px rgba(0,0,0,.25)` | drag handle |
| `.dash` | `0 20px 60px rgba(10,12,20,.18)` | the canvas sits above the stage |
| `.card` | `var(--d-shadow)` (theme-defined; 'none' for Flat Black) | content, themed |
| `.w-light.is-on .d-ico` | `0 0 22px color-mix(active 55%)` | glow = on |
| `.ha-chip i` | `0 0 0 3px color-mix(#1f9d63 22%)` | halo = live |

Where it deliberately does NOT: `.top`, `.btn` (any state), `.lib-item` (even hovered, it lifts instead),
`.wel button`, `.twg`, `.libg`, `.field` inputs (focus is border-only), `.insp-head .ic`, `.score`, `pre.code`,
`.pg` pills, `.tabs`, `.rail`. The chrome is flat; **only things that float above the page** (popover,
sheet, toast, toolbar, the canvas) cast a shadow, and the shadow is always large-blur, low-alpha, offset
downward (y = blur/3). Halos (`0 0 0 Npx`) are used for *state*, not depth.

---------------------------------------------------------------------------------------------------

## 10. Focus, transitions, motion

```css
:focus-visible{outline:2px solid var(--accent); outline-offset:2px}
.name-in:focus, .field ...:focus, .search input:focus{border-color:var(--accent); outline:none}
@media (prefers-reduced-motion: reduce){ *{transition:none !important; animation:none !important} }
```
* Keyboard focus = 2px accent outline, 2px offset, on everything. Text fields swap it for an accent border
  (because the outline would double the border). Nothing else changes on focus - no glow, no fill.
* Transitions are short and specific, never `all`:
  `.lib-item{transition:border-color .15s, transform .15s}` `.card{transition:background .25s, outline-color .15s, opacity .2s}`
  `.switch input{transition:background .2s}` / `::after{transition:transform .2s}` `.hub-tile{transition:transform .15s, background .2s}`
  `.libg summary::before{transition:transform .2s}` `.frame{transition:max-width .3s ease}` `.dash{transition:background .5s, color .5s}`
  `.posbar i{transition:width .4s}` `.v-bar i{transition:width .8s ease}` `.blind .slats{transition:height .5s ease}`.
  Durations: 150ms for hover, 200ms for toggles/chevrons, 250-500ms for theme/colour, 400-800ms for physical things (bars, slats).
* Hover micro-motion: `translateY(-1px)` on chrome cards (`.lib-item`), `translateY(-2px)` on preview tiles
  (`.hub-tile`, `.ts-tile`). Buttons do NOT move on hover; they change border colour (`.btn`) or tint (`.d-btn`).
* Press: only via the opt-in `.fx-press` effect: `:active{transform:scale(.93); transition:transform .08s}`
  with a springy return `transition:transform .2s cubic-bezier(.3,1.6,.5,1)`. Keypad: `:active{background: 18% tint}`.
* Entrances: `@keyframes cardIn{from{opacity:0; transform:translateY(18px) scale(.97)}}` `.55s cubic-bezier(.2,.8,.2,1)` staggered `45ms` per card (opt-in).
* Attention: `@keyframes pulse{50%{opacity:.25; transform:scale(.7)}}` 1s on 8px dots; `@keyframes blink{50%{opacity:.25}}` 1.4s on the LIVE dot;
  `@keyframes shake{20%,60%{transform:translateX(-6px)} 40%,80%{transform:translateX(6px)}}` .4s on a wrong PIN.
* The easing vocabulary is exactly two curves: `cubic-bezier(.2,.8,.2,1)` (settle) and `cubic-bezier(.3,1.6,.5,1)` (spring); otherwise `ease`/`linear`.

---------------------------------------------------------------------------------------------------

## 11. Icon convention

```css
svg.i{width:18px; height:18px; fill:none; stroke:currentColor; stroke-width:1.8; stroke-linecap:round; stroke-linejoin:round; flex:none}
.dash svg.i{stroke-width:var(--d-isw,1.8)}
```
```js
const ic = (n, cls='') => `<svg class="i ${cls}" viewBox="0 0 24 24" aria-hidden="true">${P[n]||''}</svg>`;
```
* 24-unit viewBox, geometry drawn between 3 and 21 (2-3 unit safe margin), 1.8 stroke, round caps/joins,
  **no fill** except the play triangle (`fill="currentColor"`). Pause uses `stroke-width="3"` to read as two bars.
* Colour always comes from `currentColor`; the icon is never coloured directly - the *container* is
  (`.lib-item .ic{color:var(--accent)}`, `.group h3 svg.i{color:var(--magic)}`, `.chip svg.i{color:var(--d-accent)}`).
* Sizes by context: 12 (`.vis-badge`), 13 (`.v-tvtag`), 14 (`.chip`, `.room-stats`), 15 (`.tabs`, `.d-pbtn`, `.tb`, `.pg.add`),
  16 (`.mark`, `.search`, `.scn`, `.pg-menu-btn`, `.hub-scene`), 18 (default; `.btn`, `.fc`), 19 (`.d-ico`), 20 (`.ts-wx`),
  21 (`.rail`), 22 (`.hub-gn`), 23 (`.ht-ico`), 26 (`.ts-ico`), 34 (`.ts-art`), 46 (`.wx-main`, `.gn-ov` - hero icons use `stroke-width:1.5`).
* Placement: icon *before* text with gap 5-8px, both vertically centred via `display:flex; align-items:center` on the parent; `flex:none` so it never squishes.
* Icon tiles (icon inside a rounded square/circle):

| tile | size | radius | bg | glyph colour | glyph size |
|---|---|---|---|---|---|
| `.mark` | 28 | 9 | `--fg` | `--bg` | 16 |
| `.lib-item .ic` | 30 | 9 | `--bg` | `--accent` | 18 |
| `.insp-head .ic` | 36 | 10 | `--bg` | `--accent` | 18 |
| `.d-ico` | 38 | `calc(--d-radius*.5+4px)` | 8% text tint | `--d-text` | 19 |
| `.wel .wi` | 44 | 13 | `--panel` | `--accent` | 18 |
| `.insp-empty .ic` | 46 | 14 | `--bg` | `--accent` | 18 |
| `.ht-ico` | 46 | 50% | 10% text tint | `--d-text` | 23 |
| `.ts-ico` | 54 | 50% | 12% text tint | inherit | 26 |

  Chrome tiles: recessed `--bg` square, accent glyph. Preview tiles: text-tinted, text-coloured glyph; solid accent + `--d-on` glyph when "on".
* Icon-only buttons always carry `aria-label` and usually `title`.

### Icon path library (exact `d` strings - reuse these so glyphs match)

```
home     <path d="M3 11 12 4l9 7M5 10v10h14V10"/>
bulb     <path d="M9 18h6M10 21h4M12 3a6 6 0 0 0-4 10.5c.8.8 1 1.6 1 2.5h6c0-.9.2-1.7 1-2.5A6 6 0 0 0 12 3z"/>
thermo   <path d="M14 14.8V5a2 2 0 1 0-4 0v9.8a4 4 0 1 0 4 0z"/>
drop     <path d="M12 3s6 6.5 6 11a6 6 0 0 1-12 0c0-4.5 6-11 6-11z"/>
rain     <path d="M7 15h10a4 4 0 0 0 .5-8A6 6 0 0 0 6 6.5 4.3 4.3 0 0 0 7 15z"/><path d="M8 18l-1 3M12 18l-1 3M16 18l-1 3"/>
cloud    <path d="M7 18h10a4 4 0 0 0 .5-8A6 6 0 0 0 6 9.5 4.3 4.3 0 0 0 7 18z"/>
sun      <circle cx="12" cy="12" r="4"/><path d="M12 2v2M12 20v2M2 12h2M20 12h2M4.9 4.9l1.4 1.4M17.7 17.7l1.4 1.4M4.9 19.1l1.4-1.4M17.7 6.3l1.4-1.4"/>
moon     <path d="M20 14.5A8 8 0 1 1 9.5 4a6.5 6.5 0 0 0 10.5 10.5z"/>
clock    <circle cx="12" cy="12" r="9"/><path d="M12 7v5l3 2"/>
gauge    <path d="M4 17a8 8 0 1 1 16 0"/><path d="M12 17l4-5"/>
bolt     <path d="M13 2 4 14h7l-1 8 9-12h-7z"/>
pin      <path d="M12 21s-7-6.2-7-11.5A7 7 0 0 1 19 9.5C19 14.8 12 21 12 21z"/><circle cx="12" cy="9.5" r="2.5"/>
lock     <rect x="5" y="11" width="14" height="10" rx="2"/><path d="M8 11V7a4 4 0 0 1 8 0v4"/>
unlock   <rect x="5" y="11" width="14" height="10" rx="2"/><path d="M8 11V7a4 4 0 0 1 7.6-1.8"/>
play     <path d="M8 5v14l11-7z" fill="currentColor"/>
pause    <path d="M8 5v14M16 5v14" stroke-width="3"/>
stop     <rect x="7" y="7" width="10" height="10" rx="1.5"/>
prev     <path d="M18 6v12l-9-6zM6 6v12"/>
next     <path d="M6 6v12l9-6zM18 6v12"/>
left     <path d="M15 6l-6 6 6 6"/>
right    <path d="M9 6l6 6-6 6"/>
up       <path d="M6 15l6-6 6 6"/>
down     <path d="M6 9l6 6 6-6"/>
plus     <path d="M12 5v14M5 12h14"/>
minus    <path d="M5 12h14"/>
close    <path d="M6 6l12 12M18 6 6 18"/>
copy     <rect x="8" y="8" width="12" height="12" rx="2"/><path d="M16 8V5a1 1 0 0 0-1-1H5a1 1 0 0 0-1 1v10a1 1 0 0 0 1 1h3"/>
trash    <path d="M4 7h16M10 11v6M14 11v6M6 7l1 13h10l1-13M9 7V4h6v3"/>
pencil   <path d="M4 20h4L19 9l-4-4L4 16z"/>
eye      <path d="M2 12s3.5-7 10-7 10 7 10 7-3.5 7-10 7S2 12 2 12z"/><circle cx="12" cy="12" r="3"/>
search   <circle cx="11" cy="11" r="7"/><path d="M20 20l-4-4"/>
sparkle  <path d="M12 3l1.8 5.2L19 10l-5.2 1.8L12 17l-1.8-5.2L5 10l5.2-1.8z"/><path d="M19 16v4M17 18h4"/>
magic    <path d="M4 20 15 9M14 4v2M19 9h2M17.5 5.5l1.5-1.5"/>
list     <path d="M8 6h13M8 12h13M8 18h13M3 6h.01M3 12h.01M3 18h.01"/>
grid     <rect x="3" y="3" width="7" height="7" rx="1.5"/><rect x="14" y="3" width="7" height="7" rx="1.5"/><rect x="3" y="14" width="7" height="7" rx="1.5"/><rect x="14" y="14" width="7" height="7" rx="1.5"/>
add-grid <rect x="3" y="3" width="7" height="7" rx="1.5"/><rect x="14" y="3" width="7" height="7" rx="1.5"/><rect x="3" y="14" width="7" height="7" rx="1.5"/><path d="M17.5 14v7M14 17.5h7"/>
palette  <path d="M12 3a9 9 0 1 0 0 18c1.1 0 1.6-.8 1.6-1.6 0-1.3-1-1.6-1-2.8 0-1 .8-1.6 1.8-1.6H17a4 4 0 0 0 4-4C21 6.6 17 3 12 3z"/>
download <path d="M12 3v12M7 10l5 5 5-5M5 21h14"/>
expand   <path d="M4 9V4h5M20 9V4h-5M4 15v5h5M20 15v5h-5"/>
undo     <path d="M9 14 4 9l5-5"/><path d="M4 9h11a5 5 0 0 1 0 10h-3"/>
redo     <path d="M15 14l5-5-5-5"/><path d="M20 9H9a5 5 0 0 0 0 10h3"/>
image    <rect x="3" y="4" width="18" height="16" rx="2"/><path d="m3 16 5-5 4 4 3-3 6 6"/>
desktop  <rect x="3" y="4" width="18" height="12" rx="2"/><path d="M8 20h8M12 16v4"/>
tablet   <rect x="5" y="3" width="14" height="18" rx="2"/><path d="M11 18h2"/>
phone    <rect x="7" y="3" width="10" height="18" rx="2"/><path d="M11 18h2"/>
cam      <path d="M3 8h3l2-3h8l2 3h3v11H3z"/><circle cx="12" cy="13" r="3.5"/>
blinds   <path d="M4 3h16M5 3v18M19 3v18M5 7h14M5 11h14M5 15h14"/><path d="M12 15v4"/>
vacuum   <circle cx="12" cy="12" r="9"/><circle cx="12" cy="12" r="3"/><path d="M12 3v3M7 17.5l1.5-1.5"/>
door     <path d="M5 21V4a1 1 0 0 1 1-1h12a1 1 0 0 1 1 1v17M3 21h18"/><circle cx="15" cy="12" r="1"/>
music    <path d="M9 18V5l11-2v13"/><circle cx="6" cy="18" r="3"/><circle cx="17" cy="16" r="3"/>
film     <rect x="3" y="4" width="18" height="16" rx="2"/><path d="M7 4v16M17 4v16M3 9h4M3 15h4M17 9h4M17 15h4"/>
coffee   <path d="M4 9h13v5a5 5 0 0 1-5 5H9a5 5 0 0 1-5-5z"/><path d="M17 10h1.5a2.5 2.5 0 0 1 0 5H17M8 3v3M12 3v3"/>
sofa     <path d="M4 11V8a2 2 0 0 1 2-2h12a2 2 0 0 1 2 2v3"/><path d="M2 13a2 2 0 0 1 4 0v2h12v-2a2 2 0 0 1 4 0v5H2z"/><path d="M5 18v2M19 18v2"/>
car      <path d="M3 16v-3l2.5-5h13L21 13v3z"/><path d="M3 13h18"/><circle cx="7.5" cy="17" r="1.8"/><circle cx="16.5" cy="17" r="1.8"/>
```
For an irrigation product the obvious additions, drawn in the same idiom (single stroke, round caps, 3-21 box):
sprinkler/zone (`drop` or a `pin`), calendar (`<rect x="3" y="5" width="18" height="16" rx="2"/><path d="M3 10h18M8 3v4M16 3v4"/>`),
folder (`<path d="M3 6a1 1 0 0 1 1-1h5l2 2h9a1 1 0 0 1 1 1v11a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1z"/>`),
file (`<path d="M6 3h8l4 4v13a1 1 0 0 1-1 1H6a1 1 0 0 1-1-1V4a1 1 0 0 1 1-1z"/><path d="M14 3v4h4"/>`),
upload (`<path d="M12 15V3M7 8l5-5 5 5M5 21h14"/>`), check (`<path d="M5 12l4 4L19 7"/>`),
refresh (`<path d="M20 12a8 8 0 1 1-2.3-5.7"/><path d="M20 4v5h-5"/>`), gear (`<circle cx="12" cy="12" r="3"/><path d="M12 2v3M12 19v3M2 12h3M19 12h3M4.9 4.9l2.1 2.1M17 17l2.1 2.1M4.9 19.1 7 17M17 7l2.1-2.1"/>`),
wifi (`<path d="M2 9a15 15 0 0 1 20 0M5.5 12.5a10 10 0 0 1 13 0M9 16a5 5 0 0 1 6 0"/><circle cx="12" cy="19" r="1"/>`),
rotate-cw (`<path d="M21 12a9 9 0 1 1-3-6.7"/><path d="M21 3v6h-6"/>`), rotate-ccw (`<path d="M3 12a9 9 0 1 0 3-6.7"/><path d="M3 3v6h6"/>`).

Sprite form for a self-contained page: put `<svg aria-hidden="true" width="0" height="0" style="position:absolute">` right after `<body>`
with one `<symbol id="i-NAME" viewBox="0 0 24 24">...</symbol>` per glyph, then `<svg class="i"><use href="#i-NAME"/></svg>`.
The `svg.i` rule supplies stroke/fill, so symbols contain bare paths only (keep `fill="currentColor"` on play, `stroke-width="3"` on pause).

---------------------------------------------------------------------------------------------------

## 12. Ten rules of thumb that make it Hearth and not "an admin UI"

1. **Panel-on-ground, border-not-shadow.** Surfaces are `--panel` on a `--bg` page separated by 1px `--line`.
   Cards, buttons, bars, panes: 1px border, zero shadow. Shadows exist only on things that float (sheet, popover, toast, toolbar).
2. **Recess the inputs, raise the buttons.** Fields and segmented-control tracks are `--bg` *inside* a `--panel`
   surface (they sink); buttons are `--panel` (they sit level). Same two colours, opposite nesting, and that is the whole depth model.
3. **One accent, two jobs.** Accent fills exactly one `.primary` button per view and marks *selection*
   (accent border + 2px 25-30% halo; accent-tinted 10-13% ground; accent icon in the selected nav item).
   Active tabs, active page pills, the brand mark and the toast are **inverted fg/bg**, not accent. Violet (`--magic`/`--pond`) is only for "the machine does it for you".
4. **Radius nests: outer minus padding.** 10 -> 7 (seg), 12 -> 9 (card -> icon tile), 18 -> 14/10 (sheet -> inner).
   Buttons 10, inputs 9, cards 12, big choices 16, sheets 18, pills 99. In the preview, child radii are `calc(var(--d-radius) * k + n)`, never fixed.
5. **Status is a tint, never a fill.** ok/warn/bad = colour at 18-24% behind text in the same colour (mixed 65% into
   text in the preview). Danger buttons are red *text* on the normal outlined button. The only solid colour fills are accent (primary / on-state) and the inverted fg tiles.
6. **Three faces, strict jobs.** Display (Bricolage) for headings 16px+ and big numbers only, tight-tracked (-.01 to -.04em).
   Body (Geist) for everything else, 11-15px, weights 500/600 for labels and names, 400 for hints. Mono (Geist Mono) for ids, values, timestamps, code - and every changing number is `tabular-nums`.
7. **Muted does the hierarchy.** There is one grey (`--muted`). Labels, hints, descriptions, inactive tabs,
   inactive nav, icon-button glyphs, chevrons are all `--muted`; the thing you are looking at is `--fg`. No third grey, no opacity tricks (except `disabled{opacity:.45}`).
8. **Icons are 1.8px strokes in currentColor, inside tinted tiles.** Every glyph is a 24-box stroke path, 18px by
   default, coloured by its container, usually sitting in a 30-46px rounded tile (chrome: recessed `--bg` + accent glyph; preview: 8-12% text tint + text glyph, solid accent when on). Never emoji, never filled icons, never coloured per-icon.
9. **Card grammar: top row (icon tile | state) -> name + muted label -> visual -> action row pinned to the bottom.**
   Actions are borderless tint buttons: round 34/44px for steppers, 36px full-width `.d-pbtn` radio rows for modes, a 40x24 toggle for on/off. "On" tints the whole card 16-22% accent and makes the icon tile glow.
10. **Motion is tiny, specific and optional.** Hover lifts cards 1-2px and recolours borders, nothing else moves.
    Transitions name their property (150ms hover, 200ms toggle, 400-800ms physical). Two easings: `cubic-bezier(.2,.8,.2,1)` and the spring `cubic-bezier(.3,1.6,.5,1)`. `prefers-reduced-motion` kills everything. Sentence-case copy, no colons after labels, no exclamation marks, toasts are one plain sentence.

Bonus tells: `aria-pressed` / `aria-selected` / `aria-expanded` carry state instead of `.active` classes;
dashed 1.5-2px borders mean "empty / drop here" and nothing else; `<details>` with a CSS-drawn 7px chevron for
collapsible groups; `.hint` directly under every non-obvious control; safe-area insets on every fixed bar.

---------------------------------------------------------------------------------------------------

## 13. Quick translation table for the irrigoto pages (Muscovy-era class -> Hearth equivalent)

| current | re-skin as |
|---|---|
| `.btn` / `.btn-primary` / `.btn-green` | `.btn` / `.btn.primary` (accent fill) - touch padding `10px 14px` |
| `.btn-red` / `.btn-danger` | `.btn.danger` (red text, outlined) with two-step confirm if destructive |
| `.mode-btn`, `.day-preset` (mutually exclusive) | `.seg` + `button[aria-pressed]`, or `.d-pbtn` row (`.on`) when it is a device mode |
| `.sbtn` d-pad / arrows | `.d-btn` 44px circle, tint fill, `aria-label`, chevron glyphs `up/down/left/right` |
| `.card`, `.zone-card`, `.status-card`, `.upload-card` | chrome: 1px `--border`, radius 12, `--bg2` fill, no shadow; live zone tile: preview `.card` grammar with `.d-top`/`.d-ico`/`.pill` |
| `.sec-hdr` / `.sec-title` | `.group` with `.eyebrow` (settings) or `h3` + icon (feature); or `.pane-title` for the page h2 |
| `.dev-row` / `.dev-label` / `.dev-val` | `.row` with 12.5/500 label and mono `.val` (tabular) |
| `.hint`, `.note` | `.hint` (12.5px muted, lh 1.5) |
| `.empty`, `.dp-empty` | `.insp-empty` (dashed 1.5px, radius 16, icon tile, display h2) |
| `.status-msg`, `.upload-status` | `.ai-status` with `.dotpulse` while busy; `.pill.ok/.warn/.bad` for results |
| `.prog-wrap/.prog-fill`, `.bar-wrap/.bar-fill`, `.watering-bar` | `.posbar` (6px, 12% tint track, accent fill, `transition:width .4s`) |
| `.theme-switch/.theme-slider` | `.switch` (38x22) or a `.seg` with sun/moon icons |
| `.toggle-row` | `label.switch` with `<span><b>title</b><small>explainer</small></span>` |
| `.save-bar` | fixed bottom bar styled like `.mnav` (panel, 1px top line, safe-area padding) holding a `.btn.primary.block` |
| `.logo` + `.hdr-title` + `.back` | `.top` with `.brand` (`.mark` inverted tile + display-face text) and a `.btn.icon` back chevron |
| `.tree`, `.file-name/.file-size`, `.dir-name` | `.hrow`-style rows: icon tile | name + mono size | `.btn.icon` actions |
| `.enc-box/.enc-val/.enc-name` | `.score`-style recessed strip, or `.d-big` + `.d-label` reading tile |
| emoji icons | sprite `<use href="#i-...">` glyphs from section 11, in tiles per the table |
