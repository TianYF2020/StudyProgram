#pragma once
//禁止waring
#pragma warning(push)
#pragma warning(disable : 4348)
#include <iostream>


// 在这里强烈声明一点,程序静态一般是指编译器执行的，动态是运行时期指定，静态一般声明啥是啥，多态是动态的

// 隐式类型转换：当编译器自动将一种类型转换为另一种类型时，称为隐式类型转换。例如，将一个整数赋值给一个浮点数变量时，编译器会自动将整数转换为浮点数。
// 显式类型转换：当程序员明确指定将一种类型转换为另一种类型时，称为显式类型转换。在C++中，有四种显式类型转换运算符：static_cast、dynamic_cast、const_cast和reinterpret_cast。
// static_cast：（转换基础的一些数据类型的）用于基本的类型转换，如将整数转换为浮点数，指针转换为整数等。它可以在编译期进行类型检查，但不能用于没有继承关系的类之间的转换。
// dynamic_cast：（多态，继承转换类型的）用于在继承关系中的类型转换。它会在运行时进行类型检查，如果转换不安全，则返回nullptr或抛出异常。
// as_const const_cast：（转换Const）用于去除变量的const或volatile属性。它可以用于修改常量对象的值，但需要谨慎使用，因为违反了const的语义。
// reinterpret_cast：(转换指针的)用于将一个指针或引用转换为另一个不相关的类型。它没有类型检查，因此非常危险，可能导致未定义的行为。

 
 //C++ 中默认是静态绑定的，如果不使用virtual，那么他的类型声明的啥就是啥,动态绑定才能根据
 //分配的类型来调用具体的实现 (比较关键重要的)
class MyBaseClass
{
public:
    MyBaseClass() = default;  // 禁止默认构造，。
    MyBaseClass(std::string str):name(str) {};  // 禁止默认构造，。
    // 把父类的析构函数定义成虚函数，保证子类的析构能执行    
    virtual ~MyBaseClass() = default;   // 使用默认构造,可以把=default理解成{}

    int func()  = delete; // 函数被删除，不能使用

    virtual void runWork()  // 函数执行    
    {
        std::cout << "MyBaseClass runing work..." << std::endl;
    }

protected:  //子类可以访问
    std::string name;
private:    // 子类无法访问
    int * ptr_a = nullptr; //空指针常量（C++11引入）
};



// 子类继承父类，需要重写父类中的虚函数，如果不重写，会使用父类中的实现

class MyTestClass : public MyBaseClass
{
public:
    MyTestClass() = default; //
    MyTestClass(std::string strs) : MyBaseClass(name) {};

    ~MyTestClass();
    void runWork() override         // 会检查函数名和父类时候一样
    {
        std::cout << "MyTestClass runing work..." << std::endl;
    }  
private:
    std::string sName;

};


extern void testAllKeyWord();

//虚函数表记录了所有虚函数值，类中只存了一个虚函数表指针
// 所有相同类型类型共享一个虚函数表，不同类型单独一个虚函数表


