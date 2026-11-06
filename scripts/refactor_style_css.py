"""
Refactors frontend/static/css/style.css to strictly align with clean UI/UX principles:
1. Kill gradients on glow (remove radial neon glow blobs, fuzzy box-shadow halos)
2. Replace emojis with real icons (eliminate emoji-specific CSS)
3. Delete meaningless badges (remove floating-drop-badge, floating-sparkle-pill)
4. Flatten cards inside cards (clean typographic data rows, flat metric deck)
5. Proximity & Matching corner radii (formula: inner_radius = outer_radius - padding)
6. Stop infinite looping animations (eliminate stickmanFloat, bookBounce, badgeFloat, etc.)
"""

css_content = """/* ==========================================================================
   ACADPULSE — CLEAN TELEMETRY & PRECISION SYSTEM UI
   Engineered following Clean UI/UX Design Principles:
   1. Kill the gradients on the glow: Restrained, physical lighting & clean elevation.
   2. Replace emojis with real icons: Standardized vector Bootstrap Icons throughout.
   3. Delete badges that don't mean anything: Purposeless stickers & floating badges eliminated.
   4. Flatten the cards that are inside cards: Direct typographic data hierarchy.
   5. Proximity & Matching Corner Radii: Geometric consistency (inner_radius = outer_radius - padding).
   6. Stop infinite looping animations: Only purposeful, meaningful state transitions.
   ========================================================================== */

@import url('https://fonts.googleapis.com/css2?family=IBM+Plex+Mono:wght@400;500;600;700&family=JetBrains+Mono:wght@400;500;600&family=Outfit:wght@400;500;600;700&family=Plus+Jakarta+Sans:wght@400;500;600;700;800&family=Space+Grotesk:wght@500;600;700&display=swap');

:root {
  /* Surface & Background Palette (No loud fluorescent glow blobs) */
  --bg-deep: #070b0e;
  --bg-cockpit: #0b1116;
  --bg-card: rgba(16, 23, 30, 0.88);
  --bg-card-hover: rgba(22, 32, 42, 0.95);

  /* Clean Physical Glass Tokens */
  --glass-bg: rgba(255, 255, 255, 0.03);
  --glass-border: rgba(255, 255, 255, 0.08);
  --glass-border-hover: rgba(255, 255, 255, 0.20);
  --glass-blur: blur(20px);
  --glass-shadow: 0 4px 20px rgba(0, 0, 0, 0.35);

  /* Precise Accents */
  --accent-violet: #8b5cf6;
  --accent-blue: #3b82f6;
  --accent-cyan: #06b6d4;
  --accent-gold: #f59e0b;
  --accent-emerald: #10b981;
  --accent-rose: #f43f5e;

  /* Typography */
  --text-main: #f8fafc;
  --text-muted: #94a3b8;
  --text-dim: #64748b;
  --font-main: 'Plus Jakarta Sans', -apple-system, BlinkMacSystemFont, sans-serif;
  --font-display: 'Space Grotesk', 'Outfit', sans-serif;
  --font-mono: 'IBM Plex Mono', 'JetBrains Mono', SFMono-Regular, Consolas, monospace;

  /* Precision Indicator Accents */
  --signal-orange: #ff4d00;
  --signal-green: #00e599;
  --hairline-border: rgba(255, 255, 255, 0.07);

  /* Geometric Corner Radius Consistency:
     Formula: inner_radius = outer_radius - padding
     Outer card: 14px | Inner interactive controls: 8px | Small pills: 6px | Tracks: 4px */
  --radius-card: 14px;
  --radius-inner: 8px;
  --radius-sm: 6px;
  --radius-track: 4px;
}

/* Global Reset */
* {
  box-sizing: border-box;
}

html {
  scroll-behavior: smooth;
}

/* Body: Clean deep slate obsidian with subtle, disciplined ambient gradient */
body {
  background-color: var(--bg-deep);
  background-image:
    linear-gradient(180deg, #070b0e 0%, #0a1016 50%, #06090c 100%);
  background-attachment: fixed;
  color: var(--text-main);
  font-family: var(--font-main);
  min-height: 100vh;
  display: flex;
  flex-direction: column;
  overflow-x: hidden;
}

/* ==========================================================================
   SCROLL-REVEAL TRANSITION (PURPOSEFUL ONE-TIME REVEAL)
   ========================================================================== */

.reveal-on-scroll {
  opacity: 0;
  transform: translateY(24px);
  transition: opacity 0.6s cubic-bezier(0.16, 1, 0.3, 1),
              transform 0.6s cubic-bezier(0.16, 1, 0.3, 1);
  will-change: opacity, transform;
}

.reveal-on-scroll.revealed {
  opacity: 1;
  transform: translateY(0);
}

.delay-1 { transition-delay: 0.08s; }
.delay-2 { transition-delay: 0.16s; }
.delay-3 { transition-delay: 0.24s; }
.delay-4 { transition-delay: 0.32s; }
.delay-5 { transition-delay: 0.40s; }

/* ==========================================================================
   SMOOTH PRECISION SCROLLBARS
   ========================================================================== */

::-webkit-scrollbar {
  width: 7px;
  height: 7px;
}
::-webkit-scrollbar-track {
  background: rgba(8, 12, 16, 0.85);
}
::-webkit-scrollbar-thumb {
  background: rgba(255, 255, 255, 0.16);
  border-radius: var(--radius-track);
}
::-webkit-scrollbar-thumb:hover {
  background: rgba(255, 255, 255, 0.28);
}

.cockpit-scroll {
  overflow-y: auto;
  overflow-x: hidden;
  max-height: 520px;
  padding-right: 8px;
  scroll-behavior: smooth;
}

.cockpit-scroll::-webkit-scrollbar {
  width: 5px;
}

/* Cockpit Horizon Quick Nav Dock */
.cockpit-dock {
  background: rgba(14, 20, 28, 0.85);
  backdrop-filter: blur(20px);
  -webkit-backdrop-filter: blur(20px);
  border: 1px solid var(--glass-border);
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.35);
  border-radius: var(--radius-inner);
  padding: 0.35rem 0.65rem;
  display: inline-flex;
  gap: 0.35rem;
  align-items: center;
}

.cockpit-dock-btn {
  color: var(--text-muted);
  font-size: 0.82rem;
  font-weight: 600;
  padding: 0.35rem 0.75rem;
  border-radius: var(--radius-sm);
  text-decoration: none;
  transition: color 0.18s ease, background 0.18s ease;
  white-space: nowrap;
}

.cockpit-dock-btn:hover {
  color: #fff;
  background: rgba(255, 255, 255, 0.08);
}

.cockpit-dock-btn.active {
  color: #fff;
  background: rgba(255, 255, 255, 0.14);
  border: 1px solid rgba(255, 255, 255, 0.12);
}

/* ==========================================================================
   CARDS & HOVER INTERACTION (NO LOUD GLOW HALOS)
   ========================================================================== */

.apple-glass {
  background: var(--glass-bg);
  backdrop-filter: var(--glass-blur);
  -webkit-backdrop-filter: var(--glass-blur);
  border: 1px solid var(--glass-border);
  box-shadow: var(--glass-shadow);
  border-radius: var(--radius-card);
  position: relative;
  transition: border-color 0.2s ease, transform 0.2s ease;
}

.apple-glass-heading {
  background: rgba(255, 255, 255, 0.04);
  backdrop-filter: var(--glass-blur);
  -webkit-backdrop-filter: var(--glass-blur);
  border: 1px solid var(--glass-border);
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.25);
  border-radius: var(--radius-card);
  position: relative;
  overflow: hidden;
}

.glass-hover {
  position: relative;
  transition: transform 0.2s cubic-bezier(0.16, 1, 0.3, 1),
              border-color 0.2s ease;
}

.glass-hover:hover {
  transform: translateY(-2px);
  border-color: var(--glass-border-hover);
}

/* Cockpit Architecture Cards */
.cockpit-card {
  background: var(--bg-card);
  backdrop-filter: var(--glass-blur);
  -webkit-backdrop-filter: var(--glass-blur);
  border: 1px solid var(--glass-border);
  border-radius: var(--radius-card);
  position: relative;
  overflow: hidden;
  box-shadow: 0 4px 18px rgba(0, 0, 0, 0.3);
  transition: border-color 0.2s ease, transform 0.2s ease;
}

.cockpit-card:hover {
  transform: translateY(-2px);
  border-color: var(--glass-border-hover);
}

/* ==========================================================================
   NAVBAR
   ========================================================================== */

.app-navbar {
  background: rgba(10, 15, 20, 0.88) !important;
  backdrop-filter: blur(20px);
  -webkit-backdrop-filter: blur(20px);
  border-bottom: 1px solid var(--hairline-border);
  padding: 0.75rem 0;
}

.navbar-brand {
  font-weight: 700;
  letter-spacing: -0.02em;
  color: #fff !important;
}

.brand-gradient-text {
  color: #ffffff;
  font-weight: 700;
}

.nav-link {
  color: var(--text-muted) !important;
  font-weight: 600;
  font-size: 0.88rem;
  padding: 0.45rem 0.85rem !important;
  border-radius: var(--radius-inner);
  border: 1px solid transparent;
  transition: all 0.18s ease;
}

.nav-link:hover {
  color: #fff !important;
  background: rgba(255, 255, 255, 0.06);
  border-color: rgba(255, 255, 255, 0.1);
}

.nav-link.active {
  color: #fff !important;
  background: rgba(255, 255, 255, 0.12);
  border-color: rgba(255, 255, 255, 0.18);
}

/* ==========================================================================
   STAT CARDS (TIGHT PROXIMITY, MATCHING RADII, NO GLOW)
   ========================================================================== */

.stat-card {
  background: var(--bg-card);
  backdrop-filter: var(--glass-blur);
  -webkit-backdrop-filter: var(--glass-blur);
  border: 1px solid var(--glass-border);
  border-radius: var(--radius-card);
  position: relative;
  overflow: hidden;
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.25);
  transition: border-color 0.2s ease, transform 0.2s ease;
}

.stat-card::after {
  content: "";
  position: absolute;
  top: 0; left: 0; width: 3px; height: 100%;
  background: var(--accent-violet);
}

.stat-card.border-success::after {
  background: var(--accent-emerald);
}
.stat-card.border-warning::after {
  background: var(--accent-gold);
}
.stat-card.border-danger::after {
  background: var(--accent-rose);
}

.stat-card:hover {
  transform: translateY(-2px);
  background: var(--bg-card-hover);
  border-color: var(--glass-border-hover);
}

/* Gestalt Proximity: Tight grouping of label to stat value */
.stat-label {
  font-size: 0.72rem;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 0.07em;
  color: var(--text-dim);
  margin-bottom: 2px;
}

.stat-value {
  font-size: 2.1rem;
  font-weight: 700;
  color: #fff;
  letter-spacing: -0.02em;
  line-height: 1.15;
}

/* ==========================================================================
   GAMECARDS (FLAT, DIRECT HIERARCHY, NO CARDS INSIDE CARDS)
   ========================================================================== */

.game-card-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(295px, 1fr));
  gap: 1.25rem;
}

.game-card {
  background: var(--bg-card);
  backdrop-filter: var(--glass-blur);
  -webkit-backdrop-filter: var(--glass-blur);
  border: 1px solid var(--glass-border);
  border-radius: var(--radius-card);
  padding: 1.25rem;
  position: relative;
  overflow: hidden;
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.25);
  transition: border-color 0.2s ease, transform 0.2s ease;
}

.game-card:hover {
  transform: translateY(-2px);
  border-color: var(--glass-border-hover);
}

/* Clean Tier Accents (Clean Hairline Borders, Zero Glowing Halos) */
.game-card-apex {
  border: 1px solid rgba(245, 158, 11, 0.45);
}
.game-card-apex::before {
  content: "";
  position: absolute;
  top: 0; left: 0; right: 0; height: 2px;
  background: var(--accent-gold);
}

.game-card-diamond {
  border: 1px solid rgba(6, 182, 212, 0.45);
}
.game-card-diamond::before {
  content: "";
  position: absolute;
  top: 0; left: 0; right: 0; height: 2px;
  background: var(--accent-cyan);
}

.game-card-epic {
  border: 1px solid rgba(139, 92, 246, 0.45);
}
.game-card-epic::before {
  content: "";
  position: absolute;
  top: 0; left: 0; right: 0; height: 2px;
  background: var(--accent-violet);
}

/* Avatar: Corner radius matches inner token (8px) */
.game-avatar {
  width: 44px;
  height: 44px;
  border-radius: var(--radius-inner);
  background: rgba(255, 255, 255, 0.08);
  border: 1px solid rgba(255, 255, 255, 0.14);
  display: flex;
  align-items: center;
  justify-content: center;
  font-weight: 700;
  font-size: 1.15rem;
  color: #fff;
}

/* Stat Meters: Corner radius matches track token (4px) */
.stat-meter-track {
  height: 6px;
  background: rgba(255, 255, 255, 0.07);
  border-radius: var(--radius-track);
  overflow: hidden;
  position: relative;
}

.stat-meter-fill {
  height: 100%;
  border-radius: var(--radius-track);
  background: var(--accent-blue);
  transition: width 0.8s cubic-bezier(0.16, 1, 0.3, 1);
}

.stat-meter-fill.fill-gold {
  background: var(--accent-gold);
}

.stat-meter-fill.fill-cyan {
  background: var(--accent-cyan);
}

.stat-meter-fill.fill-danger {
  background: var(--accent-rose);
}

/* ==========================================================================
   FLATTENED METRIC TYPOGRAPHY (NO CARD-IN-CARD CONTAINERS)
   ========================================================================== */

.metric-caption {
  font-family: var(--font-mono);
  font-size: 0.68rem;
  font-weight: 600;
  letter-spacing: 0.08em;
  text-transform: uppercase;
  color: var(--text-dim);
  margin-bottom: 2px;
}

.metric-number {
  font-family: var(--font-display);
  font-size: 1.6rem;
  font-weight: 700;
  color: #ffffff;
  line-height: 1.1;
}

.metric-number-sm {
  font-family: var(--font-display);
  font-size: 1.25rem;
  font-weight: 700;
  color: #ffffff;
  line-height: 1.1;
}

.metric-unit {
  font-size: 0.9rem;
  font-weight: 500;
  color: var(--text-muted);
  margin-left: 1px;
}

.score-pill-neutral {
  font-family: var(--font-mono);
  font-size: 0.82rem;
  font-weight: 700;
  color: #f8fafc;
  background: rgba(255, 255, 255, 0.06);
  border: 1px solid rgba(255, 255, 255, 0.1);
  padding: 3px 8px;
  border-radius: var(--radius-sm);
  display: inline-block;
}

/* ==========================================================================
   CARDS, TABLES & FORM CONTROLS (GEOMETRIC CONSISTENCY)
   ========================================================================== */

.card {
  background: var(--bg-card);
  backdrop-filter: var(--glass-blur);
  -webkit-backdrop-filter: var(--glass-blur);
  border: 1px solid var(--glass-border);
  border-radius: var(--radius-card);
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.25);
}

.card-header {
  background: rgba(255, 255, 255, 0.02) !important;
  border-bottom: 1px solid var(--hairline-border) !important;
  color: #fff !important;
  border-top-left-radius: calc(var(--radius-card) - 1px) !important;
  border-top-right-radius: calc(var(--radius-card) - 1px) !important;
}

.table {
  color: var(--text-main);
  border-color: var(--hairline-border);
  margin-bottom: 0;
}

.table thead th {
  background: rgba(14, 20, 28, 0.85);
  color: var(--text-muted);
  font-weight: 700;
  font-size: 0.76rem;
  text-transform: uppercase;
  letter-spacing: 0.06em;
  border-bottom: 1px solid var(--hairline-border);
  padding: 0.85rem 1rem;
}

.table tbody tr {
  background: transparent;
  transition: background 0.15s ease;
  border-bottom: 1px solid rgba(255, 255, 255, 0.03);
}

.table tbody tr:hover {
  background: rgba(255, 255, 255, 0.04) !important;
}

.table td {
  padding: 0.85rem 1rem;
  vertical-align: middle;
  border-color: rgba(255, 255, 255, 0.03);
}

.avatar-circle {
  width: 34px;
  height: 34px;
  border-radius: 50%;
  background: rgba(255, 255, 255, 0.08);
  color: white;
  display: inline-flex;
  align-items: center;
  justify-content: center;
  font-weight: 700;
  font-size: 0.85rem;
  margin-right: 0.5rem;
  border: 1px solid rgba(255, 255, 255, 0.15);
}

/* Form Controls & Inputs (Matching Radius Token: 8px) */
.form-control, .form-select {
  background-color: rgba(14, 20, 28, 0.85) !important;
  border: 1px solid var(--glass-border) !important;
  color: #fff !important;
  border-radius: var(--radius-inner);
  font-size: 0.88rem;
}

.form-control:focus, .form-select:focus {
  border-color: rgba(255, 255, 255, 0.3) !important;
  box-shadow: none !important;
  outline: none;
}

.input-group-text {
  background: rgba(20, 28, 38, 0.85) !important;
  border: 1px solid var(--glass-border) !important;
  color: var(--text-muted) !important;
  border-radius: var(--radius-inner);
}

/* Meaningful Functional Badges */
.badge-gold {
  background: rgba(245, 158, 11, 0.15);
  color: #fbbf24;
  border: 1px solid rgba(245, 158, 11, 0.35);
  border-radius: var(--radius-sm);
  font-weight: 600;
}

.badge-silver {
  background: rgba(148, 163, 184, 0.15);
  color: #e2e8f0;
  border: 1px solid rgba(148, 163, 184, 0.35);
  border-radius: var(--radius-sm);
  font-weight: 600;
}

.badge-bronze {
  background: rgba(217, 119, 6, 0.15);
  color: #f97316;
  border: 1px solid rgba(217, 119, 6, 0.35);
  border-radius: var(--radius-sm);
  font-weight: 600;
}

.complexity-tag {
  font-family: var(--font-mono);
  font-size: 0.74rem;
  padding: 0.2rem 0.55rem;
  background: rgba(255, 255, 255, 0.06);
  color: #cbd5e1;
  border: 1px solid rgba(255, 255, 255, 0.1);
  border-radius: var(--radius-sm);
  font-weight: 600;
}

/* Nav Pills */
.nav-pills .nav-link {
  color: var(--text-muted);
  background: rgba(255, 255, 255, 0.04);
  border: 1px solid var(--hairline-border);
  border-radius: var(--radius-inner);
  padding: 0.5rem 1rem;
  transition: all 0.18s ease;
}

.nav-pills .nav-link:hover {
  background: rgba(255, 255, 255, 0.08);
  color: #fff;
}

.nav-pills .nav-link.active {
  background: rgba(255, 255, 255, 0.14);
  color: #fff;
  border-color: rgba(255, 255, 255, 0.2);
}

/* Buttons (Matching Radius Token: 8px) */
.btn-primary {
  background: #2563eb;
  border: 1px solid rgba(255, 255, 255, 0.15);
  color: #fff;
  font-weight: 600;
  border-radius: var(--radius-inner);
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.2);
  transition: background 0.18s ease, transform 0.18s ease;
}

.btn-primary:hover {
  background: #1d4ed8;
  border-color: rgba(255, 255, 255, 0.25);
  transform: translateY(-1px);
}

.btn-outline-primary {
  color: #cbd5e1;
  border-color: rgba(255, 255, 255, 0.15);
  background: rgba(255, 255, 255, 0.04);
  border-radius: var(--radius-inner);
  font-weight: 600;
}

.btn-outline-primary:hover {
  background: rgba(255, 255, 255, 0.12);
  color: #fff;
  border-color: rgba(255, 255, 255, 0.3);
}

.btn-outline-light {
  border-color: rgba(255, 255, 255, 0.15);
  color: #e2e8f0;
  border-radius: var(--radius-inner);
}

.btn-outline-light:hover {
  background: rgba(255, 255, 255, 0.1);
  border-color: rgba(255, 255, 255, 0.3);
  color: #fff;
}

/* Modals */
.modal-content {
  background: rgba(14, 20, 28, 0.96);
  backdrop-filter: blur(24px);
  -webkit-backdrop-filter: blur(24px);
  border: 1px solid var(--glass-border);
  border-radius: var(--radius-card);
  color: #fff;
  box-shadow: 0 16px 40px rgba(0, 0, 0, 0.6);
}

.modal-header, .modal-footer {
  border-color: var(--hairline-border);
}

/* Footer */
footer {
  background: rgba(6, 9, 12, 0.95);
  border-top: 1px solid var(--hairline-border);
  padding: 1.5rem 0;
  color: var(--text-muted);
}

/* ==========================================================================
   CLEAN HERO & PRECISION METRIC DECK
   (NO LOOPING LIGHTNING, NO EMOJIS, NO TILTED 3D DISTORTION)
   ========================================================================== */

.dot-matrix-overlay {
  position: fixed;
  inset: 0;
  background-image: radial-gradient(rgba(255, 255, 255, 0.04) 1px, transparent 1px);
  background-size: 24px 24px;
  pointer-events: none;
  z-index: 0;
}

.brand-fernwood {
  display: flex;
  align-items: center;
  text-decoration: none;
  color: #fff !important;
}

.brand-text {
  font-family: var(--font-display);
  font-weight: 700;
  font-size: 1.25rem;
  letter-spacing: -0.02em;
  color: #fff;
}

/* Floating Site Header */
.site-header-floating {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 1050;
  background: rgba(8, 12, 16, 0.75);
  backdrop-filter: blur(16px);
  -webkit-backdrop-filter: blur(16px);
  border-bottom: 1px solid var(--hairline-border);
  transition: all 0.25s ease;
}

.pill-nav-capsule {
  background: rgba(255, 255, 255, 0.04);
  backdrop-filter: blur(16px);
  -webkit-backdrop-filter: blur(16px);
  border: 1px solid var(--hairline-border);
  border-radius: var(--radius-inner);
  padding: 4px 6px;
  gap: 4px;
}

.pill-nav-link {
  color: rgba(255, 255, 255, 0.7);
  font-size: 0.86rem;
  font-weight: 500;
  padding: 5px 14px;
  border-radius: var(--radius-sm);
  text-decoration: none;
  transition: all 0.18s ease;
}

.pill-nav-link:hover {
  color: #fff;
  background: rgba(255, 255, 255, 0.08);
}

.pill-nav-link.active {
  color: #fff;
  background: rgba(255, 255, 255, 0.14);
}

.pill-action-btn {
  color: #fff;
  font-size: 0.86rem;
  font-weight: 600;
  padding: 7px 18px;
  border-radius: var(--radius-inner);
  border: 1px solid rgba(255, 255, 255, 0.16);
  background: rgba(255, 255, 255, 0.06);
  transition: all 0.2s ease;
}

.pill-action-btn:hover {
  background: rgba(255, 255, 255, 0.14);
  color: #fff;
}

.mobile-nav-panel {
  background: rgba(10, 16, 22, 0.96);
  backdrop-filter: blur(20px);
  border: 1px solid var(--glass-border);
  border-radius: var(--radius-card);
}

.mobile-nav-link {
  display: block;
  padding: 0.6rem 0.8rem;
  color: rgba(255, 255, 255, 0.8);
  text-decoration: none;
  font-weight: 500;
  border-radius: var(--radius-inner);
  transition: all 0.18s ease;
}

.mobile-nav-link:hover, .mobile-nav-link.active {
  color: #fff;
  background: rgba(255, 255, 255, 0.1);
}

/* Clean Hero Section: No Hazy Radial Neon Blobs */
.fernwood-hero-section {
  min-height: 92vh;
  position: relative;
  overflow: hidden;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: flex-start;
  padding-top: 6.5rem;
  padding-bottom: 4rem;
  background: linear-gradient(180deg, #070b0e 0%, #0b1117 60%, #070a0d 100%);
  z-index: 2;
}

.hero-stage-container {
  position: relative;
  z-index: 3;
  text-align: center;
  max-width: 1100px;
  width: 100%;
  padding: 0 1.5rem;
}

.hero-subnav-links {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 1.8rem;
  margin-bottom: 1.8rem;
  flex-wrap: wrap;
}

.hero-sublink {
  color: rgba(255, 255, 255, 0.65);
  font-size: 0.86rem;
  font-weight: 500;
  text-decoration: none;
  transition: color 0.18s ease;
}

.hero-sublink:hover {
  color: #fff;
}

.hero-headline-wrap {
  position: relative;
  display: inline-block;
  margin: 0 auto;
}

.hero-headline-fernwood {
  font-family: var(--font-display);
  font-size: clamp(2.4rem, 5.2vw, 4.2rem);
  font-weight: 700;
  letter-spacing: -0.03em;
  line-height: 1.1;
  color: #f8fafc;
  margin-bottom: 1.1rem;
}

.hero-subtitle-fernwood {
  font-size: clamp(0.98rem, 1.5vw, 1.12rem);
  color: var(--text-muted);
  max-width: 660px;
  margin: 0 auto 2rem;
  line-height: 1.6;
}

.hero-cta-group {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 0.85rem;
  flex-wrap: wrap;
  margin-bottom: 3rem;
}

.btn-fernwood-primary {
  background: #ffffff;
  color: #090e13;
  font-weight: 600;
  font-size: 0.94rem;
  padding: 10px 26px;
  border-radius: var(--radius-inner);
  transition: all 0.2s ease;
  display: inline-block;
  border: 1px solid rgba(255, 255, 255, 0.8);
  text-decoration: none;
}

.btn-fernwood-primary:hover {
  background: #e2e8f0;
  color: #090e13;
  transform: translateY(-1px);
}

.btn-fernwood-secondary {
  background: rgba(255, 255, 255, 0.06);
  color: #fff;
  font-weight: 600;
  font-size: 0.94rem;
  padding: 10px 26px;
  border-radius: var(--radius-inner);
  border: 1px solid var(--hairline-border);
  transition: all 0.2s ease;
  display: inline-block;
  text-decoration: none;
}

.btn-fernwood-secondary:hover {
  background: rgba(255, 255, 255, 0.12);
  color: #fff;
}

/* ==========================================================================
   FLATTENED HERO METRIC DECK (FLAT, FLUSH, MATCHING GEOMETRY)
   Eliminates tilted 3D distortion and card-in-card nesting
   ========================================================================== */

.hero-metric-deck {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 1.25rem;
  max-width: 1040px;
  width: 100%;
  margin: 0 auto;
  text-align: left;
}

.metric-deck-card {
  background: var(--bg-card);
  backdrop-filter: var(--glass-blur);
  -webkit-backdrop-filter: var(--glass-blur);
  border: 1px solid var(--glass-border);
  border-radius: var(--radius-card);
  padding: 1.35rem 1.45rem;
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.25);
  transition: border-color 0.2s ease, transform 0.2s ease;
}

.metric-deck-card:hover {
  border-color: var(--glass-border-hover);
  transform: translateY(-2px);
}

.metric-deck-card-featured {
  background: rgba(20, 28, 38, 0.95);
  border-color: rgba(255, 255, 255, 0.16);
  text-align: center;
}

.card-top-header {
  display: flex;
  align-items: center;
  gap: 0.6rem;
}

.card-title-text {
  font-weight: 700;
  font-size: 0.92rem;
  color: #f8fafc;
  letter-spacing: -0.01em;
}

.pill-streak-badge {
  font-family: var(--font-mono);
  font-size: 0.72rem;
  font-weight: 600;
  color: var(--text-muted);
  background: rgba(255, 255, 255, 0.06);
  padding: 2px 8px;
  border-radius: var(--radius-sm);
  border: 1px solid var(--hairline-border);
}

.card-bars-list {
  display: flex;
  flex-direction: column;
  gap: 0.65rem;
}

.bar-row {
  display: grid;
  grid-template-columns: 105px 1fr 28px;
  align-items: center;
  gap: 0.55rem;
}

.bar-label {
  font-size: 0.78rem;
  font-weight: 600;
  color: var(--text-muted);
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.bar-track {
  height: 6px;
  background: rgba(255, 255, 255, 0.08);
  border-radius: var(--radius-track);
  overflow: hidden;
}

.bar-fill {
  height: 100%;
  background: #3b82f6;
  border-radius: var(--radius-track);
  transition: width 1s ease-in-out;
}

.bar-score {
  font-size: 0.78rem;
  font-weight: 700;
  color: #cbd5e1;
  text-align: right;
  font-family: var(--font-mono);
}

/* Center Card Gauge */
.center-card-header {
  text-align: center;
}

.center-subtitle {
  font-size: 0.8rem;
  font-weight: 600;
  color: var(--text-muted);
  text-transform: uppercase;
  letter-spacing: 0.06em;
}

.gauge-center-wrap {
  position: relative;
  width: 170px;
  height: 100px;
  margin: 0.8rem auto 0.4rem;
}

.gauge-svg {
  width: 100%;
  height: 100%;
  overflow: visible;
}

.gauge-score-value {
  position: absolute;
  bottom: 6px;
  left: 50%;
  transform: translateX(-50%);
  font-family: var(--font-display);
  font-size: 3rem;
  font-weight: 700;
  color: #ffffff;
  line-height: 1;
  letter-spacing: -0.03em;
}

.center-card-caption {
  font-size: 0.84rem;
  font-weight: 600;
  color: var(--text-muted);
}

/* Right Card Sparkline */
.sparkline-wrap {
  width: 100%;
  height: 105px;
}

.sparkline-svg {
  width: 100%;
  height: 100%;
}

/* Purposeful, Non-Looping Scroll Indicator */
.hero-scroll-cue {
  position: absolute;
  bottom: 1.25rem;
  left: 50%;
  transform: translateX(-50%);
  z-index: 3;
  color: var(--text-dim);
  font-size: 0.78rem;
  font-weight: 600;
  letter-spacing: 0.08em;
  text-transform: uppercase;
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.25rem;
  text-decoration: none;
  transition: color 0.2s ease;
}

.hero-scroll-cue:hover {
  color: #fff;
}

.fernwood-footer {
  background: rgba(6, 9, 12, 0.95);
  border-top: 1px solid var(--hairline-border);
  color: var(--text-muted);
}

.font-outfit {
  font-family: var(--font-display) !important;
}

/* Mobile responsive adjustments */
@media (max-width: 992px) {
  .hero-metric-deck {
    grid-template-columns: 1fr;
    max-width: 440px;
  }
}

/* Precision Telemetry Indicators */
.dot-live {
  width: 6px;
  height: 6px;
  border-radius: 50%;
  background: var(--signal-green);
  display: inline-block;
  margin-right: 4px;
}

.telemetry-badge-sharp {
  font-family: var(--font-mono);
  font-size: 0.72rem;
  font-weight: 600;
  padding: 2px 7px;
  background: rgba(255, 77, 0, 0.1);
  color: var(--signal-orange);
  border: 1px solid rgba(255, 77, 0, 0.3);
  border-radius: var(--radius-sm);
  letter-spacing: 0.04em;
}

/* Mechanical Tactile Feedback on Active Click */
.btn-fernwood-primary:active,
.btn-primary:active,
.pill-action-btn:active,
.cockpit-dock-btn:active {
  transform: translate(1px, 1px) scale(0.99) !important;
}
"""

with open("frontend/static/css/style.css", "w", encoding="utf-8") as f:
    f.write(css_content)

with open("static/css/style.css", "w", encoding="utf-8") as f:
    f.write(css_content)

print("Successfully wrote frontend/static/css/style.css and static/css/style.css!")
