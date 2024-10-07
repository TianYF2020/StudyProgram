#include "CommonThread.h"
#include "semaphore"

//信号量 
std::counting_semaphore<1> sem(1); 
//第一个1：模版类的非类型模版参数，指定最大计数值，允许同时多少个资源被访问
//第二个初始值，表示当前有多少个资源

void work()
{
    // std::cout << "work start: " << std::this_thread::get_id() << std::endl;
    //在信号量之外不是互斥的了，所以打印就乱掉了，内部是互斥的，打印就是一个线程一个线程的打印
    sem.acquire();  // 申请一个资源，如果没有，会一直等到有资源
    std::cout << "work get resource: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "work done: " << std::this_thread::get_id() << std::endl;
    sem.release();  // 释放一个资源
    // std::cout << "func1 release resource: " << std::this_thread::get_id() << std::endl;
}

int testSemaphore()
{
    std::vector<std::thread> threads;
    for(int i = 0; i <10;i++)
    {
        threads.emplace_back(work);
    }
    for(auto& t : threads)
    {
        t.join();
    }
    return 0;
}

static std::counting_semaphore<1> ready(1);
static std::counting_semaphore<1> done(0);

void producer()
{
    ready.acquire();
    std::cout << "producer produce: " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "producer done: " << std::this_thread::get_id() << std::endl;
    done.release();
   
}

void consume()
{
    done.acquire();
    std::cout << "consumer consume: " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "consumer done: " << std::this_thread::get_id() << std::endl;
    ready.release();
}

int TestSemaphore()
{
    // std::vector<std::thread> threads;
    std::thread t1(producer);
    std::thread t2(consume);
    t1.join();
    t2.join();
    std::cout << "deal finish" <<std::endl;
    return 0;
}