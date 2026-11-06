with open('frontend/templates/dsa_workbench.html', 'r', encoding='utf-8') as f:
    html = f.read()

# 1. Unit 2 Collision Strategies: Flatten nested boxed cards
old_hash_nested = '''          <div class="d-flex flex-column gap-2 small font-monospace">
            <div class="p-2 rounded d-flex justify-content-between align-items-center" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
              <span class="text-white">1. Chaining (Singly Linked List)</span>
              <span class="badge bg-primary">Load &alpha; &gt; 1 allowed</span>
            </div>
            <div class="p-2 rounded d-flex justify-content-between align-items-center" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
              <span class="text-white">2. Linear Probing: (h + i) % M</span>
              <span class="badge bg-secondary">Sequential Cluster</span>
            </div>
            <div class="p-2 rounded d-flex justify-content-between align-items-center" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
              <span class="text-white">3. Quadratic Probing: (h + i&sup2;) % M</span>
              <span class="badge bg-success">Eliminates Primary</span>
            </div>
            <div class="p-2 rounded d-flex justify-content-between align-items-center" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
              <span class="text-white">4. Double Hashing: (h1 + i&times;h2) % M</span>
              <span class="badge bg-info text-dark">Uniform Scatter</span>
            </div>
          </div>'''

new_hash_flattened = '''          <div class="d-flex flex-column small font-monospace border-top border-secondary border-opacity-10 pt-2">
            <div class="py-2 border-bottom border-secondary border-opacity-10 d-flex justify-content-between align-items-center">
              <span class="text-white">1. Chaining (Linked List)</span>
              <span class="badge bg-secondary bg-opacity-25 text-light border border-secondary border-opacity-40">Load &alpha; &gt; 1</span>
            </div>
            <div class="py-2 border-bottom border-secondary border-opacity-10 d-flex justify-content-between align-items-center">
              <span class="text-white">2. Linear Probing: (h + i) % M</span>
              <span class="badge bg-secondary bg-opacity-25 text-light border border-secondary border-opacity-40">Sequential</span>
            </div>
            <div class="py-2 border-bottom border-secondary border-opacity-10 d-flex justify-content-between align-items-center">
              <span class="text-white">3. Quadratic: (h + i&sup2;) % M</span>
              <span class="badge bg-secondary bg-opacity-25 text-light border border-secondary border-opacity-40">No 1&deg; Cluster</span>
            </div>
            <div class="py-2 d-flex justify-content-between align-items-center">
              <span class="text-white">4. Double Hash: (h1 + i&times;h2) % M</span>
              <span class="badge bg-secondary bg-opacity-25 text-light border border-secondary border-opacity-40">Uniform</span>
            </div>
          </div>'''

html = html.replace(old_hash_nested.replace('\r\n', '\n'), new_hash_flattened.replace('\r\n', '\n'))
html = html.replace(old_hash_nested, new_hash_flattened)

# 2. Unit 5 Priority Heaps: Flatten nested boxed cards
old_heaps_nested = '''          <div class="d-flex flex-column gap-2 small font-monospace">
            <div class="p-2 rounded d-flex justify-content-between align-items-center" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
              <span class="text-white">Leftist Heap (Null Path Length)</span>
              <span class="badge bg-success">O(log N) Merge</span>
            </div>
            <div class="p-2 rounded d-flex justify-content-between align-items-center" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
              <span class="text-white">Binomial Heap (Forest of Trees)</span>
              <span class="badge bg-primary">O(log N) Union</span>
            </div>
            <div class="p-2 rounded d-flex justify-content-between align-items-center" style="background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08);">
              <span class="text-white">Fibonacci Heap (Cascading Cuts)</span>
              <span class="badge bg-warning text-dark">Amortized O(1) Dec-Key</span>
            </div>
          </div>'''

new_heaps_flattened = '''          <div class="d-flex flex-column small font-monospace border-top border-secondary border-opacity-10 pt-2">
            <div class="py-2 border-bottom border-secondary border-opacity-10 d-flex justify-content-between align-items-center">
              <span class="text-white">Leftist Heap (NPL)</span>
              <span class="badge bg-secondary bg-opacity-25 text-light border border-secondary border-opacity-40 font-monospace">O(log N) Merge</span>
            </div>
            <div class="py-2 border-bottom border-secondary border-opacity-10 d-flex justify-content-between align-items-center">
              <span class="text-white">Binomial Heap</span>
              <span class="badge bg-secondary bg-opacity-25 text-light border border-secondary border-opacity-40 font-monospace">O(log N) Union</span>
            </div>
            <div class="py-2 d-flex justify-content-between align-items-center">
              <span class="text-white">Fibonacci Heap</span>
              <span class="badge bg-secondary bg-opacity-25 text-light border border-secondary border-opacity-40 font-monospace">O(1) Dec-Key</span>
            </div>
          </div>'''

html = html.replace(old_heaps_nested.replace('\r\n', '\n'), new_heaps_flattened.replace('\r\n', '\n'))
html = html.replace(old_heaps_nested, new_heaps_flattened)

with open('frontend/templates/dsa_workbench.html', 'w', encoding='utf-8') as f:
    f.write(html)
print('Updated frontend/templates/dsa_workbench.html cleanly.')

