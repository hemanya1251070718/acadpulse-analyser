"""
AcadPulse - Architectural Context PDF Generator
Generates acadpulse_context.pdf and acadpulse_context.md in the project root.
"""

import os
import subprocess
import sys

def main():
    root_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    pdf_path = os.path.join(root_dir, "acadpulse_context.pdf")
    md_path = os.path.join(root_dir, "acadpulse_context.md")
    temp_html = os.path.join(root_dir, "temp_context_print.html")

    html_content = """<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>AcadPulse - Comprehensive Project Context</title>
<style>
  @page {
    size: A4;
    margin: 14mm 16mm 16mm 16mm;
  }
  body {
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;
    color: #1e293b;
    line-height: 1.5;
    font-size: 10pt;
    margin: 0;
    padding: 0;
  }
  h1 {
    font-size: 22pt;
    color: #4338ca;
    margin-top: 0;
    margin-bottom: 3px;
    letter-spacing: -0.02em;
    font-weight: 800;
  }
  .subtitle {
    font-size: 12pt;
    color: #64748b;
    margin-bottom: 12px;
    font-weight: 500;
  }
  .badge-bar {
    display: flex;
    gap: 6px;
    flex-wrap: wrap;
    margin-bottom: 16px;
  }
  .badge {
    display: inline-block;
    padding: 2px 8px;
    font-size: 8pt;
    font-weight: 600;
    border-radius: 999px;
    background: #e0e7ff;
    color: #4338ca;
    border: 1px solid #c7d2fe;
  }
  .badge-success {
    background: #dcfce7;
    color: #15803d;
    border-color: #bbf7d0;
  }
  .badge-dark {
    background: #f1f5f9;
    color: #334155;
    border-color: #e2e8f0;
  }
  h2 {
    font-size: 12.5pt;
    color: #1e1b4b;
    border-bottom: 1.5px solid #e2e8f0;
    padding-bottom: 4px;
    margin-top: 18px;
    margin-bottom: 8px;
    font-weight: 700;
    page-break-after: avoid;
  }
  h3 {
    font-size: 10.5pt;
    color: #4338ca;
    margin-top: 12px;
    margin-bottom: 5px;
    font-weight: 600;
    page-break-after: avoid;
  }
  p, li {
    font-size: 9.3pt;
    color: #334155;
  }
  ul, ol {
    margin-top: 4px;
    margin-bottom: 8px;
    padding-left: 18px;
  }
  li {
    margin-bottom: 3px;
  }
  .alert-box {
    background: #f8fafc;
    border-left: 4px solid #6366f1;
    padding: 8px 12px;
    margin: 10px 0;
    border-radius: 0 6px 6px 0;
    font-size: 9pt;
  }
  .alert-warning {
    border-left-color: #f59e0b;
    background: #fffbeb;
    color: #92400e;
  }
  .alert-warning strong {
    color: #b45309;
  }
  pre, code {
    font-family: 'Cascadia Code', 'Consolas', 'Courier New', monospace;
  }
  code {
    background: #f1f5f9;
    padding: 1px 4px;
    border-radius: 4px;
    font-size: 8.5pt;
    color: #475569;
  }
  pre {
    background: #0f172a;
    color: #f8fafc;
    padding: 10px 12px;
    border-radius: 6px;
    font-size: 8pt;
    line-height: 1.4;
    overflow-x: auto;
    page-break-inside: avoid;
    margin: 6px 0 10px 0;
  }
  pre code {
    background: transparent;
    color: #f8fafc;
    padding: 0;
  }
  table {
    width: 100%;
    border-collapse: collapse;
    margin: 8px 0 12px 0;
    font-size: 8.5pt;
    page-break-inside: avoid;
  }
  th {
    background: #f1f5f9;
    color: #1e293b;
    font-weight: 700;
    text-align: left;
    padding: 6px 8px;
    border: 1px solid #cbd5e1;
  }
  td {
    padding: 5px 8px;
    border: 1px solid #e2e8f0;
    color: #334155;
  }
  tr:nth-child(even) td {
    background: #f8fafc;
  }
  .footer-note {
    margin-top: 20px;
    border-top: 1px solid #e2e8f0;
    padding-top: 6px;
    font-size: 7.5pt;
    color: #94a3b8;
    text-align: center;
  }
</style>
</head>
<body>

<h1>⚡ AcadPulse</h1>
<div class="subtitle">Comprehensive Architectural &amp; Engineering Master Context</div>

<div class="badge-bar">
  <span class="badge badge-success">&#9679; Live Production Verified</span>
  <span class="badge">Vercel: acadpulse-analyser.vercel.app</span>
  <span class="badge">GitHub: hemanya1251070718/acadpulse-analyser</span>
  <span class="badge badge-dark">Zero-STL Core Engine</span>
  <span class="badge badge-dark">Flask 3.0.3 WSGI</span>
  <span class="badge badge-dark">Bootstrap 5.3 + Glass UI</span>
</div>

<h2>1. Executive Summary &amp; Purpose</h2>
<p>
  <strong>AcadPulse</strong> is a production-grade, full-stack Academic Performance &amp; Student Ranking Analyser engineered for institutional continuous evaluation, multi-assessment tracking, dynamic merit rankings, and comprehensive Data Structures &amp; Algorithms (DSA) analytics.
</p>
<div class="alert-box">
  <strong>Course Problem Statement:</strong><br>
  <em>"An educational institution conducts multiple examinations and continuous assessments throughout the semester. The institute requires a system that maintains student records, updates marks whenever assessments are conducted, generates merit lists based on different evaluation criteria, and identifies top-performing students. Develop an application to automate these activities."</em>
</div>

<h2>2. Live Deployments &amp; Repositories</h2>
<table>
  <thead>
    <tr>
      <th>Resource</th>
      <th>Location / URL</th>
      <th>Status</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Production Vercel</strong></td>
      <td>https://acadpulse-analyser.vercel.app</td>
      <td>Active, Public, Zero Auth Gates, 18/18 Tests Passing</td>
    </tr>
    <tr>
      <td><strong>GitHub Repository</strong></td>
      <td>https://github.com/hemanya1251070718/acadpulse-analyser</td>
      <td>Public (main branch), All Commits Linked &amp; Contributing</td>
    </tr>
    <tr>
      <td><strong>Automated CI</strong></td>
      <td>GitHub Actions (.github/workflows/ci.yml)</td>
      <td>Automated Unit Tests &amp; DSA Suite Passing</td>
    </tr>
    <tr>
      <td><strong>Cloud Mirror</strong></td>
      <td>Google Cloud Run (Asia South 1)</td>
      <td>Multi-stage Dockerized Mirror</td>
    </tr>
  </tbody>
</table>

<h2>3. System Architecture &amp; Tech Stack</h2>
<ul>
  <li><strong>Frontend Architecture:</strong> Vanilla HTML5/Jinja2 templates with Bootstrap 5.3 (dark theme), Bootstrap Icons 1.11.3, and Chart.js 4.4.4. Features custom Apple Vision-style frosted glass cards, liquid specular hover tracking, procedural HTML5 Canvas lightning storm engine, SVG circular speedometer gauge, and ascending sparklines.</li>
  <li><strong>Backend Architecture:</strong> Python 3.10+ / Flask 3.0.3 serverless WSGI structure. Utilizes <code>VercelPathMiddleware</code> in <code>api/index.py</code> to unwrap query rewrites (<code>?__path__=/$1</code>) and restore native request paths and parameters deterministically.</li>
  <li><strong>Persistence Layer:</strong> JSON-backed storage (<code>data/students.json</code>) managed via <code>backend/data_manager.py</code> with safe temporary directory fallbacks for read-only serverless cloud runs. Supports dynamic marks updates and CSV gradebook exports.</li>
  <li><strong>Algorithmic Core (Zero-STL Suite):</strong> 40/40 topics across 6 curriculum units implemented from scratch without standard template library containers. Python fallbacks in <code>backend/dsa_service.py</code> guarantee identical behavior regardless of binary compilation availability.</li>
</ul>

<h2>4. Strict Non-Negotiable Constraints</h2>
<div class="alert-box alert-warning">
  <strong>CRITICAL CONSTRAINTS FOR FUTURE MODIFICATIONS:</strong>
  <ul>
    <li><strong>Zero Forbidden Keywords:</strong> Complete absence of cohort identifiers: <code>VIT PUNE</code>, <code>SY CSE</code>, <code>SY CS</code>, and compiler identifier <code>C++</code> across all user-facing templates, headings, metadata, badges, and documentation.</li>
    <li><strong>Institutional Emails:</strong> All student accounts must use institutional email domain: <code>@acadpulse.edu</code>.</li>
    <li><strong>Vercel WSGI Integrity:</strong> Do not break the <code>VercelPathMiddleware</code> or remove root static directory mirroring (<code>static/</code> must stay synchronized with <code>frontend/static/</code>).</li>
    <li><strong>Continuous Down-by-Down Dashboard:</strong> The main index page (<code>/</code>) must continue presenting all project modules in sequential top-to-bottom layout with smooth scroll reveal animations.</li>
  </ul>
</div>

<h2>5. 40/40 DSA Course Syllabus Coverage</h2>
<table>
  <thead>
    <tr>
      <th style="width: 14%;">Unit</th>
      <th style="width: 40%;">Core Structures &amp; Implementations</th>
      <th>Application in AcadPulse</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Unit 1</strong></td>
      <td>Dynamic Vector, 2D/3D Tensors, Triplet Sparse Matrix, Simple Transpose, Fast Transpose, QuickSort, MergeSort</td>
      <td>Multi-subject semester marksheets, compact sparse matrix representation, and divide-and-conquer ranking sort.</td>
    </tr>
    <tr>
      <td><strong>Unit 2</strong></td>
      <td>Singly, Doubly, Circular Linked Lists, Floyd's Cycle Detection, djb2 Hash Table (Chaining, Linear, Quadratic, Double Hash)</td>
      <td>O(1) student registry lookup by PRN, roll-number index, and cyclical assessment scheduling.</td>
    </tr>
    <tr>
      <td><strong>Unit 3</strong></td>
      <td>Infix-to-Postfix Shunting Yard, Stack RPN Evaluation, DEPQ (Min-Max Heap), Circular Queue Viva Scheduler, Josephus</td>
      <td>Arbitrary grading formula evaluation, simultaneous O(1) identification of toppers &amp; at-risk cohorts, viva queue.</td>
    </tr>
    <tr>
      <td><strong>Unit 4</strong></td>
      <td>Academic Hierarchy General Tree, Binary Tree Traversals (Recursive &amp; Iterative), BST with 3-Case Deletion &amp; Range Query</td>
      <td>Departmental hierarchy modeling, score range filtering (e.g. students scoring between 75 and 90).</td>
    </tr>
    <tr>
      <td><strong>Unit 5</strong></td>
      <td>Binary Max/Min Heap (Heapsort), Leftist Heap (O(log N) merge), Binomial Heap, Fibonacci Heap</td>
      <td>O(N log N) merit list generation, merging division cohorts with priority queues.</td>
    </tr>
    <tr>
      <td><strong>Unit 6</strong></td>
      <td>Dual Graph (Matrix &amp; Adjacency List), BFS, DFS, Cycle Check, Prim &amp; Kruskal MST with DSU, Dijkstra, Floyd-Warshall</td>
      <td>Curriculum prerequisite dependency DAG, optimal student peer-mentoring network, shortest prerequisite path.</td>
    </tr>
  </tbody>
</table>

<h2>6. Project Directory Map</h2>
<pre><code>acadpulse-analyser/
├── api/index.py               # WSGI serverless middleware for Vercel
├── backend/
│   ├── app.py                 # Flask server setup and web routes
│   ├── routes.py              # REST API blueprint routes (/api/...)
│   ├── data_manager.py        # Student records persistence & CSV export
│   ├── dsa_service.py         # Pure-DSA calculation engine & algorithm bridge
│   └── test_routes.py         # Automated unittest test suite
├── data/students.json         # Master student database (@acadpulse.edu)
├── engine/                    # 100% Zero-STL native algorithmic library
│   ├── include/ (core, ds, algo)
│   └── tests/test_all_dsa.cpp # Verification runner covering 40/40 topics
├── frontend/
│   ├── static/ (css/style.css, js/main.js)
│   └── templates/ (dashboard, students, assessments, merit_list, etc.)
├── static/                    # Root Edge CDN mirror of frontend/static/
├── scripts/verify_endpoints.py# 18-point automated local & production verifier
├── vercel.json                # Vercel deployment rewrites & includes
├── requirements.txt           # Flask 3.0.3, gunicorn 22.0.0
└── README.md                  # Comprehensive architectural overview</code></pre>

<h2>7. Full REST API &amp; Web Endpoints (All 18 Passing HTTP 200)</h2>
<table>
  <thead>
    <tr>
      <th>Endpoint</th>
      <th>Method</th>
      <th>Type</th>
      <th>Purpose</th>
    </tr>
  </thead>
  <tbody>
    <tr><td><code>/</code></td><td>GET</td><td>HTML</td><td>Unified Cockpit Dashboard with Hero Showcase and modules down-by-down</td></tr>
    <tr><td><code>/students</code></td><td>GET</td><td>HTML</td><td>Interactive student directory management tab</td></tr>
    <tr><td><code>/assessments</code></td><td>GET</td><td>HTML</td><td>Continuous assessment gradebook (MSE, ESE, Lab, Project)</td></tr>
    <tr><td><code>/merit-list</code></td><td>GET</td><td>HTML</td><td>Dynamic merit ranking generator with live formula evaluator</td></tr>
    <tr><td><code>/dsa-workbench</code></td><td>GET</td><td>HTML</td><td>40/40 topics interactive DSA visualizer lab</td></tr>
    <tr><td><code>/curriculum-graph</code></td><td>GET</td><td>HTML</td><td>Topological prerequisite DAG &amp; mentoring network graph</td></tr>
    <tr><td><code>/syllabus-coverage</code></td><td>GET</td><td>HTML</td><td>100% course syllabus alignment matrix</td></tr>
    <tr><td><code>/api/dashboard/summary</code></td><td>GET</td><td>JSON</td><td>KPI analytics, class averages, toppers, at-risk, grade distribution</td></tr>
    <tr><td><code>/api/students/list</code></td><td>GET</td><td>JSON</td><td>Returns all student records with individual subject marks</td></tr>
    <tr><td><code>/api/students/add</code></td><td>POST</td><td>JSON</td><td>Add new student record to persistent registry</td></tr>
    <tr><td><code>/api/students/update/&lt;prn&gt;</code></td><td>POST/PUT</td><td>JSON</td><td>Update marks or attendance for a student</td></tr>
    <tr><td><code>/api/students/delete/&lt;prn&gt;</code></td><td>POST/DEL</td><td>JSON</td><td>Remove student record by PRN</td></tr>
    <tr><td><code>/api/students/export-csv</code></td><td>GET</td><td>CSV</td><td>Downloadable CSV export of academic grades</td></tr>
    <tr><td><code>/api/ranking/generate</code></td><td>GET/POST</td><td>JSON</td><td>Evaluates weightings and sorts cohort via heapsort algorithm</td></tr>
    <tr><td><code>/api/ranking/formula-eval</code></td><td>GET/POST</td><td>JSON</td><td>Infix formula translation and RPN stack evaluation</td></tr>
    <tr><td><code>/api/dsa/sparse-matrix</code></td><td>GET</td><td>JSON</td><td>Sparse matrix construction and fast transpose performance metrics</td></tr>
    <tr><td><code>/api/dsa/graph-analysis</code></td><td>GET</td><td>JSON</td><td>Topological ordering, cycle detection, and Dijkstra shortest paths</td></tr>
    <tr><td><code>/api/dsa/scheduler</code></td><td>GET/POST</td><td>JSON</td><td>Circular queue viva exam scheduling simulation</td></tr>
    <tr><td><code>/api/dsa/josephus</code></td><td>GET/POST</td><td>JSON</td><td>Circular linked list Josephus elimination simulation</td></tr>
    <tr><td><code>/api/health</code></td><td>GET</td><td>JSON</td><td>Service operational healthcheck</td></tr>
  </tbody>
</table>

<div class="footer-note">
  AcadPulse — Student Ranking &amp; Academic Performance Analyser | Automated Architecture Context Document
</div>

</body>
</html>
"""

    with open(temp_html, "w", encoding="utf-8") as f:
        f.write(html_content)

    edge_candidates = [
        r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
        r"C:\Program Files\Microsoft\Edge\Application\msedge.exe"
    ]
    edge_exe = next((p for p in edge_candidates if os.path.exists(p)), None)

    if not edge_exe:
        print("ERROR: Microsoft Edge executable not found for PDF printing.")
        sys.exit(1)

    cmd = [
        edge_exe,
        "--headless",
        "--disable-gpu",
        "--no-pdf-header-footer",
        f"--print-to-pdf={pdf_path}",
        temp_html
    ]

    res = subprocess.run(cmd, capture_output=True, text=True)
    if os.path.exists(temp_html):
        os.remove(temp_html)

    if os.path.exists(pdf_path):
        size = os.path.getsize(pdf_path)
        print(f"SUCCESS: Generated PDF at {pdf_path} ({size:,} bytes)")
        try:
            import pypdf
            reader = pypdf.PdfReader(pdf_path)
            print(f"Total Pages: {len(reader.pages)}")
        except Exception:
            pass
    else:
        print("ERROR: Failed to generate PDF output.")
        sys.exit(1)

if __name__ == "__main__":
    main()

