#include <KeyWord.h>
#include <variant>
#include <array>
#include <tuple>
#include <optional>
#include <vector>
#include <iostream>
#include <functional>
#include <type_traits>

//声明静态变量或函数。
static int a = 10;

//constexpr：声明编译时常量。
constexpr unsigned int b = 20;

//编译期计算函数，如果不能有new 动态分配内存的情况，
// 如果想函数是编译期运行，那么输入的也是constexpr常量
constexpr unsigned int addAB(unsigned int a, unsigned int b)
{
    return a + b;
}




// 编译器的常量对象
class myObject
{
public:
    // 构造函数必须使用初始化列表，
    //1.构造函数必须使用constexpr关键词修饰 2.成员函数的初始化必须通过初始化列表完成
    constexpr myObject(int a,int b,int c):m_id(allid++),m_a(a),m_b(b),m_c(c){}   //在构造时候为const 初始化

    constexpr int cal_sum() const 
    {
        return m_a + m_b + m_c;
    }
    static int testStatic;   // c++17 之前
    static inline int allid = 0;   //之后使用inline
private:
    int m_a, m_b, m_c;

    const int m_id;    // const 可以没有定义初始化，在构造时候初始化
};
 int myObject::testStatic = 20;
// 使用
// constexpr myObject(10,20,30);
// constexpr int a = myObject.cal_sum();



struct myStruct
{
    int value;
};

// 判断是左值引用还是右值引用
void printValue(const myStruct&& myStruct)
{
    if (std::is_lvalue_reference<decltype(myStruct)>::value) {
        std::cout << "Left value\n";
    } else {
        std::cout << "Right value\n";
    }
}


// extern：用于声明外部变量或函数。
extern int add(int a, int b);

int add(int a,int b)
{
    return a + b;
}

class Printer
{
    public:
    void printProduct(int a, int b) {
        std::cout << "Product: " << a * b << std::endl;
    }
};

//函数调用的例子
void testFunCall()
{
    //1 std::function 是一个可调用对象的封装，能够存储任何可以调用的目标
    std::function<int(int, int)> func = add; 
    func(2, 3); 
    //2 std::invoke 用于统一调用各种可调用对象（如函数、成员函数、lambda 等）
    Printer printer;
    std::invoke(add, 2, 3); // 调用普通函数
    std::invoke(&Printer::printProduct, &printer, 3, 7); // 调用成员函数
    //std::mem_fn std::mem_fn 用于生成一个可调用对象，该对象可以调用给定类型的成员函数。
    auto memberFunc = std::mem_fn(&Printer::printProduct);
    memberFunc(printer, 3, 7); // 调用成员函数

// std::function 用于存储和调用各种可调用对象，具有类型擦除的特性。
// std::invoke 统一调用机制，简化可调用对象的调用，不涉及存储。
// std::mem_fn 主要用于生成成员函数的可调用对象，便于批量调用成员函数。
}






//static_for
// 编译时递归实现 static_for ,这里使用了模版参数，意思，且可以使任何参数来调用、
// 这里模版F 是传参，进来的，类型编译器推导，因此不需要声明参数了
template <std::size_t Start, std::size_t End, typename F>
void static_for(F const& func) {
    if constexpr (Start < End) {
        func(std::integral_constant<std::size_t, Start>{});
        static_for<Start + 1, End>(func);  // 递归调用
    }
}


template <typename T, typename U>
void check_types() {
    if constexpr (std::is_same<T, U>::value) {
        std::cout << "类型相同\n";
    } else {
        std::cout << "类型不同\n";
    }
}


int testStatic_for() 
{
    // 编译时执行从 0 到 4 的循环
    static_for<0, 5>([](auto i) {
        std::cout << i << std::endl;  // 输出 i 的值，编译时展开
    });
    return 0;
}


