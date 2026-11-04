import sys
import os

sys.path.insert(0, os.path.dirname(__file__))
from app import app

client = app.test_client()

routes = [
    '/',
    '/students',
    '/assessments',
    '/merit-list',
    '/dsa-workbench',
    '/curriculum-graph',
    '/syllabus-coverage',
    '/api/health',
    '/api/dashboard/summary',
    '/api/students/list',
    '/api/dsa/sparse-matrix',
    '/api/dsa/graph-analysis'
]

all_ok = True
for r in routes:
    res = client.get(r)
    status = res.status_code
    print(f"GET {r:30} -> {status}")
    if status != 200:
        all_ok = False

rank_res = client.post('/api/ranking/generate', json={'subject': 'DS', 'algorithm': 'heapsort'})
print(f"POST /api/ranking/generate          -> {rank_res.status_code}")
if rank_res.status_code != 200:
    all_ok = False

eval_res = client.post('/api/ranking/formula-eval', json={'formula': '(MSE * 0.3) + (ESE * 0.5) + (LAB * 0.2)', 'mse': 30, 'ese': 50, 'lab': 20, 'proj': 20})
data = eval_res.get_json()
score = data.get("score") if data else None
print(f"POST /api/ranking/formula-eval      -> {eval_res.status_code}, score: {score}")
if eval_res.status_code != 200:
    all_ok = False

if all_ok:
    print("\n=============================================")
    print(" ALL FLASK ROUTES AND DSA APIS VERIFIED 100%! ")
    print("=============================================")
else:
    sys.exit(1)

