#ifndef THREADPOOL_H_INCLUDED
#define THREADPOOL_H_INCLUDED

#include <thread>
#include <utility>
#include <vector>
#include "ParallelQueueForThreadPool.hpp"

template <class T>
class ThreadPool
{
public:

	ThreadPool() : countOfWorkers(8)
	{
		for (int i = 0; i < countOfWorkers; ++i)
		{
			workers.emplace_back(std::thread(job));
		}
	}

	~ThreadPool()
	{
		workers.shutDown();
	}

	returnedValue<T> submit(std::function f)
	{
		//make a box;
		tasks.push(std::make_pair(f, 0 /* std::promise */));
		return 0; //std::future
	}

private:

	ThreadPool(ThreadPool& otherThreadPool) = delete;
	void operator =(ThreadPool& otherThreadPool) = delete;

	ParallelQueueForThreadPool tasks;
	std::vector<std::thread> workers;
	const size_t countOfWorkers;

	void job()
	{
		while (true)
		{
			std::pair < std::function, int /* std::promise */> task;
			queueOfTasks.pop(task);
			//std::promise = f();
		}
	}
};

#endif //THREADPOOL_H_INCLUDED