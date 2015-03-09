#include "Barrier.h"

Barrier::Barrier()
{
	count = 1;
	current = 0;
	left = 0;
}

Barrier::Barrier(int newCount)
{
	count = newCount;
	current = 0;
	left = 0;
}

void Barrier::enter()
{
	std::unique_lock<std::mutex> lock(mtx);
	++current;
	if (current != count)
	{
		while (left == 0)
		{
			ring.wait(lock);
		}
		--left;
		if (left != 0)
		{
			ring.notify_one();
		}
	}
	else
	{
		current -= count;
		left = count - 1;
		ring.notify_one();
	}
}