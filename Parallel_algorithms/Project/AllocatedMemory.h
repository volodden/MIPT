#ifndef ALLOCATED_MEMORY_H_INCLUDED
#define ALLOCATED_MEMORY_H_INCLUDED

class AllocatedMemory
{
public:
	AllocatedMemory(size_t newSize);

	~AllocatedMemory();

	size_t degreeOfSize;
	void* memory;

private:

	size_t powerOfTwo(size_t size);

};

#endif // ALLOCATED_MEMORY_H_INCLUDED
