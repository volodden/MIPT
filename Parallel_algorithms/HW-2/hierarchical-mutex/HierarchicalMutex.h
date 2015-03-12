#ifndef HIERARCHIAL_MUTEX_H_INCLUDED
#define HIERARCHIAL_MUTEX_H_INCLUDED

#include <mutex>

class HierarchicalMutex
{
public:

	HierarchicalMutex(int newLevel);
	~HierarchicalMutex();

	bool lock(unsigned int& value);

	bool unlock(unsigned int& value);

private:

	unsigned int level;
	unsigned int oldLevel;
	std::mutex mtx;
};

#endif // HIERARCHIAL_MUTEX_H_INCLUDED