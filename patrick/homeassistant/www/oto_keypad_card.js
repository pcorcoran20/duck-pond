/*  OtO keypad card -- drive the joystick scripts from the keyboard.
 *
 *  Install (once):
 *    1. copy this file to  config/www/oto_keypad_card.js
 *    2. Settings -> Dashboards -> (top-right menu) Resources -> Add resource
 *         URL:  /local/oto_keypad_card.js?v=5   type: JavaScript module
 *       HA serves /local/ files with a 31-day browser cache, so every time
 *       you update this file bump the ?v= number on the resource URL (match
 *       OTO_CARD_VERSION below) or the browser keeps running the old copy.
 *       The grey hint line at the bottom of the card shows which version
 *       is actually running.  Companion app: Settings -> Companion App ->
 *       Debugging -> Reset frontend cache.
 *    3. add a Manual card:   type: custom:oto-keypad-card
 *
 *  Keys (while the dashboard is on screen and no text box has focus):
 *    arrows        left / right / further / closer   (script.oto_left ...)
 *    Enter, Space  ON (aim + open)         Esc, X   OFF
 *    S             Sweep                   W        Swing
 *    H             Hold (stop the swing, keep watering)
 *    P             Pool clean              M        toggle Mirror
 *    A             add the current aim to the pool outline;  Z  undo
 *  While a swing/sweep runs, the arrows move it (firmware b552+).
 *
 *  Mirror is applied inside the HA scripts, so buttons and keys agree.
 */
const OTO_CARD_VERSION = 5;
const OTO_KEYS = {
  ArrowLeft: 'oto_left',  ArrowRight: 'oto_right',
  ArrowUp:   'oto_up',    ArrowDown:  'oto_down',
  Enter:     'oto_on',    ' ':        'oto_on',
  Escape:    'oto_off',   x:          'oto_off',
  s:         'oto_sweep', w:          'oto_swing',
  h:         'oto_hold',  p:          'oto_pool_clean',
  m:         'oto_mirror_toggle',
  a:         'oto_pool_point_add', z: 'oto_pool_point_undo',
};

class OtoKeypadCard extends HTMLElement {
  setConfig(config) { this._config = config || {}; }
  getCardSize()     { return 3; }

  set hass(hass) {
    this._hass = hass;
    this._render();
  }

  connectedCallback() {
    this._onKey = (e) => this._handleKey(e);
    window.addEventListener('keydown', this._onKey);
    this._render();
  }
  disconnectedCallback() {
    window.removeEventListener('keydown', this._onKey);
  }

  _typingSomewhere(e) {
    const path = e.composedPath ? e.composedPath() : [e.target];
    return path.some((el) => {
      const tag = (el && el.tagName || '').toLowerCase();
      return tag === 'input' || tag === 'textarea' || tag === 'select' ||
             (el && el.isContentEditable === true);
    });
  }

  _handleKey(e) {
    if (!this._hass || e.repeat) return;              // hold-to-repeat would flood the device
    if (e.ctrlKey || e.metaKey || e.altKey) return;
    if (this.offsetParent === null) return;           // card not on the visible view
    if (this._typingSomewhere(e)) return;
    const key = e.key.length === 1 ? e.key.toLowerCase() : e.key;
    const script = OTO_KEYS[key];
    if (!script) return;
    e.preventDefault();
    this._hass.callService('script', script, {});
    this._last = key === ' ' ? 'Space' : key;
    this._flash = Date.now();
    this._render();
  }

  _state(id, fallback = '?') {
    const st = this._hass && this._hass.states[id];
    return st ? st.state : fallback;
  }

