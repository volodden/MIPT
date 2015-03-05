#ifndef LOCK_GUARD_FOR_MUTEX_IN_QUEUE_H_INCLUDED
#define LOCK_GUARD_FOR_MUTEX_IN_QUEUE_H_INCLUDED

#include <mutex>

class LockGuardForMutexInQueue
{
public:

	LockGuardForMutexInQueue(std::mutex& currentMutex);
	
	~LockGuardForMutexInQueue();

private:

	LockGuardForMutexInQueue(LockGuardForMutexInQueue& otherLockGuard) = delete;
	void operator =(const LockGuardForMutexInQueue otherLockGuard) = delete;

	std::mutex& insideMutex;
};

#endif //LOCK_GUARD_FOR_MUTEX_IN_QUEUE_H_INCLUDED