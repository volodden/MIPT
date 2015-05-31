#ifndef SHELL_FOR_ATOMIC_H_INCLUDED
#define SHELL_FOR_ATOMIC_H_INCLUDED

#include <atomic>

template <class T>
class ShellForAtomic
{

public:

	ShellForAtomic() : atomicElement()
	{
	}

	ShellForAtomic(const std::atomic<T>& newAtomicElement) : atomicElement(newAtomicElement.load())
	{
	}

	ShellForAtomic(const ShellForAtomic<T>& otherAtomicElement) : atomicElement(otherAtomicElement.atomicElement.load())
	{
	}

	ShellForAtomic<T>& operator= (const ShellForAtomic<T>& otherAtomicElement)
	{
		atomicElement.store(otherAtomicElement.atomicElement.load());
	}

	T load()
	{
		return atomicElement.load();
	}

	void store(T x)
	{
		atomicElement.store(x);
	}

	std::atomic<T> atomicElement;
};

#endif //SHELL_FOR_ATOMIC_H_INCLUDED