// ==========================================================================
// ACADPULSE — CYBER-COCKPIT & THOR THUNDER ENGINE
// Procedural Lightning Storm, Bi-Directional Scroll-Reveal & Apple Glass Specular
// ==========================================================================

function showToast(message, type = 'primary') {
  const toastEl = document.getElementById('liveToast');
  if (!toastEl) return;
  const msgEl = document.getElementById('toastMessage');
  if (msgEl) msgEl.textContent = message;

  toastEl.className = `toast align-items-center text-bg-${type} border-0 shadow-lg`;
  const toast = new bootstrap.Toast(toastEl, { delay: 3500 });
  toast.show();
}

async function apiFetch(url, options = {}) {
  try {
    const res = await fetch(url, {
      headers: {
        'Content-Type': 'application/json',
        ...(options.headers || {})
      },
      ...options
    });
    if (!res.ok) {
      throw new Error(`HTTP error ${res.status}`);
    }
    return await res.json();
  } catch (err) {
    console.error('API Error:', err);
    showToast(`Request failed: ${err.message}`, 'danger');
    throw err;
  }
}

// --------------------------------------------------------------------------
// Thor Lightning / Thunderbolts Canvas Engine
// Live procedural electric storm dancing around the central AcadPulse ⚡ logo
// --------------------------------------------------------------------------

