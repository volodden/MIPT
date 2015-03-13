#include "CyclicBarrier.h"

CyclicBarrier::CyclicBarrier()
{
	count = 1;
	current = 0;
	epoch = 0;
}

CyclicBarrier::CyclicBarrier(int newCount)
{
	count = newCount;
	current = 0;
	epoch = 0;
}

void CyclicBarrier::enter()
{
	std::unique_lock<std::mutex> lock(mtx);
	++current;
	if (current != count)
	{
		int newEpoch = epoch;
		while (newEpoch == epoch)
		{
			ring.wait(lock);
		}
	}
	else
	{
		current -= count;
		++epoch;
		ring.notify_all();
	}
}