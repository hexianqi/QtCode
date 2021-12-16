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

HE_END_NAMESPACE
