#ifndef THREAD_GUARD_H_INCLUDED
#define THREAD_GUARD_H_INCLUDED

#include <thread>

class ThreadGuard
{
public:

	ThreadGuard(std::thread currentThread);
	ThreadGuard(ThreadGuard&& otherThread);
	~ThreadGuard();

private:

	ThreadGuard& operator =(const ThreadGuard& other) = delete;
	ThreadGuard(const ThreadGuard& otherThread) = delete;
	std::thread insideThread;
};

#endif //THREAD_GUARD_H_INCLUDED
