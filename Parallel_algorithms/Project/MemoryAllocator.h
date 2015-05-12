#ifndef MEMORY_ALLOCATOR_H_INCLUDED
#define MEMORY_ALLOCATOR_H_INCLUDED

#include <list>
#include <mutex>

#include "AllocatedMemory.h"
#include "MemAlloc.h"

#define elementOfSubList std::pair<std::pair<std::mutex, bool>, AllocatedMemory>
#define subList std::pair<std::mutex, std::list<elementOfSubList>>

class MemoryAllocator
{

public:

	MemoryAllocator();

	~MemoryAllocator();

	MemAlloc createMemAlloc();

	AllocatedMemory* allocateMemory(size_t sizeOfNeededMemory);
	void retrieveMemory(AllocatedMemory* returnedMemory);
	
	std::list<subList> listOfPointers;

private:

	int degreeOfTwo(size_t size);
	std::mutex globalMutex;

};

#endif // MEMORY_ALLOCATOR_H_INCLUDED
