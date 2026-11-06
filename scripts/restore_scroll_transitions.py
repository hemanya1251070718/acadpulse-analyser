"""
Restores the exact previous smooth slow Apple fade-in transition and
liquid specular cursor spotlight across style.css
"""

old_transition_block = """/* ==========================================================================
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
.delay-5 { transition-delay: 0.40s; }"""

restored_transition_block = """/* ==========================================================================
   SCROLL-REVEAL APPLE TRANSITION (INVISIBLE TO VISIBLE SMOOTH FLOAT-IN)
   ========================================================================== */

.reveal-on-scroll {
  opacity: 0;
  transform: translateY(48px) scale(0.96);
  filter: blur(10px);
  transition: opacity 1.4s cubic-bezier(0.16, 1, 0.3, 1),
              transform 1.4s cubic-bezier(0.16, 1, 0.3, 1),
              filter 1.4s cubic-bezier(0.16, 1, 0.3, 1);
  will-change: opacity, transform, filter;
}

.reveal-on-scroll.revealed {
  opacity: 1;
  transform: translateY(0) scale(1);
  filter: blur(0);
}

/* Staggered animation delays */
.delay-1 { transition-delay: 0.16s; }
.delay-2 { transition-delay: 0.32s; }
.delay-3 { transition-delay: 0.48s; }
.delay-4 { transition-delay: 0.64s; }
.delay-5 { transition-delay: 0.80s; }"""

specular_css = """
/* Liquid Specular Cursor Spotlight (Apple Vision Specular) */
.stat-card::before,
.game-card::before,
.card::before,
.cockpit-card::before {
  content: "";
  position: absolute;
  top: 0; left: 0; right: 0; bottom: 0;
  border-radius: inherit;
  background: radial-gradient(380px circle at var(--mouse-x, -999px) var(--mouse-y, -999px), rgba(168, 85, 247, 0.22), rgba(6, 182, 212, 0.12), transparent 70%);
  opacity: 0;
  pointer-events: none;
  transition: opacity 0.3s ease;
  z-index: 1;
}

.stat-card:hover::before,
.game-card:hover::before,
.card:hover::before,
.cockpit-card:hover::before {
  opacity: 1;
}
"""

with open("frontend/static/css/style.css", "r", encoding="utf-8") as f:
    css = f.read()

# Replace transition block
if old_transition_block in css:
    css = css.replace(old_transition_block, restored_transition_block)
    print("Replaced transition block successfully!")
else:
    print("Old transition block not found by exact string, checking fallback...")
    import re
    css = re.sub(
        r'/\* =+ *\n *SCROLL-REVEAL TRANSITION[\s\S]*?\.delay-5 \{ transition-delay: [0-9.]+s; \}',
        restored_transition_block,
        css
    )
    print("Applied regex replacement for transition block.")

# Add specular CSS if not present
if "var(--mouse-x" not in css:
    target_pos = css.find(".cockpit-card {")
    if target_pos != -1:
        css = css[:target_pos] + specular_css + "\n" + css[target_pos:]
        print("Added specular cursor reflection successfully!")

with open("frontend/static/css/style.css", "w", encoding="utf-8") as f:
    f.write(css)

with open("static/css/style.css", "w", encoding="utf-8") as f:
    f.write(css)

print("Successfully updated frontend/static/css/style.css and static/css/style.css!")

