/* Auto-generated from schedule.html -- edit the .html, then run regen.py */
#ifdef IRRIGOTO_HTML_PAYLOAD
R"SCHEDHTML(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no">
<title>Schedule &mdash; irrigoto</title>
<script>
// Apply theme before body renders to avoid flash. localStorage = instant
// cache; /api/theme = source of truth (NVS-backed).
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
// b437: set the device clock from this phone (zero-config; works offline / AP
// mode, no NTP). Critical for standalone scheduling -- opening this page is
// what gives the device a clock to arm the schedule from.
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
/* ---- Shared prelude: Hearth component language ---- */
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
  /* Hearth faces; system fallbacks on the device AP */
  --font:"Geist","Inter",system-ui,-apple-system,"Segoe UI",Roboto,"Helvetica Neue",sans-serif;
  --display:"Bricolage Grotesque","Geist",system-ui,-apple-system,"Segoe UI",Roboto,sans-serif;
  --mono:"Geist Mono",ui-monospace,"SF Mono","Cascadia Mono","JetBrains Mono",Menlo,Consolas,monospace;
  /* appended tokens; *-ink = text on a status tint */
  --dot:#1c2028;--tint:rgba(236,238,243,.09);--tint-2:rgba(236,238,243,.16);--ok-ink:#2fc77a;--orange-ink:#ff9f40;--red-ink:#ff5a5a;
  --scrim:rgba(8,10,14,.55);--knob:#ffffff;--shadow-float:0 30px 80px rgba(0,0,0,.35);--shadow-knob:0 1px 2px rgba(0,0,0,.2);
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
  /* appended tokens; light inks darkened for sunlight */
  --dot:#d3d6de;--tint:rgba(21,23,28,.09);--tint-2:rgba(21,23,28,.16);--ok-ink:#146b43;--orange-ink:#8a4d0a;--red-ink:#a02828;
  --scrim:rgba(8,10,14,.55);--knob:#ffffff;--shadow-float:0 30px 80px rgba(16,18,26,.25);--shadow-knob:0 1px 2px rgba(16,18,26,.12);
}
html,body{background:var(--bg);}
body{color:var(--text);font:14px/1.45 var(--font);-webkit-font-smoothing:antialiased;}
button,input,select,textarea{font:inherit;color:inherit;}
button{cursor:pointer;}
a{color:var(--green);}
:focus-visible{outline:2px solid var(--green);outline-offset:2px;}
::selection{background:var(--green-dim);}
/* icons */
svg.i{width:18px;height:18px;fill:none;stroke:currentColor;stroke-width:1.8;stroke-linecap:round;stroke-linejoin:round;flex:none;}

