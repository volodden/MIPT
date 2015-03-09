#ifndef RETURNED_VALUE_H_INCLUDED
#define RETURNED_VALUE_H_INCLUDED

template<class T>
class ReturnedValue
{
public:

	ReturnedValue()
	{
		isValue = false;
	}

	~ReturnedValue()
	{
	}

	T get()
	{
		if (!isValue)
		{
			// value = ...
			isValue = true;
		}
		return value;
	}

private:

	// std::future
	bool isValue;
	T value;

};

#endif // RETURNED_VALUE_H_INCLUDED