/*  OtO keypad card -- drive the joystick scripts from the keyboard.
 *
 *  Install (once):
 *    1. copy this file to  config/www/oto_keypad_card.js
 *    2. Settings -> Dashboards -> (top-right menu) Resources -> Add resource
 *         URL:  /local/oto_keypad_card.js      type: JavaScript module
 *       (reload the browser tab afterwards)
 *    3. add a Manual card:   type: custom:oto-keypad-card
 *
 *  Keys (while the dashboard is on screen and no text box has focus):
 *    arrows        left / right / further / closer   (script.oto_left ...)
 *    Enter, Space  ON (aim + open)         Esc, X   OFF
 *    S             Sweep                   W        Swing
 *    M             toggle Mirror (input_boolean.oto_mirror)
 *
 *  Mirror is applied inside the HA scripts, so buttons and keys agree.
 */
const OTO_KEYS = {
  ArrowLeft: 'oto_left',  ArrowRight: 'oto_right',
  ArrowUp:   'oto_up',    ArrowDown:  'oto_down',
  Enter:     'oto_on',    ' ':        'oto_on',
  Escape:    'oto_off',   x:          'oto_off',
  s:         'oto_sweep', w:          'oto_swing',
  m:         'oto_mirror_toggle',
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

  _render() {
    if (!this._hass) return;
    const mirror  = this._state('input_boolean.oto_mirror') === 'on';
    const bearing = this._state('input_number.oto_bearing');
    const throwFt = this._state('input_number.oto_throw_ft');
    const stepDeg = this._state('input_number.oto_step_deg');
    const stepFt  = this._state('input_number.oto_step_ft');
    const presses = this._state('input_number.oto_swing_presses');
    const watering = this._state('binary_sensor.irrigoto_43c89c_irrigoto_watering', 'unknown');
    const l = mirror ? '→' : '←', r = mirror ? '←' : '→';
    const u = mirror ? 'closer' : 'further', d = mirror ? 'further' : 'closer';
    const title = (this._config && this._config.title) || 'OtO keyboard';
    this.innerHTML = `
      <ha-card header="${title}">
        <div style="padding:0 16px 16px; font-family:inherit">
          <div style="display:flex; gap:16px; flex-wrap:wrap; margin-bottom:8px">
            <span>Bearing <b>${bearing}°</b></span>
            <span>Throw <b>${throwFt} ft</b></span>
            <span>Step <b>${stepDeg}° / ${stepFt} ft</b></span>
            <span>Watering <b>${watering}</b></span>
            <span style="${mirror ? 'color:var(--warning-color)' : ''}">Mirror <b>${mirror ? 'ON' : 'off'}</b></span>
          </div>
          <table style="border-collapse:collapse; line-height:1.7">
            <tr><td><kbd>←</kbd> <kbd>→</kbd></td><td style="padding-left:12px">rotate ${l} / ${r} by ${stepDeg}°</td></tr>
            <tr><td><kbd>↑</kbd> <kbd>↓</kbd></td><td style="padding-left:12px">${u} / ${d} by ${stepFt} ft</td></tr>
            <tr><td><kbd>Enter</kbd> <kbd>Space</kbd></td><td style="padding-left:12px">ON (aim here)</td></tr>
            <tr><td><kbd>Esc</kbd> <kbd>X</kbd></td><td style="padding-left:12px">OFF</td></tr>
            <tr><td><kbd>S</kbd></td><td style="padding-left:12px">Sweep the sector</td></tr>
            <tr><td><kbd>W</kbd></td><td style="padding-left:12px">Swing ${presses} presses either side</td></tr>
            <tr><td><kbd>M</kbd></td><td style="padding-left:12px">toggle Mirror</td></tr>
          </table>
          <div style="margin-top:8px; color:var(--secondary-text-color); font-size:0.9em">
            ${this._last ? `last key: <b>${this._last}</b>` : 'Click anywhere on the page first, then use the keys.'}
          </div>
        </div>
      </ha-card>`;
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
