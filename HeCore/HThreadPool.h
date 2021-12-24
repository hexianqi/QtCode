/***************************************************************************************************
**      2021-12-15  HThreadPool 线程池
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

HE_BEGIN_NAMESPACE

class HThreadPool
{
public:
    HThreadPool(size_t);
    ~HThreadPool();

public:
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _tasks;

    // synchronization
    std::mutex _mutex;
    std::condition_variable _condition;
    bool _stop = false;
};

template<class F, class... Args>
auto HThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(_mutex);
        // don't allow enqueueing after stopping the pool
        if (_stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        _tasks.emplace([task](){ (*task)(); });
    }
    _condition.notify_one();
    return res;
}

HE_END_NAMESPACE
