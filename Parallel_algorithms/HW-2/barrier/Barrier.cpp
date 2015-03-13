#include "Barrier.h"

Barrier::Barrier()
{
	count = 1;
	current = 0;
	epoch = 0;
}

Barrier::Barrier(int newCount)
{
	count = newCount;
	current = 0;
	epoch = 0;
}

void Barrier::enter()
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