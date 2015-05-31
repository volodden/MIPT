#include <iostream>
#include <thread>
#include <vector>

#include "CyclicBarrier.h"

void simpleTest()
{
	int count = 10;

	CyclicBarrier barrier(count);
	std::vector<std::thread> threads;

	for (int i = 0; i < count; ++i)
	{
		threads.push_back(std::thread([&]
				{
				srand(time(NULL));
				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
				for (int i = 0; i < 7; ++i)
				{
					barrier.enter();
				}
			}));
	}

	for (int i = 0; i < count; ++i)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
		}
	}
}

void stressTest()
{
	int count = 10;

	CyclicBarrier barrier(count);
	std::vector<std::thread> threads;

	for (int i = 0; i < count; ++i)
	{
		threads.push_back(std::thread([&]
			{
				srand(time(NULL));
				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
				for (int i = 0; i < 1000000; ++i)
				{
					//std::cout << "enter: " << std::this_thread::get_id() << '\n';
					barrier.enter();
					//]std::cout << "exit: " << std::this_thread::get_id() << '\n';
				}
			}));
	}

	for (int i = 0; i < count; ++i)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
		}
	}
}

void rotateTest()
{
	const std::size_t LENGTH = 10;
	const std::size_t NUM_ITERS = 100003;

	std::vector<int> data;
	for (size_t i = 0; i < LENGTH; ++i)
	{
		data.push_back(i);
	}

	CyclicBarrier barrier(data.size());

	std::vector<std::thread> threads;
	for (size_t i = 0; i < data.size(); ++i) {
		threads.emplace_back([i, &data, &barrier, &NUM_ITERS]()
			{
				for (size_t k = 0; k < NUM_ITERS; ++k)
				{
					int next = data[(i + 1) % data.size()];
					barrier.enter();
					data[i] = next;
					barrier.enter();
				}
			});
	}

	for (auto& t : threads) {
		t.join();
	}

	for (size_t i = 0; i < data.size(); ++i) {
		std::cout << i << ": " << data[i] << std::endl;
	}
}

int main()
{
	rotateTest();
	return 0;
}