//get
int testGet() 
{

     std::tuple<int, double, std::string> myTuple(1, 2.5, "hello");
    // 使用 get 获取 tuple 中的元素
    std::cout << std::get<0>(myTuple) << std::endl;  // 输出: 1
    std::cout << std::get<1>(myTuple) << std::endl;  // 输出: 2.5
    std::cout << std::get<2>(myTuple) << std::endl;  // 输出: hello

    std::variant<int, double, std::string> myVar = 10;
    // 获取 variant 中当前存储的值
    std::cout << std::get<int>(myVar) << std::endl;  // 输出: 10
    myVar = "hello";
    std::cout << std::get<std::string>(myVar) << std::endl; 
    
    std::array<int, 3> arr = {1, 2, 3};
    // 使用 get 获取 array 中的元素
    std::cout << std::get<0>(arr) << std::endl;  // 输出: 1
    std::cout << std::get<1>(arr) << std::endl;  // 输出: 2
    std::cout << std::get<2>(arr) << std::endl;  // 输出: 3

    //optional 获取里面中的值
    std::optional<int> opt = 42;
    if (opt) {
        std::cout << opt.value() << std::endl;  // 输出: 42
    }
    // std::nullopt 表示 optional 不包含值
    opt = std::nullopt;
    try {
        std::cout << opt.value() << std::endl;  // 抛出异常
    } catch (const std::bad_optional_access& e) {
        std::cout << "No value!" << std::endl;  // 输出: No value!
    }

    return 0;
}




struct Visitor {
    void operator()(int i) const {
        std::cout << "int: " << i << std::endl;
    }

    void operator()(double d) const {
        std::cout << "double: " << d << std::endl;
    }

    void operator()(const std::string& str) const {
        std::cout << "string: " << str << std::endl;
    }
};
int testVist()
{

//在 C++ 中，visit 通常与 C++17 引入的 std::variant 类型一起使用。
//std::visit 是一个函数模板，它用于访问和操作 std::variant 中当前存储的值。
//std::variant 是一种类似于联合体的类型，但更加安全和灵活，它可以存储多个不同类型的值中的一个
    std::variant<int, double, std::string> var;

    // 存储 int 类型,这里的定义了一个访问函数
    var = 42;
    std::visit(Visitor{}, var);  // 输出: int: 42
    var = 3.14;
    std::visit(Visitor{}, var);  // 输出: double: 3.14
    var = std::string("hello");
    std::visit(Visitor{}, var);  // 输出: string: hello

    std::variant<int, double, std::string> var1 = "hello";

    // 使用 lambda 表达式作为访问器
    std::visit([](auto&& arg) {
        std::cout << "Value: " << arg << std::endl;
    }, var);  // 输出: Value: hello

    //
    std::variant<int, double> var3 = 10;
    std::variant<int, double> var4 = 3.14;
    // 访问两个 variant
    std::visit([](auto&& arg1, auto&& arg2) {
        std::cout << "arg1: " << arg1 << ", arg2: " << arg2 << std::endl;
    }, var3, var4);  // 输出: arg1: 10, arg2: 3.14

//std::visit 是一个用于访问和操作 std::variant 中当前存储值的工具。
//通过 std::visit，可以更优雅、类型安全地处理 variant 的值，避免了手动类型检查和类型转换。
    return 0;
}

#include <list>
int testslt1()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};

    auto begin = vec.begin(); // 向量的起始迭代器
    auto end = vec.end(); // 向量的结束迭代器

    auto count = std::distance(begin, end); // 计算距离

    std::list<int> list = {1, 2, 3, 4, 5};
    std::list<int>::iterator it = list.begin();
    std::advance(it, 2);              // `it` 被移动了2步，`it` 的值发生了改变
    std::list<int>::iterator it2 = std::next(it, 2); // `it` 不变，返回新的迭代器 `it2`

    return 0;
}

#include <iostream>
#include <type_traits>

template <typename T>
void printType() {
    // 使用 std::decay_t 获取衰减后的类型
    using DecayType = std::decay_t<T>;
    std::cout << "Original type: " << typeid(T).name() << std::endl;
    std::cout << "Decayed type: " << typeid(DecayType).name() << std::endl;
}

int testDecay() {
    printType<int>();            // 原始类型是 int，衰减后的类型也是 int
    printType<int&>();           // 原始类型是 int&，衰减后的类型是 int
    printType<const int[]>();    // 原始类型是 const int[]，衰减后的类型是 const int*
    printType<void(int)>();      // 原始类型是 void(int)，衰减后的类型是 void(*)(int)
    
    // std::decay用途：去除类型的引用和 cv（const/volatile）修饰符，通常用于类型推导。
    using DecayedType = std::decay<int&>::type; // DecayedType 为 int
    
    return 0;
}



template <typename T, T v>
struct integral_constant {
    static constexpr T value =    v;
    typedef T                     value_type;
    typedef integral_constant     type;
    
    // ...
};

