"""
AcadPulse - Endpoint Verification Script
Tests all web pages, REST endpoints, and static assets against local or production deployments.
"""

import urllib.request
import json
import sys

def verify_all(base_url="https://acadpulse-analyser.vercel.app"):
    print(f"Testing AcadPulse Endpoints on: {base_url}")
    print("-" * 65)

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

    all_pass = True
    for ep in endpoints:
        method = ep[0]
        path = ep[1]
        payload = ep[2] if len(ep) > 2 else None
        url = base_url + path
        headers = {"User-Agent": "AcadPulse-Verification/1.0"}
        data = None
        if payload:
            data = json.dumps(payload).encode("utf-8")
            headers["Content-Type"] = "application/json"

        req = urllib.request.Request(url, data=data, headers=headers, method=method)
        try:
            with urllib.request.urlopen(req, timeout=12) as res:
                body = res.read()
                print(f"[{method:4}] {path:32} -> {res.status} ({len(body):6} B)")
        except Exception as e:
            all_pass = False
            print(f"[{method:4}] {path:32} -> FAILED: {e}")

    print("-" * 65)
    print("ALL TESTS PASSED?", all_pass)
    return all_pass

if __name__ == "__main__":
    url = sys.argv[1] if len(sys.argv) > 1 else "https://acadpulse-analyser.vercel.app"
    success = verify_all(url)
    sys.exit(0 if success else 1)
