#include <KeyWord.h>
#include <variant>
#include <array>
#include <tuple>
#include <optional>

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
// 编译时递归实现 static_for
template <std::size_t Start, std::size_t End, typename F>
void static_for(F const& func) {
    if constexpr (Start < End) {
        func(std::integral_constant<std::size_t, Start>{});
        static_for<Start + 1, End>(func);  // 递归调用
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