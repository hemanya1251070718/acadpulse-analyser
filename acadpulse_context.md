# 📋 AcadPulse — Complete Project Context & Architecture Master Prompt

## 1. 🌐 LIVE DEPLOYMENTS & REPOSITORIES
- **Production Vercel URL:** https://acadpulse-analyser.vercel.app
- **GitHub Repository:** https://github.com/hemanya1251070718/acadpulse-analyser (Branch: `main`)
- **Alternative Cloud Mirror:** Google Cloud Run (Asia South 1)
- **CI / CD:** GitHub Actions automated verification workflow (`.github/workflows/ci.yml`) passing on every push.

---

## 2. 🏛️ SYSTEM ARCHITECTURE & TECH STACK
1. **Frontend**:
   - Vanilla HTML5 / Jinja2 templates (`frontend/templates/`).
   - Custom Glassmorphism CSS (`frontend/static/css/style.css` & root mirror `static/css/style.css`).
   - Vanilla JavaScript (`frontend/static/js/main.js` & root mirror `static/js/main.js`).
   - Bootstrap 5.3 (Dark theme), Bootstrap Icons 1.11.3, Chart.js 4.4.4.
   - Procedural HTML5 Canvas ambient lightning engine, SVG circular speedometer gauge, SVG ascending sparkline graphs.
   - Typography: Google Fonts `'Outfit'` (headlines), `'Plus Jakarta Sans'` (body), and `'JetBrains Mono'` (code/data metrics).

2. **Backend**:
   - Python 3.10+ / Flask 3.0.3 modular application.
   - WSGI Serverless bridge (`api/index.py`) using `VercelPathMiddleware` to handle Vercel query-string route rewrites (`?__path__=/$1`).
   - Modular Flask Blueprint (`backend/routes.py`) registered with prefix `/api`.
   - Data persistence manager (`backend/data_manager.py`) with support for read-only `/tmp` serverless execution environments.
   - Native DSA bridge (`backend/dsa_service.py`) running Zero-STL algorithmic engines with pure Python mathematical fallbacks.

3. **Core Algorithmic Suite (40/40 Complete DSA Course Topics)**:
   - Zero external libraries or STL containers.
   - Unit 1: Dynamic Vectors, Row/Col Major 2D/3D Tensors, Sparse Matrix (Triplet form, Simple & Fast Transpose $O(rows + non\_zeros)$), In-place QuickSort (median-of-three), Iterative MergeSort.
   - Unit 2: Singly, Doubly, Circular Linked Lists with Floyd’s Fast/Slow cycle detector, Polynomial arithmetic, and djb2 Hash Table with 4 collision techniques (Chaining, Linear Probing, Quadratic Probing, Double Hashing).
   - Unit 3: Shunting-Yard Infix-to-Postfix Stack parser, Reverse Polish Notation evaluator, Double-Ended Priority Queue (DEPQ / Min-Max Heap) with $O(1)$ simultaneous topper & remedial at-risk lookup, Circular Queue Viva Scheduler, Circular List Josephus elimination.
   - Unit 4: Academic Hierarchy General Tree, Binary Tree (recursive & iterative Pre/In/Post/Level traversals), Binary Search Tree (BST) with 3-case deletion and Range Queries.
   - Unit 5: Binary Max/Min Heap (Heapsort), Leftist Heap with $O(\log N)$ merge, Binomial Heap, and Fibonacci Heap structure with amortized $O(1)$ operations.
   - Unit 6: Dual Representation Graph (Adjacency Matrix & Adjacency List), BFS, DFS, Cycle Detection, Prim's and Kruskal's Minimum Spanning Tree (with Disjoint Set Union / DSU by rank and path compression), Dijkstra's single-source shortest path, and Floyd-Warshall all-pairs shortest path.

---

## 3. ⚠️ STRICT CONSTRAINTS & CODING RULES (DO NOT BREAK)
1. **ZERO FORBIDDEN KEYWORDS**:
   - Absolutely **NO** mention of institutional cohort strings such as `"VIT PUNE"`, `"SY CSE"`, `"SY CS"`, or language compiler tag `"C++"` in user-facing templates, badge text, headings, or documentation.
   - All institutional student emails must use `@acadpulse.edu` (e.g. `aarav.sharma23@acadpulse.edu`).
2. **VERCEL SERVERLESS COMPATIBILITY**:
   - Vercel routes all requests via `vercel.json` rewrites to `/api/index.py?__path__=/$1`.
   - Any query string in the requested URL is parsed in `VercelPathMiddleware`. Static files must be mirrored in both `frontend/static/` and the root `static/` folder so Vercel Edge CDN serves them with proper MIME types.
3. **DOWN-BY-DOWN DASHBOARD ARRANGEMENT**:
   - The Home/Dashboard (`/`) contains all feature sections arranged sequentially down the page (Student Registry, Assessments, Dynamic Merit List, Curriculum Graph, DSA Lab Workbench, Syllabus Coverage) with smooth bi-directional scroll-reveal animations (`.reveal-on-scroll`).
   - Dedicated standalone tabs exist for each module (`/students`, `/assessments`, `/merit-list`, `/dsa-workbench`, `/curriculum-graph`, `/syllabus-coverage`).
