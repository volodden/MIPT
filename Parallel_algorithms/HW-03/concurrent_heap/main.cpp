#include <vector>
#include <thread>

#include <iostream>

#include "CuncurrentHeap.hpp"

int main()
{
	int count = 31;
	
	CuncurrentHeap<int> CH(count);

	std::vector<std::thread> threads;
	for (int i = 0; i < count + 2; ++i)
	{
		threads.emplace_back([&]()
			{
				std::cout << i << ": " << (CH.insert(count - i) ? "yes\n" : "no\n");
			});
	}

	for (int i = 0; i < count + 2; ++i)
	{
		threads[i].join();
	}

	int x;
	CH.extractMin(x);
	std::cout << "EXTRACT " << x << "\n";
	CH.extractMin(x);
	std::cout << "EXTRACT " << x << "\n";
	CH.extractMin(x);
	std::cout << "EXTRACT " << x << "\n";
	CH.extractMin(x);
	std::cout << "EXTRACT " << x << "\n";
	CH.insert(2);
	CH.extractMin(x);
	std::cout << "EXTRACT " << x << "\n";

	int i;
	std::cin >> i;
	return 0;
}