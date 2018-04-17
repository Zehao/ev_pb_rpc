#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include<mutex>
#include<condition_variable>
#include<deque>

template<typename T>
class BlockingQueue
{
public:
	BlockingQueue():_mutex(), _queue()
	{
	}

	BlockingQueue(const BlockingQueue&) = delete;
	void operator = (const BlockingQueue&) = delete;

public:

	void put(const T& elem);
	void put(T&& elem);
	T get();

private:
	std::mutex _mutex;
	std::condition_variable _condition;
	std::deque<T> _queue;
};
#endif
