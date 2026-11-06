import os
import sys
import json

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from backend.app import app

client = app.test_client()

endpoints = [
    ("GET", "/"),
    ("GET", "/students"),
    ("GET", "/assessments"),
    ("GET", "/merit-list"),
    ("GET", "/dsa-workbench"),
    ("GET", "/curriculum-graph"),
    ("GET", "/syllabus-coverage"),
    ("GET", "/api/dashboard/summary"),
    ("GET", "/api/students/list"),
    ("POST", "/api/ranking/generate", {
        "subject": "DS",
        "formula": "(MSE * 0.3) + (ESE * 0.5) + (LAB * 0.2)",
        "algorithm": "heapsort"
    }),
    ("POST", "/api/ranking/formula-eval", {
        "formula": "(MSE * 0.3) + (ESE * 0.5)",
        "mse": 25.0,
        "ese": 45.0
    }),
    ("GET", "/api/dsa/sparse-matrix"),
    ("GET", "/api/dsa/graph-analysis"),
    ("GET", "/api/dsa/scheduler"),
    ("GET", "/api/dsa/josephus?n=7&k=3"),
    ("GET", "/api/health"),
    ("GET", "/static/css/style.css"),
    ("GET", "/static/js/main.js"),
]

all_passed = True
for ep in endpoints:
    method = ep[0]
    path = ep[1]
    payload = ep[2] if len(ep) > 2 else None
    
    if method == "GET":
        res = client.get(path)
    else:
        res = client.post(path, json=payload)
        
    status = res.status_code
    if status == 200:
        print(f"[PASS] [{method:4}] {path:<32} -> {status} ({len(res.data):6} B)")
    else:
        print(f"[FAIL] [{method:4}] {path:<32} -> {status}")
        all_passed = False

if all_passed:
    print("\n>>> ALL 18 ENDPOINTS PASSED WITH 200 OK ON LOCAL FLASK! <<<")
else:
    sys.exit(1)
