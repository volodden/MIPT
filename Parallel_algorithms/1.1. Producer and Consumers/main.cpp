#include <iostream>
#include <thread>
#include <random>
#include <vector>

#include "ParallelQueue.hpp"
#include "ThreadGuard.h"


#include <windows.h>

const int numberOfConsumers = 8;
const int numberOfTasks = 10;
const int rangeOfNumbers = 100;
std::mutex mutexForCout;

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
		std::lock_guard<std::mutex> lockForCout(mutexForCout);
		std::cout << std::this_thread::get_id() << ": " << value << " is " << (checkIsPrime(value) ? "" : "not ") << "prime number.\n";
	}
}

int main()
{
	ParallelQueue<int> tasks;
	std::vector<std::thread> consumers;
	std::vector<ThreadGuard> consumersUnderGuards;
	
	std::thread a(producer, std::ref(tasks));
	ThreadGuard threadGuard(a);

	for (int i = 0; i < numberOfConsumers; ++i)
	{
		consumers.emplace_back(consumer, std::ref(tasks));
	}
	for (int i = 0; i < numberOfConsumers; ++i)
	{
		consumersUnderGuards.emplace_back(consumers[i]);
	}

	int q;
	std::cin >> q;
	return 0;
}