/* top bar (.top) */
header{display:flex;align-items:center;gap:10px;padding:8px 16px;min-height:56px;
border-bottom:1px solid var(--border);background:var(--bg2);flex-shrink:0;min-width:0;}
.back{display:inline-flex;align-items:center;justify-content:center;width:40px;height:40px;flex-shrink:0;
border-radius:var(--radius-sm);border:1px solid var(--border);background:var(--bg2);color:var(--text-mid);text-decoration:none;}
.back:active{background:var(--bg3);color:var(--text);}
.logo{display:inline-flex;align-items:center;gap:10px;font-family:var(--display);font-weight:700;font-size:17px;
letter-spacing:-.01em;color:var(--text);text-decoration:none;white-space:nowrap;}
/* duck in the inverted .mark tile (own fills: brand exception) */
.logo .duck{flex-shrink:0;width:28px;height:28px;padding:4px 3px;border-radius:9px;background:var(--text);}
/* page identity: .name-in weight, not an eyebrow */
.hdr-title,.header-mid{flex:1;min-width:0;overflow:hidden;text-overflow:ellipsis;white-space:nowrap;font-size:15px;font-weight:600;color:var(--text);}
.sec-title{font-size:11px;font-weight:600;letter-spacing:.08em;text-transform:uppercase;color:var(--text-mid);}
.page-logo{display:none;}
/* .ha-chip; .usage = .stage-meta */
#conn,.usage{display:inline-flex;align-items:center;gap:7px;margin-left:auto;padding:5px 11px;white-space:nowrap;
font-size:12.5px;font-weight:500;color:var(--text-mid);border:1px solid var(--border);border-radius:99px;}
.usage{font-size:11px;padding:0;border:0;max-width:50%;overflow:hidden;text-overflow:ellipsis;display:block;font-family:var(--mono);font-variant-numeric:tabular-nums;}
#conn-dot{width:8px;height:8px;border-radius:50%;background:var(--text-dim);transition:background .4s,box-shadow .4s;flex-shrink:0;}
#conn-dot.ok{background:var(--ok);box-shadow:0 0 0 3px var(--ok-dim);}
#conn-dot.err{background:var(--red);box-shadow:0 0 0 3px var(--red-dim);}
@media (max-width:400px){header{gap:6px;padding:8px 12px;}}
@media (max-width:350px){#conn span{display:none;}#conn{padding:5px 7px;}}

/* page, groups, cards */
main{padding:16px 16px 28px;display:flex;flex-direction:column;gap:16px;}
section{display:flex;flex-direction:column;gap:10px;}
/* .sec-hdr = .group rule; off on the first section (first-of-type: cal starts with a callout) */
.sec-hdr{display:flex;align-items:center;justify-content:space-between;gap:10px;min-height:36px;
padding-top:16px;border-top:1px solid var(--border);}
section:first-of-type > .sec-hdr,main > .sec-hdr:first-child,.card > .sec-hdr{padding-top:0;border-top:0;}
/* header action = .mini at the 36px floor */
.sec-btn,#refresh-btn{display:inline-flex;align-items:center;justify-content:center;gap:6px;min-height:36px;padding:6px 12px;
border-radius:var(--radius-sm);border:1px solid var(--border);background:var(--bg);color:var(--text-mid);
font-size:12.5px;font-weight:500;cursor:pointer;text-decoration:none;white-space:nowrap;}
.sec-btn:active,#refresh-btn:active{color:var(--text);border-color:var(--text-mid);}
.sec-btn svg.i,#refresh-btn svg.i{width:16px;height:16px;}
.card,.status-card,.upload-card{background:var(--bg2);border:1px solid var(--border);border-radius:12px;padding:14px;}
/* .insp-empty; quiet inside a card (fs: #tree.tree) */
.empty,.card.empty{color:var(--text-mid);font-size:12.5px;line-height:1.45;text-align:center;padding:22px 12px;
border:1.5px dashed var(--border);border-radius:16px;background:transparent;}
.card > .empty,.card .tree > .empty{border:0;border-radius:0;padding:8px 0;}
.hint,.note,.cal-desc{font-size:12.5px;color:var(--text-mid);line-height:1.5;margin:0;}
.note,.cal-desc{margin-bottom:12px;}
/* .score strip */
.score{display:flex;align-items:center;gap:10px;padding:10px 12px;border-radius:var(--radius-sm);background:var(--bg);border:1px solid var(--border);font-size:12.5px;line-height:1.45;}
.score b{font-family:var(--mono);font-variant-numeric:tabular-nums;}
.kv{display:flex;align-items:center;justify-content:space-between;gap:12px;}
.val{font-family:var(--mono);font-size:12px;color:var(--text-mid);font-variant-numeric:tabular-nums;}
@keyframes pulse{50%{opacity:.25;transform:scale(.7);}}

/* .btn at touch density; danger = red text, never a red fill */
.btn{display:inline-flex;align-items:center;justify-content:center;gap:7px;min-height:42px;padding:10px 14px;
border-radius:var(--radius-sm);border:1px solid var(--border);background:var(--btn);color:var(--text);
font-size:13px;font-weight:500;line-height:20px;cursor:pointer;text-decoration:none;white-space:nowrap;
transition:border-color .15s,background .15s;}
.btn:active{background:var(--btn-hover);border-color:var(--text-mid);}
.btn:disabled{opacity:.45;cursor:default;}
.btn-primary,.btn-green{background:var(--green);border-color:transparent;color:var(--accent-ink);}
.btn-primary:active,.btn-green:active{background:var(--green);border-color:transparent;filter:brightness(.94);}
.btn-danger,.btn-red{color:var(--red);}
.btn.icon{width:40px;min-height:40px;padding:0;}
.btn.sm{min-height:36px;padding:6px 12px;}
/* hover (laptops only) */
@media (hover:hover){
.btn:hover:not(:disabled),.sec-btn:hover,#refresh-btn:hover,.act-btn:hover,.entry-del:hover{border-color:var(--text-mid);}
.btn-primary:hover:not(:disabled),.btn-green:hover:not(:disabled){filter:brightness(1.06);}
}

