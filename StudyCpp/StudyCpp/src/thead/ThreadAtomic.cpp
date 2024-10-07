#include "CommonThread.h"
#include <iostream>
#include <atomic>

// load(): 读取原子变量的值。
// store(): 设置原子变量的值。
// exchange(): 设置原子变量的值并返回旧值。
// compare_exchange_weak(): 比较并交换，通常用于实现锁-free数据结构。
// compare_exchange_strong	比较并交换值（强版本）	Compare and exchange values (strong version)
//  当前值与期望值(expect)相等时，修改当前值为设定值(desired)，返回true
//  当前值与期望值(expect)不等时，将期望值(expect)修改为当前值，返回false

// fetch_add(): 原子加法，返回旧值。
// fetch_sub(): 原子减法，返回旧值。
// fetch_and()
// fetch_or()
// fetch_xor()


//内存顺序
// memory_order_relaxed：这个内存顺序表示编译器可以自由地重新排序内存操作，以提高性能。
// memory_order_acquire：获取顺序要求在当前线程中，所有后续的读操作都必须在原子操作完成后执行
// memory_order_seq_cst：这个内存顺序表示编译器在执行这个操作之前，必须确保之前的操作已经完成。
// memory_order_release：在这条指令执行前的对内存的读写指令都执行完毕，这条语句之后的对内存的修改指令不能超越这条指令优先执行，因为它可以确保在执行这个操作之后，之后的操作已经对其他线程可见。

// std::memory_order_relaxed：没有同步和顺序保证，仅保证原子性。适用于不需要考虑操作顺序的情况。
////弃用 std::memory_order_consume：保证依赖于该操作的后续操作的顺序。 适用于有数据依赖的场景，但在一些实现中可能不被完全支持。
// std::memory_order_acquire：保证在该操作之前的所有读写操作在该操作之后可见。通常与释放操作一起使用，形成锁的效果。
// std::memory_order_release： 保证在该操作之前的所有读写操作在该操作之前可见。与获取操作结合使用以实现同步。
// std::memory_order_acq_rel：同时具有获取和释放的效果。在读写操作都需要同步的情况下使用。
// std::memory_order_seq_cst（默认）：提供最强的顺序保证，所有操作都以单一顺序执行。确保所有线程看到的操作顺序一致。


//原子操作
static std::atomic<int> atomicInt(0);

static std::mutex mutex;

static int num = 0;
void addNum()
{
    for(int i = 0; i < 100000;i++)
    {
        // mutex.lock();
        num++;
        // mutex.unlock();
    }
}

void addNumAtomic()
{
    for(int i = 0; i < 100000;i++)
    {
        atomicInt++;    //原子变量是线程安全，+ 不是原子操作
        atomicInt.fetch_add(1,std::memory_order_relaxed);
        //不能使用 atomicInt = atomicInt + 1; //不是原子性操作
    }
}

int testAtomic()
{
    std::thread t1(addNum);
    std::thread t2(addNum);
    t1.join();
    t2.join();
    std::cout << "num ==" << num << std::endl;  //不不是原子操作，线程会切换掉 值不是20000

    std::thread t1_a(addNumAtomic);
    std::thread t2_a(addNumAtomic);
    t1_a.join();
    t2_a.join();
    std::cout << "atomic num ==" << atomicInt << std::endl;  //不不是原子操作，线程会切换掉 值不是20000


    return 0;
}


int TestCompare_exchange()
{
    int expected = 0;
    int desired = 1;
    if(atomicInt.compare_exchange_strong(expected, desired))
    {
        // 如果atomicInt 当前值等于expected，将其设置成desired
        // 并返回true,否则更新为atomicInt的当前值，返回false
    }
    return 0;
}

