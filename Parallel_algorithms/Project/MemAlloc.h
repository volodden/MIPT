#ifndef MEMORY_ALLOC_H_INCLUDED
#define MEMORY_ALLOC_H_INCLUDED

#include <list>

#include "AllocatedMemory.h"
#include "MemoryAllocator.h"

#define subListForMemAlloc std::list<AllocatedMemory*>

class MemAlloc
{

public:
	
	MemAlloc(MemoryAllocator* allocator);

	~MemAlloc();

	void* newMemory(size_t size);
	void deleteMemory(void* memory);

private:

	int toDegreeOfTwo(size_t size);
	int powerOfTwo(int degree);

	MemoryAllocator* memoryAllocator;
	std::list<subListForMemAlloc> listOfUsingMemory;
	std::list<subListForMemAlloc> listOfFreeMemory;

};

#endif // MEMORY_ALLOC_H_INCLUDED
