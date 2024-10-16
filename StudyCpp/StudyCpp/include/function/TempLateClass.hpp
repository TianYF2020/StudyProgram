﻿#pragma once

#include <iostream>
//hpp 包含了h和cpp实现，包含头文件和实现，一般是是模版类



//模版可以默认参数
template <class T1 = int,class T2 = double>
class Student
{
public:

    Student() = default;
    Student(std::string iname, T1 iage, T2 iscore):name(iname),age(iage),score(iscore) {}
    void ShowMe()
    {
        std::cout << "name: " << this->name << ", age: " << this->age << ", score: " << this->score << std::endl;
    }

private:
    std::string name;
    T1 age;
    T2 score;
};


// int testMyTemplate()
// {
//     // 模版类没有自动推导的可能
//     Student<int, double> stu1("Tom", 18, 98);
//     Student<char, double> stu2("lias", 'A', 98);

//     Student stu3("lias", 12, 98);
//     stu1.ShowMe();
//     return 0;
// }

//延迟实例化
template <class T>
class MyclassTest
{
public: 
    void runing()
    {
        // 编译器不知道什么时候传入的类型，有没有这个方法，因此没有报错
        T obj1;
        obj1.ShowMe();
    }
};




//*********类作为模版参数传递*************
//方法1 - 确定具体的类型即可
inline void fun1(Student<int,double> &p)
{
    p.ShowMe();
}

//方法2 - 参数也模版化
template <typename T1, typename T2>
void fun2(Student<T1,T2> &p)
{
    p.ShowMe();
}

//方法3 - 将类模版化,直接把类直接当做模版传入
template <typename T>
void fun3(T &p)
{
    p.ShowMe();
}




//***********模版的继承 **********************/
template <typename T>
class Base
{
public:
    T var;
};


//方法1 确定父类的类型
//父类是模版类，子类是普通类 - 去顶父类的范类的类型
class myClass : public Base<int>
{

};


//方法2 父类是模版类，子类也是模版类
template <typename T,typename U>
class myClass1: public Base<T>
{

public:
    U age;
};



// C++20引入了概念（Concepts），其中包含了一个新的关键字——requires，用于限制模板参数的类型。requires表达式能够对模板参数进行约束，确保模板实例化时满足特定的条件。
template <typename T, typename U>
requires std::integral<T> && std::floating_point<U>   // 约束一个是Int ，一个是float
void print1(T t, U u) {
    std::cout << "Integer: " << t << ", Floating point: " << u << std::endl;
}

template <typename T, typename U>
requires (std::same_as<T, int> || std::same_as<T, float>) && std::floating_point<U>
void print2(T t, U u) {
    std::cout << "T: " << t << ", U: " << u << std::endl;
}

