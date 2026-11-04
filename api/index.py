import sys
import os
from urllib.parse import parse_qs, urlencode, unquote

ROOT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BACKEND_DIR = os.path.join(ROOT_DIR, "backend")

if ROOT_DIR not in sys.path:
    sys.path.insert(0, ROOT_DIR)
if BACKEND_DIR not in sys.path:
    sys.path.insert(0, BACKEND_DIR)

from backend.app import app

class VercelPathMiddleware:
    """
    WSGI Middleware for Vercel Serverless Functions.
    Restores the true client request path and query string.
    """
    def __init__(self, wsgi_app):
        self.wsgi_app = wsgi_app

    def __call__(self, environ, start_response):
        target_path = None
        
        # 1. Check if rewrite forwarded __path__ via query string
        qs_raw = environ.get('QUERY_STRING', '')
        qs = parse_qs(qs_raw, keep_blank_values=True)
        if '__path__' in qs:
            target_path = qs['__path__'][0]
            del qs['__path__']
            if '?' in target_path:
                target_path, extra_qs = target_path.split('?', 1)
                for k, v in parse_qs(extra_qs, keep_blank_values=True).items():
                    qs[k] = v
            environ['QUERY_STRING'] = urlencode(qs, doseq=True)
        
        # 2. Check Vercel headers if __path__ was not found or is default function entry
        if not target_path or target_path in ('/api/index.py', '/api/index'):
            for header_key in [
                'HTTP_X_MATCHED_PATH',
                'HTTP_X_FORWARDED_URI',
                'HTTP_X_ORIGINAL_URL',
                'RAW_URI',
                'REQUEST_URI'
            ]:
                val = environ.get(header_key)
                if val and not val.startswith('/api/index'):
                    target_path = val.split('?')[0]
                    break

        # 3. Check route matches header: HTTP_X_NOW_ROUTE_MATCHES
        if not target_path or target_path in ('/api/index.py', '/api/index'):
            route_matches = environ.get('HTTP_X_NOW_ROUTE_MATCHES')
            if route_matches:
                try:
                    rm_qs = parse_qs(route_matches)
                    if '1' in rm_qs:
                        target_path = unquote(rm_qs['1'][0])
                except Exception:
                    pass

        # 4. Fallback based on PATH_INFO
        if not target_path or target_path in ('/api/index.py', '/api/index'):
            path_info = environ.get('PATH_INFO', '')
            if path_info.startswith('/api/index.py'):
                target_path = path_info[len('/api/index.py'):] or '/'
            elif path_info.startswith('/api/index'):
                target_path = path_info[len('/api/index'):] or '/'
            else:
                target_path = path_info or '/'

        if not target_path.startswith('/'):
            target_path = '/' + target_path

        # Clean duplicate slashes if any (e.g. //students -> /students)
        while target_path.startswith('//'):
            target_path = target_path[1:]

        environ['PATH_INFO'] = target_path
        return self.wsgi_app(environ, start_response)

app.wsgi_app = VercelPathMiddleware(app.wsgi_app)

if __name__ == "__main__":
    app.run(port=5000)
