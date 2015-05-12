#include "MemAlloc.h"

MemAlloc::MemAlloc(MemoryAllocator* allocator)
{
	memoryAllocator = allocator;
}

MemAlloc::~MemAlloc()
{
	for (auto currentListInListOfFreeMemory = listOfFreeMemory.begin(); currentListInListOfFreeMemory != listOfFreeMemory.end(); ++currentListInListOfFreeMemory)
	{
		for (auto currentElementOfMemory = currentListInListOfFreeMemory->begin(); currentElementOfMemory != currentListInListOfFreeMemory->end(); ++currentElementOfMemory)
		{
			memoryAllocator->retrieveMemory(*currentElementOfMemory);
		}
	}
	for (auto currentListInListOfUsingMemory = listOfUsingMemory.begin(); currentListInListOfUsingMemory != listOfUsingMemory.end(); ++currentListInListOfUsingMemory)
	{
		for (auto currentElementOfMemory = currentListInListOfUsingMemory->begin(); currentElementOfMemory != currentListInListOfUsingMemory->end(); ++currentElementOfMemory)
		{
			memoryAllocator->retrieveMemory(*currentElementOfMemory);
		}
	}
}

void* MemAlloc::newMemory(size_t size)
{
	int degree = toDegreeOfTwo(size);

	int power = powerOfTwo(degree);
	while (listOfFreeMemory.size() < degree + 1)
	{
		listOfFreeMemory.push_back(subListForMemAlloc());
		listOfUsingMemory.push_back(subListForMemAlloc());
	}

	auto currentListInListOfFreeMemory = listOfFreeMemory.begin();
	auto currentListInListOfUsingMemory = listOfUsingMemory.begin();

	for (int i = 0; i <= degree; ++i)
	{
		++currentListInListOfFreeMemory;
		++currentListInListOfUsingMemory;
	}

	if (currentListInListOfFreeMemory->empty())
	{
		currentListInListOfUsingMemory->push_back(memoryAllocator->allocateMemory(degree));
	}
	else
	{
		currentListInListOfUsingMemory->push_back(currentListInListOfFreeMemory->back());
		currentListInListOfFreeMemory->pop_back();
	}
	return &(currentListInListOfUsingMemory->back()->memory);
}

void MemAlloc::deleteMemory(void* memory)
{
	memory = (void*) memory;
	int degree = 0;
	for (auto currentListInListOfUsingMemory = listOfUsingMemory.begin(); currentListInListOfUsingMemory != listOfUsingMemory.end(); ++currentListInListOfUsingMemory)
	{
		for (auto currentElementOfMemory = currentListInListOfUsingMemory->begin(); currentListInListOfUsingMemory != listOfUsingMemory.end(); ++currentListInListOfUsingMemory)
		{
			if (&((*currentElementOfMemory)->memory) == memory)
			{
				auto currentListInListOfFreeMemory = listOfFreeMemory.begin();
				for (int i = 0; i <= degree; ++i)
				{
					++currentListInListOfFreeMemory;
				}
				if (currentListInListOfFreeMemory->size() >= currentListInListOfUsingMemory->size())
				{
					memoryAllocator->retrieveMemory(*currentElementOfMemory);
				}
				else
				{
					currentListInListOfFreeMemory->push_back(*currentElementOfMemory);
					currentListInListOfUsingMemory->erase(currentElementOfMemory);
				}
				return;
			}
		}
		++degree;
	}
	// throw Exception
}

int MemAlloc::toDegreeOfTwo(size_t size)
{
	if (size == 1)
	{
		return 0;
	}
	int degree = 1;
	bool isPowerOfTwo = true;
	while (size != 1)
	{
		if ((isPowerOfTwo) && (size != 1) && (size % 2 == 1))
		{
			++degree;
			isPowerOfTwo = false;
		}
		++degree;
		size >>= 1;
	}
	return degree;
}

int MemAlloc::powerOfTwo(int degree)
{
	int power = 1;
	for (int i = 1; i <= degree; ++i)
	{
		power <<= 1;
	}
	return power;
}
