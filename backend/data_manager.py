import json
import os
import csv
import io
import shutil

BASE_DATA_FILE = os.path.join(os.path.dirname(__file__), "..", "data", "students.json")

# Serverless environment handling (e.g. Vercel read-only filesystem)
if os.environ.get("VERCEL") or os.environ.get("AWS_LAMBDA_FUNCTION_NAME"):
    DATA_FILE = "/tmp/students.json"
    if not os.path.exists(DATA_FILE) and os.path.exists(BASE_DATA_FILE):
        try:
            shutil.copyfile(BASE_DATA_FILE, DATA_FILE)
        except Exception:
            DATA_FILE = BASE_DATA_FILE
else:
    DATA_FILE = BASE_DATA_FILE

class DataManager:
    @staticmethod
    def _load():
        target = DATA_FILE if os.path.exists(DATA_FILE) else BASE_DATA_FILE
        if not os.path.exists(target):
            try:
                from sample_data import init_sample_data
            except ImportError:
                from backend.sample_data import init_sample_data
            init_sample_data(DATA_FILE)
            target = DATA_FILE
        with open(target, "r", encoding="utf-8") as f:
            return json.load(f)

    @staticmethod
    def _save(data):
        try:
            with open(DATA_FILE, "w", encoding="utf-8") as f:
                json.dump(data, f, indent=2)
        except Exception as e:
            print(f"[DataManager save warning]: {e}")

    @classmethod
    def get_all(cls):
        return cls._load()

    @classmethod
    def get_by_prn(cls, prn):
        students = cls._load()
        for s in students:
            if s.get("prn") == prn:
                return s
        return None

    @classmethod
    def add(cls, student_dict):
        students = cls._load()
        # check duplicate PRN
        if any(s.get("prn") == student_dict.get("prn") for s in students):
            return False, "Student with this PRN already exists"
        
        # default marks structure if missing
        if "marks" not in student_dict:
            student_dict["marks"] = {
                "DS": {"mse": 0, "ese": 0, "lab": 0, "proj": 0},
                "COA": {"mse": 0, "ese": 0, "lab": 0, "proj": 0},
                "DM": {"mse": 0, "ese": 0, "lab": 0, "proj": 0}
            }
        students.append(student_dict)
        cls._save(students)
        return True, "Student added successfully"

    @classmethod
    def update(cls, prn, updated_fields):
        students = cls._load()
        found = False
        for s in students:
            if s.get("prn") == prn:
                for k, v in updated_fields.items():
                    if k == "marks" and isinstance(v, dict):
                        for sub, m in v.items():
                            if sub not in s["marks"]:
                                s["marks"][sub] = {}
                            s["marks"][sub].update(m)
                    else:
                        s[k] = v
                found = True
                break
        if found:
            cls._save(students)
            return True, "Student record updated"
        return False, "Student not found"

    @classmethod
    def delete(cls, prn):
        students = cls._load()
        new_list = [s for s in students if s.get("prn") != prn]
        if len(new_list) < len(students):
            cls._save(new_list)
            return True, "Student deleted"
        return False, "Student not found"

    @classmethod
    def export_csv(cls):
        students = cls._load()
        output = io.StringIO()
        writer = csv.writer(output)
        writer.writerow(["PRN", "RollNo", "Name", "Division", "Batch", "Attendance", "DS_MSE", "DS_ESE", "DS_LAB", "DS_PROJ"])
        for s in students:
            ds = s.get("marks", {}).get("DS", {})
            writer.writerow([
                s.get("prn", ""),
                s.get("roll_no", ""),
                s.get("name", ""),
                s.get("division", ""),
                s.get("batch", ""),
                s.get("attendance", 0),
                ds.get("mse", 0),
                ds.get("ese", 0),
                ds.get("lab", 0),
                ds.get("proj", 0)
            ])
        return output.getvalue()

