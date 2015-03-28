#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED

#include <atomic>
#include <condition_variable>
#include <mutex>

class CyclicBarrier
{
public:

	CyclicBarrier(int newCount);

	~CyclicBarrier()
	{
	}

	void enter();

private:

	CyclicBarrier() = delete;

	std::condition_variable ring;
	std::mutex mtx;
	int count;
	std::atomic<int> epoch;
	std::atomic<int> currentNumberOfThreads;

};

#endif // BARRIER_H_INCLUDED