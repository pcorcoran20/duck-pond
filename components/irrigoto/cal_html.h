/* Auto-generated from cal.html -- edit the .html, then run regen.py */
#ifdef IRRIGOTO_HTML_PAYLOAD
R"CALHTML(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no">
<title>Calibration</title>
<script>
(function(){
  try{var t=localStorage.getItem('irrigoto_theme');
    if(t==='light'||t==='dark')document.documentElement.dataset.theme=t;}catch(e){}
  fetch('/api/theme').then(function(r){return r.json();}).then(function(d){
    var t2=d.dark?'dark':'light';
    if(document.documentElement.dataset.theme!==t2){
      document.documentElement.dataset.theme=t2;
      try{localStorage.setItem('irrigoto_theme',t2);}catch(e){}}
  }).catch(function(){});
})();
// b532: set the device clock from this phone (as landing/schedule, b437), so
// ANY page opened after a power loss with no HA gives the unit a clock.
(function(){try{fetch('/api/time',{method:'POST',
  headers:{'Content-Type':'application/x-www-form-urlencoded'},
  body:'epoch='+Math.floor(Date.now()/1000)+'&tz='+(-new Date().getTimezoneOffset())
}).catch(function(){});}catch(e){}})();
// b535: winter mode -- the only allowed action is exiting winter, which
// lives on the home page. Lock this page (banner + no clicks + disabled
// controls, including ones this page renders later).
(function(){
  function lock(){
    fetch('/api/all').then(function(r){return r.json();}).then(function(d){
      if(!d||!d.winter)return;
      var st=document.createElement('style');
      st.textContent='body.winter-lock{pointer-events:none}body.winter-lock #winter-lock{pointer-events:auto}'
        +'body.winter-lock button,body.winter-lock input,body.winter-lock select,body.winter-lock canvas,body.winter-lock svg{opacity:.45}';
      document.head.appendChild(st);
      var b=document.createElement('div'); b.id='winter-lock';
      b.style.cssText='position:sticky;top:0;z-index:9999;margin:8px 12px;padding:10px 12px;border-radius:var(--radius-sm);background:var(--green-dim);color:var(--text);border:1px solid var(--border);font:600 14px var(--font)';
      b.innerHTML='&#10052; Winter sleep active — controls are disabled. <a href="/" style="color:var(--green)">Go to the home page to resume normal operation</a>.';
      document.body.prepend(b); document.body.classList.add('winter-lock');
      var off=function(){document.querySelectorAll('button,input,select,textarea').forEach(function(e){e.disabled=true;});};
      off(); new MutationObserver(off).observe(document.body,{childList:true,subtree:true});
    }).catch(function(){});
  }
  if(document.readyState==='loading')document.addEventListener('DOMContentLoaded',lock);else lock();
})();
</script>
<!-- Hearth's faces, matching the dashboard studio. Non-blocking: on the setup
     hotspot there is no internet, so this must never hold up first paint --
     media="print" keeps it off the critical path and onload promotes it. The
     system stack in --font/--display/--mono covers the offline case. -->
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link rel="stylesheet" media="print" onload="this.media='all'"
      href="https://fonts.googleapis.com/css2?family=Bricolage+Grotesque:opsz,wght@12..96,500..800&family=Geist:wght@400..700&family=Geist+Mono:wght@400..600&display=swap">
