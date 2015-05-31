#include "CyclicBarrier.h"

CyclicBarrier::CyclicBarrier(size_t newThreadCount) : threadCount(newThreadCount), currentNumberOfThreads(0), epoch(0)
{
}

void CyclicBarrier::setCountOfThreads(size_t newThreadCount)
{
	threadCount = newThreadCount;
}

void CyclicBarrier::enter()
{
	std::unique_lock<std::mutex> lock(mtx);
	++currentNumberOfThreads;
	if (currentNumberOfThreads != threadCount)
	{
		int oldEpoch = epoch;
		while (oldEpoch == epoch)
		{
			ring.wait(lock);
		}
	}
	else
	{
		currentNumberOfThreads = 0;
		++epoch;
		ring.notify_all();
	}
}
