#include "CommonThread.h"

static std::mutex m_mutex1;
static std::mutex m_mutex2;



// 死锁问题
void task1()
{
    std::lock_guard<std::mutex> lock1(m_mutex1);
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::lock_guard<std::mutex> lock2(m_mutex2);
    std::cout << "Task 1 finish\n";
}

void task2()
{
    std::lock_guard<std::mutex> lock1(m_mutex2);
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::lock_guard<std::mutex> lock2(m_mutex1);
    std::cout << "Task 2 finish\n";
}

int TestDeadLock()
{
    std::thread t1(task1);
    std::thread t2(task2);
    t1.join();
    t2.join();
    return 0;
}