<style>
/* ---- Muscovy design system ------------------------------------------ */
*{box-sizing:border-box;margin:0;padding:0;-webkit-tap-highlight-color:transparent;}
:root,:root[data-theme="dark"]{
  color-scheme:dark;
  --bg:#0e1014;--bg2:#15181e;--bg3:#1c2028;
  --green:#8a94ff;--green-dim:#222842;--green-glow:rgba(138,148,255,.28);
  --accent-ink:#0e1014;
  --pond:#b49bff;--pond-dim:rgba(180,155,255,.16);
  --orange:#ff9f40;--orange-dim:rgba(255,159,64,.14);
  --red:#ff5a5a;--red-dim:rgba(255,90,90,.14);
  --ok:#2fc77a;--ok-dim:rgba(47,199,122,.22);
  --text:#eceef3;--text-mid:#8c92a1;--text-dim:#4d5461;
  --border:#252932;--btn:#15181e;--btn-hover:#1c2028;
  --radius:14px;--radius-sm:10px;
  --radar-bg:#0a0c0f;--radar-grid:#272c38;
  --shadow:0 1px 2px rgba(0,0,0,.25),0 10px 30px -18px rgba(0,0,0,.65);
  /* Hearth's faces, then system fallbacks: the device serves these pages from
     its own AP, which has no internet, so we never link Google Fonts. */
  --font:"Geist","Inter",system-ui,-apple-system,"Segoe UI",Roboto,"Helvetica Neue",sans-serif;
  --display:"Bricolage Grotesque","Geist",system-ui,-apple-system,"Segoe UI",Roboto,sans-serif;
  --mono:"Geist Mono",ui-monospace,"SF Mono","Cascadia Mono","JetBrains Mono",Menlo,Consolas,monospace;
}
:root[data-theme="light"]{
  color-scheme:light;
  --bg:#f3f4f7;--bg2:#ffffff;--bg3:#e9ebf0;
  --green:#4352f0;--green-dim:#dcdff6;--green-glow:rgba(67,82,240,.22);
  --accent-ink:#ffffff;
  --pond:#7b4dff;--pond-dim:rgba(123,77,255,.12);
  --orange:#c87210;--orange-dim:rgba(200,114,16,.12);
  --red:#d23b3b;--red-dim:rgba(210,59,59,.10);
  --ok:#1f9d63;--ok-dim:rgba(31,157,99,.18);
  --text:#15171c;--text-mid:#666c7a;--text-dim:#9aa0ad;
  --border:#e2e4ea;--btn:#ffffff;--btn-hover:#eef0f4;
  --radar-bg:#e9ebf0;--radar-grid:#c5cbd8;
  --shadow:0 1px 2px rgba(16,18,26,.05),0 10px 30px -18px rgba(16,18,26,.28);
}
html,body{background:var(--bg);}
body{color:var(--text);font:15px/1.45 var(--font);-webkit-font-smoothing:antialiased;}
button,input,select,textarea{font:inherit;color:inherit;}
button{cursor:pointer;}
a{color:var(--green);}
:focus-visible{outline:2px solid var(--green);outline-offset:2px;}
::selection{background:var(--green-dim);}

/* top bar, shared by every page */
header{display:flex;align-items:center;gap:12px;padding:14px 18px 12px;
  border-bottom:1px solid var(--border);background:var(--bg);flex-shrink:0;}
.back{display:inline-flex;align-items:center;justify-content:center;width:34px;height:34px;
  border-radius:50%;border:1px solid var(--border);background:var(--bg2);color:var(--text);
  text-decoration:none;font-size:18px;line-height:1;flex-shrink:0;}
.back:active{background:var(--bg3);}
.logo{display:inline-flex;align-items:center;gap:8px;font-family:var(--display);font-weight:700;font-size:17px;
  letter-spacing:-.01em;color:var(--text);text-decoration:none;white-space:nowrap;}
.logo .duck{flex-shrink:0;}
.hdr-title,.header-mid{font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;
  color:var(--text-mid);flex:1;min-width:0;overflow:hidden;text-overflow:ellipsis;white-space:nowrap;}
.page-logo{display:none;}
#conn,.usage{display:flex;align-items:center;gap:6px;font-size:12px;color:var(--text-mid);margin-left:auto;white-space:nowrap;}
.usage{font-size:11px;max-width:42%;overflow:hidden;text-overflow:ellipsis;display:block;}
#conn-dot{width:8px;height:8px;border-radius:50%;background:var(--text-dim);transition:all .4s;flex-shrink:0;}
#conn-dot.ok{background:var(--ok);box-shadow:0 0 0 3px var(--ok-dim);}
#conn-dot.err{background:var(--red);box-shadow:0 0 0 3px var(--red-dim);}

/* sections and cards */
main{padding:18px 18px 28px;}
section{margin-bottom:22px;}
.sec-hdr{display:flex;align-items:center;justify-content:space-between;margin:0 2px 10px;gap:10px;}
.sec-title{font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;color:var(--text-mid);}
.sec-btn,#refresh-btn{font-size:13px;font-weight:600;color:var(--green);background:var(--bg2);
  padding:6px 12px;border-radius:999px;cursor:pointer;border:1px solid var(--border);text-decoration:none;}
.sec-btn:active,#refresh-btn:active{background:var(--green-dim);}
.card,.status-card,.upload-card{background:var(--bg2);border:1px solid var(--border);
  border-radius:var(--radius);padding:16px;margin-bottom:12px;box-shadow:var(--shadow);}
.empty{color:var(--text-mid);font-size:14px;padding:6px 0;text-align:center;}
.hint,.note,.cal-desc{font-size:13px;color:var(--text-mid);line-height:1.55;}
.note,.cal-desc{margin-bottom:12px;}

