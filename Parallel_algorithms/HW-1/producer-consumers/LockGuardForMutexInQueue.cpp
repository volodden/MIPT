#include "LockGuardForMutexInQueue.h"

LockGuardForMutexInQueue::LockGuardForMutexInQueue(std::mutex& currentMutex) : insideMutex(currentMutex)
{
	insideMutex.lock();
}

LockGuardForMutexInQueue::LockGuardForMutexInQueue(LockGuardForMutexInQueue&& otherMutexGuard) : insideMutex(otherMutexGuard.insideMutex)
{
	insideMutex.lock();
}

LockGuardForMutexInQueue::~LockGuardForMutexInQueue()
{
	insideMutex.unlock();
}

