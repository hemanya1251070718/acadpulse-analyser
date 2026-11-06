"""
Restores the complete Liquid Frosted Glass Top Bar & Floating Pill Architecture styles
in frontend/static/css/style.css and static/css/style.css
"""

pill_architecture_css = """/* ==========================================================================
   FERNWOOD-STYLE AESTHETIC & FLOATING PILL ARCHITECTURE (LIQUID GLASS TOP BAR)
   ========================================================================== */

/* Dot Matrix Vignette Background */
.dot-matrix-overlay {
  position: fixed;
  inset: 0;
  background-image: radial-gradient(rgba(255, 255, 255, 0.08) 1.2px, transparent 1.2px);
  background-size: 22px 22px;
  mask-image: radial-gradient(ellipse 70% 60% at 50% 48%, transparent 25%, black 85%);
  -webkit-mask-image: radial-gradient(ellipse 70% 60% at 50% 48%, transparent 25%, black 85%);
  pointer-events: none;
  z-index: 0;
}

/* Brand Minimalist */
.brand-fernwood {
  display: flex;
  align-items: center;
  text-decoration: none;
  color: #fff !important;
}

.brand-sprout {
  font-size: 1.4rem;
  filter: drop-shadow(0 0 12px rgba(139, 92, 246, 0.9));
}

.brand-text {
  font-family: var(--font-display);
  font-weight: 700;
  font-size: 1.35rem;
  letter-spacing: -0.02em;
  color: #fff;
}

/* Top Floating Capsule Header (Liquid Glass) */
.site-header-floating {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 1050;
  background: rgba(8, 18, 16, 0.55);
  backdrop-filter: blur(20px) saturate(180%);
  -webkit-backdrop-filter: blur(20px) saturate(180%);
  border-bottom: 1px solid rgba(255, 255, 255, 0.08);
  transition: all 0.3s ease;
}

.site-header-floating.header-scrolled {
  background: rgba(6, 12, 14, 0.88);
  box-shadow: 0 10px 30px rgba(0, 0, 0, 0.6);
}

.pill-nav-capsule {
  background: rgba(255, 255, 255, 0.08);
  backdrop-filter: blur(24px) saturate(200%);
  -webkit-backdrop-filter: blur(24px) saturate(200%);
  border: 1px solid rgba(255, 255, 255, 0.14);
  border-radius: 9999px;
  padding: 5px 8px;
  box-shadow: 0 8px 30px rgba(0, 0, 0, 0.35), inset 0 1px 1px rgba(255, 255, 255, 0.2);
  display: inline-flex;
  align-items: center;
  gap: 4px;
}

.pill-nav-link {
  color: rgba(255, 255, 255, 0.72) !important;
  font-size: 0.88rem;
  font-weight: 500;
  padding: 6px 16px;
  border-radius: 9999px;
  text-decoration: none !important;
  transition: all 0.2s ease;
  white-space: nowrap;
}

.pill-nav-link:hover {
  color: #fff !important;
  background: rgba(255, 255, 255, 0.08);
  text-decoration: none !important;
}

.pill-nav-link.active {
  color: #fff !important;
  background: rgba(255, 255, 255, 0.18);
  box-shadow: 0 2px 10px rgba(0, 0, 0, 0.2), inset 0 1px 1px rgba(255, 255, 255, 0.25);
  text-decoration: none !important;
}

.pill-action-btn {
  color: #fff !important;
  font-size: 0.88rem;
  font-weight: 600;
  padding: 8px 20px;
  border-radius: 9999px;
  border: 1px solid rgba(255, 255, 255, 0.22);
  background: rgba(255, 255, 255, 0.06);
  backdrop-filter: blur(12px);
  -webkit-backdrop-filter: blur(12px);
  transition: all 0.25s ease;
  text-decoration: none !important;
  white-space: nowrap;
}

.pill-action-btn:hover {
  background: rgba(255, 255, 255, 0.15);
  border-color: rgba(255, 255, 255, 0.4);
  color: #fff !important;
  transform: translateY(-1px);
  text-decoration: none !important;
}

.mobile-nav-panel {
  background: rgba(10, 16, 20, 0.95);
  backdrop-filter: blur(28px);
  -webkit-backdrop-filter: blur(28px);
  border: 1px solid rgba(255, 255, 255, 0.12);
  border-radius: 20px;
}

.mobile-nav-link {
  display: block;
  padding: 0.6rem 0.8rem;
  color: rgba(255, 255, 255, 0.8) !important;
  text-decoration: none !important;
  font-weight: 500;
  border-radius: 12px;
  transition: all 0.2s ease;
}

.mobile-nav-link:hover, .mobile-nav-link.active {
  color: #fff !important;
  background: rgba(139, 92, 246, 0.2);
  text-decoration: none !important;
}

"""

with open("frontend/static/css/style.css", "r", encoding="utf-8") as f:
    content = f.read()

marker = "/* ==========================================================================\n   FERNWOOD HERO SECTION"
if marker in content:
    idx = content.find(marker)
    new_content = content[:idx] + pill_architecture_css + content[idx:]
    with open("frontend/static/css/style.css", "w", encoding="utf-8") as f:
        f.write(new_content)
    with open("static/css/style.css", "w", encoding="utf-8") as f:
        f.write(new_content)
    print("Successfully restored Liquid Glass Top Bar in style.css!")
else:
    print("Marker not found!")
