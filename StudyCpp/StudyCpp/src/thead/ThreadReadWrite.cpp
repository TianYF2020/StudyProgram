#include <CommonThread.h>
#include <shared_mutex>
#include <iostream>
#include <mutex>

//shared_lock 共享锁
// unique_lock 


static std::shared_mutex rw_mutex;
int shared_data = 0;

void reader()
{
    // std::shared_lock<std::shared_mutex> lock(rw_mutex);
    std::shared_lock lock(rw_mutex);
    std::cout << "Reader thread: " << std::this_thread::get_id() << " read value "<< shared_data << std::endl;
}


void writer(int value)
{
    // std::shared_lock<std::shared_mutex> lock(rw_mutex);
    std::unique_lock lock(rw_mutex);
    shared_data = value;
    std::cout << "Writer thread: " << std::this_thread::get_id() << " read value "<< shared_data << std::endl;
}

int testLockReadWrite()
{
    std::vector<std::thread> threads;
    //创建读线程
    for(int i = 0; i <5; ++i)
    {
        threads.emplace_back(reader);
    }
    // 创建写线程
    for(int i = 0; i <2; ++i)
    {
        threads.emplace_back(writer,i);
    }
    
    for(auto& t: threads)
    {
        t.join();
    }
    //输出结果读取的内容是乱掉的，因为都可以操作，读是互斥的，只能一个一个执行，因此一行一行的
    return 0;
}