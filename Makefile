CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -I engine/include

.PHONY: all test run clean help

all: test build-engine

build-engine:
	$(CXX) $(CXXFLAGS) engine/src/engine_api.cpp -o engine/engine_api.exe
	$(CXX) $(CXXFLAGS) engine/src/engine_main.cpp -o engine/acadpulse_engine.exe

test:
	$(CXX) $(CXXFLAGS) engine/tests/test_all_dsa.cpp -o engine/tests/test_all_dsa.exe
	./engine/tests/test_all_dsa.exe

run: build-engine
	cd backend && python app.py

clean:
	rm -f engine/*.exe engine/tests/*.exe

