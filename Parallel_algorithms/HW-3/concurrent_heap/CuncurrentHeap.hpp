#ifndef CUNCURRENT_HEAP_H_INCLUDED
#define CUNCURRENT_HEAP_H_INCLUDED

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <utility>
#include <vector>

template<class T>
class CuncurrentHeap
{
public:

	CuncurrentHeap(int count) : capacity(count + 1), size(0), heap(count + 1)
	{
	}

	~CuncurrentHeap()
	{
	}

	void insert(T key)
	{
		mutexForSize.lock();
		if (size == capacity)
		{
			mutexForSize.unlock();
			std::unique_lock<std::mutex> lockSize(mutexForSize);
			while (size == capacity)
			{
				overflow.wait(lockSize);
			}
			mutexForSize.lock();
		}

		int idx = ++size;
		heap[idx].first.lock();
		mutexForSize.unlock();

		while (idx != 1)
		{
			heap[idx >> 1].first.lock();
			if (heap[idx].second < heap[idx >> 1].second)
			{
				std::swap(heap[idx].second, heap[idx >> 1].second);
				heap[idx].first.unlock();
				idx >>= 1;
			}
			else
			{
				heap[idx >> 1].first.unlock();
				heap[idx].first.unlock();
				return;
			}
		}
		heap[idx].second = key;
		heap[idx].first.unlock();
	}

	T extractMin()
	{

	}

private:

	std::vector<std::pair<std::mutex, T>> heap;
	int capacity;
	int size;
	std::condition_variable overflow;
	std::mutex mutexForSize;

};

#endif // CUNCURRENT_HEAP_H_INCLUDED