function initThunderEngine() {
  const canvas = document.getElementById('thunderCanvas');
  if (!canvas) return;
  const ctx = canvas.getContext('2d');
  if (!ctx) return;

  let width = (canvas.width = window.innerWidth);
  let height = (canvas.height = window.innerHeight);

  window.addEventListener('resize', () => {
    if (!canvas) return;
    width = canvas.width = window.innerWidth;
    height = canvas.height = window.innerHeight;
  });

  // Lightning Bolt Data Structures
  const bolts = [];
  const sparks = [];
  let flashOpacity = 0;

  class Bolt {
    constructor(startX, startY, endX, endY, branches = 2) {
      this.segments = [];
      this.alpha = 1;
      this.branches = branches;
      this.build(startX, startY, endX, endY);
    }

    build(x1, y1, x2, y2) {
      const dx = x2 - x1;
      const dy = y2 - y1;
      const dist = Math.hypot(dx, dy);
      const steps = Math.max(8, Math.floor(dist / 22));

      let curX = x1;
      let curY = y1;
      this.segments.push({ x1: curX, y1: curY, x2: curX, y2: curY });

      for (let i = 1; i <= steps; i++) {
        const progress = i / steps;
        const targetX = x1 + dx * progress;
        const targetY = y1 + dy * progress;

        // Perpendicular fractal jitter
        const normalX = -dy / dist;
        const normalY = dx / dist;
        const jitter = (Math.random() - 0.5) * 38;

        const nextX = i === steps ? x2 : targetX + normalX * jitter;
        const nextY = i === steps ? y2 : targetY + normalY * jitter;

        this.segments.push({ x1: curX, y1: curY, x2: nextX, y2: nextY });

        // Branching secondary forks
        if (this.branches > 0 && Math.random() < 0.28 && i > 2 && i < steps - 1) {
          const branchLength = dist * (0.2 + Math.random() * 0.25);
          const angle = Math.atan2(dy, dx) + (Math.random() - 0.5) * 1.2;
          const bx2 = nextX + Math.cos(angle) * branchLength;
          const by2 = nextY + Math.sin(angle) * branchLength;
          bolts.push(new Bolt(nextX, nextY, bx2, by2, this.branches - 1));
        }

        curX = nextX;
        curY = nextY;
      }

      // Spawn impact sparks
      for (let s = 0; s < 6; s++) {
        sparks.push({
          x: x2,
          y: y2,
          vx: (Math.random() - 0.5) * 8,
          vy: (Math.random() - 0.5) * 8,
          life: 1,
          decay: 0.04 + Math.random() * 0.04
        });
      }
    }

    draw(ctx) {
      ctx.save();
      ctx.lineCap = 'round';

      // Outer Corona Glow
      ctx.strokeStyle = `rgba(139, 92, 246, ${this.alpha * 0.55})`;
      ctx.lineWidth = 6;
      ctx.beginPath();
      for (const seg of this.segments) {
        ctx.moveTo(seg.x1, seg.y1);
        ctx.lineTo(seg.x2, seg.y2);
      }
      ctx.stroke();

      // Middle Cyan Arc
      ctx.strokeStyle = `rgba(56, 189, 248, ${this.alpha * 0.85})`;
      ctx.lineWidth = 3;
      ctx.beginPath();
      for (const seg of this.segments) {
        ctx.moveTo(seg.x1, seg.y1);
        ctx.lineTo(seg.x2, seg.y2);
      }
      ctx.stroke();

      // Core White Plasma
      ctx.strokeStyle = `rgba(255, 255, 255, ${this.alpha})`;
      ctx.lineWidth = 1.5;
      ctx.beginPath();
      for (const seg of this.segments) {
        ctx.moveTo(seg.x1, seg.y1);
        ctx.lineTo(seg.x2, seg.y2);
      }
      ctx.stroke();

      ctx.restore();
    }
  }

  // Trigger electric bolt targeting near center emblem
  function spawnThunderbolt() {
    const centerX = width / 2;
    const centerY = height * 0.44;

    // Originates from sky / perimeter
    const side = Math.random();
    let sx, sy;
    if (side < 0.5) {
      sx = centerX + (Math.random() - 0.5) * width * 0.7;
      sy = Math.random() * 80;
    } else if (side < 0.75) {
      sx = Math.random() * 120;
      sy = centerY + (Math.random() - 0.5) * height * 0.5;
    } else {
      sx = width - Math.random() * 120;
      sy = centerY + (Math.random() - 0.5) * height * 0.5;
    }

    // Strike around the AcadPulse emblem
    const tx = centerX + (Math.random() - 0.5) * 220;
    const ty = centerY + (Math.random() - 0.5) * 200;

    bolts.push(new Bolt(sx, sy, tx, ty, 2));
    flashOpacity = 0.22;
  }

  let lastSpawn = 0;
  function loop(timestamp) {
    // Semi-clear for electric trail
    ctx.clearRect(0, 0, width, height);

    if (flashOpacity > 0.01) {
      ctx.fillStyle = `rgba(139, 92, 246, ${flashOpacity * 0.25})`;
      ctx.fillRect(0, 0, width, height);
      flashOpacity *= 0.85;
    }

    if (timestamp - lastSpawn > 450 + Math.random() * 850) {
      spawnThunderbolt();
      lastSpawn = timestamp;
    }

    // Draw and fade bolts
    for (let i = bolts.length - 1; i >= 0; i--) {
      const b = bolts[i];
      b.draw(ctx);
      b.alpha -= 0.055;
      if (b.alpha <= 0) {
        bolts.splice(i, 1);
      }
    }

    // Draw and fade sparks
    for (let i = sparks.length - 1; i >= 0; i--) {
      const s = sparks[i];
      s.x += s.vx;
      s.y += s.vy;
      s.life -= s.decay;

      if (s.life > 0) {
        ctx.fillStyle = `rgba(56, 189, 248, ${s.life})`;
        ctx.beginPath();
        ctx.arc(s.x, s.y, 2, 0, Math.PI * 2);
        ctx.fill();
      } else {
        sparks.splice(i, 1);
      }
    }

    requestAnimationFrame(loop);
  }

  requestAnimationFrame(loop);
}

// --------------------------------------------------------------------------
// Bi-Directional Scroll-Reveal Observer
// Fades in & blurs out smoothly both when scrolling DOWN and scrolling UP!
// --------------------------------------------------------------------------

let scrollObserver = null;

function initScrollReveal(scope = document) {
  if (!('IntersectionObserver' in window)) {
    const all = scope.querySelectorAll('.reveal-on-scroll');
    all.forEach(el => el.classList.add('revealed'));
    return;
  }

  if (!scrollObserver) {
    const observerOptions = {
      root: null,
      rootMargin: '0px 0px -100px 0px',
      threshold: 0.14
    };

    scrollObserver = new IntersectionObserver((entries) => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          entry.target.classList.add('revealed');
        } else {
          // Allow re-triggering fade in / fade out when user scrolls back UP!
          const rect = entry.target.getBoundingClientRect();
          if (rect.top > window.innerHeight * 0.95 || rect.bottom < 0) {
            entry.target.classList.remove('revealed');
          }
        }
      });
    }, observerOptions);
  }

  const elements = scope.querySelectorAll('.reveal-on-scroll');
  elements.forEach((el, index) => {
    const rect = el.getBoundingClientRect();
    if (rect.top < window.innerHeight && rect.bottom > 80) {
      setTimeout(() => {
        el.classList.add('revealed');
      }, Math.min(index * 50, 300));
    }
    scrollObserver.observe(el);
  });

  attachSpecularTracking(scope);
}

