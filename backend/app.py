"""
AcadPulse - Student Ranking & Academic Performance Analyser
Academic Performance & Student Ranking Platform
Production-Ready Implementation
"""

import os
import sys

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BACKEND_DIR = os.path.join(BASE_DIR, "backend")

if BACKEND_DIR not in sys.path:
    sys.path.insert(0, BACKEND_DIR)

from flask import Flask, render_template

TEMPLATE_DIR = os.path.join(BASE_DIR, "frontend", "templates")
STATIC_DIR = os.path.join(BASE_DIR, "frontend", "static")

app = Flask(
    __name__,
    template_folder=TEMPLATE_DIR,
    static_folder=STATIC_DIR,
)

try:
    from routes import api
except ImportError:
    from backend.routes import api

app.register_blueprint(api, url_prefix="/api")

@app.route("/")
def dashboard():
    return render_template("dashboard.html")

@app.route("/students")
def students_page():
    return render_template("students.html")

@app.route("/assessments")
def assessments_page():
    return render_template("assessments.html")

@app.route("/merit-list")
def merit_list_page():
    return render_template("merit_list.html")

@app.route("/dsa-workbench")
def dsa_workbench_page():
    return render_template("dsa_workbench.html")

@app.route("/curriculum-graph")
def curriculum_graph_page():
    return render_template("curriculum_graph.html")

@app.route("/syllabus-coverage")
def syllabus_coverage_page():
    return render_template("syllabus_matrix.html")

if __name__ == "__main__":
    port = int(os.environ.get("PORT", 5000))
    app.run(host="0.0.0.0", port=port, debug=True)
