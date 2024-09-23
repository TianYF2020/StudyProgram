#include <KeyWord.h>


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

