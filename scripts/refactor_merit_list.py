with open('frontend/templates/merit_list.html', 'r', encoding='utf-8') as f:
    html = f.read()

old_nested = '''        <div class="d-flex justify-content-between align-items-center p-2 rounded mb-2" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
          <div>
            <div class="small text-muted font-monospace">SCORE</div>
            <div class="fs-5 fw-bold text-white">${s.composite_score}%</div>
          </div>
          <div class="text-center">
            <div class="small text-muted font-monospace">PERCENTILE</div>
            <div class="fw-bold text-info">${s.percentile}%</div>
          </div>
          <div class="text-end">
            <div class="small text-muted font-monospace">SGPA</div>
            <span class="badge px-2 py-1 fw-bold" style="background: rgba(16, 185, 129, 0.2); color: #34d399; border: 1px solid rgba(16, 185, 129, 0.4);">
              ${s.sgpa}
            </span>
          </div>
        </div>'''

new_flattened = '''        <!-- Flattened Metrics Row (Eliminating nested card container) -->
        <div class="d-flex justify-content-between align-items-baseline mb-3 pb-2 border-bottom border-secondary border-opacity-10">
          <div>
            <div class="metric-caption">SCORE</div>
            <div class="metric-number-sm">${s.composite_score}<span class="metric-unit">%</span></div>
          </div>
          <div class="text-center">
            <div class="metric-caption">PERCENTILE</div>
            <div class="fw-semibold text-info font-monospace">${s.percentile}%</div>
          </div>
          <div class="text-end">
            <div class="metric-caption">SGPA</div>
            <span class="score-pill-neutral">${s.sgpa}</span>
          </div>
        </div>'''

html = html.replace(old_nested.replace('\r\n', '\n'), new_flattened.replace('\r\n', '\n'))
html = html.replace(old_nested, new_flattened)

with open('frontend/templates/merit_list.html', 'w', encoding='utf-8') as f:
    f.write(html)
print('Updated frontend/templates/merit_list.html cleanly.')
