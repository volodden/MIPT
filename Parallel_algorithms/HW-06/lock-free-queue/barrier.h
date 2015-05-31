#pragma once

#include <atomic>

class barrier {
public:
	barrier(const size_t num_threads)
		: num_threads_(num_threads)
		, entered_count_(0)
	{}

	void enter() {
		++entered_count_;
		while (entered_count_ != num_threads_) {
			std::this_thread::yield();
		}
	}

private:
	size_t num_threads_;
	std::atomic_size_t entered_count_;
};