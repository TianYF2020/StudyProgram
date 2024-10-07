#pragma once
#include <iostream>
#include <condition_variable>
#include <functional>
#include <vector>
#include <future>
#include <queue>
#include <mutex>
#include <stdexcept>

class ThreadPool
{
private:
    /* data */
public:
    ThreadPool(int threadNums);
    template <typename F,typename ...Args>
    decltype(auto) enqueue(F&& f, Args&&... args);
    // auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result_t<F(Args...)>>;
     //使用 typename 明确表示 type 是一个类型，使编译器能够正确解析并编译代码。
    ~ThreadPool();
    void worker();
private:
        // need to keep track of threads so we can join them
    std::vector<std::thread > workers;
    // the task queue
    std::queue<std::function<void()>> tasks;
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool isStop;

};

ThreadPool::ThreadPool(int threadNums) : isStop(false)
{
    for(size_t i = 0;i < threadNums;i++)
    {
        workers.emplace_back([this]()
        {
            this->worker();
        });
    }
}

ThreadPool::~ThreadPool()
{   
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        isStop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
    {
        worker.join();
    }
}


void ThreadPool::worker()
{
    while(true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            this->condition.wait(lock,[this]{ return this->isStop || !this->tasks.empty(); });
            if(this->isStop && this->tasks.empty())
                return;
            task = std::move(this->tasks.front());
            this->tasks.pop();
        }
    }
}

// add new work item to the pool
template<class F, class... Args>
decltype(auto) ThreadPool::enqueue(F&& f, Args&&... args)
// auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result_t<F(Args...)>>
{
    // using return_type = typename std::invoke_result_t<F(Args...)>;
    // //定义一个只能指针，类型是packaged_task，传入参数，是万能函数，std::bind(f,args)
    // auto task = std::make_shared<std::packaged_task<return_type()>>(
    //         std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    //     );//forward 完美转发，类型不变
    // std::future<return_type> res = task->get_future();
    // {
    //     std::unique_lock<std::mutex> lock(queue_mutex);
    //     // don't allow enqueueing after stopping the pool
    //     if(isStop)
    //         throw std::runtime_error("enqueue on stopped ThreadPool");
    //     tasks.emplace([task](){ (*task)(); });
    // }
    // condition.notify_one();
    	// return res;
    
    using return_type = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>;
	auto task = std::make_shared<std::packaged_task<return_type()>>([Func = std::forward<F>(f)] { return Func(); });
	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		// don't allow enqueueing after stopping the pool
		if (isStop) { throw std::runtime_error("enqueue on stopped ThreadPool"); }
		tasks.emplace([task]() { (*task)(); });
	}
	condition.notify_one();
    return res;
}


int testThreadPool()
{
    
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i]()->int {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}