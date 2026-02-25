main:
	g++ simulation.cpp source.cpp -Wall -Wextra -Wpedantic -o simulation.exe -std=gnu++17

clean:
	rm simulation.exe