//静态断言 整形常量
void testaaaaaaaaaaa()
{
    typedef integral_constant<int, 2> two_type;

    
    typedef integral_constant<int, 6> six_type;

    static_assert(two_type::value * 3 == six_type::value, "2*3 != 6");
}



template<typename T>
void testNoParams(T x) 
{
    std::cout << "Template no parameter " << x <<std::endl;
}




//constexprc
// c++11中的constexpr指定的函数返回值和参数都必须保证是字面值，而且必须有且只有一行代码（return代码）。所以通常只能通过return 三目运算符+递归来计算返回的字面值。
constexpr int max_value = 100; // 编译时常量
constexpr int factorial (int n)
{
    return n > 0 ? n * factorial( n - 1 ) : 1;
}

constexpr int multiply(int x,int y)
{
    return x* y;
}
//将在编译时期计算
const int var = multiply(10,10);



// void TestMem_fn()
// {
//     Printer printer;
//     auto memberFunc = std::mem_fn(&Printer::printProduct);
//     memberFunc(printer, 2, 3); // 输出 Product: 6
// }



#include <type_traits>
#include <functional>

int add(int x, double y)
{
    return x + static_cast<int>(y);
}
// c++14之前
// std::result_of是一个函数类型萃取器（function type traits），它可以推导函数类型的返回值类型，它定义在头文件<type_traits>中。std::result_of模板类需要两个模板参数：第一个是函数类型，第二个是函数的参数类型。它的定义如下：
// template <typename F, typename... Args>
// class result_of<F(Args...)>;
// 在模板参数中，F必须是可调用类型、对函数的引用或对可调用类型的引用，Args代表函数参数类型。例如，如果我们有一个函数add，它的类型为int(int, double)，我们可以按照下列示例代码来使用std::result_of以获取其返回值类型
// int testresult_of()
// {
//     std::result_of<std::function<int(int, double)>(int, double)>::type result = 0;
//     static_assert(std::is_same<decltype(result), int>::value, "result type should be int");
//     return 0;
// }

// int testresult_of_t()
// {
//     std::result_of_t<decltype(&add)(int, double))> result = 0;
//     static_assert(std::is_same<decltype(result), int>::value, 
//     return 0;
// }



// std::invoke_result/std::invoke_result_t的定义如下：

template <typename F, typename... Args>
struct invoke_result;
template <typename F, typename... Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;


class A
{
public:
    int add(int x, double y)
    {
        return x + static_cast<int>(y);
    }
};


int testinvoke_result()
{
    //例子1 访问成员函数
    std::invoke_result_t<decltype(&A::add), A*, int, double> result = 0;
    static_assert(std::is_same<decltype(result), int>::value, "result type should be int");
    
        //例子2 访lambda表达式
    std::function<int(int, double)> add = [](int x, double y) {
        return x + static_cast<int>(y);
    };
    std::invoke_result_t<decltype(add), int, double> result1 = 0;
    static_assert(std::is_same<decltype(result1), int>::value, "result type should be int");
    return 0;
}



//C++ 运行时类型识别 RTTI

// typeid 获取类型,运行时编译期都能获取到
void testTypeId()
{
    int a = 0;
    std::cout << typeid(a).name() << " " << a << std::endl;   //int
    MyBaseClass mStruct;  
    std::cout << typeid(mStruct).name() << " " << a << std::endl; // MyBaseClass

   // 对于枚举类型,可以使用 输出 enum:: 然后名字，需要处理


    int *p = &a;
    std::cout << typeid(p).name() << " " << a << std::endl;   //int
    MyBaseClass *mClass = new MyBaseClass;  
    std::cout << typeid(mClass).name() << " " << a << std::endl; // MyBaseClass
    // 静态时候，原来声明的啥，输出的是啥，声明父类，后面是子类输出也是父类
}


class Base {
public:
    virtual ~Base() = default; // 确保有虚析构函数
};

class Derived1 : public Base {};
class Derived2 : public Base {};

void identify(Base* base) 
{
    if (dynamic_cast<Derived1*>(base)) {
        std::cout << "base is of type Derived1" << std::endl;
    } else if (dynamic_cast<Derived2*>(base)) {
        std::cout << "base is of type Derived2" << std::endl;
    } else {
        std::cout << "base is of an unknown type" << std::endl;
    }
}



void testAllKeyWord()
{
    // 无参函数，自动推导

    testaaaaaaaaaaa();
    int x = 0;
    testNoParams(x);
    
    testDecay();

    testslt1();

    testVist();

    testGet();

    testStatic_for();


}

