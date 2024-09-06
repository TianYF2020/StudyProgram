#pragma once
#include <iostream>
#include <memory> // 包含智能指针库


class SharedPtrClass 
{
public:
    // 定义一个类public:
    SharedPtrClass() {
        std::cout << "SharedPtrClass creat\n";
    }
    ~SharedPtrClass() {
        std::cout << "MyClass destory\n";
    }
    void show() {
        std::cout << "MyClass::show call\n";
    }
};


// 定义一个类
class UniquePtrClass {
public:
    UniquePtrClass() {
        std::cout << "UniquePtrClass creat\n";
    }
    ~UniquePtrClass() {
        std::cout << "UniquePtrClass destory\n";
    }
    void show() {
        std::cout << "UniquePtrClass::show call\n";
    }
};

class SmartPointer
{
};





extern int testSmartPtr();

