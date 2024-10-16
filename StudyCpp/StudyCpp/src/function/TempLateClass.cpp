#include "TempLateClass.h"
#include "TempLateClass.hpp"

//class 更常用于类模板的定义，虽然它在类型模板中也可以使用。
template <class T,class U>
T PrintValue(T a,T b)
{
    cout << "a: " << a << ", b: " << b << endl;
    return a + b;
}
//总之，二者功能相同，选择哪个通常是个人偏好或代码风格的一部分。


//typename 通常用来表示一个类型，强调它是一个类型。
template <typename T>
T GetMaxValue(T a,T b)
{
    return (a > b)? a : b;
}


template<typename T>
T add(T a,T b)
{
    return a + b;
}
//**********模版特化，具有较高的优先级
template<>
int add(int a, int b)
{
    return 2*a + b;
}


// ****************延迟实例化，模版函数只有在调用的时候才实例化
int testTempLate()
{
    int a = 4,b = 6;
    std::cout << "MaxValue = " << GetMaxValue<int>(a,b) << std::endl;

    double da = 4.0,db = 6.0;
    std::cout << "a+b = " << add<float>(da,db) << std::endl;
    //特例话，以特例的为主
    std::cout << "Special a+b = " << add(a,b) << std::endl;

    return 0;
}

// ctrl+alt+d   vs中进入调试反汇编汇代码,看掉了几次call 指令，
//00007FF64FC796D8  call        std::operator<<<std::char_traits<char> > (07FF64FBF56AEh) 



int testMyTemplate()
{
    // 模版类没有自动推导的可能
    Student<int, double> stu1("Tom", 18, 98);
    Student<char, double> stu2("lias", 'A', 98);

    Student stu3("lias", 12, 98);
    stu1.ShowMe();
    return 0;
}



int testMyTemplateClass()
{
    // Myclass<int> ob;
    // ob.runing();    // 运行会报错

    MyclassTest<Student<int,double>> ob;
    ob.runing();    // 运行会报错

    return 0;
}
