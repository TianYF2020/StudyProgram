#include "CommonThread.h"
// 线程同步方式
// 锁，互斥，读写锁，条件变量， 信号亮 ，原子操作,栅栏  //C++20

// 条件变量
#include <mutex>
#include <condition_variable>

static std::mutex cv_mutex;
static std::condition_variable cv;

bool flag = false;

void myprint(int i);
void updateflag();


int TestThreadSync_condition_variable()
{
    std::vector<std::thread> mybox;
    for(int i = 0; i < 10;i++) 
    {
        mybox.emplace_back(myprint, i);
    }
    updateflag();
    for(std::thread &t: mybox)
    {
        t.join();
    }
	return 0;
}



void myprint(int i)
{
    std::unique_lock<std::mutex> lock(cv_mutex);
#if 0   //wait
    while (!flag)  // 线程在阻塞，等待唤醒的时候，才会再次判断flag  这里使用flag防止虚假唤醒
    {
        cv.wait(lock);  //条件不成立的时候，会释放掉这个锁的
    }
    cv.wait(lock,[](){return flag;});  //可以使用谓词，直接使用lambda表达式
#else   // wait for
    //    std::cv_status::no_timeout timeout  有的会返回这个
   bool ret = cv.wait_for(lock,std::chrono::seconds(1),[](){return flag;});
#endif
    std::cout << "Thread " << std::this_thread::get_id() << " : " << i << std::endl;
}


void updateflag()
{
    // 睡眠2s
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // std::this_thread::sleep_for(3s);
    std::unique_lock<std::mutex> lock(cv_mutex);
    flag = true;
    cv.notify_all();  // 通知所有等地啊线程
    // cv.notify_one();  //通知一个
    //注意 如果你没有通知 flag 为真夜不会执行，如果你通知了，但条件不成立，仍然会阻塞的，不会
    // 执行，他的顺序是先通知在检测条件
}