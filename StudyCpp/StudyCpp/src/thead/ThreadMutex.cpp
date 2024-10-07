#include "CommonThread.h"

//线程同步的方式
//1,互斥锁 2.条件变量 3.信号量 4.原子操作

//mutex 4中锁
// 1. std::mutex		//	基础的互斥锁
// 2. std::recursive_mutex 	// 递归锁,允许多次锁定 ，加几次锁，解几次锁
// 3. std::timed_mutex   //带时限的互斥锁， try_lock_for 和 try_lock_until
// 4. std::recursive_timed_mutex		//递归时限锁 

#include <mutex>

std::mutex mymutex;
int count = 0;

void increment_counter(int time)
{
	for(int i=0; i<time; i++)
	{
		mymutex.lock();
		count ++;
		std::cout << std::this_thread::get_id() << std::endl;
		mymutex.unlock();
	}
}

int TestMutex()
{
	std::thread t1(increment_counter,100);
	std::thread t2(increment_counter,100);
	t1.join();
	t2.join();
	return 0;
}

//lock_guard的一些问题 
//1. 锁的作用域过大 ，无法中途解锁， 不支持条件变量，不支持递归
//
int TestLockGuard()
{
	int n = 0;
	{
		std::lock_guard<std::mutex> lock(mymutex);
		for(int i=0;i<1000;i++)
		{
			n++;
		}	
		//lock_guard 声明周期结束
	}

	for(int i=0;i<1000;i++)
	{
		n++;
	}
	return 0;
}

//unique_lock
//定义
int TestUnique_lock()
{
	std::mutex mtx;
	std::unique_lock<std::mutex> lk1(mtx); //自动锁定,相当于lock_guard
	std::unique_lock<std::mutex> lk_defer(mtx, std::defer_lock);//延迟锁，不要自动上锁定
	std::unique_lock<std::mutex> lk_tryLock(mtx, std::try_to_lock);//尝试锁定，能锁定true 否则false
	std::unique_lock<std::mutex> lk_adopt(mtx, std::adopt_lock);//接受已经锁定的 mutex
	// 成员函数 lock(); 锁定关联的mutxe  unlock(); 解锁关联的mutex
    // try_lock(); 尝试锁定关联的mutex，返回true 成功， false 失败
    // try_lock_for(std::chrono::milliseconds duration); 尝试锁定关联的mutex，返回true 成功， false 失败，并在duration 内
    // try_lock_until(std::chrono::system_clock::time_point time_point); 尝试锁定关联的mutex，返回true 成功， false 失败，并在time_point 之前
    // swap(unique_lock& other); 交换 unique_lock 对象的锁
	// owns_lock()  // 返回指示是否用于mutex的所有权
    std::unique_lock<std::mutex> lk2(mtx);
    if(lk1.try_lock())
    {
        std::cout << "lk1 locked" << std::endl;
    }
	//延迟锁
 	lk_defer.lock();
	std::cout << "lock deferred" << std::endl;
	lk_defer.unlock();  // 可以隐式解锁

	//尝试锁
	if(lk_tryLock.owns_lock())
	{
		std::cout << "lock success" << std::endl;
	}
	else{
		std::cout << "lock failure" << std::endl;
	}

	//接受锁
	std::mutex testmutex;
	testmutex.lock();
	std::unique_lock<std::mutex> lk_adopt1(testmutex, std::adopt_lock);
	lk_adopt1.unlock();// 可以不解锁自动解锁
    return 0;
}