#include <thread>
#include <vector>
#include <iostream>

#include "HierarchicalMutex.h"

#define thread_local __declspec(thread)

thread_local unsigned int levelOfThread = 0;

int main()
{
	HierarchicalMutex a(1);
	HierarchicalMutex b(3);
	HierarchicalMutex c(2);

	a.lock(levelOfThread);
	b.lock(levelOfThread);
	c.lock(levelOfThread);
	c.unlock(levelOfThread);
	b.unlock(levelOfThread);
	a.unlock(levelOfThread);

	return 0;
}