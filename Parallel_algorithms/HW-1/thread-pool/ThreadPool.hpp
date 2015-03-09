#ifndef THREADPOOL_H_INCLUDED
#define THREADPOOL_H_INCLUDED

#include <functional>
#include <future>
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
					std::pair<std::function<T()>, std::promise<T>> task;
					if (!tasks.pop(task))
					{
						break;
					}
					try
					{
						task.second.set_value(task.first());
					}
					catch (std::exception&)
					{
						task.second.set_exception(std::current_exception());
					}
				}
			}));
		}
	}

	~ThreadPool()
	{
		tasks.shutDown();
		for (int i = 0; i < countOfWorkers; ++i)
		{
			if (workers[i].joinable())
			{
				workers[i].join();
			}
		}
	}

	ReturnedValue<T> submit(std::function<T()> f)
	{
		std::promise<T> prom;
		std::future<T> fut = prom.get_future();
		tasks.push(std::make_pair(f, prom));
		return ReturnedValue<T>(fut);
	}

private:

	ThreadPool(ThreadPool& otherThreadPool) = delete;
	void operator =(ThreadPool& otherThreadPool) = delete;

	ParallelQueueForThreadPool<std::pair<std::function<T()>, std::promise<T>>> tasks;
	std::vector<std::thread> workers;

};

#endif //THREADPOOL_H_INCLUDED