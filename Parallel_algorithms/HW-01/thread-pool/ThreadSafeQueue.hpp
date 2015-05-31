#ifndef THREAD_SAFE_QUEUE_H_INCLUDED
#define THREAD_SAFE_QUEUE_H_INCLUDED

#include <atomic>
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
		if (!isEnd.load())
		{
			std::lock_guard<std::mutex> lock(mtx);
			if (isEnd.load())
			{
				return;
			}
			dataQueue.push(std::move(newElement));
			queueNotEmpty.notify_one();
		}
	}

	bool pop(T& returnedElement)
	{
		if (!isEnd.load())
		{
			std::unique_lock<std::mutex> lockMutex(mtx);
			while ((dataQueue.empty()) && (!isEnd.load()))
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
		isEnd.store(true);
		queueNotEmpty.notify_all();
	}

private:

	std::queue<T> dataQueue;
	std::condition_variable queueNotEmpty;
	std::mutex mtx;
	std::atomic<bool> isEnd;

};

#endif // THREAD_SAFE_QUEUE_H_INCLUDED