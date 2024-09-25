#pragma once

#include <iostream>
using namespace std;

//模版类建议使用hpp的方案，且模版因为，延迟实例化的原因，在h文件中没有调用，就没有实例，因此模版的声明和实例都要放在一起

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

    //在外部实现
    void showMe(T a);

private:
    T x,y;
};


//在实现文件中实现类模板中定义的函数
template <typename T>
void C_TempLateClass<T>::showMe(T a)
{
    std::cout << a << std::endl;
}



extern int testTempLate();




