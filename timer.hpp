#include <chrono>


class Timer {
private:

	std::chrono::time_point<std::chrono::system_clock> start_time;
	std::chrono::time_point<std::chrono::system_clock> end_time;
	bool running = false;

public:

	void start();

	void stop();

	long long elapsed();

};