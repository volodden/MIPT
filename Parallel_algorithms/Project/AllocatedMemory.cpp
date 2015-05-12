#include "AllocatedMemory.h"

#include <cstdlib>

AllocatedMemory::AllocatedMemory(size_t newSize)
{
	degreeOfSize = newSize;
	memory = malloc(powerOfTwo(newSize));
}


AllocatedMemory::~AllocatedMemory()
{
	free(memory);
}

size_t AllocatedMemory::powerOfTwo(size_t size)
{
	unsigned int power = 1;
	for (size_t i = 1; i <= size; ++i)
	{
		power <<= 1;
	}
	return power;
}