  // Build the card ONCE and then only patch the text fields that changed.
  // HA pushes a new `hass` object several times a second; replacing the
  // whole <ha-card> each time made translucent / blurred themes flicker.
  _build() {
    const title = (this._config && this._config.title) || 'OtO keyboard';
    this.innerHTML = `
      <ha-card>
        <div style="padding:0 16px 16px; font-family:inherit">
          <div style="display:flex; gap:16px; flex-wrap:wrap; margin-bottom:8px">
            <span>Bearing <b data-f="bearing"></b></span>
            <span>Throw <b data-f="throw"></b></span>
            <span>Step <b data-f="step"></b></span>
            <span>Watering <b data-f="watering"></b></span>
            <span data-f="mirror-wrap">Mirror <b data-f="mirror"></b></span>
          </div>
          <table style="border-collapse:collapse; line-height:1.7">
            <tr><td><kbd>\u2190</kbd> <kbd>\u2192</kbd></td><td style="padding-left:12px" data-f="rotate"></td></tr>
            <tr><td><kbd>\u2191</kbd> <kbd>\u2193</kbd></td><td style="padding-left:12px" data-f="updown"></td></tr>
            <tr><td><kbd>Enter</kbd> <kbd>Space</kbd></td><td style="padding-left:12px">ON (aim here)</td></tr>
            <tr><td><kbd>Esc</kbd> <kbd>X</kbd></td><td style="padding-left:12px">OFF</td></tr>
            <tr><td><kbd>S</kbd></td><td style="padding-left:12px">Sweep the sector</td></tr>
            <tr><td><kbd>W</kbd></td><td style="padding-left:12px" data-f="swing"></td></tr>
            <tr><td><kbd>H</kbd></td><td style="padding-left:12px">Hold: stop the swing, keep watering</td></tr>
            <tr><td><kbd>P</kbd></td><td style="padding-left:12px" data-f="pool"></td></tr>
            <tr><td><kbd>M</kbd></td><td style="padding-left:12px">toggle Mirror</td></tr>
            <tr><td><kbd>A</kbd> <kbd>Z</kbd></td><td style="padding-left:12px" data-f="outline"></td></tr>
          </table>
          <div style="margin-top:8px; color:var(--secondary-text-color); font-size:0.9em" data-f="hint"></div>
        </div>
      </ha-card>`;
    this.querySelector('ha-card').setAttribute('header', title);
    this._f = {};
    this.querySelectorAll('[data-f]').forEach((el) => { this._f[el.dataset.f] = el; });
    this._shown = {};
  }

  _set(field, text) {
    if (this._shown[field] === text) return;      // untouched DOM = no repaint
    this._shown[field] = text;
    this._f[field].textContent = text;
  }

  _render() {
    if (!this._hass) return;
    if (!this._f) this._build();
    const mirror  = this._state('input_boolean.oto_mirror') === 'on';
    const bearing = this._state('input_number.oto_bearing');
    const throwFt = this._state('input_number.oto_throw_ft');
    const stepDeg = this._state('input_number.oto_step_deg');
    const stepFt  = this._state('input_number.oto_step_ft');
    const presses = this._state('input_number.oto_swing_presses');
    const poolMin = this._state('input_number.oto_pool_minutes');
    const outline = this._state('sensor.oto_pool_outline_summary', '');
    const watering = this._state('binary_sensor.irrigoto_43c89c_irrigoto_watering', 'unknown');
    const l = mirror ? '\u2192' : '\u2190', r = mirror ? '\u2190' : '\u2192';
    const u = mirror ? 'closer' : 'further', d = mirror ? 'further' : 'closer';
    this._set('bearing',  `${bearing}\u00b0`);
    this._set('throw',    `${throwFt} ft`);
    this._set('step',     `${stepDeg}\u00b0 / ${stepFt} ft`);
    this._set('watering', watering);
    this._set('mirror',   mirror ? 'ON' : 'off');
    this._set('rotate',   `rotate ${l} / ${r} by ${stepDeg}\u00b0 (moves a running swing too)`);
    this._set('updown',   `${u} / ${d} by ${stepFt} ft`);
    this._set('swing',    `Swing ${presses} presses either side`);
    this._set('pool',     `Pool clean for ${poolMin} min`);
    this._set('outline',  `add / undo a pool outline point (${outline || 'no outline yet'})`);
    this._set('hint',     (this._last ? `last key: ${this._last}`
                                      : 'Click anywhere on the page first, then use the keys.')
                          + `  \u00b7 card v${OTO_CARD_VERSION}`);
    const mirrorColor = mirror ? 'var(--warning-color)' : '';
    if (this._shown.mirrorColor !== mirrorColor) {
      this._shown.mirrorColor = mirrorColor;
      this._f['mirror-wrap'].style.color = mirrorColor;
    }
  }
}

if (!customElements.get('oto-keypad-card')) {
  customElements.define('oto-keypad-card', OtoKeypadCard);
}
window.customCards = window.customCards || [];
window.customCards.push({
  type: 'oto-keypad-card',
  name: 'OtO keypad',
  description: 'Arrow-key control of the OtO joystick scripts (mirror, sweep, swing).',
});
