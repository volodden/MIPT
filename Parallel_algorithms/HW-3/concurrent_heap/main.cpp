#include <vector>
#include <thread>

#include <iostream>

#include "CuncurrentHeap.hpp"

int main()
{
	int count = 31;
	
	CuncurrentHeap<int> CH(32);

	std::vector<std::thread> threads;
	for (int i = 0; i < count; ++i)
	{
		threads.emplace_back([&]()
			{
				CH.insert(count - i);
				std::cout << i << "\n";
			});
	}

	for (int i = 0; i < count; ++i)
	{
		threads[i].join();
	}

	int i;
	std::cin >> i;
	return 0;
}