/* fields: recessed, accent focus border (range/checkbox keep the ring) */
input[type=text],input[type=number],input[type=time],select,.throw-inp,.path-inp,.file-inp{
background:var(--bg);border:1px solid var(--border);border-radius:9px;
color:var(--text);font-size:15px;padding:10px 12px;min-height:42px;width:100%;}
input:not([type=range]):not([type=checkbox]):focus,select:focus{outline:none;border-color:var(--green);}
input::placeholder{color:var(--text-dim);}
input[type=range]{accent-color:var(--green);width:100%;height:36px;}
.field{display:flex;flex-direction:column;gap:6px;}
.field label{font-size:12.5px;font-weight:500;}
/* .name-in: border on hover; resting border on touch */
input.name-in,.name-in{background:transparent;border:1px solid transparent;border-radius:8px;padding:6px 8px;min-height:0;min-width:0;font-weight:500;color:var(--text);}
input.name-in:hover{border-color:var(--border);}
input.name-in:focus{border-color:var(--green);outline:none;}
@media (hover:none){input.name-in{border-color:var(--border);}}

/* .switch 44x26; knob on .theme-slider:before; label :before pads the hit box to 56x44 */
.theme-switch{position:relative;display:inline-block;width:44px;height:26px;vertical-align:middle;flex-shrink:0;cursor:pointer;}
.theme-switch:before{content:"";position:absolute;inset:-9px -6px;}
.theme-switch input{position:absolute;inset:0;width:100%;height:100%;margin:0;opacity:0;cursor:pointer;}
.theme-slider{position:absolute;inset:0;border-radius:99px;background:var(--border);transition:background .2s;pointer-events:none;}
.theme-slider:before{position:absolute;content:"";width:20px;height:20px;left:3px;top:3px;border-radius:50%;
background:var(--knob);box-shadow:var(--shadow-knob);transition:transform .2s;}
.theme-switch input:checked + .theme-slider{background:var(--green);}
.theme-switch input:checked + .theme-slider:before{transform:translateX(18px);}
.theme-switch input:focus-visible + .theme-slider{outline:2px solid var(--green);outline-offset:2px;}

/* .rep rows: panel fill, tint only on the 22px icon */
.banner{margin:12px 16px 0;padding:12px;border-radius:var(--radius-sm);border:1px solid var(--border);
background:var(--bg2);font-size:13px;font-weight:500;line-height:1.45;color:var(--text);}
.banner-row{display:flex;gap:10px;align-items:flex-start;}
.banner-i{width:22px;height:22px;border-radius:50%;display:grid;place-items:center;flex:none;background:var(--green-dim);color:var(--green);}
.banner-i svg.i{width:14px;height:14px;}
.banner-body{flex:1;min-width:0;}
.banner-info .banner-i{background:var(--green-dim);color:var(--green);}
.banner-warn .banner-i{background:var(--orange-dim);color:var(--orange-ink);}
.banner .btn{margin-top:10px;}