/* buttons */
.btn{display:inline-flex;align-items:center;justify-content:center;gap:6px;padding:10px 16px;
  border-radius:var(--radius-sm);border:1px solid var(--border);background:var(--btn);color:var(--text);
  font-size:13.5px;font-weight:500;cursor:pointer;text-decoration:none;white-space:nowrap;
  transition:background .12s,transform .06s;}
.btn:active{background:var(--btn-hover);transform:translateY(1px);}
.btn:disabled{opacity:.45;cursor:default;transform:none;}
.btn-primary,.btn-green{background:var(--green);border-color:var(--green);color:var(--accent-ink);}
.btn-primary:active,.btn-green:active{filter:brightness(.92);background:var(--green);}
.btn-danger,.btn-red{color:var(--red);border-color:var(--red);background:transparent;}
.btn-danger:active,.btn-red:active{background:var(--red-dim);}

/* fields */
input[type=text],input[type=number],input[type=time],select,.throw-inp,.path-inp,.file-inp{
  background:var(--bg);border:1px solid var(--border);border-radius:var(--radius-sm);
  color:var(--text);font-size:15px;padding:10px 12px;width:100%;}
input:focus,select:focus{outline:2px solid var(--green);outline-offset:-1px;border-color:transparent;}
input::placeholder{color:var(--text-dim);}

/* toggle switch */
.theme-switch{position:relative;display:inline-block;width:46px;height:26px;vertical-align:middle;flex-shrink:0;}
.theme-switch input{opacity:0;width:0;height:0;}
.theme-slider{position:absolute;cursor:pointer;inset:0;background:var(--bg3);transition:.25s;
  border-radius:26px;border:1px solid var(--border);}
.theme-slider:before{position:absolute;content:"";height:18px;width:18px;left:3px;top:3px;
  background:var(--text-mid);transition:.25s;border-radius:50%;}
