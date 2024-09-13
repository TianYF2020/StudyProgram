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
    // 使用std::async启动异步任务
    std::future<int> result = std::async(std::launch::async, longTask, 10);
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
