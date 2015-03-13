#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED

#include <atomic>
#include <condition_variable>
#include <mutex>

class Barrier
{
public:

	Barrier();
	Barrier(int newCount);

	~Barrier()
	{
	}

	void enter();

private:

	std::condition_variable ring;
	std::mutex mtx;
	int count;
	std::atomic_int epoch;
	std::atomic_int current;

};

#endif // BARRIER_H_INCLUDED