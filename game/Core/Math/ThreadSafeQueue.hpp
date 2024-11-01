#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <vector>

template <typename T>
class ThreadSafeQueue
{
public:
    void enqueue(const T &item)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(item);
        m_condVar.notify_one();
    }

    std::optional<T> dequeue()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condVar.wait(lock, [this]
                       { return !m_queue.empty(); });

        T item = m_queue.front();
        m_queue.pop();
        return item;
    }

    std::optional<T> tryDequeue()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty())
        {
            return std::nullopt;
        }
        T item = m_queue.front();
        m_queue.pop();
        return item;
    }

    template <typename Container>
    void bulk_enqueue(const Container &items)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (const auto &item : items)
        {
            m_queue.push(item);
        }
        m_condVar.notify_all();
    }

    std::vector<T> bulk_dequeue(size_t maxItems)
    {
        std::vector<T> items;
        std::unique_lock<std::mutex> lock(m_mutex);

        m_condVar.wait(lock, [this]
                       { return !m_queue.empty(); });

        while (!m_queue.empty() && items.size() < maxItems)
        {
            items.push_back(m_queue.front());
            m_queue.pop();
        }

        return items;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    int size() const 
    {
        return m_queue.size();
    }

private:
    mutable std::mutex m_mutex;
    std::condition_variable m_condVar;
    std::queue<T> m_queue;
};
