main:
	g++ simulation.cpp Source.cpp Detector.cpp -Wall -o simulation.exe -std=gnu++17

clean:
	rm simulation.exe