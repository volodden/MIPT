#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED

#include <atomic>
#include <condition_variable>
#include <mutex>

class CyclicBarrier
{
public:

	CyclicBarrier(size_t newThreadCount);

	~CyclicBarrier()
	{
	}

	void setCountOfThreads(size_t newThreadCount);

	void enter();

private:

	CyclicBarrier() = delete;

	std::condition_variable ring;
	std::mutex mtx;
	size_t threadCount;
	std::atomic<int> epoch;
	std::atomic<int> currentNumberOfThreads;

};

#endif // BARRIER_H_INCLUDED