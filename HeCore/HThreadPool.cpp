#include "HThreadPool.h"

HE_BEGIN_NAMESPACE

HThreadPool::HThreadPool(size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        _workers.emplace_back(
            [this]
            {
                for(;;)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->_mutex);
                        this->_condition.wait(lock, [this]{ return this->_stop || !this->_tasks.empty(); });
                        if (this->_stop && this->_tasks.empty())
                            return;
                        task = std::move(this->_tasks.front());
                        this->_tasks.pop();
                    }
                    task();
                }
            }
            );
    }
}

HThreadPool::~HThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for (std::thread &worker : _workers)
        worker.join();
}

HE_END_NAMESPACE
