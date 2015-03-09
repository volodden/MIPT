#include <iostream>

#include <functional>
#include "ReturnedValue.hpp"
#include "ThreadPool.hpp"

void printNumber(int i = 0)
{
	std::cout << i << '\n';
}

int main()
{ 
	ThreadPool<int> tp;
	
	/*
	// store a free function
	std::function<void(int)> f_free = printNumber;
	ReturnedValue<int> a = tp.submit(f_free);

	// store a lambda
	std::function<void()> f_labmda = []() { printNumber(42); };
	ReturnedValue<int> b = tp.submit(f_labmda);

	// store the result of a call to std::bind
	std::function<void()> f_bind = std::bind(printNumber, 31337);
	ReturnedValue<int> c = tp.submit(f_bind);

	std::cout << "a = " << a.get() << "\nb = " << b.get() << "\nc = " << c.get() << '\n';
	*/

	return 0;
}