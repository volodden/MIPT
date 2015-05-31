#ifndef CUNCURRENT_HEAP_H_INCLUDED
#define CUNCURRENT_HEAP_H_INCLUDED

#include <mutex>
#include <utility>
#include <vector>

template<class T>
class CuncurrentHeap
{
public:

	CuncurrentHeap(int count) : capacity(count + 1), size(0), heap(count + 1)
	{
		for (int i = 0; i < capacity; ++i)
		{
			heap[i].second.second = false;
		}
	}

	~CuncurrentHeap()
	{
	}

	bool insert(T key)
	{
		mutexForSize.lock();
		if (size + 1 == capacity)
		{
			mutexForSize.unlock();
			return false;
		}

		int index = ++size;
		lockElement(index);
		setValue(index, key);
		mutexForSize.unlock();

		while (true)
		{
			lockElement(parent(index));
			if (getValue(index) < getValue(parent(index)))
			{
				std::swap(heap[index].second, heap[parent(index)].second);
				unlockElement(index);
				index = parent(index);
				if (index == 1)
				{
					unlockElement(index);
					return true;
				}
			}
			else
			{
				unlockElement(parent(index));
				unlockElement(index);
				return true;
			}
		}
	}

	bool extractMin(T& element)
	{
		mutexForSize.lock();
		if (size == 0)
		{
			mutexForSize.unlock();
			return false;
		}

		int index = 1;
		lockElement(index);
		element = getValue(index);
		lockElement(size);
		std::swap(heap[index].second, heap[size].second);
		deleteElement(size);
		unlockElement(size);
		--size;
		mutexForSize.unlock();

		while (true)
		{
			if (childLeft(index) <= capacity)
			{
				lockElement(childLeft(index));
				if (!elementIsExist(childLeft(index)))
				{
					unlockElement(childLeft(index));
					unlockElement(index);
					return true;
				}
				else
				{
					if (childRight(index) <= capacity)
					{
						lockElement(childRight(index));
						if (elementIsExist(childRight(index)))
						{
							if (getValue(childLeft(index)) < getValue(childRight(index)))
							{
								if (getValue(childLeft(index)) < getValue(index))
								{
									std::swap(heap[index].second, heap[childLeft(index)].second);
									unlockElement(childRight(index));
									unlockElement(index);
									index = childLeft(index);
								}
								else
								{
									unlockElement(childRight(index));
									unlockElement(childLeft(index));
									unlockElement(index);
									return true;
								}
							}
							else
							{
								if (getValue(childRight(index)) < getValue(index))
								{
									std::swap(heap[index].second, heap[childRight(index)].second);
									unlockElement(childLeft(index));
									unlockElement(index);
									index = childRight(index);
								}
								else
								{
									unlockElement(childRight(index));
									unlockElement(childLeft(index));
									unlockElement(index);
									return true;
								}
							}
						}
						else
						{
							unlockElement(childRight(index));
							if (getValue(childLeft(index)) < getValue(index))
							{
								std::swap(heap[index].second, heap[childLeft(index)].second);
								unlockElement(index);
								index = childLeft(index);
							}
							else
							{
								unlockElement(childLeft(index));
								unlockElement(index);
								return true;
							}
						}
					}
					else
					{
						if (getValue(childLeft(index)) < getValue(index))
						{
							std::swap(heap[index].second, heap[childLeft(index)].second);
							unlockElement(index);
							index = childLeft(index);
						}
						else
						{
							unlockElement(childLeft(index));
							unlockElement(index);
							return true;
						}
					}
				}
			}
			else
			{
				unlockElement(index);
				return true;
			}
		}
	}

private:

	std::vector<std::pair<std::mutex, std::pair<T, bool>>> heap;
	int capacity;
	int size;
	std::mutex mutexForSize;

	int childLeft(int index) const
	{
		return index * 2;
	}

	int childRight(int index) const
	{
		return index * 2 + 1;
	}

	int parent(int index) const
	{
		return index / 2;
	}

	void lockElement(int index)
	{
		heap[index].first.lock();
		return;
	}

	void unlockElement(int index)
	{
		heap[index].first.unlock();
		return;
	}

	T getValue(int index) const
	{
		return heap[index].second.first;
	}

	void setValue(int index, T value)
	{
		heap[index].second.first = value;
		heap[index].second.second = true;
		return;
	}

	void deleteElement(int index)
	{
		heap[index].second.second = false;
		return;
	}

	bool elementIsExist(int index)
	{
		return heap[index].second.second;
	}

};

#endif // CUNCURRENT_HEAP_H_INCLUDED