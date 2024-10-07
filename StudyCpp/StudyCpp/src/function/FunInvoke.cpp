#include <CommonTest.h>
#include <functional>


void foo(int a,int b)
{
    std::cout <<"a+b = " << a+b << std::endl;
}

class Bar
{
    public:
    void operator()(int a, int b) const {
        std::cout <<"a+b = " << a+b << std::endl;
    }
};

int testFunInvoke()
{
    
    int a = 10, b = 5;
    std::invoke(foo, a, b); // 调用普通函数
    Bar bar;
    std::invoke(bar, a, b); // 调用函数对象
    std::invoke(&Bar::operator(), bar, a, b); // 调用成员函数
    std::function<void(int, int)> f = foo;
    std::invoke(f, a, b); // 调用std::function对象
    return 0;

}