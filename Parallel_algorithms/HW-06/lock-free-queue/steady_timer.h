#pragma once

#include <chrono>

class steady_timer {
public:
	steady_timer() {
		reset();
	}

	void reset() {
		start_ = std::chrono::steady_clock::now();
	}

	double seconds_elapsed() const {
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast< std::chrono::duration<double> >(now - start_);
		return elapsed.count();
	}

private:
	std::chrono::steady_clock::time_point start_;
};