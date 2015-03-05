#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread& currentThread) : insideThread(currentThread) //std::move(currentThread))
{
}

ThreadGuard::~ThreadGuard()
{
	if (insideThread.joinable())
	{
		insideThread.join();
	}
}

