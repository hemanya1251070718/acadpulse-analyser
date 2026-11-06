"""
1. Fixes the Assessment Marks Entry & Gradebook Matrix undefined bug in frontend/templates/dashboard.html
2. Applies max border-radius (ultra-rounded curvature) across style.css
"""

# Step 1: Update dashboard.html
with open("frontend/templates/dashboard.html", "r", encoding="utf-8") as f:
    dashboard_html = f.read()

# Replace renderMarksMatrix function
old_render_marks = """function renderMarksMatrix(students) {
  const tbody = document.querySelector('#dashMarksTable tbody');
  if (!tbody) return;

  tbody.innerHTML = students.map(s => {
    const composite = Math.round((s.marks.MSE * 0.3) + (s.marks.ESE * 0.5) + (s.marks.LAB * 0.2));
    return `
      <tr>
        <td><code class="font-monospace text-info">${s.prn}</code></td>
        <td><span class="fw-bold text-white">${s.name}</span></td>
        <td><span class="badge bg-secondary font-monospace">Div ${s.division}</span></td>
        <td><span class="font-monospace text-white">${s.marks.MSE}</span></td>
        <td><span class="font-monospace text-white">${s.marks.ESE}</span></td>
        <td><span class="font-monospace text-white">${s.marks.LAB}</span></td>
        <td><span class="font-monospace text-white">${s.marks.PROJ}</span></td>
        <td><strong class="font-monospace text-success">${composite}%</strong></td>
      </tr>
    `;
  }).join('');
}"""

new_render_marks = """function renderMarksMatrix(students) {
  const tbody = document.querySelector('#dashMarksTable tbody');
  if (!tbody) return;

  const course = document.getElementById('dashCourseSelect')?.value || 'DS';
  const div = document.getElementById('dashAssessmentDivSelect')?.value || 'ALL';

  const dataList = students || allStudentsList || [];
  const filtered = dataList.filter(s => div === 'ALL' || s.division === div);

  if (filtered.length === 0) {
    tbody.innerHTML = '<tr><td colspan="8" class="text-center py-4 text-muted">No cadet assessment records found.</td></tr>';
    return;
  }

  tbody.innerHTML = filtered.map(s => {
    const m = (s.marks && s.marks[course]) || (s.marks && s.marks.DS) || { mse: 0, ese: 0, lab: 0, proj: 0 };
    const mse = m.mse !== undefined ? m.mse : (m.MSE !== undefined ? m.MSE : 0);
    const ese = m.ese !== undefined ? m.ese : (m.ESE !== undefined ? m.ESE : 0);
    const lab = m.lab !== undefined ? m.lab : (m.LAB !== undefined ? m.LAB : 0);
    const proj = m.proj !== undefined ? m.proj : (m.PROJ !== undefined ? m.PROJ : 0);
    const composite = Math.round((mse * 0.3) + (ese * 0.5) + (lab * 0.2));
    return `
      <tr>
        <td><code class="font-monospace text-info">${s.prn}</code></td>
        <td><span class="fw-bold text-white">${s.name}</span></td>
        <td><span class="badge bg-secondary font-monospace">Div ${s.division}</span></td>
        <td><span class="font-monospace text-white">${mse}</span></td>
        <td><span class="font-monospace text-white">${ese}</span></td>
        <td><span class="font-monospace text-white">${lab}</span></td>
        <td><span class="font-monospace text-white">${proj}</span></td>
        <td><strong class="font-monospace text-success">${composite}%</strong></td>
      </tr>
    `;
  }).join('');
}"""

if old_render_marks in dashboard_html:
    dashboard_html = dashboard_html.replace(old_render_marks, new_render_marks)
    print("Replaced renderMarksMatrix in dashboard.html successfully!")
else:
    print("Warning: old_render_marks not found by exact string!")

# Add event listeners for dashCourseSelect and dashAssessmentDivSelect
if "dashCourseSelect" not in dashboard_html or "dashCourseSelect'?.addEventListener" not in dashboard_html:
    target_event = "divFilter?.addEventListener('change', applyFilter);"
    event_additions = """divFilter?.addEventListener('change', applyFilter);

  // Gradebook Matrix interactive selectors
  document.getElementById('dashCourseSelect')?.addEventListener('change', () => renderMarksMatrix(allStudentsList));
  document.getElementById('dashAssessmentDivSelect')?.addEventListener('change', () => renderMarksMatrix(allStudentsList));"""
    if target_event in dashboard_html:
        dashboard_html = dashboard_html.replace(target_event, event_additions)
        print("Added gradebook filter event listeners in dashboard.html!")

with open("frontend/templates/dashboard.html", "w", encoding="utf-8") as f:
    f.write(dashboard_html)

# Step 2: Update style.css with MAX BORDER-RADIUS
with open("frontend/static/css/style.css", "r", encoding="utf-8") as f:
    css = f.read()

# Update root tokens
css = css.replace("--radius-card: 14px;", "--radius-card: 28px;")
css = css.replace("--radius-inner: 8px;", "--radius-inner: 18px;")
css = css.replace("--radius-sm: 6px;", "--radius-sm: 14px;")
css = css.replace("--radius-track: 4px;", "--radius-track: 9999px;")

# Add max curvature master overrides
max_curvature_css = """
/* ==========================================================================
   ULTRA-ROUNDED MAX CURVATURE AESTHETIC (ALL BORDERS ROUNDED AT MAX)
   ========================================================================== */

.card,
.cockpit-card,
.stat-card,
.game-card,
.apple-glass,
.apple-glass-heading,
.modal-content,
.fernwood-card,
.card-left-tilt,
.card-center-feature,
.card-right-tilt {
  border-radius: 28px !important;
}

.card-header {
  border-top-left-radius: 28px !important;
  border-top-right-radius: 28px !important;
}

.btn,
.btn-primary,
.btn-secondary,
.btn-outline-primary,
.btn-outline-light,
.btn-outline-danger,
.btn-sm,
.pill-action-btn,
.btn-fernwood-primary,
.btn-fernwood-secondary {
  border-radius: 9999px !important;
}

.form-control,
.form-select,
.input-group-text {
  border-radius: 9999px !important;
  padding-left: 1.15rem !important;
  padding-right: 1.15rem !important;
}

.badge,
.complexity-tag,
.telemetry-badge-sharp,
.pill-streak-badge,
.score-pill-neutral {
  border-radius: 9999px !important;
  padding: 4px 12px !important;
}

.bar-track,
.bar-fill,
.stat-meter-track,
.stat-meter-fill {
  border-radius: 9999px !important;
}

.nav-pills .nav-link,
.nav-link,
.cockpit-dock,
.cockpit-dock-btn,
.pill-nav-capsule,
.pill-nav-link {
  border-radius: 9999px !important;
}

.table-responsive,
.cockpit-scroll {
  border-radius: 24px;
}
"""

if "ULTRA-ROUNDED MAX CURVATURE" not in css:
    css = css + "\n" + max_curvature_css
    print("Added ultra-rounded max curvature styles to style.css!")

with open("frontend/static/css/style.css", "w", encoding="utf-8") as f:
    f.write(css)

with open("static/css/style.css", "w", encoding="utf-8") as f:
    f.write(css)

print("Successfully written to frontend/static/css/style.css and static/css/style.css!")
