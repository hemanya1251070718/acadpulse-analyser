from flask import Blueprint, render_template, request, jsonify, Response
from data_manager import DataManager
from dsa_service import DSAService

api = Blueprint("api", __name__)

# ==========================================================
# PAGE ROUTES
# ==========================================================

@api.route("/dashboard/summary", methods=["GET"])
def dashboard_summary():
    students = DataManager.get_all()
    ranked, algo_meta = DSAService.rank_students(students)
    top_at_risk = DSAService.get_top_and_at_risk(students)

    avg_score = round(sum(s["composite_score"] for s in ranked) / len(ranked), 2) if ranked else 0
    avg_attendance = round(sum(s.get("attendance", 0) for s in students) / len(students), 2) if students else 0
    total_students = len(students)

    # Score distribution for Chart.js
    dist = {"90-100": 0, "75-89": 0, "60-74": 0, "40-59": 0, "Below 40": 0}
    for s in ranked:
        sc = s["composite_score"]
        if sc >= 90: dist["90-100"] += 1
        elif sc >= 75: dist["75-89"] += 1
        elif sc >= 60: dist["60-74"] += 1
        elif sc >= 40: dist["40-59"] += 1
        else: dist["Below 40"] += 1

    return jsonify({
        "status": "success",
        "data": {
            "total_students": total_students,
            "avg_score": avg_score,
            "avg_attendance": avg_attendance,
            "toppers": top_at_risk["depq_toppers"],
            "at_risk": top_at_risk["depq_at_risk"],
            "distribution": dist,
            "recent_ranked": ranked[:6]
        }
    })

@api.route("/students/list", methods=["GET"])
def students_list():
    students = DataManager.get_all()
    return jsonify({"status": "success", "data": students})

@api.route("/students/add", methods=["POST"])
def student_add():
    payload = request.get_json() or {}
    ok, msg = DataManager.add(payload)
    return jsonify({"status": "success" if ok else "error", "message": msg})

@api.route("/students/update/<prn>", methods=["POST", "PUT"])
def student_update(prn):
    payload = request.get_json() or {}
    ok, msg = DataManager.update(prn, payload)
    return jsonify({"status": "success" if ok else "error", "message": msg})

@api.route("/students/delete/<prn>", methods=["POST", "DELETE"])
def student_delete(prn):
    ok, msg = DataManager.delete(prn)
    return jsonify({"status": "success" if ok else "error", "message": msg})

@api.route("/students/export-csv", methods=["GET"])
def export_csv():
    csv_data = DataManager.export_csv()
    return Response(
        csv_data,
        mimetype="text/csv",
        headers={"Content-Disposition": "attachment;filename=acadpulse_student_records.csv"}
    )

@api.route("/ranking/generate", methods=["GET", "POST"])
def generate_ranking():
    payload = request.get_json(silent=True) or (request.args.to_dict() if request.method == "GET" else {})
    subject = payload.get("subject", "DS")
    formula = payload.get("formula", "(MSE * 0.3) + (ESE * 0.5) + (LAB * 0.2)")
    algorithm = payload.get("algorithm", "heapsort")

    students = DataManager.get_all()
    ranked, algo_meta = DSAService.rank_students(students, subject=subject, formula=formula, algorithm=algorithm)

    return jsonify({
        "status": "success",
        "data": {
            "ranked_students": ranked,
            "algorithm": algo_meta,
            "formula": formula,
            "subject": subject
        }
    })

@api.route("/ranking/formula-eval", methods=["GET", "POST"])
def formula_eval():
    payload = request.get_json(silent=True) or (request.args.to_dict() if request.method == "GET" else {})
    formula = payload.get("formula", "(MSE * 0.3) + (ESE * 0.5) + (LAB * 0.2)")
    try:
        mse = float(payload.get("mse", 25.0))
        ese = float(payload.get("ese", 45.0))
        lab = float(payload.get("lab", 18.0))
        proj = float(payload.get("proj", 18.0))
    except (ValueError, TypeError):
        mse, ese, lab, proj = 25.0, 45.0, 18.0, 18.0

    res = DSAService.eval_formula(formula, mse, ese, lab, proj)
    return jsonify(res)

@api.route("/dsa/sparse-matrix", methods=["GET"])
def dsa_sparse_matrix():
    res = DSAService.run_sparse_matrix()
    return jsonify(res)

@api.route("/dsa/graph-analysis", methods=["GET"])
def dsa_graph_analysis():
    res = DSAService.run_graph_analysis()
    return jsonify(res)

@api.route("/dsa/scheduler", methods=["GET", "POST"])
def dsa_scheduler():
    res = DSAService.run_scheduler()
    return jsonify(res)

@api.route("/dsa/josephus", methods=["GET", "POST"])
def dsa_josephus():
    n = int(request.args.get("n", 7))
    k = int(request.args.get("k", 3))
    res = DSAService.run_josephus(n, k)
    return jsonify(res)

@api.route("/health", methods=["GET"])
def health():
    return jsonify({"status": "healthy", "service": "AcadPulse Student Ranking Analyser", "version": "2.0"})

