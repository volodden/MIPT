#ifndef THREADPOOL_H_INCLUDED
#define THREADPOOL_H_INCLUDED

#include <functional>
#include <thread>
#include <utility>
#include <vector>

#include "ParallelQueueForThreadPool.hpp"

const size_t countOfWorkers = 8;

template <class T>
class ThreadPool
{
public:

	ThreadPool()
	{
		for (size_t i = 0; i < countOfWorkers; ++i)
		{
			workers.emplace_back(std::thread([&](){ //thread_guard!
				while (true)
				{
					std::pair < std::function<T()>, int /* std::promise */> task;
					if (!tasks.pop(task))
					{
						break;
					}
					//std::promise = f();
				}
			}));
		}
	}

	~ThreadPool()
	{
		tasks.shutDown();
	}

	ReturnedValue<T> submit(std::function<T()> f)
	{
		//make a box;
		tasks.push(std::make_pair(f, 0 /* std::promise */));
		return ReturnedValue<T>(); //std::future
	}

private:

	ThreadPool(ThreadPool& otherThreadPool) = delete;
	void operator =(ThreadPool& otherThreadPool) = delete;

	ParallelQueueForThreadPool<std::pair<std::function<T()>, int /* std::promise */> > tasks;
	std::vector<std::thread> workers;

	void job()
	{
		while (true)
		{
			std::pair < std::function, int /* std::promise */> task;
			if (!queueOfTasks.pop(task))
			{
				break;
			}
			//std::promise = f();
		}
	}
};

#endif //THREADPOOL_H_INCLUDED