#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread currentThread) : insideThread(std::move(currentThread))
{
}

ThreadGuard::ThreadGuard(ThreadGuard&& otherThread) : insideThread(std::move(otherThread.insideThread))
{
}

ThreadGuard::~ThreadGuard()
{
	if (insideThread.joinable())
	{
		insideThread.join();
	}
}

