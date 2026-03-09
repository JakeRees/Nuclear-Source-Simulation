main:
	g++ simulation.cpp Source.cpp Detector.cpp -Wall -Wextra -Wpedantic -o simulation.exe -std=gnu++17

clean:
	rm simulation.exe