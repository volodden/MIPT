#ifndef THREAD_SAFE_QUEUE_H_INCLUDED
#define THREAD_SAFE_QUEUE_H_INCLUDED

#include <condition_variable>
#include <mutex>
#include <vector>
#include <queue>

template <class T>
class ThreadSafeQueue
{
public:
	ThreadSafeQueue() : isEnd(false)
	{
	}

	~ThreadSafeQueue()
	{
	}

	void push(T newElement)
	{
		if (!isEnd)
		{
			std::lock_guard<std::mutex> lock(mtx);
			dataQueue.push(std::move(newElement));
			queueNotEmpty.notify_one();
		}
	}

	bool pop(T& returnedElement)
	{
		if (!isEnd)
		{
			std::unique_lock<std::mutex> lockMutex(mtx);
			while ((dataQueue.empty()) && (!isEnd))
			{
				queueNotEmpty.wait(lockMutex);
			}
			if (!dataQueue.empty())
			{
				returnedElement = std::move(dataQueue.front());
				dataQueue.pop();
				return true;
			}
			return false;
		}
		return false;
	}

	bool tryPop(T& returnedElement)
	{
		std::lock_guard<std::mutex> lockMutex(mtx);
		while (dataQueue.empty())
		{
			return false;
		}
		returnedElement = std::move(dataQueue.front());
		dataQueue.pop();
		return true;
	}

	void shutDown()
	{
		std::unique_lock<std::mutex> lockMutex(mtx);
		isEnd = true;
		queueNotEmpty.notify_all();
	}

private:

	std::queue<T> dataQueue;
	std::condition_variable queueNotEmpty;
	std::mutex mtx;
	bool isEnd;

};

#endif // THREAD_SAFE_QUEUE_H_INCLUDED