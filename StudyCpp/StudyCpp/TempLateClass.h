#pragma once

#include <iostream>
using namespace std;


template <class T> //声明一个模板，虚拟数据类型名为T
class C_TempLateClass //类模板名为Compare
{
public:
    C_TempLateClass() {};
    ~C_TempLateClass() {};


    void Compare(T a, T b)
    {
        x = a;
        y = b;
        cout << "swap " << a << " " << b;
    }

    T max()  //类模板中的成员函数
    {
        return (x > y) ? x : y;
    }

private:
    T x,y;
};




