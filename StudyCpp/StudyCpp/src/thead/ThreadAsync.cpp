#include "ThreadAsync.h"
#include <iostream>

// 一个耗时的函数
int longTask(int num)
{
    std::cout << __FUNCTION__ << ":start run thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5)); // 模拟耗时任务
    std::cout << __FUNCTION__ << ":end thread" << std::endl;
    return num * 2;
}

int testThreadAsync()
{
    // 使用std::async启动异步任务   默认是std::lanch::async|std::lanch::deferred 不确定什么时候执行
    //std::lanch::async 立即执行
    //std::lanch::deferred 当调用 wai时候或get时候执行 
    std::future<int> result = std::async(std::launch::async, longTask, 10);
    result.wait(); //等待异步线程执行
    std::cout << __FILE__ << std::endl;
    // 你可以在这里做其他的事情
    std::cout << __FUNCTION__ << ":Deal other ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟耗时任务
    // 获取异步任务的结果
    std::cout << __FUNCTION__ << ":Wiat result" << std::endl;
    int value = result.get();  // 阻塞，直到任务完成

    std::cout << __FUNCTION__ << ":get Result: " << value << std::endl;

    return 0;
}


// promise 设置异步操作结果的机制
int TestThreadPromise()
{
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t([&](std::promise<int> prom) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        prom.set_value(100);
    },std::move(prom));

    std::cout << "Waiting for result..." << std::endl;
    int result = fut.get();
    std::cout << "Result: " << result << std::endl;
    t.join();
    return 0;
}


//3 .packaged_task的使用

int multiply(int a, int b)
{
    return a * b;
}
int testThreadPackagedTask()
{
    // 把lambda表达式封装成了任务 返回类型， 名字，后面跟函数
    std::packaged_task<int(int,int)> task([](int a,int b) 
    {
        return a + b;
    });
    std::future<int> myfuture = task.get_future();
    task(2,23);  //执行任务
    std::cout << myfuture.get() << std::endl;

    // 普通函数
    //创建packaged_task包装函数 
    std::packaged_task<decltype(multiply)> task1(multiply);
    // 关联tash和future
    std::future<int> myfuture1 = task1.get_future();
    //交给线程执行  //只能移动，不能复制
    std::thread t(std::move(task1),5,6); //
    int value = myfuture1.get();
    std::cout << "Result: " << value << std::endl;
    
    t.join();
    return 0;
}

