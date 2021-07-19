#include "HThreadPool.h"
#include <iostream>

inline HThreadPool::HThreadPool(size_t size)
{
    for(size_t i = 0; i < size; ++i)
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
                        if(this->_stop && this->_tasks.empty())
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

inline HThreadPool::~HThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for(std::thread &worker: _workers)
        worker.join();
}


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


void testThreadPool()
{
    HThreadPool pool(4);
    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i)
    {
        results.emplace_back(pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return  i * i;
            }));
    }

    for (auto && result : results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
}
