#ifndef THREAD_GUARD_H_INCLUDED
#define THREAD_GUARD_H_INCLUDED

#include <thread>

class ThreadGuard
{
public:

	ThreadGuard(std::thread& currentThread);

	~ThreadGuard();

private:
	
	void operator =(const ThreadGuard otherLockGuard) = delete;

	std::thread& insideThread;
};

#endif //THREAD_GUARD_H_INCLUDED