/* Auto-generated from fs.html -- edit the .html, then run regen.py */
#ifdef IRRIGOTO_HTML_PAYLOAD
R"FSHTML(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no">
<title>Filesystem &mdash; irrigoto</title>
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
</style>
</head>
<body>
<svg aria-hidden="true" width="0" height="0" style="position:absolute"><symbol id="i-chevron-left" viewBox="0 0 24 24"><path d="M15 6l-6 6 6 6"/></symbol><symbol id="i-upload" viewBox="0 0 24 24"><path d="M12 15V3M7 8l5-5 5 5M5 21h14"/></symbol><symbol id="i-refresh" viewBox="0 0 24 24"><path d="M20 12a8 8 0 1 1-2.3-5.7"/><path d="M20 4v5h-5"/></symbol><symbol id="i-folder" viewBox="0 0 24 24"><path d="M3 6a1 1 0 0 1 1-1h5l2 2h9a1 1 0 0 1 1 1v11a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1z"/></symbol><symbol id="i-file" viewBox="0 0 24 24"><path d="M6 3h8l4 4v13a1 1 0 0 1-1 1H6a1 1 0 0 1-1-1V4a1 1 0 0 1 1-1z"/><path d="M14 3v4h4"/></symbol><symbol id="i-download" viewBox="0 0 24 24"><path d="M12 3v12M7 10l5 5 5-5M5 21h14"/></symbol></svg>
<header>
  <a class="back" href="/" title="Back"><svg class="i"><use href="#i-chevron-left"/></svg></a>
  <a class="logo" href="/"><svg class="duck" width="26" height="22" viewBox="0 0 30 26" aria-hidden="true"><path d="M3 18c1-6 5-9 10-9 3 0 5 1 7 3l6-1-3 4c0 5-5 9-11 9S3 22 3 18z" fill="var(--pond)"/><circle cx="21.5" cy="12.5" r="3.6" fill="var(--pond)"/><path d="M24.5 12.5l4 1-3.5 1.5z" fill="var(--red)"/><circle cx="22" cy="12" r=".9" fill="var(--bg2)"/></svg>Irrigoto</a>
  <span class="hdr-title">Filesystem</span>
  <span class="usage" id="usage">&mdash;</span>
</header>
<main>

  <!-- Upload -->
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

  <!-- Directory tree -->
  <div class="card">
    <div class="sec-hdr">
      <span class="sec-title">Files</span>
      <button id="refresh-btn" onclick="loadTree()"><svg class="i"><use href="#i-refresh"/></svg>Refresh</button>
    </div>
    <div id="tree" class="tree"><div class="empty">Loading&hellip;</div></div>
  </div>

</main>
<script>
function fmtSize(b){
  if(b<1024) return b+'B';
  if(b<1048576) return (b/1024).toFixed(1)+'KB';
  return (b/1048576).toFixed(2)+'MB';
}
// .wbin files are binary water logs served as CSV -- show and download as .csv
function displayName(n){ return n.endsWith('.wbin')?n.slice(0,-5)+'.csv':n; }

function sumEntries(entries){
  if(!entries) return 0;
  return entries.reduce((s,e)=>s+(e.type==='file'?e.size:sumEntries(e.children)),0);
}

async function loadTree(){
  document.getElementById('tree').innerHTML='<div class="empty">Loading&hellip;</div>';
  try{
    const d=await fetch('/fs/list',{cache:'no-store'}).then(r=>r.json());
    const dataBytes=sumEntries(d.entries);
    document.getElementById('usage').textContent=
      fmtSize(dataBytes)+' files · '+fmtSize(d.used)+' / '+fmtSize(d.total)+' blocks';
    renderTree(d.entries, document.getElementById('tree'), 0);
  }catch(e){
    document.getElementById('tree').innerHTML='<div class="empty">Could not load &mdash; is storage mounted?</div>';
  }
}

function renderTree(entries, container, depth){
  if(depth===0) container.innerHTML='';
  if(!entries||!entries.length){
    if(depth===0) container.innerHTML='<div class="empty">Empty</div>';
    return;
  }
  entries.forEach(e=>{
    const row=document.createElement('div');
    row.className='dir-row';
    const indent='<span class="indent" style="width:'+(depth*16)+'px"></span>';
    if(e.type==='dir'){
      row.innerHTML=indent+
        '<span class="dir-icon"><svg class="i"><use href="#i-folder"/></svg></span>'+
        '<span class="dir-name">'+e.name+'/</span>';
      container.appendChild(row);
      if(e.children&&e.children.length)
        renderTree(e.children, container, depth+1);
    } else {
      row.innerHTML=indent+
        '<span class="file-icon"><svg class="i"><use href="#i-file"/></svg></span>'+
        '<span class="file-name">'+displayName(e.name)+'</span>'+
        '<span class="file-size">'+fmtSize(e.size)+'</span>'+
        '<span class="file-actions">'+
          '<a class="act-btn" href="/fs/download?path='+encodeURIComponent(e.path)+'" download="'+displayName(e.name)+'"><svg class="i"><use href="#i-download"/></svg>dl</a>'+
          '<button class="act-btn del" onclick="deleteFile(\''+e.path+'\')">del</button>'+
        '</span>';
      container.appendChild(row);
    }
  });
}

// Pre-fill upload path when file selected
document.getElementById('upload-file').addEventListener('change', function(){
  if(this.files[0]){
    const cur=document.getElementById('upload-path').value;
    const dir=cur.endsWith('/')?cur:cur.replace(/\/[^/]*$/,'/');
    document.getElementById('upload-path').value=dir+this.files[0].name;
  }
});

async function uploadFile(){
  const fileInp=document.getElementById('upload-file');
  const path=document.getElementById('upload-path').value.trim();
  const st=document.getElementById('upload-status');
  if(!fileInp.files[0]){st.textContent='Select a file first.';return;}
  if(!path.startsWith('/lfs/')){st.textContent='Path must start with /lfs/';return;}
  st.style.color='var(--text-mid)'; st.textContent='Uploading\u2026';
  const fd=new FormData();
  fd.append('path',path);
  fd.append('file',fileInp.files[0]);
  try{
    const r=await fetch('/fs/upload',{method:'POST',body:fd});
    const d=await r.json();
    if(d.ok){
      st.style.color='var(--green)';
      st.textContent='Uploaded '+fmtSize(d.size)+' to '+path;
      loadTree();
    } else {
      st.style.color='var(--red)'; st.textContent=d.error||'Upload failed.';
    }
  }catch(e){ st.style.color='var(--red)'; st.textContent='Error: '+e.message; }
}

async function deleteFile(path){
  if(!confirm('Delete '+path+'?')) return;
  try{
    const r=await fetch('/fs/delete',{method:'POST',
      body:'path='+encodeURIComponent(path),
      headers:{'Content-Type':'application/x-www-form-urlencoded'}});
    const text=await r.text();
    let d; try{d=JSON.parse(text);}catch(e){alert('Server error: '+text.substring(0,120));return;}
    if(d.ok) loadTree();
    else alert(d.error||'Delete failed.');
  }catch(e){ alert('Error: '+e.message); }
}

loadTree();
</script>
</body>
</html>
)FSHTML"
#endif /* IRRIGOTO_HTML_PAYLOAD */
