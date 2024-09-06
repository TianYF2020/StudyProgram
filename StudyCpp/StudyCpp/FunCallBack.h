#pragma once
#include "stdio.h"
#include <iostream>
#include <functional> // 包含std::function
using namespace std;
// 普通函数 使用回调
extern int testCallBack();

// 全局静态函数来调用

class MyClass {
public:
    // 静态成员函数作为回调函数
    static void staticCallback(int result)
    {
        std::cout << "Class:function callBack(1): result: " << result << std::endl;
    }

    // 普通函数，处理数据并调用回调函数
    void processData(int a, int b, void (*callback)(int)) {
        int result = a + b;
        callback(result);
    }

    //设置回调函数
    void setCallBack(void (*cb)(int))
    {
        if (callback)
            callback = cb;  //callback赋值
        else
            std::cout << "cb is null" << std::endl;
    }

    void setBindCallBack(const std::function<float(int, float)>& cb)
    {
        bindcallback = cb;
    }



public:
    void(*callback)(int);  //定义了一个callback的函数
    std::function<float(int, float)> bindcallback;
};


// 使用std::bind 来进行回调

class MyBindClass {
public:
    // 普通成员函数作为回调函数
    void memberCallback(int result) {
        std::cout << "rember call back:result is : " << result << std::endl;
    }

    // 处理数据，并调用回调函数
    void processData(int a, int b, const std::function<void(int)>& callback) {
        int result = a + b;
        callback(result);
    }

};





