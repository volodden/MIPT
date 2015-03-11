#ifndef PARALLELQUEUE_HPP_INCLUDED
#define PARALLELQUEUE_HPP_INCLUDED

#include <condition_variable>
#include <mutex>
#include <queue>

#include "LockGuardForMutexInQueue.h"

template <class T>
class ParallelQueue
{
public:
	ParallelQueue()
	{
	}

	~ParallelQueue()
	{
	}

	void push(const T& newElement)
	{
		//std::lock_guard<std::mutex> lock(mtx);
		LockGuardForMutexInQueue lockMutex123(mtx);
		dataQueue.push(newElement);
		queueNotEmpty.notify_one();
	}

	T pop(T& returnedElement)
	{
		std::unique_lock<std::mutex> lockMutex(mtx);
		//LockGuardForMutexInQueue lockMutex(mtx);
		while (dataQueue.empty())
		{
			queueNotEmpty.wait(lockMutex);
		}
		returnedElement = dataQueue.front();
		dataQueue.pop();
		if (returnedElement == POISON_PILL)
		{
			dataQueue.push(POISON_PILL);
			queueNotEmpty.notify_one();
			return false;
		}
		return true;
	}

	int getPoisonPill() const
	{
		return POISON_PILL;
	}

private:
	std::queue<T> dataQueue;
	std::condition_variable queueNotEmpty;
	std::mutex mtx;
	const int POISON_PILL = -23;

};

#endif // PARALLELQUEUE_HPP_INCLUDED
