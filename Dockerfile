# Multi-stage Dockerfile for AcadPulse - Student Ranking & Performance Analyser
# Optimized for Google Cloud Run (GCP) and Local Container Execution

FROM python:3.11-slim

# Install g++ and build essentials for C++ DSA Engine compilation
RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy dependency definition and install
COPY backend/requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Copy entire repository
COPY . .

# Compile C++ DSA Core Engine inside the container
RUN g++ -std=c++17 -O2 -I engine/include engine/src/engine_api.cpp -o engine/engine_api && \
    cp engine/engine_api engine/engine_api.exe && \
    chmod +x engine/engine_api engine/engine_api.exe

# GCP Cloud Run injects PORT environment variable (default 8080)
ENV PORT=8080
ENV PYTHONUNBUFFERED=1

EXPOSE 8080

WORKDIR /app/backend

# Run using production WSGI server Gunicorn
CMD exec gunicorn --bind 0.0.0.0:$PORT --workers 2 --threads 4 --timeout 0 app:app

