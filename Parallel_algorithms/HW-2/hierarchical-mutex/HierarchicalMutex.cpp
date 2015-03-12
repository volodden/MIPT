#include <iostream>

#include "HierarchicalMutex.h"

HierarchicalMutex::HierarchicalMutex(int newLevel) : level(newLevel)
{
}

HierarchicalMutex::~HierarchicalMutex()
{
}

void HierarchicalMutex::lock(unsigned int& currentLevel)
{
	if (currentLevel <= level)
	{
		mtx.lock();
		oldLevel = currentLevel;
		currentLevel = level;
		std::cout << "lock with level [" << level << "]\n";
		return;
	}
	throw std::exception();
}

bool HierarchicalMutex::lockWithOutEmergencyShutdown(unsigned int& currentLevel)
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

void HierarchicalMutex::unlock(unsigned int& currentLevel)
{
	if (currentLevel == level)
	{
		currentLevel = oldLevel;
		mtx.unlock();
		return;
	}
	throw std::exception();
}

bool HierarchicalMutex::unlockWithOutEmergencyShutdown(unsigned int& currentLevel)
{
	if (currentLevel == level)
	{
		currentLevel = oldLevel;
		mtx.unlock();
		return true;
	}
	return false;
}