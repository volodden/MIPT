#ifndef RETURNED_VALUE_H_INCLUDED
#define RETURNED_VALUE_H_INCLUDED

#include <future>

template<class T>
class ReturnedValue
{
public:

	ReturnedValue(std::future<T> otherFut) : fut(otherFut), isValue(false)
	{
	}

	~ReturnedValue()
	{
	}

	T get()
	{
		if (!isValue)
		{
			try
			{
				value = fut.get();
				isValue = true;
			}
			catch (std::exception& e)
			{
				std::cout << "exception: " << e.what() << '\n';
			}
		}
		return value;
	}

private:

	std::future fut;
	bool isValue;
	T value;

};

#endif // RETURNED_VALUE_H_INCLUDED