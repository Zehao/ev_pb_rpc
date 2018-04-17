#include "blocking_queue.h

template<typename T>
void BlockingQueue::put(const T& elem)
{
    std::unique_lock<std::mutex> lock(_mutex);
    _queue.push_back(elem);
    _condition.notify_one();
}

template<typename T>
void BlockingQueue::put(T&& elem)
{
    std::unique_lock<std::mutex> lock(_mutex);
    _queue.push_back(std::move(elem));
    _condition.notify_one();
}

template<typename T>
T BlockingQueue::get()
{	std::unique_lock<std::mutex> lock(_mutex);
    while(_queue.empty())
    {
        _condition.wait(lock);
    }
    T elem(std::move(_queue.front()));
    _queue.pop_front();
    return std::move(elem);
}