4. **UI VISUAL DESIGN IDENTITY**:
   - **Floating Pill Capsule Navigation Header**: Minimal brand `⚡ AcadPulse` on the left, centered pill capsule nav `[ Home | Students | Assessments | Merit List | DSA Lab | Graph | Syllabus ]`, and pill action button `Launch Engine` on the right.
   - **Atmospheric Hero Stage**:
     - Deep forest-obsidian dark gradient with a central glowing violet nebula bloom.
     - Slower ambient lightning flashes (every 1.8s–3.8s) with graceful decay (`b.alpha -= 0.022`).
     - Floating cartoon student stickmen (`🧑‍🎓`), bouncing books (`📚`, `📖`), mortarboards (`🎓`), and academic scrolls (`📜`).
     - Tilted circular badge (`TOP MERIT`) and floating star sparkle (`✦`).
     - Headline: *"Rank every student, one assessment at a time."*
   - **Three 3D Floating Perspective Hero Cards**:
     - *Left Card (tilted -3.5°)*: Subject Health with purple horizontal progress bars.
     - *Center Card (elevated glowing violet gradient)*: Top Performer with SVG semi-circular speedometer gauge (`92`) and caption `Aarav Sharma, Thriving`.
     - *Right Card (tilted +3.5°)*: Merit Velocity with `12 weeks` badge and smooth ascending SVG sparkline curve.

---

## 4. 🗂️ DIRECTORY STRUCTURE
```
acadpulse-analyser/
├── acadpulse_context.pdf      # Visual vector PDF of this full context
├── acadpulse_context.md       # Markdown version of this full context
├── api/
│   └── index.py               # WSGI entrypoint with VercelPathMiddleware
├── backend/
│   ├── app.py                 # Flask server setup and root page routes
│   ├── routes.py              # REST API blueprint routes (/api/...)
│   ├── data_manager.py        # JSON & CSV student persistence manager
│   ├── dsa_service.py         # Algorithmic bridge & calculation logic
│   ├── sample_data.py         # Mock dataset generator
│   └── test_routes.py         # Unittest test cases
├── data/
│   └── students.json          # Persistent student records (@acadpulse.edu)
├── docs/
│   ├── SYLLABUS_COVERAGE.md   # 40/40 topic mapping across Units 1–6
│   └── VIVA_QUESTIONS.md      # Examiner viva reference guide
├── engine/                    # High-performance native algorithmic source
│   ├── include/core/          # Vector, Pair, Array2D, Array3D, Metrics
│   ├── include/ds/            # LinkedLists, Queue, Stack, Hash, Trees, Heaps
│   ├── include/algo/          # Sorting, Graph, MST, ShortestPath, ShuntingYard
│   ├── src/                   # C++ engine runners & API bridge
│   └── tests/test_all_dsa.cpp # 100% Zero-STL verification suite
├── frontend/
│   ├── static/
│   │   ├── css/style.css      # Core styles, glassmorphism, animations
│   │   └── js/main.js         # Lightning engine, gauge animation, specular cursor
│   └── templates/
│       ├── base.html          # Floating pill header, footer, global assets
│       ├── dashboard.html     # Hero stage + down-by-down sequential dashboard
│       ├── students.html      # Standalone student registry management
│       ├── assessments.html   # Standalone continuous assessment marks entry
│       ├── merit_list.html    # Standalone dynamic merit generator & formula eval
│       ├── dsa_workbench.html # Standalone 40/40 DSA visualizer lab
│       ├── curriculum_graph.html # Standalone curriculum DAG & mentoring graph
│       └── syllabus_matrix.html  # Standalone syllabus coverage matrix
├── static/                    # Root CDN mirror of frontend/static/
│   ├── css/style.css
│   └── js/main.js
├── scripts/
│   ├── generate_context_pdf.py# Generator for this PDF & MD context
│   └── verify_endpoints.py    # Automated test runner testing all 18 endpoints
├── .github/workflows/ci.yml   # GitHub Actions automated test & build matrix
├── vercel.json                # Vercel serverless rewrite & include configuration
├── requirements.txt           # Python dependencies (Flask==3.0.3, gunicorn==22.0.0)
└── README.md                  # Comprehensive architectural project documentation
```

---

## 5. 🔌 API ENDPOINT REFERENCE
- `GET /` — Full Dashboard with Fernwood Hero & down-by-down modules
- `GET /students` — Student Directory Management page
- `GET /assessments` — Continuous Assessment Entry page
- `GET /merit-list` — Dynamic Merit Leaderboard & Formula Evaluation page
- `GET /dsa-workbench` — Interactive 40/40 DSA Laboratory page
- `GET /curriculum-graph` — Curriculum DAG and Student Mentoring Graph page
- `GET /syllabus-coverage` — 100% Comprehensive Syllabus Coverage page
- `GET /api/dashboard/summary` — JSON: KPI totals, class averages, toppers, at-risk, grade distribution
- `GET /api/students/list` — JSON: List of all 15 student records with marks
- `POST /api/students/add` — JSON: Add student record
- `POST/PUT /api/students/update/<prn>` — JSON: Update marks or student profile
- `POST/DELETE /api/students/delete/<prn>` — JSON: Remove student
- `GET /api/students/export-csv` — Returns CSV file download of grade records
- `GET/POST /api/ranking/generate` — JSON: Evaluates weights, sorts via heapsort, returns ranked cohort
- `GET/POST /api/ranking/formula-eval` — JSON: Evaluates custom Shunting-Yard infix formula
- `GET /api/dsa/sparse-matrix` — JSON: Triplet sparse matrix and fast transpose benchmarks
- `GET /api/dsa/graph-analysis` — JSON: Graph topological order, cycle check, Dijkstra shortest paths
- `GET/POST /api/dsa/scheduler` — JSON: Circular queue examination viva slot scheduler
- `GET/POST /api/dsa/josephus?n=7&k=3` — JSON: Josephus elimination sequence
- `GET /api/health` — JSON: Healthcheck (`status: healthy`, `version: 2.0`)
- `GET /static/css/style.css` — CSS: 200 OK text/css
- `GET /static/js/main.js` — JS: 200 OK text/javascript

