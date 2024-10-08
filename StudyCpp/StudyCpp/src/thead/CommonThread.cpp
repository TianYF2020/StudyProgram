#include "CommonThread.h"
#include "mutex"
#include "condition_variable"

struct TestStruct
{
    int count = 0;
    bool isSet = false;
    /* data */
};



class TestThreadSync
{
public:
    TestStruct DealThreadTask(int args, std::string &str,TestStruct &testStruct)
    {
        testStruct.count = 100;
        testStruct.isSet = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Thread ID: " << std::this_thread::get_id() << ", count: " << testStruct.count << ", str: " << str  << " "  << args<< std::endl;
        str = "Deal Finish";
        return testStruct;
    }
};


int TestCommonThread()
{
    TestThreadSync mTestThreadSync;
    std::mutex mutex;
    std::unique_lock<std::mutex> mlock(mutex,std::defer_lock);
    mlock.lock();
    std::string str = "ha ha";
    TestStruct testStruct;
    int argc = 0;
#if 0
    // pack_task 不可移动，必须move
    std::packaged_task<TestStruct(int,std::string &,TestStruct &)> task([&mTestThreadSync](int args, std::string &str,TestStruct &testStruct)  
    {
        return mTestThreadSync.DealThreadTask(args, str, testStruct);
    });
#else
    std::packaged_task<TestStruct(int,std::string &,TestStruct &)> task(std::bind(&TestThreadSync::DealThreadTask,&mTestThreadSync,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
#endif
    mlock.unlock();
    std::future<TestStruct> future = task.get_future();
    std::thread t(std::move(task),argc,std::ref(str),std::ref(testStruct));
   // 等待线程完成
    t.join();
    TestStruct temp = future.get();
    return 0;
}