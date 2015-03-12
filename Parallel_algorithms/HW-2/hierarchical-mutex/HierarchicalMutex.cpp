#include <iostream>

#include "HierarchicalMutex.h"

HierarchicalMutex::HierarchicalMutex(int newLevel) : level(newLevel)
{
}

HierarchicalMutex::~HierarchicalMutex()
{
}

bool HierarchicalMutex::lock(unsigned int& currentLevel)
{
	if (currentLevel <= level)
	{
		mtx.lock();
		oldLevel = currentLevel;
		currentLevel = level;
		std::cout << "lock with level [" << level << "]\n";
		return true;
	}
	return false;
}

bool HierarchicalMutex::unlock(unsigned int& currentLevel)
{
	if (currentLevel == level)
	{
		currentLevel = oldLevel;
		mtx.unlock();
		return true;
	}
	return false;
}