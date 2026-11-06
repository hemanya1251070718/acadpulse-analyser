"""
Refactors frontend/static/js/main.js to eliminate infinite looping animations
and update selectors for the flattened metric deck.
"""

main_js_content = """// ==========================================================================
// ACADPULSE — SYSTEM UI & PURPOSEFUL INTERACTION ENGINE
// Clean UI/UX: Purposeful one-time state transitions, no infinite looping animations
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
// Bi-Directional Scroll-Reveal Observer (Purposeful One-Time Entrance)
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
}

// --------------------------------------------------------------------------
// Dashboard Navbar Scroll Revealer
// --------------------------------------------------------------------------

function initDashboardNavbarReveal() {
  const navbar = document.getElementById('appMainNavbar');
  if (!navbar || !navbar.classList.contains('app-navbar-dashboard')) return;

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
// Hero Metric Deck: Intentional One-Time Progress Fill & Gauge Animation
// --------------------------------------------------------------------------

function initFernwoodHeroAnimations() {
  // Animate speedometer gauge arc once on load
  const gaugePath = document.querySelector('.gauge-meter-path');
  if (gaugePath) {
    gaugePath.style.strokeDasharray = '235.6';
    gaugePath.style.strokeDashoffset = '235.6';
    setTimeout(() => {
      gaugePath.style.transition = 'stroke-dashoffset 1.4s cubic-bezier(0.16, 1, 0.3, 1)';
      gaugePath.style.strokeDashoffset = '18.8'; // 92% of arc
    }, 350);
  }

  // Animate horizontal progress bars once on load
  const bars = document.querySelectorAll('.metric-deck-card .bar-fill, .card-left-tilt .bar-fill');
  bars.forEach((bar, i) => {
    const targetW = bar.style.width;
    bar.style.width = '0%';
    setTimeout(() => {
      bar.style.transition = 'width 1s cubic-bezier(0.16, 1, 0.3, 1)';
      bar.style.width = targetW;
    }, 250 + i * 100);
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
  // Purposeful one-time interactions only (no infinite CPU-heavy loops)
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
"""

with open("frontend/static/js/main.js", "w", encoding="utf-8") as f:
    f.write(main_js_content)

with open("static/js/main.js", "w", encoding="utf-8") as f:
    f.write(main_js_content)

print("Successfully wrote frontend/static/js/main.js and static/js/main.js!")
