#include <iostream>

#include <functional>
#include "ThreadPool.hpp"

#include <future>

int printNumber(int i)
{
	std::cout << i << '\n';
	return i;
}

int printNumber2()
{
	std::cout << 23 << '\n';
	return 23;
}

int main()
{ 
	ThreadPool<int> tp;

	// store a lambda
	std::function<int()> f_labmda = []() { return printNumber(42); };
	std::future<int> a = tp.submit(f_labmda);

	// store the result of a call to std::bind
	std::function<int()> f_bind = std::bind(printNumber, 31337);
	std::future<int> b = tp.submit(f_bind);

	// store a free function
	std::function<int()> f_free = printNumber2;
	std::future<int> c = tp.submit(f_free);

	std::cout << "a = " << a.get() << "\nb = " << b.get() << "\nc = " << c.get() << '\n';
	
	return 0;
}