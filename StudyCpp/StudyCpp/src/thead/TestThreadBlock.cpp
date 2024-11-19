#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "CommonThread.h"
static std::mutex mtx;
static std::condition_variable cv_main, cv_worker;
static bool ready_main = false;  // 主线程标志
static bool ready_worker = false;  // 测量线程标志



// 我现在进入当前线程后，我会创建一下新的线程，新线程进入后阻塞，新的线程功能是会测量一个数据，
// 当前线程有个for循环，当执行设置后会自己唤醒测量线程，阻塞自己，当另一线程执行完一次测量，线程阻塞，
//原始的线程开始重新执行，直到for循环结束，后销毁线程，帮我使用实现c标准20，还有防止加唤醒

void measurement_thread() {
    std::unique_lock<std::mutex> lock(mtx);
    while (true) {
        // 等待主线程唤醒
        cv_worker.wait(lock, [] { return ready_worker; });

        // 检查是否需要退出
        if (!ready_worker) break;

        // 模拟测量操作
        std::cout << "测量线程：正在测量数据..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟耗时操作

        // 通知主线程，测量完成
        ready_main = true;
        ready_worker = false;
        cv_main.notify_one();
    }
    std::cout << "测量线程：退出线程" << std::endl;
}

int TestThreadBlock() 
{
    std::thread worker(measurement_thread);
    {
        std::unique_lock<std::mutex> lock(mtx);
        for (int i = 0; i < 5; ++i) {  // 模拟一个for循环
            // 唤醒测量线程
            ready_worker = true;
            cv_worker.notify_one();

            // 主线程进入等待，直到测量线程完成
            cv_main.wait(lock, [] { return ready_main; });

            // 模拟主线程设置操作
            std::cout << "主线程：完成设置 " << i + 1 << std::endl;

            // 准备下一轮循环
            ready_main = false;
        }

        // 通知测量线程退出
        ready_worker = true; // 唤醒测量线程退出循环
        cv_worker.notify_one();
    }

    worker.join();
    std::cout << "主线程：程序结束" << std::endl;
    return 0;
}



#include <atomic>
#include <vector>

class ThreadManager {
public:
    ThreadManager() : measure_done(false), stop(false) {}

    void startMeasurementThread() {
        measure_thread = std::thread([this]() {
            while (true) {
                // 等待主线程唤醒
                std::unique_lock<std::mutex> lock(measure_mutex);
                measure_cv.wait(lock, [this]() { return measure_done || stop; });

                if (stop) break;

                // 模拟测量
                std::cout << "Measurement thread: Measuring data..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟耗时任务

                // 测量完成，唤醒主线程
                measure_done = false;
                main_cv.notify_one();
            }
        });
    }

    void stopMeasurementThread() {
        {
            std::lock_guard<std::mutex> lock(measure_mutex);
            stop = true;
            measure_cv.notify_all();
        }
        if (measure_thread.joinable()) {
            measure_thread.join();
        }
    }

    void measureInLoop(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            // 唤醒测量线程
            {
                std::lock_guard<std::mutex> lock(measure_mutex);
                measure_done = true;
                measure_cv.notify_one();
            }

            // 等待测量线程完成
            {
                std::unique_lock<std::mutex> lock(main_mutex);
                main_cv.wait(lock, [this]() { return !measure_done; });
            }

            // 主线程继续执行
            std::cout << "Main thread: Iteration " << i + 1 << " completed.\n";
        }
    }

private:
    std::thread measure_thread;
    std::condition_variable measure_cv;
    std::condition_variable main_cv;
    std::mutex measure_mutex;
    std::mutex main_mutex;
    std::atomic<bool> measure_done;
    std::atomic<bool> stop;
};

int testmain() {
    ThreadManager manager;
    manager.startMeasurementThread();

    // 主线程循环
    manager.measureInLoop(5);

    // 停止测量线程
    manager.stopMeasurementThread();

    std::cout << "All iterations complete, threads stopped." << std::endl;
    return 0;
}


// #include <iostream>
// #include <thread>
// #include <condition_variable>
// #include <mutex>
// #include <chrono>

// std::mutex mtx; // 互斥锁
// std::condition_variable_any cv; // 条件变量
// bool ready = false; // 标志变量，用于控制唤醒
// bool finished = false; // 标志变量，用于终止测量线程

// void measurementThread() {
//     while (true) {
//         // 进入阻塞状态，等待唤醒信号
//         std::unique_lock lock(mtx);
//         cv.wait(lock, [] { return ready || finished; });
//         if (finished) {
//             break; // 终止线程
//         }

//         // 执行测量任务
//         std::cout << "Performing measurement..." << std::endl;
//         std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟测量时间

//         // 测量完成，通知主线程
//         ready = false;
//         cv.notify_one();
//     }
// }

// int main() {
//     // 创建测量线程
//     std::jthread measurer(measurementThread);

//     // 主线程控制循环
//     for (int i = 0; i < 5; ++i) {
//         std::unique_lock lock(mtx);

//         // 设置任务并唤醒测量线程
//         ready = true;
//         std::cout << "Starting measurement " << i + 1 << std::endl;
//         cv.notify_one();

//         // 等待测量线程完成
//         cv.wait(lock, [] { return !ready; });

//         std::cout << "Measurement " << i + 1 << " completed!" << std::endl;
//     }

//     // 通知测量线程退出
//     {
//         std::unique_lock lock(mtx);
//         finished = true;
//         cv.notify_one();
//     }

//     // 测量线程会自动清理
//     std::cout << "All measurements completed. Exiting program." << std::endl;

//     return 0;
// }