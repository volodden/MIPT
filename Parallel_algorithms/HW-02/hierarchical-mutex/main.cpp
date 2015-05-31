#include <thread>
#include <vector>

#include "HierarchicalMutex.h"

#define thread_local __declspec(thread)

thread_local unsigned int levelOfThread = 0;

int main()
{
	HierarchicalMutex a(1);
	HierarchicalMutex b(3);
	HierarchicalMutex c(2);

	a.lockWithOutEmergencyShutdown(levelOfThread);
	b.lockWithOutEmergencyShutdown(levelOfThread);
	c.lockWithOutEmergencyShutdown(levelOfThread);
	c.unlockWithOutEmergencyShutdown(levelOfThread);
	b.unlockWithOutEmergencyShutdown(levelOfThread);
	a.unlockWithOutEmergencyShutdown(levelOfThread);

	return 0;
}