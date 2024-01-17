#include <chrono>
#include "timer.hpp"


void Timer::start() {
	start_time = std::chrono::system_clock::now();
	running = true;
}

void Timer::stop() {
	end_time = std::chrono::system_clock::now();
	running = false;
}

long long Timer::elapsed() {
	std::chrono::time_point<std::chrono::system_clock> timepoint;

	if (running)
		timepoint = std::chrono::system_clock::now();
	else
		timepoint = end_time;

	return std::chrono::duration_cast<std::chrono::milliseconds>(timepoint - start_time).count();
}
