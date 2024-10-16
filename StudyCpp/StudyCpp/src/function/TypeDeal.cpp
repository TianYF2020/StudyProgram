#include <CommonTest.h>
#include "iostream"
#include "type_traits"


// std::is_integral<T>：判断类型 T 是否为整数类型。
// std::is_floating_point<T>：判断类型 T 是否为浮点类型。
// std::is_class<T>：判断类型 T 是否为类类型。
// std::is_same<T1, T2>：判断 T1 和 T2 是否相同。


//常量表达式（Constant Expression）是指在编译时可以求值的表达式。这意味着这些表达式的值在程序运行前就已确定，编译器可以在编译阶段进行计算和优化。

// 编译时条件判断：if constexpr 会在编译时检查条件，并根据结果决定是否编译相应的代码块。
// 这对于模板编程非常有用，可以根据模板参数的特性选择不同的实现。


template<typename T>
void checkType(T value) {
    if constexpr(std::is_integral<T>::value) 
    {
        std::cout << "是整数类型" << std::endl;
    } 
    else if constexpr (std::is_floating_point<T>::value)
    {
        std::cout << "是浮点类型" << std::endl;
    } 
    else {
        std::cout << "其他类型" << std::endl;
    }
}



template<typename T>
void printType(T&& arg) {
    using DecayedType = typename std::decay<T>::type; // 使用 std::decay 进行类型衰减
    if constexpr (std::is_same<DecayedType, int>::value) {
        std::cout << "衰减后的类型是 int" << std::endl;
    } else {
        std::cout << "衰减后的类型不是 int" << std::endl;
    }
}

template<typename T>
void printDecayType() {
    using DecayedType = typename std::decay<T>::type; // 使用 std::decay 进行类型衰减
    std::cout << "衰减后的类型: " << typeid(DecayedType).name() << std::endl;
}

int testTypeDeal() 
{
    constexpr int value = 5; // 定义常量

    checkType(42);        // 输出：是整数类型
    checkType(3.14);     // 输出：是浮点类型
    checkType("hello");   // 输出：其他类型

    int arr[10];
    printType(arr); // 输出：衰减后的类型不是 int
    printType(42);  // 输出：衰减后的类型是 int

    printDecayType<decltype(arr)>(); // 输出指针类型
    printDecayType<const int>();       // 输出 int
    printDecayType<void(*)()>();       // 输出指向函数的指针
    return 0;
}