// --------------------------------------------------------------------------
// Apple Liquid Glass Specular Cursor Reflection
// --------------------------------------------------------------------------

function attachSpecularTracking(scope = document) {
  const cards = scope.querySelectorAll('.game-card, .apple-glass, .stat-card, .apple-glass-heading, .card, .cockpit-card');
  cards.forEach(card => {
    if (card._hasSpecular) return;
    card._hasSpecular = true;

    card.addEventListener('mousemove', (e) => {
      const rect = card.getBoundingClientRect();
      const x = e.clientX - rect.left;
      const y = e.clientY - rect.top;
      card.style.setProperty('--mouse-x', `${x}px`);
      card.style.setProperty('--mouse-y', `${y}px`);
    });

    card.addEventListener('mouseleave', () => {
      card.style.setProperty('--mouse-x', `-999px`);
      card.style.setProperty('--mouse-y', `-999px`);
    });
  });
}

// --------------------------------------------------------------------------
// Dashboard Navbar Scroll Revealer (Clean Hero -> Reveals Past Cover)
// --------------------------------------------------------------------------

function initDashboardNavbarReveal() {
  const navbar = document.getElementById('appMainNavbar');
  if (!navbar || !navbar.classList.contains('app-navbar-dashboard')) return;

  // Trigger navbar after user scrolls 2 to 3 times past the front hero screen
  const triggerOffset = Math.max(window.innerHeight * 0.72, 620);

  function checkNavbar() {
    if (window.scrollY > triggerOffset) {
      navbar.classList.add('navbar-visible');
    } else {
      navbar.classList.remove('navbar-visible');
    }
  }

  window.addEventListener('scroll', checkNavbar, { passive: true });
  checkNavbar();
}

// --------------------------------------------------------------------------
// Fernwood Hero Showcase Interactive Animations (Gauge & Progress Bars)
// --------------------------------------------------------------------------

function initFernwoodHeroAnimations() {
  // Animate speedometer gauge arc
  const gaugePath = document.querySelector('.gauge-meter-path');
  if (gaugePath) {
    gaugePath.style.strokeDasharray = '235.6';
    gaugePath.style.strokeDashoffset = '235.6';
    setTimeout(() => {
      gaugePath.style.transition = 'stroke-dashoffset 1.8s cubic-bezier(0.16, 1, 0.3, 1)';
      gaugePath.style.strokeDashoffset = '18.8'; // 92% of arc
    }, 400);
  }

  // Animate horizontal progress bars in left card
  const bars = document.querySelectorAll('.card-left-tilt .bar-fill');
  bars.forEach((bar, i) => {
    const targetW = bar.style.width;
    bar.style.width = '0%';
    setTimeout(() => {
      bar.style.transition = 'width 1.2s cubic-bezier(0.16, 1, 0.3, 1)';
      bar.style.width = targetW;
    }, 300 + i * 120);
  });
}

function initFloatingHeaderScroll() {
  const header = document.getElementById('siteFloatingHeader');
  if (!header) return;

  function onScroll() {
    if (window.scrollY > 40) {
      header.classList.add('header-scrolled');
    } else {
      header.classList.remove('header-scrolled');
    }
  }

  window.addEventListener('scroll', onScroll, { passive: true });
  onScroll();
}

// Initialize on DOM Ready
document.addEventListener('DOMContentLoaded', () => {
  initThunderEngine();
  initDashboardNavbarReveal();
  initFloatingHeaderScroll();
  initFernwoodHeroAnimations();
  initScrollReveal();

  // Re-observe elements on tab clicks
  document.querySelectorAll('button[data-bs-toggle="pill"], button[data-bs-toggle="tab"]').forEach(tabTrigger => {
    tabTrigger.addEventListener('shown.bs.tab', (event) => {
      const targetSelector = event.target.getAttribute('data-bs-target');
      if (targetSelector) {
        const targetPane = document.querySelector(targetSelector);
        if (targetPane) {
          initScrollReveal(targetPane);
        }
      }
    });
  });
});
