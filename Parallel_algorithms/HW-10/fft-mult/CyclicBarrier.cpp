#include "CyclicBarrier.h"

CyclicBarrier::CyclicBarrier(int newCount) : count(newCount), currentNumberOfThreads(0), epoch(0)
{
}

void CyclicBarrier::setCountOfThreads(int newCount)
{
	count = newCount;
}

void CyclicBarrier::enter()
{
	std::unique_lock<std::mutex> lock(mtx);
	++currentNumberOfThreads;
	if (currentNumberOfThreads != count)
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
