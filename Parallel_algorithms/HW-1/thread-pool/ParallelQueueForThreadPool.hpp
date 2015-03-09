#ifndef PARALLEL_QUEUE_FOR_THREADPOOL_H_INCLUDED
#define PARALLEL_QUEUE_FOR_THREADPOOL_H_INCLUDED

template <class T>
class ParallelQueue
{
public:
	ParallelQueue()
	{
		isEnd = false;
	};

	~ParallelQueue()
	{
	};

	void push(const T& newElement)
	{
		std::lock_guard<std::mutex> lock(mtx);
		dataQueue.push(newElement);
		queueNotEmpty.notify_one();
	}

	bool pop(T& returnedElement)
	{
		std::unique_lock<std::mutex> lockMutex(mtx);
		while ((dataQueue.empty()) && (!isEnd))
		{
			queueNotEmpty.wait(lockMutex);
		}
		if (!dataQueue.empty())
		{
			returnedElement = dataQueue.front();
			dataQueue.pop();
			return true;
		}
		return false;
	}

	void shutDown() const
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

#endif // PARALLEL_QUEUE_FOR_THREADPOOL_H_INCLUDED