"""
Restores the exact previous front page hero design (above the fold)
while preserving the clean, flattened card UI across the rest of the application.
"""

import subprocess
import os

# 1. Update frontend/templates/dashboard.html
with open("frontend/templates/dashboard.html", "r", encoding="utf-8") as f:
    current_dashboard = f.read()

cockpit_start_marker = '<div id="cockpitStart"'
cockpit_idx = current_dashboard.find(cockpit_start_marker)

# Get previous hero from 62b5aec
git_out = subprocess.check_output(
    ["git", "show", "62b5aec:frontend/templates/dashboard.html"],
    encoding="utf-8"
)
hero_end_marker = '<!-- ==========================================================================\n     UNIFIED DASHBOARD CONTAINER'
hero_prev = git_out[:git_out.find(hero_end_marker)]

# New dashboard content: previous hero + current cockpitStart & below
new_dashboard = hero_prev + current_dashboard[cockpit_idx:]

with open("frontend/templates/dashboard.html", "w", encoding="utf-8") as f:
    f.write(new_dashboard)

print("Restored hero in frontend/templates/dashboard.html!")

# 2. Update frontend/templates/base.html
with open("frontend/templates/base.html", "r", encoding="utf-8") as f:
    base_html = f.read()

# Restore brand ⚡ in navbar
base_html = base_html.replace(
    '<i class="bi bi-activity text-primary fs-5 me-2"></i>\n        <span class="brand-text">AcadPulse</span>',
    '<span class="brand-sprout me-2">⚡</span>\n        <span class="brand-text">AcadPulse</span>'
)
# Restore brand ⚡ in footer
base_html = base_html.replace(
    '<i class="bi bi-activity text-primary fs-5 me-2"></i>\n            <strong class="text-white fs-5"',
    '<span class="fs-4 me-2">⚡</span>\n            <strong class="text-white fs-5"'
)

with open("frontend/templates/base.html", "w", encoding="utf-8") as f:
    f.write(base_html)

print("Restored brand sprout in frontend/templates/base.html!")

# 3. Update main.js
main_js_prev = subprocess.check_output(
    ["git", "show", "62b5aec:frontend/static/js/main.js"],
    encoding="utf-8"
)

with open("frontend/static/js/main.js", "w", encoding="utf-8") as f:
    f.write(main_js_prev)

with open("static/js/main.js", "w", encoding="utf-8") as f:
    f.write(main_js_prev)

print("Restored frontend/static/js/main.js and static/js/main.js!")

# 4. Update style.css:
# We combine the clean tokens & flattened components with the previous hero styles!
style_css_prev = subprocess.check_output(
    ["git", "show", "62b5aec:frontend/static/css/style.css"],
    encoding="utf-8"
)

# Extract the hero section and floating animations from style_css_prev
hero_css_start = style_css_prev.find("/* ==========================================================================\n   FERNWOOD HERO SECTION")
hero_css_content = style_css_prev[hero_css_start:]

# Read our current style.css
with open("frontend/static/css/style.css", "r", encoding="utf-8") as f:
    current_style = f.read()

# Replace the hero section in current_style with hero_css_content
current_hero_start = current_style.find("/* ==========================================================================\n   CLEAN HERO & PRECISION METRIC DECK")
if current_hero_start == -1:
    current_hero_start = current_style.find(".fernwood-hero-section")

combined_style = current_style[:current_hero_start] + hero_css_content

with open("frontend/static/css/style.css", "w", encoding="utf-8") as f:
    f.write(combined_style)

with open("static/css/style.css", "w", encoding="utf-8") as f:
    f.write(combined_style)

print("Successfully updated frontend/static/css/style.css and static/css/style.css!")