/* winter lock (b535) */
body.winter-lock{pointer-events:none;}
body.winter-lock #winter-banner{pointer-events:auto;}
body.winter-lock button:not(#winter-banner button),body.winter-lock input,
body.winter-lock select,body.winter-lock a{opacity:.45;}
/* don't double-dim icons the head script already dimmed */
body.winter-lock button svg.i,body.winter-lock a svg.i{opacity:1;}
@media (prefers-reduced-motion:reduce){*{transition:none!important;animation:none!important;}}

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
</style>
</head>
<body>
<svg aria-hidden="true" width="0" height="0" style="position:absolute"><symbol id="i-chevron-left" viewBox="0 0 24 24"><path d="M15 6l-6 6 6 6"/></symbol><symbol id="i-plus" viewBox="0 0 24 24"><path d="M12 5v14M5 12h14"/></symbol><symbol id="i-clock" viewBox="0 0 24 24"><circle cx="12" cy="12" r="9"/><path d="M12 7v5l3 2"/></symbol><symbol id="i-calendar" viewBox="0 0 24 24"><rect x="3" y="5" width="18" height="16" rx="2"/><path d="M3 10h18M8 3v4M16 3v4"/></symbol><symbol id="i-refresh" viewBox="0 0 24 24"><path d="M20 12a8 8 0 1 1-2.3-5.7"/><path d="M20 4v5h-5"/></symbol></svg>
<header>
  <a class="back" href="/" title="Back"><svg class="i"><use href="#i-chevron-left"/></svg></a>
  <a class="logo" href="/"><svg class="duck" width="26" height="22" viewBox="0 0 30 26" aria-hidden="true"><path d="M3 18c1-6 5-9 10-9 3 0 5 1 7 3l6-1-3 4c0 5-5 9-11 9S3 22 3 18z" fill="var(--pond)"/><circle cx="21.5" cy="12.5" r="3.6" fill="var(--pond)"/><path d="M24.5 12.5l4 1-3.5 1.5z" fill="var(--red)"/><circle cx="22" cy="12" r=".9" fill="var(--bg2)"/></svg>Irrigoto</a>
  <span class="hdr-title">Schedule</span>
</header>
<main>
  <div class="status-card">
    <div class="status-row"><span class="lbl"><svg class="i"><use href="#i-clock"/></svg>Device time</span><span class="val" id="st-time">&mdash;</span></div>
    <div class="status-row"><span class="lbl"><svg class="i"><use href="#i-calendar"/></svg>Next run</span><span class="val" id="st-next">&mdash;</span></div>
    <div class="status-row"><span class="lbl"><svg class="i"><use href="#i-refresh"/></svg>Last update</span><span class="val" id="st-last">&mdash;</span></div>
  </div>

  <div class="sec-hdr">
    <span class="sec-title">Rain Delay</span>
    <span class="sec-title" id="delay-state">off</span>
  </div>
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

  <div class="sec-hdr">
    <span class="sec-title">Entries</span>
    <span class="sec-title" id="ent-count">0 of 32</span>
  </div>
  <div id="entries"><div class="empty">Loading&hellip;</div></div>

  <button class="add-btn" id="add-btn" onclick="addEntry()"><svg class="i"><use href="#i-plus"/></svg>Add entry</button>

  <div class="save-bar">
    <button class="btn btn-danger" onclick="clearAll()" title="Remove all entries">Clear all</button>
    <button class="btn btn-primary" id="save-btn" onclick="saveAll()">Save</button>
  </div>
  <div id="save-status"></div>

  <div class="hint">
    Schedule entries fire at the device's local time. Time comes from Home Assistant
    (no NTP). Overlapping entries on shared days are rejected at save time.
  </div>
</main>

<script>
const DAY_LABELS = ['Sun','Mon','Tue','Wed','Thu','Fri','Sat'];
const MODE_LABELS = ['Pulse','Gentle','Smooth','Serpentine'];
// Depth is eighths of an inch, indexed by the stored value (1..8); index 0 is
// an unused placeholder. Deeper targets are achieved as multiple 1/8" passes
// (same as the other modes), so Smooth is no longer 1/8"-only.
const DEPTH_LABELS = ['—','1/8&Prime;','1/4&Prime;','3/8&Prime;','1/2&Prime;','5/8&Prime;','3/4&Prime;','7/8&Prime;','1&Prime;'];

let state = {
  zones: [],         // [{id, name}]
  entries: [],       // working copy (edited locally)
  maxEntries: 32,
  fwBuild: 0,
  lastStatus: '',
  nextRun: null,
  deviceTime: 0,
  tzOffsetMin: 0,
  delayUntil: 0,     // epoch; 0 = no delay
};

// ── Initial load ─────────────────────────────────────────────────────────────
async function init() {
  try {
    const r = await fetch('/api/schedule', {cache:'no-store'});
    if (!r.ok) throw new Error('HTTP ' + r.status);
    const d = await r.json();
    state.zones = d.zones || [];
    state.entries = (d.entries || []).map(normalizeEntry);
    state.maxEntries = d.max_entries || 32;
    state.fwBuild = d.fw_build || 0;
    state.lastStatus = d.last_status || '';
    state.nextRun = d.next_run || null;
    state.deviceTime = d.now || 0;
    state.tzOffsetMin = (typeof d.tz_offset_min === 'number') ? d.tz_offset_min : 0;
    state.delayUntil = d.delay_until || 0;
    renderAll();
  } catch (e) {
    document.getElementById('entries').innerHTML =
      '<div class="empty" style="color:var(--red)">Load failed: ' + (e.message||e) + '</div>';
  }
}

function normalizeEntry(e) {
  return {
    zone: +e.zone || 1,
    mode: +e.mode || 0,
    depth: +e.depth || 1,   // eighths (1..8); 0/missing -> 1/8"
    hour: +e.hour || 0,
    minute: +e.minute || 0,
    days_mask: +e.days_mask || 0,
    enabled: e.enabled ? 1 : 0,
  };
}

// ── Render ───────────────────────────────────────────────────────────────────
function renderAll() {
  renderStatus();
  renderDelay();
  renderEntries();
  document.getElementById('ent-count').textContent =
    state.entries.length + ' of ' + state.maxEntries;
  document.getElementById('add-btn').disabled =
    state.entries.length >= state.maxEntries;
}

function renderDelay() {
  const lbl  = document.getElementById('delay-state');
  const btn  = document.getElementById('delay-cancel-btn');
  const note = document.getElementById('delay-status');
  if (state.delayUntil > 1700000000 && state.delayUntil > (state.deviceTime || 0)) {
    const until = formatLocal(state.delayUntil);
    lbl.textContent = 'active until ' + until;
    lbl.style.color = 'var(--orange)';
    btn.style.display = '';
    note.textContent = 'Schedule entries that fall within this window will be skipped.';
  } else {
    lbl.textContent = 'off';
    lbl.style.color = '';
    btn.style.display = 'none';
    note.textContent = '';
  }
}

function renderStatus() {
  const t = document.getElementById('st-time');
  const n = document.getElementById('st-next');
  const l = document.getElementById('st-last');
  if (state.deviceTime > 1700000000) {
    t.textContent = formatLocal(state.deviceTime);
    t.classList.remove('warn');
  } else {
    t.textContent = 'not synced';
    t.classList.add('warn');
  }
  if (state.nextRun && state.nextRun.epoch > 1700000000) {
    const zname = lookupZoneName(state.nextRun.zone);
    n.textContent = zname + ' → ' + formatLocal(state.nextRun.epoch);
  } else if (state.entries.length === 0) {
    n.textContent = 'no entries';
  } else if (state.deviceTime <= 1700000000) {
    n.textContent = 'waiting for time';
  } else {
    n.textContent = 'no upcoming runs';
  }
  l.textContent = state.lastStatus || '—';
  if (state.lastStatus.indexOf('rejected') === 0 ||
      state.lastStatus.indexOf('parse failed') === 0 ||
      state.lastStatus.indexOf('out-of-range') === 0) {
    l.classList.add('err'); l.classList.remove('warn');
  } else if (state.lastStatus.indexOf('ok') === 0) {
    l.classList.remove('err'); l.classList.remove('warn');
  } else {
    l.classList.remove('err'); l.classList.add('warn');
  }
}

function lookupZoneName(zoneOneBased) {
  // schedule entries use 1-based zone numbers; zones[] uses 0-based ids.
  // Fallback label shows the 0-based "#id" (display convention everywhere).
  const z = state.zones.find(z => z.id === (zoneOneBased - 1));
  return z ? z.name : ('Zone #' + (zoneOneBased - 1));
}

function formatLocal(epochSec) {
  // Device epoch is already local-wall-clock if we trust the device clock.
  // For display, render it using device's offset so it always matches what
  // the user typed (independent of the browser's TZ).
  const d = new Date(epochSec * 1000);
  // Use UTC pieces, then apply tzOffsetMin to convert to device-local.
  const t = epochSec + state.tzOffsetMin * 60;
  const u = new Date(t * 1000);
  const Y = u.getUTCFullYear();
  const M = String(u.getUTCMonth()+1).padStart(2,'0');
  const D = String(u.getUTCDate()).padStart(2,'0');
  const h = String(u.getUTCHours()).padStart(2,'0');
  const m = String(u.getUTCMinutes()).padStart(2,'0');
  return Y + '-' + M + '-' + D + ' ' + h + ':' + m;
}

function renderEntries() {
  const el = document.getElementById('entries');
  if (!state.entries.length) {
    el.innerHTML = '<div class="card empty">No entries yet. Tap "Add entry" below to schedule a watering run.</div>';
    return;
  }
  el.innerHTML = '';
  state.entries.forEach((e, idx) => el.appendChild(renderEntry(e, idx)));
}

// Compute the next fire instant for an entry given the current device
// time. Mirrors the firmware's next_run walker so per-entry previews
// match what HA's Next Scheduled Run will say after Save. Returns a
// short human-readable label ("Today 17:30", "Sun 5/17 17:30",
// "Sat 5/23 17:30") and the unix epoch.
function entryNextFire(e, deviceEpoch, tzOffMin) {
  if (!e.enabled || !e.days_mask) {
    return { label: 'never (disabled)', epoch: 0, today: false };
  }
  if (!deviceEpoch || deviceEpoch < 1700000000) {
    return { label: 'waiting for time sync', epoch: 0, today: false };
  }
  // Compute device-local wall-clock fields from epoch + tz offset.
  // We work in a "local-shifted UTC" — epoch + tzOff*60, then read
  // UTC pieces. That gives the same calendar fields the device sees.
  function localFields(epoch) {
    const u = new Date((epoch + tzOffMin*60) * 1000);
    return { y: u.getUTCFullYear(), mo: u.getUTCMonth()+1, d: u.getUTCDate(),
             h: u.getUTCHours(), mi: u.getUTCMinutes(), wday: u.getUTCDay() };
  }
  // Walk forward up to 14 days, matching the firmware.
  for (let off = 0; off < 15; off++) {
    const cand = deviceEpoch + off * 86400;
    const f = localFields(cand);
    // Build the candidate fire moment: same Y-M-D as cand (in device
    // local), with the entry's H:M:00. Inverse of localFields:
    //   epoch = Date.UTC(...) / 1000 - tzOff*60
    const fireEpoch = Math.floor(Date.UTC(f.y, f.mo-1, f.d, e.hour, e.minute, 0) / 1000) - tzOffMin*60;
    if (fireEpoch <= deviceEpoch) continue;       // past for today
    const fireFields = localFields(fireEpoch);
    if (!(e.days_mask & (1 << fireFields.wday))) continue;
    // Format label.
    const today    = localFields(deviceEpoch);
    const isToday  = (fireFields.y === today.y && fireFields.mo === today.mo && fireFields.d === today.d);
    const tomorrow = localFields(deviceEpoch + 86400);
    const isTomorrow = (fireFields.y === tomorrow.y && fireFields.mo === tomorrow.mo && fireFields.d === tomorrow.d);
    const t = String(fireFields.h).padStart(2,'0') + ':' + String(fireFields.mi).padStart(2,'0');
    const wdayLbl = ['Sun','Mon','Tue','Wed','Thu','Fri','Sat'][fireFields.wday];
    let label;
    if (isToday)         label = 'Today ' + t;
    else if (isTomorrow) label = 'Tomorrow ' + t;
    else                 label = wdayLbl + ' ' + fireFields.mo + '/' + fireFields.d + ' ' + t;
    return { label, epoch: fireEpoch, today: isToday };
  }
  return { label: 'no upcoming fire', epoch: 0, today: false };
}

function renderEntry(e, idx) {
  const card = document.createElement('div');
  card.className = 'card entry' + (e.enabled ? '' : ' disabled');

  // Build the zone <option> list, anchored on whatever zones the API
  // returned plus the entry's current zone number (in case the user
  // deleted that zone after creating this entry).
  const zoneOpts = buildZoneOptions(e.zone);
  const timeStr = String(e.hour).padStart(2,'0') + ':' + String(e.minute).padStart(2,'0');
  // Per-entry next fire preview (computed client-side; matches the
  // firmware's next_run walker so what you see is what HA will see).
  const nf = entryNextFire(e, state.deviceTime, state.tzOffsetMin);
  const nfCol = nf.today ? 'var(--green)'
              : nf.epoch ? 'var(--text-mid)'
              : 'var(--orange)';

  card.innerHTML =
    '<div class="entry-hdr">' +
      '<span class="entry-num">ENTRY #' + (idx+1) + '</span>' +
      '<span class="next-preview" style="font-size:11px;color:' + nfCol + ';font-family:monospace;">' +
        '&rarr; ' + nf.label +
      '</span>' +
      '<button class="entry-del" onclick="delEntry(' + idx + ')">Delete</button>' +
    '</div>' +
    '<div class="row">' +
      '<div class="col" style="flex:2"><label>Zone</label>' +
        '<select data-k="zone">' + zoneOpts + '</select></div>' +
      '<div class="col"><label>Time</label>' +
        '<input type="time" data-k="time" value="' + timeStr + '"></div>' +
    '</div>' +
    '<div class="row">' +
      '<div class="col"><label>Mode</label>' +
        '<select data-k="mode">' +
          '<option value="0"' + (e.mode===0?' selected':'') + '>Pulse</option>' +
          '<option value="1"' + (e.mode===1?' selected':'') + '>Gentle</option>' +
          '<option value="2"' + (e.mode===2?' selected':'') + '>Smooth</option>' +
          '<option value="3"' + (e.mode===3?' selected':'') + '>Serpentine</option>' +
        '</select></div>' +
      '<div class="col"><label>Depth</label>' +
        '<select data-k="depth">' +
          [1,2,3,4,5,6,7,8].map(v =>
            '<option value="' + v + '"' + (((+e.depth)||1)===v ? ' selected' : '') + '>' +
            DEPTH_LABELS[v] + '</option>'
          ).join('') +
        '</select></div>' +
    '</div>' +
    '<div><label style="font-size:10px;letter-spacing:.12em;text-transform:uppercase;color:var(--text-mid);display:block;margin-bottom:4px;">Days</label>' +
      '<div class="days" data-k="days">' +
        DAY_LABELS.map((lbl, i) =>
          '<button class="day' + (e.days_mask & (1<<i) ? ' sel' : '') + '" ' +
          'data-bit="' + i + '">' + lbl + '</button>'
        ).join('') +
      '</div>' +
      '<div class="day-presets">' +
        '<button class="day-preset" data-preset="127">Every day</button>' +
        '<button class="day-preset" data-preset="62">Weekdays</button>' +
        '<button class="day-preset" data-preset="65">Weekends</button>' +
        '<button class="day-preset" data-preset="42">MWF</button>' +
        '<button class="day-preset" data-preset="20">Tu/Th</button>' +
        '<button class="day-preset" data-preset="0">None</button>' +
      '</div>' +
    '</div>' +
    '<div class="toggle-row" style="margin-top:12px;">' +
      '<span class="toggle-lbl">Enabled</span>' +
      '<label class="theme-switch">' +
        '<input type="checkbox" data-k="enabled"' + (e.enabled ? ' checked' : '') + '>' +
        '<span class="theme-slider"></span>' +
      '</label>' +
    '</div>';

  // Wire up change handlers — keep state.entries in sync immediately so
  // saveAll() always sends the visible state.
  card.querySelector('[data-k="zone"]').addEventListener('change', ev => {
    state.entries[idx].zone = +ev.target.value || 1;
  });
  card.querySelector('[data-k="time"]').addEventListener('change', ev => {
    const [h,m] = ev.target.value.split(':').map(Number);
    state.entries[idx].hour = h|0;
    state.entries[idx].minute = m|0;
    updateEntryPreview(card, state.entries[idx]);
  });
  card.querySelector('[data-k="mode"]').addEventListener('change', ev => {
    state.entries[idx].mode = +ev.target.value;
    // Re-render this card so the depth-disabled state updates.
    rerenderEntry(idx);
  });
  card.querySelector('[data-k="depth"]').addEventListener('change', ev => {
    state.entries[idx].depth = +ev.target.value;
  });
  card.querySelector('[data-k="enabled"]').addEventListener('change', ev => {
    state.entries[idx].enabled = ev.target.checked ? 1 : 0;
    card.classList.toggle('disabled', !ev.target.checked);
    updateEntryPreview(card, state.entries[idx]);
  });
  card.querySelectorAll('.day').forEach(btn => {
    btn.addEventListener('click', () => {
      const bit = +btn.dataset.bit;
      state.entries[idx].days_mask ^= (1 << bit);
      btn.classList.toggle('sel');
      updateEntryPreview(card, state.entries[idx]);
    });
  });
  card.querySelectorAll('.day-preset').forEach(btn => {
    btn.addEventListener('click', () => {
      const mask = +btn.dataset.preset;
      state.entries[idx].days_mask = mask;
      card.querySelectorAll('.day').forEach(d => {
        const bit = +d.dataset.bit;
        d.classList.toggle('sel', !!(mask & (1<<bit)));
      });
      updateEntryPreview(card, state.entries[idx]);
    });
  });

  return card;
}

function rerenderEntry(idx) {
  const el = document.getElementById('entries');
  const old = el.children[idx];
  const fresh = renderEntry(state.entries[idx], idx);
  if (old) el.replaceChild(fresh, old);
}

// Cheap in-place refresh of just the "→ next: ..." chip on an entry
// card. Avoids the full rerenderEntry flash when the user toggles a
// day chip or scrubs the time picker.
function updateEntryPreview(card, e) {
  const chip = card.querySelector('.next-preview');
  if (!chip) return;
  const nf = entryNextFire(e, state.deviceTime, state.tzOffsetMin);
  chip.textContent = '→ ' + nf.label;
  chip.style.color = nf.today ? 'var(--green)'
                  : nf.epoch ? 'var(--text-mid)'
                  : 'var(--orange)';
}

function buildZoneOptions(currentZone) {
  // Build option list anchored on known zones; also include the current
  // zone number even if it's no longer in the device's zone list, so we
  // don't silently mutate the user's value just by rendering.
  const seen = new Set();
  let opts = '';
  state.zones.forEach(z => {
    seen.add(z.id + 1);
    const sel = (z.id + 1 === currentZone) ? ' selected' : '';
    // value = 1-based wire zone number (functional); label "(#id)" = 0-based
    // storage id (display convention shared with HA's schedule tab).
    opts += '<option value="' + (z.id+1) + '"' + sel + '>' +
            escapeHtml(z.name) + ' (#' + z.id + ')</option>';
  });
  if (!seen.has(currentZone)) {
    opts = '<option value="' + currentZone + '" selected>Zone #' + (currentZone-1) +
           ' (missing)</option>' + opts;
  }
  return opts;
}

function escapeHtml(s) {
  return String(s).replace(/[&<>"']/g, c =>
    ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
}

// ── Entry add / delete ───────────────────────────────────────────────────────
function addEntry() {
  if (state.entries.length >= state.maxEntries) return;
  // Sensible defaults: first available zone, Smooth 1/8", 6:00 AM, every day.
  const firstZone = state.zones.length ? state.zones[0].id + 1 : 1;
  state.entries.push({
    zone: firstZone, mode: 2, depth: 1,
    hour: 6, minute: 0,
    days_mask: 127, enabled: 1,
  });
  renderAll();
  // Scroll the new entry into view.
  const el = document.getElementById('entries');
  const last = el.lastChild;
  if (last && last.scrollIntoView) last.scrollIntoView({behavior:'smooth', block:'center'});
}

function delEntry(idx) {
  state.entries.splice(idx, 1);
  renderAll();
}

// ── Save / clear ─────────────────────────────────────────────────────────────
function entriesToText(entries) {
  return entries.map(e =>
    [e.zone, e.mode, e.depth, e.hour, e.minute, e.days_mask, e.enabled].join(',')
  ).join(';');
}

async function saveAll() {
  const btn = document.getElementById('save-btn');
  const st = document.getElementById('save-status');
  btn.disabled = true; btn.textContent = 'Saving…';
  st.className = ''; st.textContent = '';
  try {
    const text = entriesToText(state.entries);
    const r = await fetch('/api/schedule', {
      method:'POST',
      headers:{'Content-Type':'application/x-www-form-urlencoded'},
      body: 'text=' + encodeURIComponent(text),
    });
    const d = await r.json();
    state.lastStatus = d.status || (d.ok ? 'ok' : 'failed');
    state.nextRun = d.next_run || null;
    state.deviceTime = d.now || state.deviceTime;
    renderStatus();
    if (d.ok) {
      st.className = 'ok';
      st.textContent = 'Saved ✓ ' + state.lastStatus;
    } else {
      st.className = 'err';
      st.textContent = state.lastStatus;
    }
  } catch (e) {
    st.className = 'err';
    st.textContent = 'Save failed: ' + (e.message||e);
  } finally {
    btn.disabled = false; btn.textContent = 'Save';
  }
}

async function setDelay(hours) {
  const st = document.getElementById('save-status');
  st.className = ''; st.textContent = '';
  try {
    const r = await fetch('/api/schedule/delay', {
      method: 'POST',
      headers: {'Content-Type': 'application/x-www-form-urlencoded'},
      body: 'hours=' + (hours | 0),
    });
    const d = await r.json();
    if (!d.ok) throw new Error(d.error || 'delay failed');
    state.delayUntil = d.delay_until || 0;
    // The server's next_run may have shifted past the delay window —
    // re-fetch to keep the page consistent.
    await init();
    st.className = 'ok';
    st.textContent = hours > 0
      ? ('Rain delay set for ' + hours + ' h.')
      : 'Rain delay cancelled.';
  } catch (e) {
    st.className = 'err';
    st.textContent = 'Delay failed: ' + (e.message || e);
  }
}

function setDelayCustom() {
  const inp = document.getElementById('delay-custom');
  const h = parseInt(inp.value, 10);
  if (!h || h < 1) return;
  setDelay(Math.min(h, 336));   // server clamps to 14 d but match here too
  inp.value = '';
}

async function clearAll() {
  if (!state.entries.length) return;
  if (!confirm('Remove all ' + state.entries.length + ' schedule entries?')) return;
  const btn = document.getElementById('save-btn');
  const st = document.getElementById('save-status');
  st.className = ''; st.textContent = '';
  try {
    const r = await fetch('/api/schedule/clear', {method:'POST'});
    const d = await r.json();
    if (!d.ok) throw new Error(d.error || 'clear failed');
    state.entries = [];
    state.lastStatus = 'cleared';
    state.nextRun = null;
    renderAll();
    st.className = 'ok';
    st.textContent = 'Schedule cleared.';
  } catch (e) {
    st.className = 'err';
    st.textContent = 'Clear failed: ' + (e.message||e);
  }
}

init();
</script>
</body>
</html>
)SCHEDHTML"
#endif /* IRRIGOTO_HTML_PAYLOAD */
