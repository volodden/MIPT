#include <iostream>
#include <thread>
#include <vector>

#include "Barrier.h"

int main()
{
	int count = 10;

	Barrier barrier(count);
	std::vector<std::thread> threads;

	for (int i = 0; i < count; ++i)
	{
		threads.push_back(std::thread([&]{
			srand(time(NULL));
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
			//for (int i = 0; i < 100000; ++i)
			{
				std::cout << "enter: " << std::this_thread::get_id() << '\n';
				barrier.enter();
				std::cout << "exit: " << std::this_thread::get_id() << '\n';
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

	std::cin >> count;
	return 0;
}