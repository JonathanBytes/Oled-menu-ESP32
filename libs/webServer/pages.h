// Embed the HTML as a constant string
const char index_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <link rel="icon" type="image/svg+xml" href="./penguin.svg" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>ESPMIDI</title>
    <script type="module" crossorigin>(function(){const t=document.createElement("link").relList;if(t&&t.supports&&t.supports("modulepreload"))return;for(const e of document.querySelectorAll('link[rel="modulepreload"]'))r(e);new MutationObserver(e=>{for(const c of e)if(c.type==="childList")for(const o of c.addedNodes)o.tagName==="LINK"&&o.rel==="modulepreload"&&r(o)}).observe(document,{childList:!0,subtree:!0});function i(e){const c={};return e.integrity&&(c.integrity=e.integrity),e.referrerPolicy&&(c.referrerPolicy=e.referrerPolicy),e.crossOrigin==="use-credentials"?c.credentials="include":e.crossOrigin==="anonymous"?c.credentials="omit":c.credentials="same-origin",c}function r(e){if(e.ep)return;e.ep=!0;const c=i(e);fetch(e.href,c)}})();const l="data:image/svg+xml,%3c?xml%20version='1.0'%20encoding='iso-8859-1'?%3e%3c!--%20Uploaded%20to:%20SVG%20Repo,%20www.svgrepo.com,%20Generator:%20SVG%20Repo%20Mixer%20Tools%20--%3e%3csvg%20height='800px'%20width='800px'%20version='1.1'%20id='Layer_1'%20xmlns='http://www.w3.org/2000/svg'%20xmlns:xlink='http://www.w3.org/1999/xlink'%20viewBox='0%200%20512.001%20512.001'%20xml:space='preserve'%3e%3cg%3e%3cpath%20style='fill:%23333E48;'%20d='M343.136,503.866c36.185,0,65.521-29.336,65.521-65.522V160.791%20c0-84.309-68.347-152.657-152.657-152.657c-84.311,0-152.657,68.347-152.657,152.657v277.553c0,36.187,29.334,65.522,65.521,65.522%20H343.136z'/%3e%3cpath%20style='fill:%23333E48;'%20d='M101.158,325.044c14.712,14.709,38.557,14.709,53.265,0c14.707-14.71,14.707-38.554,0-53.262%20l-91.134-91.133c-29.415,29.415-29.415,77.106-0.002,106.523L101.158,325.044z'/%3e%3cpath%20style='fill:%23333E48;'%20d='M410.842,325.044c-14.712,14.709-38.557,14.709-53.265,0c-14.707-14.71-14.707-38.554,0-53.262%20l91.134-91.133c29.414,29.415,29.414,77.106,0,106.523L410.842,325.044z'/%3e%3c/g%3e%3cpath%20style='fill:%23E8E8E8;'%20d='M256.001,294.739c-46.041,0-83.364,37.324-83.364,83.365v125.762h166.729V378.105%20C339.365,332.063,302.041,294.739,256.001,294.739z'/%3e%3cpath%20style='fill:%23FFFFFF;'%20d='M354.804,178.141v-43.709c0-29.978-24.304-54.28-54.28-54.28c-18.437,0-34.714,9.197-44.524,23.244%20c-9.811-14.046-26.088-23.244-44.524-23.244c-29.977,0-54.28,24.303-54.28,54.28v43.709c-6.756,8.449-10.807,19.16-10.807,30.819%20c0,27.283,22.119,49.401,49.403,49.401h120.416c27.283,0,49.401-22.118,49.401-49.401%20C365.609,197.301,361.56,186.59,354.804,178.141z'/%3e%3cg%3e%3cpath%20style='fill:%23ED9900;'%20d='M280.749,188.989c0-13.667-11.08-24.748-24.748-24.748c-13.668,0-24.748,11.083-24.748,24.748%20c0,13.669,24.748,24.749,24.748,24.749S280.749,202.657,280.749,188.989z'/%3e%3cpath%20style='fill:%23ED9900;'%20d='M211.744,467.171h-40.43c-10.132,0-18.348,8.216-18.348,18.349c0,10.135,8.215,18.348,18.348,18.348%20h40.43c10.135,0,18.349-8.213,18.349-18.348C230.093,475.387,221.879,467.171,211.744,467.171z'/%3e%3cpath%20style='fill:%23ED9900;'%20d='M300.253,467.171h40.432c10.134,0,18.348,8.216,18.348,18.349c0,10.135-8.214,18.348-18.348,18.348%20h-40.432c-10.131,0-18.345-8.213-18.345-18.348C281.907,475.387,290.122,467.171,300.253,467.171z'/%3e%3c/g%3e%3cpath%20style='fill:%231E252B;'%20d='M454.463,174.897c-3.178-3.175-8.327-3.175-11.503,0l-26.168,26.168v-40.274%20C416.791,72.131,344.661,0,256.001,0S95.209,72.131,95.209,160.791v40.274l-26.168-26.168c-3.178-3.175-8.327-3.175-11.503,0%20C25.001,207.436,25,260.381,57.536,292.922l37.673,37.676v107.747c0,40.613,33.041,73.656,73.655,73.656h174.272%20c40.613,0,73.655-33.043,73.655-73.656V330.598l37.673-37.676C487.001,260.381,487,207.436,454.463,174.897z%20M95.209,307.591%20l-26.17-26.171c-24.248-24.253-26.051-62.581-5.403-88.923l31.573,31.574V307.591z%20M211.744,495.733h-40.43%20c-5.632,0-10.214-4.582-10.214-10.214c0-5.632,4.582-10.215,10.214-10.215h40.43c5.632,0,10.215,4.583,10.215,10.215%20C221.959,491.152,217.376,495.733,211.744,495.733z%20M275.825,495.733h-39.65c1.321-3.144,2.052-6.595,2.052-10.214%20c0-14.603-11.88-26.482-26.482-26.482H180.77v-80.932c0-41.483,33.749-75.232,75.231-75.232s75.231,33.749,75.231,75.232v80.932%20h-30.974c-14.603,0-26.482,11.88-26.482,26.482C273.773,489.138,274.505,492.589,275.825,495.733z%20M340.687,495.733h-40.43%20c-5.632,0-10.215-4.582-10.215-10.214c0-5.632,4.583-10.215,10.215-10.215h40.43c5.632,0,10.214,4.583,10.214,10.215%20C350.901,491.152,346.319,495.733,340.687,495.733z%20M400.523,438.344c0,23.263-13.922,43.323-33.862,52.324%20c0.33-1.666,0.506-3.388,0.506-5.149c0-12.248-8.358-22.575-19.67-25.59v-81.824c0-50.453-41.046-91.499-91.498-91.499%20s-91.498,41.047-91.498,91.499v81.824c-11.311,3.014-19.67,13.342-19.67,25.59c0,1.761,0.177,3.483,0.506,5.149%20c-19.941-9.001-33.862-29.061-33.862-52.324V160.791C111.477,81.1,176.309,16.267,256.001,16.267S400.524,81.1,400.524,160.791%20v277.553H400.523z%20M442.961,281.42l-26.17,26.171v-83.52l31.573-31.574C469.013,218.839,467.21,257.167,442.961,281.42z%20M311.954,135.375c-5.921,0-10.725,4.801-10.725,10.726c0,5.922,4.803,10.726,10.725,10.726c5.924,0,10.726-4.803,10.726-10.726%20C322.68,140.176,317.878,135.375,311.954,135.375z%20M200.046,135.375c-5.924,0-10.726,4.801-10.726,10.726%20c0,5.922,4.802,10.726,10.726,10.726c5.921,0,10.725-4.803,10.725-10.726C210.77,140.176,205.967,135.375,200.046,135.375z'/%3e%3c/svg%3e";document.querySelector("#app").innerHTML=`
  <div>
    <a href="/">
      <img src="${l}" class="logo" alt="Vite logo" />
    </a>
    <h1>ESPMidi Configurator</h1>
      <p>ESPMidi is a MIDI controller that uses the ESP32 microcontroller to act as simple midi Guitar Footswitch.</p>
    <p>This page is a work in progress.</p>
    <a href="todo"> TODO </a>
    <p class="gray">
      Made with love by <a href="https://github.com/JonathanBytes" target="_blank">JonathanBytes</a>
    </p>
  </div>
`;</script>
    <style rel="stylesheet" crossorigin>:root{font-family:Inter,system-ui,Avenir,Helvetica,Arial,sans-serif;line-height:1.5;font-weight:400;color-scheme:light dark;color:#ffffffde;background-color:#242424;font-synthesis:none;text-rendering:optimizeLegibility;-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale}a{font-weight:500;color:#646cff;text-decoration:inherit}a:hover{color:#535bf2}body{margin:0;display:flex;place-items:center;min-width:320px;min-height:100vh}h1{font-size:3.2em;line-height:1.1}#app{max-width:1280px;margin:0 auto;padding:2rem;text-align:center}.logo{height:6em;padding:1.5em;will-change:filter;transition:filter .3s}.logo:hover{filter:drop-shadow(0 0 2em #646cffaa)}.logo.vanilla:hover{filter:drop-shadow(0 0 2em #f7df1eaa)}.card{padding:2em}.gray{color:#888}button{border-radius:8px;border:1px solid transparent;padding:.6em 1.2em;font-size:1em;font-weight:500;font-family:inherit;background-color:#1a1a1a;cursor:pointer;transition:border-color .25s}button:hover{border-color:#646cff}button:focus,button:focus-visible{outline:4px auto -webkit-focus-ring-color}@media (prefers-color-scheme: light){:root{color:#213547;background-color:#fff}a:hover{color:#747bff}button{background-color:#f9f9f9}}</style>
  </head>
  <body>
    <div id="app"></div>
  </body>
</html>
)rawliteral";

