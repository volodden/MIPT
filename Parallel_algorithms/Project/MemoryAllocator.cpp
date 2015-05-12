#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator()
{
	/*
	for (int degree = 0; degree <= 10; ++degree)
	{
		listOfPointers.push_back(subList());
		for (int j = 1; j <= 4; ++j)
		{
			listOfPointers.back().second.push_back(std::make_pair(std::make_pair(std::mutex(), true), AllocatedMemory(degree)));
		}
	}
	*/
}

MemoryAllocator::~MemoryAllocator()
{
}

MemAlloc MemoryAllocator::createMemAlloc()
{
	return MemAlloc(this);
}

AllocatedMemory* MemoryAllocator::allocateMemory(size_t sizeOfNeededMemory)
{
	if (sizeOfNeededMemory < 1)
	{
		//throw Exception
	}

	int degree = degreeOfTwo(sizeOfNeededMemory);

	int sizeOfList = listOfPointers.size();
	if (degree > sizeOfList)
	{
		globalMutex.lock();
		while (degree > sizeOfList)
		{
			listOfPointers.push_back(subList());
		}
		listOfPointers.back().first.lock();
		globalMutex.unlock();
		listOfPointers.back().second.push_back(std::make_pair(std::make_pair(std::mutex(), false), AllocatedMemory(degree)));
		auto newElement = listOfPointers.back().second.back();
		listOfPointers.back().first.unlock();
		return &(newElement.second);
	}

	auto currentList = listOfPointers.begin();
	for (int i = 2; i < degree; ++i)
	{
		++currentList;
	}
	for (auto currentElement = currentList->second.begin(); currentElement != currentList->second.end(); ++currentElement)
	{
		currentElement->first.first.lock();
		if (currentElement->first.second)
		{
			currentElement->first.second = false;
			currentElement->first.first.unlock();
			return &(currentElement->second);
		}
	}
	currentList->first.lock();
	currentList->second.push_back(std::make_pair(std::make_pair(std::mutex(), false), AllocatedMemory(degree)));
	AllocatedMemory memory = currentList->second.back().second;
	currentList->first.unlock();
	return &memory;
}

void MemoryAllocator::retrieveMemory(AllocatedMemory* returnedMemory)
{
	int degree = returnedMemory->degreeOfSize;
	auto currentList = listOfPointers.begin();
	for (int i = 1; i < degree; ++i)
	{
		++currentList;
	}
	auto currentElement = currentList->second.begin();
	while ((currentElement != currentList->second.end()) && (&(currentElement->second) != returnedMemory))
	{
		++currentElement;
	}
	if (currentElement != currentList->second.end())
	{
		//throw Exception
		return;
	}
	currentElement->first.first.lock();
	currentElement->first.second = true;
	currentElement->first.first.unlock();
	return;
}


int MemoryAllocator::degreeOfTwo(size_t size)
{
	int degree = 0;
	while (size > 0)
	{
		size >>= 1;
		++degree;
	}
	return degree;
}
