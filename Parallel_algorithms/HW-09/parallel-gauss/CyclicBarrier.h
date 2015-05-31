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

	void enter();

private:

	CyclicBarrier() = delete;
	CyclicBarrier& operator= (const CyclicBarrier&) = delete;

	std::condition_variable ring;
	std::mutex mtx;
	size_t threadCount;
	std::atomic<int> epoch;
	std::atomic<int> currentNumberOfThreads;

};

#endif // BARRIER_H_INCLUDED