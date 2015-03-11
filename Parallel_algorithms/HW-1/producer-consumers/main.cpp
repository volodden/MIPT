#include <iostream>
#include <thread>
#include <random>
#include <vector>

#include "ParallelQueue.hpp"
#include "ThreadGuard.h"

const int numberOfConsumers = 20;
const int numberOfTasks = 50;
const int rangeOfNumbers = 100;

bool checkIsPrime(int value)
{
	if (value == 1)
	{
		return false;
	}
	for (int i = 2; i < value / 2 + 1; ++i)
	{
		if (value % i == 0)
		{
			return false;
		}
	}
	return true;
}

void producer(ParallelQueue<int>& tasks)
{
	std::random_device randomDeviceUnit;
	std::mt19937 generator(randomDeviceUnit());
	std::uniform_int_distribution<int> distribution(1, rangeOfNumbers);
	for (int i = 0; i < numberOfTasks; ++i)
	{
		int new_number = distribution(generator);
		tasks.push(new_number);
	}
	tasks.push(tasks.getPoisonPill());
}

void consumer(ParallelQueue<int>& tasks)
{
	int value;
	while (tasks.pop(value))
	{
		std::cout << std::this_thread::get_id() << ": " << value << " is " << (checkIsPrime(value) ? "" : "not ") << "prime number.\n";
	}
}

int main()
{
	ParallelQueue<int> tasks;
	std::vector<ThreadGuard> consumersUnderGuards;
	
	ThreadGuard threadGuard(std::thread(producer, std::ref(tasks)));
	for (int i = 0; i < numberOfConsumers; ++i)
	{
		consumersUnderGuards.emplace_back(std::thread(consumer, std::ref(tasks)));
	}
	
	return 0;
}