<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<title>Countdown</title>
<style>
  :root{
    --bg: #14171c;
    --card: #1c2028;
    --line: #2a2f3a;
    --accent: #ff6b4a;
    --text: #eef0f3;
    --muted: #8b93a1;
  }
  *{ box-sizing: border-box; }
  html, body{
    margin:0; padding:0; height:100%;
    background: var(--bg);
    font-family: -apple-system, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
    display:flex; align-items:center; justify-content:center;
    overflow:hidden;
  }
  .card{
    width: 100%; height:100%;
    background: var(--card);
    border: 1px solid var(--line);
    border-radius: 14px;
    display:flex; flex-direction:column;
    align-items:center; justify-content:center;
    padding: 18px 12px;
  }
  .label{
    color: var(--muted);
    font-size: 13px;
    letter-spacing: 0.06em;
    text-transform: uppercase;
    margin-bottom: 10px;
    text-align:center;
  }
  .units{
    display:flex; gap: 18px;
  }
  .unit{
    display:flex; flex-direction:column; align-items:center;
    min-width: 52px;
  }
  .num{
    font-size: 34px;
    font-weight: 700;
    color: var(--text);
    font-variant-numeric: tabular-nums;
    line-height:1;
  }
  .unit-label{
    margin-top: 6px;
    font-size: 10px;
    color: var(--muted);
    letter-spacing: 0.08em;
    text-transform: uppercase;
  }
  .sep{
    font-size: 34px;
    color: var(--line);
    align-self: flex-start;
    margin-top: 1px;
  }
  .bar-wrap{
    width: 80%;
    height: 4px;
    background: var(--line);
    border-radius: 2px;
    margin-top: 16px;
    overflow: hidden;
  }
  .bar{
    height: 100%;
    background: var(--accent);
    width: 0%;
    transition: width 0.6s ease;
  }
  .done{
    color: var(--accent);
    font-size: 20px;
    font-weight: 700;
    text-align:center;
  }
</style>
</head>
<body>
  <div class="card">
    <div class="label" id="label">deadline</div>
    <div id="timerArea">
      <div class="units">
        <div class="unit"><div class="num" id="d">00</div><div class="unit-label">dias</div></div>
        <div class="sep">:</div>
        <div class="unit"><div class="num" id="h">00</div><div class="unit-label">horas</div></div>
        <div class="sep">:</div>
        <div class="unit"><div class="num" id="m">00</div><div class="unit-label">min</div></div>
        <div class="sep">:</div>
        <div class="unit"><div class="num" id="s">00</div><div class="unit-label">seg</div></div>
      </div>
      <div class="bar-wrap" id="barWrap"><div class="bar" id="bar"></div></div>
    </div>
  </div>

<script>
  const params = new URLSearchParams(window.location.search);

  const toParam = params.get('to');
  const labelParam = params.get('label');
  const startParam = params.get('start');

  // Trata espaços na URL e valida o Date objeto
  function parseDate(str) {
    if (!str) return null;
    const formatted = str.trim().replace(' ', 'T');
    const d = new Date(formatted);
    return isNaN(d.getTime()) ? null : d;
  }

  const deadline = parseDate(toParam) || new Date(Date.now() + 7 * 24 * 60 * 60 * 1000);
  const start = parseDate(startParam);

  document.getElementById('label').textContent = labelParam || 'deadline';

  // Se não houver data de início, oculta a barra uma única vez fora do loop
  const barWrap = document.getElementById('barWrap');
  if (!start && barWrap) {
    barWrap.style.display = 'none';
  }

  function pad(n){ return String(n).padStart(2, '0'); }

  let timerId = null;

  function tick(){
    const now = new Date();
    const diff = deadline - now;

    if (diff <= 0){
      document.getElementById('timerArea').innerHTML = '<div class="done">prazo encerrado</div>';
      if (timerId) clearInterval(timerId); // Interrompe o loop quando expira
      return;
    }

    const totalSeconds = Math.floor(diff / 1000);
    const days = Math.floor(totalSeconds / 86400);
    const hours = Math.floor((totalSeconds % 86400) / 3600);
    const minutes = Math.floor((totalSeconds % 3600) / 60);
    const seconds = totalSeconds % 60;

    document.getElementById('d').textContent = pad(days);
    document.getElementById('h').textContent = pad(hours);
    document.getElementById('m').textContent = pad(minutes);
    document.getElementById('s').textContent = pad(seconds);

    if (start){
      const totalSpan = deadline - start;
      const elapsed = now - start;
      const pct = Math.min(100, Math.max(0, (elapsed / totalSpan) * 100));
      document.getElementById('bar').style.width = pct + '%';
    }
  }

  tick();
  timerId = setInterval(tick, 1000);
</script>
</body>
</html>
