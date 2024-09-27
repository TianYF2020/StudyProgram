#include <KeyWord.h>
#include <variant>
#include <array>
#include <tuple>
#include <optional>
#include <vector>

//声明静态变量或函数。
static int a = 10;

//constexpr：声明编译时常量。
constexpr unsigned int b = 20;

// extern：用于声明外部变量或函数。
extern int add();

int add(int a,int b)
{
    return a + b;
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