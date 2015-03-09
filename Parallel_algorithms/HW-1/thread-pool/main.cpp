#include <iostream>

#include <functional>
#include "ReturnedValue.hpp"
#include "ThreadPool.hpp"

#include <future>

int printNumber(int i = 23)
{
	std::cout << i << '\n';
	return i;
}

int main()
{ 
	ThreadPool<int> tp;
	
	// store a free function
	std::function<int(int)> f_free = printNumber;
	//ReturnedValue<int> a = tp.submit(f_free);
	std::future<int> a = tp.submit(f_free);

	// store a lambda
	std::function<int()> f_labmda = []() { printNumber(42); };
	//ReturnedValue<int> b = tp.submit(f_labmda);
	std::future<int> b = tp.submit(f_labmda);

	// store the result of a call to std::bind
	std::function<int()> f_bind = std::bind(printNumber, 31337);
	//ReturnedValue<int> c = tp.submit(f_bind);
	std::future<int> c = tp.submit(f_bind);

	std::cout << "a = " << a.get() << "\nb = " << b.get() << "\nc = " << c.get() << '\n';
	
	return 0;
}