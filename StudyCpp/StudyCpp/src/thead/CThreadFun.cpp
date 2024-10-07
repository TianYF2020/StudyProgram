#include "CThreadFun.h"
//#include <iostream>
//#include <thread>
//
//using namespace std;
//
//void output(int i)
//{
//	cout << i << endl;
//}
//
//int main()
//{
//	for (uint8_t i = 0; i < 4; i++)
//	{
//		thread t(output,i);
//		//t.detach();
//		t.join();
//	}
//
//	getchar();
//	return 0;
//}

//#include <iostream>
//#include <thread>
//#include <mutex>
//
//std::mutex myMutex;
//using namespace std;
//
//void thread_1()
//{
//    //if (myMutex.try_lock())
//    //{
//    //    cout << "test == lock ------ " << endl;
//    //}
//    myMutex.lock();
//    int n = 1000;
//    while (n--)
//    {
//        cout << "子线程1" << endl;
//    }
//    myMutex.unlock();
//}
//
//void thread_2(int x)
//{
//    myMutex.lock();
//    int n = 100;
//    while (n--)
//    //while (1)
//    {
//        cout << "子线程2" << endl;
//    }
//    myMutex.unlock();
//}
//
//int main()
//{
//    thread first(thread_1); // 开启线程，线程已经开启，调用：thread_1()
// 
//    thread second(thread_2, 100); // 开启线程，调用：thread_2(100)
//    //thread third(thread_2,3);//开启第3个线程，共享thread_2函数。
//    std::cout << "主线程\n";
//
//    first.join(); //必须说明添加线程的方式，等待线程执行完后才向下运行。
//    std::cout << "---------------\n";
//    second.join();
//    std::cout << "子线程结束.\n";//必须join完成
//    return 0;
//}


//#include <thread>
//#include <mutex>
//#include <iostream>
//int g_i = 0;
//std::mutex g_i_mutex;  // protects g_i，用来保护g_i
//
//void safe_increment();
//
//int main()
//{
//    safe_increment();
//}
//
//void safe_increment()
//{
//    const std::lock_guard<std::mutex> lock(g_i_mutex);
//    ++g_i;
//    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';// g_i_mutex自动解锁}int main(){
//    std::cout << "main id: " << std::this_thread::get_id() << std::endl;
//    std::cout << "main: " << g_i << '\n';
//
//    std::thread t1(safe_increment);
//    std::thread t2(safe_increment);
//
//    t1.join();
//    t2.join();
//
//    std::cout << "main: " << g_i << '\n';
//}


//#include <mutex>
//#include <thread>
//#include <iostream>
//
//struct Box {
//	explicit Box(int num) :num_things{ num } {}
//	int num_things;
//	std::mutex m;
//};
//
//void transfer(Box& from, Box& to, int num)
//{
//	std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
//	std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);//两个同时加锁
//
//	std::lock(lock1, lock2); //或lock1.lock(); lock2.lock();
//	from.num_things -= num;
//	to.num_things += num;//作用域结束自动解锁,也可以使用lock1.unlock()手动解锁
//}
//
//int main()
//{
//	Box acc1(100);
//	Box acc2(50);
//
//	std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
//	std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
//
//	t1.join();
//	t2.join();
//	std::cout << "acc1 num_things: " << acc1.num_things << std::endl;
//	std::cout << "acc2 num_things: " << acc2.num_things << std::endl;
//}


#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
using namespace std;
static std::mutex mtx;
static std::mutex mtx1;
static std::condition_variable cv;
static std::condition_variable cv1;
int cargo = 0;
bool shipment_available()
{
    return cargo != 0;
}
void consume(int n)
{
    cout << "endl" << endl;
    for (int i = 0; i < n; ++i)
    {
        std::unique_lock<std::mutex> lck(mtx);//自动上锁
        //第二个参数为false才阻塞（wait），阻塞完即unlock，给其它线程资源
        cv.wait(lck, shipment_available);// consume:
        std::cout << cargo << '\n';
        cargo = 0;
        cv1.notify_one();
    }
}
int testThreadCom()
{
    std::thread consumer_thread(consume, 10);
    for (int i = 0; i < 10; ++i)
    {
        //每次cargo每次为0才运行。
        //while (shipment_available())
        //{
        //    std::this_thread::yield();
        //}
        int n = 10000000;
        while (n--);
        std::unique_lock<std::mutex> lck(mtx);
        cargo = i + 1;
        cv.notify_one();
        lck.unlock();
        std::unique_lock<std::mutex> lck1(mtx);
        cv1.wait(lck1);
    }

    consumer_thread.join();

    mutex tesx;
    unique_lock<mutex> lockk(tesx, defer_lock);

    return 0;
}