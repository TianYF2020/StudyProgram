#include "CommonThread.h"
#include "barrier"
#include <iostream>
//栅栏

void worker(int id,std::barrier<>& sync_point) 
{
    std::cout << "worker " << id << " is doing pase 1 work\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100*id));

    sync_point.arrive_and_wait();   //到达栏杆，等待其他线程
    std::cout << "worker " << id << " has completed pase 1 and is doing pase 2"<< std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100*id));
}


int TestBarrier(void)
{
    const int num_threads = 5;
    std::barrier sync_point(num_threads); //创建栅栏

    std::vector<std::thread> threads;  
    for(int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(worker,i+1,std::ref(sync_point));
    }
    for(auto &t: threads)
    {
        t.join();
    }
    std::cout << "All threads have finished." << std::endl;
    return 0;
}