// Función para manejar la página principal
void handleRoot() { server.send(200, "text/html", index_html); }

const char todo_html[] PROGMEM = R"rawliteral(
  
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <link rel="icon" type="image/svg+xml" href="./penguin.svg" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>ESPMIDI</title>
    <script type="module" crossorigin>(function(){const t=document.createElement("link").relList;if(t&&t.supports&&t.supports("modulepreload"))return;for(const e of document.querySelectorAll('link[rel="modulepreload"]'))r(e);new MutationObserver(e=>{for(const c of e)if(c.type==="childList")for(const o of c.addedNodes)o.tagName==="LINK"&&o.rel==="modulepreload"&&r(o)}).observe(document,{childList:!0,subtree:!0});function i(e){const c={};return e.integrity&&(c.integrity=e.integrity),e.referrerPolicy&&(c.referrerPolicy=e.referrerPolicy),e.crossOrigin==="use-credentials"?c.credentials="include":e.crossOrigin==="anonymous"?c.credentials="omit":c.credentials="same-origin",c}function r(e){if(e.ep)return;e.ep=!0;const c=i(e);fetch(e.href,c)}})();const l="data:image/svg+xml,%3c?xml%20version='1.0'%20encoding='iso-8859-1'?%3e%3c!--%20Uploaded%20to:%20SVG%20Repo,%20www.svgrepo.com,%20Generator:%20SVG%20Repo%20Mixer%20Tools%20--%3e%3csvg%20height='800px'%20width='800px'%20version='1.1'%20id='Layer_1'%20xmlns='http://www.w3.org/2000/svg'%20xmlns:xlink='http://www.w3.org/1999/xlink'%20viewBox='0%200%20512.001%20512.001'%20xml:space='preserve'%3e%3cg%3e%3cpath%20style='fill:%23333E48;'%20d='M343.136,503.866c36.185,0,65.521-29.336,65.521-65.522V160.791%20c0-84.309-68.347-152.657-152.657-152.657c-84.311,0-152.657,68.347-152.657,152.657v277.553c0,36.187,29.334,65.522,65.521,65.522%20H343.136z'/%3e%3cpath%20style='fill:%23333E48;'%20d='M101.158,325.044c14.712,14.709,38.557,14.709,53.265,0c14.707-14.71,14.707-38.554,0-53.262%20l-91.134-91.133c-29.415,29.415-29.415,77.106-0.002,106.523L101.158,325.044z'/%3e%3cpath%20style='fill:%23333E48;'%20d='M410.842,325.044c-14.712,14.709-38.557,14.709-53.265,0c-14.707-14.71-14.707-38.554,0-53.262%20l91.134-91.133c29.414,29.415,29.414,77.106,0,106.523L410.842,325.044z'/%3e%3c/g%3e%3cpath%20style='fill:%23E8E8E8;'%20d='M256.001,294.739c-46.041,0-83.364,37.324-83.364,83.365v125.762h166.729V378.105%20C339.365,332.063,302.041,294.739,256.001,294.739z'/%3e%3cpath%20style='fill:%23FFFFFF;'%20d='M354.804,178.141v-43.709c0-29.978-24.304-54.28-54.28-54.28c-18.437,0-34.714,9.197-44.524,23.244%20c-9.811-14.046-26.088-23.244-44.524-23.244c-29.977,0-54.28,24.303-54.28,54.28v43.709c-6.756,8.449-10.807,19.16-10.807,30.819%20c0,27.283,22.119,49.401,49.403,49.401h120.416c27.283,0,49.401-22.118,49.401-49.401%20C365.609,197.301,361.56,186.59,354.804,178.141z'/%3e%3cg%3e%3cpath%20style='fill:%23ED9900;'%20d='M280.749,188.989c0-13.667-11.08-24.748-24.748-24.748c-13.668,0-24.748,11.083-24.748,24.748%20c0,13.669,24.748,24.749,24.748,24.749S280.749,202.657,280.749,188.989z'/%3e%3cpath%20style='fill:%23ED9900;'%20d='M211.744,467.171h-40.43c-10.132,0-18.348,8.216-18.348,18.349c0,10.135,8.215,18.348,18.348,18.348%20h40.43c10.135,0,18.349-8.213,18.349-18.348C230.093,475.387,221.879,467.171,211.744,467.171z'/%3e%3cpath%20style='fill:%23ED9900;'%20d='M300.253,467.171h40.432c10.134,0,18.348,8.216,18.348,18.349c0,10.135-8.214,18.348-18.348,18.348%20h-40.432c-10.131,0-18.345-8.213-18.345-18.348C281.907,475.387,290.122,467.171,300.253,467.171z'/%3e%3c/g%3e%3cpath%20style='fill:%231E252B;'%20d='M454.463,174.897c-3.178-3.175-8.327-3.175-11.503,0l-26.168,26.168v-40.274%20C416.791,72.131,344.661,0,256.001,0S95.209,72.131,95.209,160.791v40.274l-26.168-26.168c-3.178-3.175-8.327-3.175-11.503,0%20C25.001,207.436,25,260.381,57.536,292.922l37.673,37.676v107.747c0,40.613,33.041,73.656,73.655,73.656h174.272%20c40.613,0,73.655-33.043,73.655-73.656V330.598l37.673-37.676C487.001,260.381,487,207.436,454.463,174.897z%20M95.209,307.591%20l-26.17-26.171c-24.248-24.253-26.051-62.581-5.403-88.923l31.573,31.574V307.591z%20M211.744,495.733h-40.43%20c-5.632,0-10.214-4.582-10.214-10.214c0-5.632,4.582-10.215,10.214-10.215h40.43c5.632,0,10.215,4.583,10.215,10.215%20C221.959,491.152,217.376,495.733,211.744,495.733z%20M275.825,495.733h-39.65c1.321-3.144,2.052-6.595,2.052-10.214%20c0-14.603-11.88-26.482-26.482-26.482H180.77v-80.932c0-41.483,33.749-75.232,75.231-75.232s75.231,33.749,75.231,75.232v80.932%20h-30.974c-14.603,0-26.482,11.88-26.482,26.482C273.773,489.138,274.505,492.589,275.825,495.733z%20M340.687,495.733h-40.43%20c-5.632,0-10.215-4.582-10.215-10.214c0-5.632,4.583-10.215,10.215-10.215h40.43c5.632,0,10.214,4.583,10.214,10.215%20C350.901,491.152,346.319,495.733,340.687,495.733z%20M400.523,438.344c0,23.263-13.922,43.323-33.862,52.324%20c0.33-1.666,0.506-3.388,0.506-5.149c0-12.248-8.358-22.575-19.67-25.59v-81.824c0-50.453-41.046-91.499-91.498-91.499%20s-91.498,41.047-91.498,91.499v81.824c-11.311,3.014-19.67,13.342-19.67,25.59c0,1.761,0.177,3.483,0.506,5.149%20c-19.941-9.001-33.862-29.061-33.862-52.324V160.791C111.477,81.1,176.309,16.267,256.001,16.267S400.524,81.1,400.524,160.791%20v277.553H400.523z%20M442.961,281.42l-26.17,26.171v-83.52l31.573-31.574C469.013,218.839,467.21,257.167,442.961,281.42z%20M311.954,135.375c-5.921,0-10.725,4.801-10.725,10.726c0,5.922,4.803,10.726,10.725,10.726c5.924,0,10.726-4.803,10.726-10.726%20C322.68,140.176,317.878,135.375,311.954,135.375z%20M200.046,135.375c-5.924,0-10.726,4.801-10.726,10.726%20c0,5.922,4.802,10.726,10.726,10.726c5.921,0,10.725-4.803,10.725-10.726C210.77,140.176,205.967,135.375,200.046,135.375z'/%3e%3c/svg%3e";document.querySelector("#app").innerHTML=`
  <div>
    <a href="/">
      <img src="${l}" class="logo" alt="Vite logo" />
    </a>
    <h2>TODO</h2>
    <p>
      Home Screen, Bank Customization, Preset Editor, Global Settings, Live Preview.
    </p>
    <p class="gray">
      Made with love by <a href="https://github.com/JonathanBytes" target="_blank">JonathanBytes</a>
    </p>
    
  </div>
`;</script>
    <style rel="stylesheet" crossorigin>:root{font-family:Inter,system-ui,Avenir,Helvetica,Arial,sans-serif;line-height:1.5;font-weight:400;color-scheme:light dark;color:#ffffffde;background-color:#242424;font-synthesis:none;text-rendering:optimizeLegibility;-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale}a{font-weight:500;color:#646cff;text-decoration:inherit}a:hover{color:#535bf2}body{margin:0;display:flex;place-items:center;min-width:320px;min-height:100vh}h1{font-size:3.2em;line-height:1.1}#app{max-width:1280px;margin:0 auto;padding:2rem;text-align:center}.logo{height:6em;padding:1.5em;will-change:filter;transition:filter .3s}.logo:hover{filter:drop-shadow(0 0 2em #646cffaa)}.logo.vanilla:hover{filter:drop-shadow(0 0 2em #f7df1eaa)}.card{padding:2em}.gray{color:#888}button{border-radius:8px;border:1px solid transparent;padding:.6em 1.2em;font-size:1em;font-weight:500;font-family:inherit;background-color:#1a1a1a;cursor:pointer;transition:border-color .25s}button:hover{border-color:#646cff}button:focus,button:focus-visible{outline:4px auto -webkit-focus-ring-color}@media (prefers-color-scheme: light){:root{color:#213547;background-color:#fff}a:hover{color:#747bff}button{background-color:#f9f9f9}}</style>
  </head>
  <body>
    <div id="app"></div>
  </body>
</html>
)rawliteral";

void handleTODO() { server.send(200, "text/html", todo_html); }
// Función para manejar la configuración del banco actual
void handleSetBank() {}

void handleEditBank() {}

void handleSaveBank() {}

void handleNotFound() { server.send(404, "text/plain", "Not found"); }
