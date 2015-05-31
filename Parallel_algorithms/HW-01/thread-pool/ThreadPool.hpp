#ifndef THREADPOOL_H_INCLUDED
#define THREADPOOL_H_INCLUDED

#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>

#include "ThreadSafeQueue.hpp"

#define DEFAULT_COUNT_OF_WORKERS 8

template <class T>
class ThreadPool
{
public:

	ThreadPool()
	{
		countOfWorkers = std::thread::hardware_concurrency();
		if (countOfWorkers < 1)
		{
			countOfWorkers = DEFAULT_COUNT_OF_WORKERS;
		}
		startWorkers();
	}

	ThreadPool(size_t newCountOfWorkers)
	{
		if (newCountOfWorkers < 1)
		{
			countOfWorkers = std::thread::hardware_concurrency();
			if (countOfWorkers < 1)
			{
				countOfWorkers = DEFAULT_COUNT_OF_WORKERS;
			}
		}
		startWorkers();
	}

	~ThreadPool()
	{
		tasks.shutDown();
		for (thread& worker : workers)
		{
			worker.join();
		}
	}

	std::future<T> submit(std::function<T()> f)
	{
		std::promise<T> prom;
		std::future<T> fut = prom.get_future();
		tasks.push(std::make_pair(f, std::move(prom)));
		return fut;
	}

private:

	void startWorkers()
	{
		for (size_t i = 0; i < countOfWorkers; ++i)
		{
			workers.emplace_back(std::thread([&](){ //thread_guard!
												      runWorker();
			                                      }));
		}
	}

	void runWorker()
	{
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
	}

	size_t countOfWorkers;
	ThreadSafeQueue<std::pair<std::function<T()>, std::promise<T>>> tasks;
	std::vector<std::thread> workers;

};

#endif //THREADPOOL_H_INCLUDED
