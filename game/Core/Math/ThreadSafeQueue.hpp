#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class ThreadSafeQueue
{
public:
    void push(const T &item)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condVar_.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this]()
                      { return !queue_.empty(); });
        T item = queue_.front();
        queue_.pop();
        return item;
    }

    bool tryPop(T &item)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty())
        {
            return false;
        }
        item = queue_.front();
        queue_.pop();
        return true;
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condVar_;
};
