#ifndef QUEUE_LOCK_FREE__HPP_INCLUDED
#define QUEUE_LOCK_FREE__HPP_INCLUDED

#include <iostream>
#include <atomic>

template <class T>
class QueueLockFree
{

public:
	
	QueueLockFree()
	{
		Node* newNode = new Node(T());
		head = tail = headOfList = newNode;
		countOfWorkedThreads.store(0);
	}
	
	~QueueLockFree()
	{
		Node* oldHead = head.load();

		while (oldHead != nullptr)
		{
			Node* oldHeadDelete = oldHead;
			oldHead = oldHead->next;
			delete oldHeadDelete;
		}
	}

	void push(T dataForElement)
	{
		countOfWorkedThreads.fetch_add(1);

		Node* newNode = new Node(dataForElement);
		while (true)
		{
			Node* oldTail = tail.load();
			Node* nextTail = oldTail->next.load();
			if (oldTail != tail.load())
			{
				continue;
			}
			if (nextTail == nullptr)
			{
				if (oldTail->next.compare_exchange_strong(nextTail, newNode))
				{
					tail.compare_exchange_strong(oldTail, newNode);
					break;
				}
			}
			else
			{
				tail.compare_exchange_strong(oldTail, nextTail);
			}
		}

		clearList();
		countOfWorkedThreads.fetch_sub(1);
	}

	bool pop(T& returnedElement)
	{
		countOfWorkedThreads.fetch_add(1);

		while (true)
		{
			Node* oldHead = head.load();
			Node* oldTail = tail.load();
			Node* oldNext = head.load()->next.load();

			if (oldHead != head.load())
			{
				continue;
			}
			if (oldHead == oldTail)
			{
				if (oldNext == nullptr)
				{
					clearList();
					countOfWorkedThreads.fetch_sub(1);
					return false;
				}
				tail.compare_exchange_strong(oldTail, oldNext);
			}
			else
			{
				T rValue = oldNext->data;
				if (head.compare_exchange_strong(oldHead, oldNext))
				{
					returnedElement = rValue;
					clearList();
					countOfWorkedThreads.fetch_sub(1);
					return true;
				}
			}
		}
	}

private:

	void clearList()
	{
		if (countOfWorkedThreads.load() != 1)
		{
			return;
		}
		Node* oldHead = head.load();
		Node* toDelete = headOfList.exchange(oldHead);

		while (toDelete != oldHead)
		{
			Node* oldNext = toDelete->next.load();
			delete toDelete;
			toDelete = oldNext;
		}
	}

	class Node
	{
	
	public:
		
		Node(T newData) : data(newData), next(nullptr)
		{
		}

		T data;
		std::atomic<Node*> next;

	};

	std::atomic<Node*> head;
	std::atomic<Node*> tail;
	std::atomic<Node*> headOfList;
	std::atomic<int> countOfWorkedThreads;
};

#endif // QUEUE_LOCK_FREE__HPP_INCLUDED