.theme-switch input:checked + .theme-slider{background:var(--green);border-color:var(--green);}
.theme-switch input:checked + .theme-slider:before{transform:translateX(20px);background:#fff;}

/* banners (landing winter / cal-incomplete) */
.banner{margin:12px 18px 0;padding:12px 14px;border-radius:var(--radius-sm);font-size:14px;
  font-weight:600;text-align:center;border:1px solid;}
.banner-info{color:var(--green);border-color:var(--green);background:var(--green-dim);}
.banner-warn{color:var(--red);border-color:var(--red);background:var(--red-dim);}
.banner .btn{margin-top:10px;}

/* winter lock (b535) */
body.winter-lock{pointer-events:none;}
body.winter-lock #winter-banner{pointer-events:auto;}
body.winter-lock button:not(#winter-banner button),body.winter-lock input,
body.winter-lock select,body.winter-lock a{opacity:.45;}
@media (prefers-reduced-motion:reduce){*{transition:none!important;animation:none!important;}}

body{max-width:560px;margin:0 auto;padding-bottom:24px;}
.prog-wrap{background:var(--bg3);border-radius:4px;height:8px;margin:12px 0;overflow:hidden;}
.prog-fill{height:100%;border-radius:4px;background:var(--green);transition:width .4s;}
.status-msg{font-size:13px;color:var(--text-mid);min-height:18px;margin:6px 0;}
.btn-row{display:flex;gap:8px;flex-wrap:wrap;margin-top:12px;}
table{width:100%;border-collapse:collapse;font-size:13px;margin-top:12px;}
th{color:var(--text-mid);font-weight:700;text-align:left;padding:6px 8px;border-bottom:1px solid var(--border);
  font-size:11px;letter-spacing:.08em;text-transform:uppercase;}
td{padding:7px 8px;border-bottom:1px solid var(--border);font-family:var(--mono);color:var(--text);}
tr:last-child td{border-bottom:none;}
.bar-wrap{background:var(--bg3);border-radius:3px;height:6px;width:80px;}
.bar-fill{height:100%;border-radius:3px;background:var(--green);}
.throw-input-block{display:none;margin-top:14px;padding:14px;background:var(--orange-dim);border-radius:var(--radius-sm);border:1px solid var(--orange);}
.throw-input-block.show{display:block;}
.throw-label{font-size:14px;color:var(--text);margin-bottom:10px;line-height:1.5;}
.throw-row{display:flex;gap:8px;align-items:center;flex-wrap:wrap;}
.throw-inp{flex:1;min-width:140px;background:var(--bg2);font-size:16px;font-family:var(--mono);}
.enc-grid{display:grid;grid-template-columns:1fr 1fr;gap:10px;}
.enc-box{background:var(--bg2);border-radius:var(--radius);padding:14px;border:1px solid var(--border);box-shadow:var(--shadow);}
.enc-name{font-size:11px;font-weight:700;letter-spacing:.1em;color:var(--text-mid);margin-bottom:6px;}
.enc-val{font-size:24px;font-weight:800;font-family:var(--mono);color:var(--text);letter-spacing:-.02em;}
.enc-sub{font-size:12px;color:var(--text-mid);margin-top:4px;}
.enc-ok{color:var(--green);} .enc-warn{color:var(--orange);}
.spd-row{display:flex;justify-content:space-between;padding:6px 0;border-bottom:1px solid var(--border);font-size:13px;}
.spd-row:last-child{border-bottom:none;}
.spd-label{color:var(--text-mid);}
.spd-val{font-family:var(--mono);}
</style>
</head>
<body>
<header>
  <a class="back" href="/" title="Back">&larr;</a>
  <a class="logo" href="/"><svg class="duck" width="26" height="22" viewBox="0 0 30 26" aria-hidden="true"><path d="M3 18c1-6 5-9 10-9 3 0 5 1 7 3l6-1-3 4c0 5-5 9-11 9S3 22 3 18z" fill="var(--pond)"/><circle cx="21.5" cy="12.5" r="3.6" fill="var(--pond)"/><path d="M24.5 12.5l4 1-3.5 1.5z" fill="var(--red)"/><circle cx="22" cy="12" r=".9" fill="var(--bg2)"/></svg>Irrigoto</a>
  <span class="hdr-title">Calibration</span>
</header>
<main>

<div class="note card" style="margin:0 0 16px">Run <b>Pressure &rarr; Throw</b> first &mdash; complete it before speed cal, jog cal, or zone creation. The other calibrations use its pressure map to open the valve; until it completes they run with the valve closed (dry).</div>

<!-- Pressure calibration -->
<section id="pressure">
  <div class="sec-hdr"><span class="sec-title">Pressure &rarr; Throw</span></div>
  <div class="card">
    <div class="note">Sweeps the valve open&rarr;closed, reads pressure at each step, then averages opening and closing readings to remove hysteresis. Water supply must be connected and pressurised. Allow several minutes for the sweep, plus the throw-distance measurement steps.</div>
    <div class="btn-row">
      <button class="btn btn-green" id="pres-start-btn" onclick="presStart()">&#9654; Run scan</button>
      <button class="btn btn-red" id="pres-cancel-btn" style="display:none" onclick="presCancel()">&#9632; Cancel</button>
      <button class="btn btn-red" id="pres-clear-btn" onclick="presClear()">&#10005; Clear cal</button>
    </div>
    <div class="prog-wrap" id="pres-prog-wrap" style="display:none">
      <div class="prog-fill" id="pres-prog" style="width:0%"></div>
    </div>
    <div class="status-msg" id="pres-msg"></div>
    <!-- Low throw entry (shown after scan, step 1 of 2) -->
    <div class="throw-input-block" id="throw-low-block">
      <div class="throw-label">&#128167; Step 1 of 2: Valve is open a little (short throw). Go measure the distance to the outer edge of this short spray ellipse, then enter it below.</div>
      <div class="throw-row">
        <input class="throw-inp" id="throw-low-inp" type="text" placeholder="e.g. 1200 or 4.0f" inputmode="decimal">
        <button class="btn btn-green" id="throw-low-save-btn" onclick="submitThrowLow()">Save short throw</button>
      </div>
      <div class="status-msg" id="throw-low-msg" style="margin-top:6px"></div>
    </div>
    <!-- Max throw entry (shown after low throw, step 2 of 2) -->
    <div class="throw-input-block" id="throw-block">
      <div class="throw-label">&#127775; Step 2 of 2: Valve is now open at full pressure. Go measure the distance to the outer edge of the spray ellipse, then enter it below.</div>
      <div class="throw-row">
        <input class="throw-inp" id="throw-inp" type="text" placeholder="e.g. 6200 or 20.3f" inputmode="decimal">
        <button class="btn btn-green" id="throw-save-btn" onclick="submitThrow()">Save max throw</button>
      </div>
      <div class="status-msg" id="throw-msg" style="margin-top:6px"></div>
    </div>
    <!-- Results table -->
    <div id="pres-table-wrap" style="display:none">
      <table>
        <thead><tr><th>#</th><th>Valve (deg)</th><th>PSI</th><th>Throw</th><th></th></tr></thead>
        <tbody id="pres-tbody"></tbody>
      </table>
    </div>
  </div>
</section>

<!-- Nozzle speed calibration -->
<section id="speed">
  <div class="sec-hdr"><span class="sec-title">Nozzle Speed</span></div>
  <div class="card">
    <div class="note">Runs the nozzle at each PWM duty level and measures deg/sec from the encoder. CW then CCW. Takes ~4 minutes. With a completed pressure cal (and water connected) the valve opens to ~30% pressure; without one it runs dry with the valve closed.</div>
    <div class="btn-row">
      <button class="btn btn-green" id="noz-start-btn" onclick="nozStart()">&#9654; Run speed cal</button>
    </div>
    <div class="prog-wrap" id="noz-prog-wrap" style="display:none">
      <div class="prog-fill" id="noz-prog" style="width:0%"></div>
    </div>
    <div class="status-msg" id="noz-msg"></div>
    <div id="noz-table-wrap" style="display:none"></div>
  </div>
</section>

<!-- Jog pulse calibration -->
<section id="jog">
  <div class="sec-hdr"><span class="sec-title">Jog Pulse Calibration</span></div>
  <div class="card">
    <div class="note">Measures how far the nozzle moves per PWM pulse under water load. Run AFTER nozzle speed cal. With a completed pressure cal (and water connected) the valve opens to ~30% pressure; without one it runs dry with the valve closed.</div>
    <div class="btn-row">
      <button class="btn btn-green" id="jog-start-btn" onclick="jogStart()">&#9654; Run jog cal</button>
      <button class="btn btn-red" id="jog-cancel-btn" style="display:none" onclick="jogCancel()">&#9632; Cancel</button>
    </div>
    <div class="prog-wrap" id="jog-prog-wrap" style="display:none">
      <div class="prog-fill" id="jog-prog" style="width:0%"></div>
    </div>
    <div class="status-msg" id="jog-msg"></div>
  </div>
</section>

<!-- Encoder health -->
<section>
  <div class="sec-hdr">
    <span class="sec-title">Encoder Health</span>
    <button class="btn" style="font-size:12px;padding:4px 10px" onclick="loadEncoder()">&#8635; Refresh</button>
  </div>
  <div class="enc-grid">
    <div class="enc-box">
      <div class="enc-name">VALVE (AS5600L)</div>
      <div class="enc-val" id="enc-v-deg">&mdash;</div>
      <div class="enc-sub">AGC: <span id="enc-v-agc">&mdash;</span> &nbsp; <span id="enc-v-st"></span></div>
    </div>
    <div class="enc-box">
      <div class="enc-name">NOZZLE (AS5600)</div>
      <div class="enc-val" id="enc-n-deg">&mdash;</div>
      <div class="enc-sub">AGC: <span id="enc-n-agc">&mdash;</span> &nbsp; <span id="enc-n-st"></span></div>
    </div>
  </div>
</section>

</main>
<script>
const WCAL_IDLE=0,WCAL_PRES_SCAN=1,WCAL_AWAIT_THROW=2,WCAL_NOZ=3,WCAL_JOG=4,WCAL_DONE=5,WCAL_ERR=6,WCAL_AWAIT_THROW_LOW=7;
let pollTimer=null, lastCalSection='', calActive=false;

// ── Pressure cal ─────────────────────────────────────────────────────────────
async function presClear(){
  if(!confirm('Clear pressure calibration (LittleFS + NVS backup)?')) return;
  const r=await fetch('/api/cal/clear',{method:'POST'});
  const d=await r.json();
  if(d.ok){
    document.getElementById('pres-table-wrap').innerHTML='';
    document.getElementById('pres-msg').textContent='Calibration cleared.';
  }
}
async function presStart(){
  const r=await fetch('/cal/pressure/start',{method:'POST'});
  const d=await r.json();
  if(!d.ok){alert(d.error||'Failed');return;}
  calActive=true;
  document.getElementById('pres-start-btn').disabled=true;
  document.getElementById('pres-clear-btn').disabled=true;
  document.getElementById('pres-cancel-btn').style.display='';
  document.getElementById('pres-prog-wrap').style.display='';
  document.getElementById('pres-table-wrap').style.display='none';
  document.getElementById('throw-block').classList.remove('show');
  document.getElementById('throw-low-block').classList.remove('show');
  document.getElementById('throw-low-save-btn').disabled=false;
  document.getElementById('throw-save-btn').disabled=false;
  startPoll();
}
async function presCancel(){
  await fetch('/cal/pressure/cancel',{method:'POST'});
  stopPoll(); resetPresUI();
}
// The throw handlers block ~10s while the valve drives (open for the max step,
// closed at the end), so disable the button during the request and give
// feedback -- otherwise an impatient second click lands after the device has
// advanced and returns "not awaiting throw". On error we restart the poll so
// the UI reconciles to the device's real state instead of stranding the block.
async function submitThrowLow(){
  const val=document.getElementById('throw-low-inp').value.trim();
  if(!val){return;}
  const btn=document.getElementById('throw-low-save-btn');
  if(btn.disabled) return;
  btn.disabled=true;
  const msg=document.getElementById('throw-low-msg');
  msg.textContent='Saving short throw... opening valve fully (~10s)';
  msg.style.color='var(--text-mid)';
  try{
    const body='throw_mm='+encodeURIComponent(val);
    const r=await fetch('/cal/pressure/throw_low',{method:'POST',body,
      headers:{'Content-Type':'application/x-www-form-urlencoded'}});
    const d=await r.json();
    if(d.ok){
      msg.textContent='Short throw saved. Opening fully...';
      msg.style.color='var(--green)';
      document.getElementById('throw-low-block').classList.remove('show');
      startPoll();   // poll picks up AWAIT_THROW and shows the max-throw block
    } else {
      msg.textContent=d.error||'Error';
      msg.style.color='var(--red)';
      btn.disabled=false;
      startPoll();
    }
  }catch(e){
    msg.textContent='Connection error: '+e.message;
    msg.style.color='var(--red)';
    btn.disabled=false;
  }
}
async function submitThrow(){
  const val=document.getElementById('throw-inp').value.trim();
  if(!val){return;}
  const btn=document.getElementById('throw-save-btn');
  if(btn.disabled) return;
  btn.disabled=true;
  const msg=document.getElementById('throw-msg');
  msg.textContent='Saving max throw... closing valve (~10s)';
  msg.style.color='var(--text-mid)';
  try{
    const body='throw_mm='+encodeURIComponent(val);
    const r=await fetch('/cal/pressure/throw',{method:'POST',body,
      headers:{'Content-Type':'application/x-www-form-urlencoded'}});
    const d=await r.json();
    if(d.ok){
      msg.textContent='Saved.';
      msg.style.color='var(--green)';
      document.getElementById('throw-block').classList.remove('show');
      setTimeout(loadCal, 300); // cal written to flash before POST returned
      startPoll();              // continue polling so done-state UI cleanup fires
    } else {
      msg.textContent=d.error||'Error';
      msg.style.color='var(--red)';
      btn.disabled=false;
      startPoll();              // reconcile: device may already be DONE
    }
  }catch(e){
    msg.textContent='Connection error: '+e.message;
    msg.style.color='var(--red)';
    btn.disabled=false;
  }
}
function resetPresUI(){
  document.getElementById('pres-start-btn').disabled=false;
  document.getElementById('pres-clear-btn').disabled=false;
  document.getElementById('pres-cancel-btn').style.display='none';
  document.getElementById('pres-prog-wrap').style.display='none';
}

// ── Nozzle cal ───────────────────────────────────────────────────────────────
async function jogStart(){
  const btn=document.getElementById('jog-start-btn');
  const msg=document.getElementById('jog-msg');
  btn.disabled=true;
  document.getElementById('jog-prog-wrap').style.display='';
  msg.textContent='Connecting...';
  msg.style.color='var(--text-mid)';
  try{
    const r=await fetch('/cal/jog/start',{method:'POST'});
    const d=await r.json();
    if(!d.ok){
      msg.textContent='Error: '+(d.error||'start failed');
      msg.style.color='var(--red)';
      btn.disabled=false;
      document.getElementById('jog-prog-wrap').style.display='none';
      return;
    }
    msg.textContent='Running...';
    document.getElementById('jog-cancel-btn').style.display='';
  calActive=true;
  }catch(e){
    msg.textContent='Connection error: '+e.message;
    msg.style.color='var(--red)';
    btn.disabled=false;
    document.getElementById('jog-prog-wrap').style.display='none';
    document.getElementById('jog-cancel-btn').style.display='none';
    return;
  }
  startPoll();
}

async function jogCancel(){
  await fetch('/cal/jog/cancel',{method:'POST'});
  stopPoll();
  document.getElementById('jog-start-btn').disabled=false;
  document.getElementById('jog-cancel-btn').style.display='none';
  document.getElementById('jog-prog-wrap').style.display='none';
  document.getElementById('jog-msg').textContent='Cancelled.';
  calActive=false;
}

async function nozStart(){
  document.getElementById('noz-start-btn').disabled=true;
  document.getElementById('noz-prog-wrap').style.display='';
  document.getElementById('noz-msg').textContent='Starting...';
  try{
    const r=await fetch('/cal/nozzle/start',{method:'POST'});
    const d=await r.json();
    if(!d.ok){
      alert(d.error||'Start failed');
      document.getElementById('noz-start-btn').disabled=false;
      document.getElementById('noz-prog-wrap').style.display='none';
      return;
    }
  calActive=true;
  }catch(e){
    alert('Connection error: '+e.message);
    document.getElementById('noz-start-btn').disabled=false;
    document.getElementById('noz-prog-wrap').style.display='none';
    return;
  }
  startPoll();
}

// ── Polling ──────────────────────────────────────────────────────────────────
// Sequential: next poll is scheduled only after current fetch completes,
// preventing request pile-up when the ESP32 is slow to respond.
var _pollRunning=false;
function startPoll(){ stopPoll(); _pollRunning=true; poll(); }
function stopPoll(){ _pollRunning=false; clearTimeout(pollTimer); pollTimer=null; }

async function poll(){
  try{
    const r=await fetch('/cal/status');
    const txt=await r.text();
    const d=JSON.parse(txt);
    updatePresUI(d);
    if(d.state===WCAL_DONE||d.state===WCAL_ERR){
      stopPoll(); return;
    }
  }catch(e){
    if(calActive) document.getElementById('pres-msg').textContent='poll err:'+e.message;
  }
  if(_pollRunning) pollTimer=setTimeout(poll,800);
}

function updatePresUI(d){
  // Only update section that owns the current state
  const presActive = d.state===WCAL_PRES_SCAN||d.state===WCAL_AWAIT_THROW||d.state===WCAL_AWAIT_THROW_LOW;
  const nozActive  = d.state===WCAL_NOZ;
  const jogActive  = d.state===WCAL_JOG;
  const done       = d.state===WCAL_DONE||d.state===WCAL_ERR;
  const msg=document.getElementById('pres-msg');
  if(presActive||done) {
    msg.textContent=presActive?d.msg||'':'';
    msg.style.color=d.state===WCAL_ERR?'var(--red)':d.state===WCAL_DONE?'var(--green)':'var(--text-mid)';
  }
  const nozMsg=document.getElementById('noz-msg');
  if(nozActive){lastCalSection='noz';
    nozMsg.textContent=d.msg||'';
    document.getElementById('noz-prog').style.width=d.progress+'%';
    document.getElementById('noz-prog-wrap').style.display='';
  } else if(jogActive){lastCalSection='jog';
    document.getElementById('jog-cancel-btn').style.display='';
    document.getElementById('jog-msg').textContent=d.msg||'';;
    document.getElementById('jog-prog').style.width=d.progress+'%';
    document.getElementById('jog-prog-wrap').style.display='';
  }
  if(done){
    const col=d.state===WCAL_ERR?'var(--red)':'var(--green)';
    ['noz-prog-wrap','jog-prog-wrap','pres-prog-wrap'].forEach(id=>{
      const el=document.getElementById(id); if(el) el.style.display='none';
    });
    ['jog-cancel-btn','pres-cancel-btn'].forEach(id=>{
      const el=document.getElementById(id); if(el) el.style.display='none';
    });
    // Cal finished (DONE/ERR): tear down the throw-input steps and reset their
    // buttons, otherwise the last step's block stays on screen and a re-click
    // hits "not awaiting throw".
    ['throw-low-block','throw-block'].forEach(id=>{
      const el=document.getElementById(id); if(el) el.classList.remove('show');
    });
    ['throw-low-save-btn','throw-save-btn'].forEach(id=>{
      const el=document.getElementById(id); if(el) el.disabled=false;
    });
    // Re-enable after short delay so result message is readable
    calActive=false;
    setTimeout(()=>{
      if(!calActive) {  // only re-enable if no new cal started
        ['noz-start-btn','jog-start-btn','pres-start-btn'].forEach(id=>{
          const el=document.getElementById(id); if(el) el.disabled=false;
        });
      }
    }, 2000);
    document.getElementById('pres-cancel-btn').style.display='none';
    // Show final message in whichever section was running
    if(lastCalSection==='jog'){
      document.getElementById('jog-msg').textContent=d.msg||''; 
      document.getElementById('jog-msg').style.color=col;
    } else if(lastCalSection==='noz'){
      nozMsg.textContent=d.msg||''; nozMsg.style.color=col;
    }
    lastCalSection='';
    setTimeout(loadCal, 800);  // refresh cal table after scan completes
  }

  if(d.state===WCAL_PRES_SCAN){
    document.getElementById('pres-prog').style.width=d.progress+'%';
    document.getElementById('pres-cancel-btn').style.display='';
  }

  if(d.state===WCAL_AWAIT_THROW_LOW){
    document.getElementById('pres-prog').style.width='100%';
    document.getElementById('pres-cancel-btn').style.display='none';
    document.getElementById('throw-low-block').classList.add('show');
    document.getElementById('throw-block').classList.remove('show');
    renderPresTable(d);
  }

  if(d.state===WCAL_AWAIT_THROW){
    document.getElementById('pres-prog').style.width='100%';
    document.getElementById('pres-cancel-btn').style.display='none';
    document.getElementById('throw-low-block').classList.remove('show');
    document.getElementById('throw-block').classList.add('show');
    renderPresTable(d);
  }

  if((d.state===WCAL_DONE||d.state===WCAL_IDLE)&&d.num_points>0){
    renderPresTable(d);
  }
}

function renderPresTable(d){
  if(!d.points||!d.points.length) return;
  const wrap=document.getElementById('pres-table-wrap');
  const tbody=document.getElementById('pres-tbody');
  const maxT=Math.max(...d.points.map(p=>p.t));
  tbody.innerHTML=d.points.map((p,i)=>{
    const pct=maxT>0?Math.round(p.t/maxT*100):0;
    const tStr=p.t>0?(p.t/304.8).toFixed(1)+'ft':'&mdash;';
    return `<tr>
      <td>${i+1}</td>
      <td>${p.v.toFixed(1)}</td>
      <td>${p.p.toFixed(3)}</td>
      <td>${tStr}</td>
      <td><div class="bar-wrap"><div class="bar-fill" style="width:${pct}%"></div></div></td>
    </tr>`;
  }).join('');
  wrap.style.display='';
}

// ── Encoder ──────────────────────────────────────────────────────────────────
async function loadEncoder(){
  try{
    const d=await fetch('/cal/encoder').then(r=>r.json());
    function agcStatus(agc){
      if(agc===undefined||agc===null) return {cls:'',txt:'no data'};
      const ok=agc>50&&agc<200;
      return {cls:ok?'enc-ok':'enc-warn', txt:ok?'OK':'check magnet'};
    }
    document.getElementById('enc-v-deg').textContent=d.valve.deg.toFixed(1)+'\u00b0';
    document.getElementById('enc-n-deg').textContent=d.nozzle.deg.toFixed(1)+'\u00b0';
    const vs=agcStatus(d.valve.agc), ns=agcStatus(d.nozzle.agc);
    document.getElementById('enc-v-agc').textContent=d.valve.agc;
    document.getElementById('enc-n-agc').textContent=d.nozzle.agc;
    document.getElementById('enc-v-st').className=vs.cls;
    document.getElementById('enc-v-st').textContent=vs.txt;
    document.getElementById('enc-n-st').className=ns.cls;
    document.getElementById('enc-n-st').textContent=ns.txt;
  }catch(e){}
}

// Scroll to speed section if #speed hash
if(location.hash==='#speed') setTimeout(()=>document.getElementById('speed').scrollIntoView({behavior:'smooth'}),200);

// Initial load

async function loadCal(){
  try{
    const d=await fetch('/api/cal').then(r=>r.json());
    if(!d.num_points) return;
    const tbody=document.getElementById('pres-tbody');
    const wrap=document.getElementById('pres-table-wrap');
    const maxT=Math.max(...d.throw_mm.filter(t=>t>0))||1;
    tbody.innerHTML=d.valve_deg.map((v,i)=>{
      const t=d.throw_mm[i];
      const pct=Math.round(t/maxT*100);
      const tStr=t>0?(t/304.8).toFixed(1)+'ft':'&mdash;';
      return `<tr>
        <td>${i+1}</td>
        <td>${v.toFixed(1)}</td>
        <td>${d.pressure_psi[i].toFixed(3)}</td>
        <td>${tStr}</td>
        <td><div class="bar-wrap"><div class="bar-fill" style="width:${pct}%"></div></div></td>
      </tr>`;
    }).join('');
    wrap.style.display='';
  }catch(e){}
}

loadCal();
poll();
loadEncoder();
</script>
</body>
</html>
)CALHTML"
#endif /* IRRIGOTO_HTML_PAYLOAD */
