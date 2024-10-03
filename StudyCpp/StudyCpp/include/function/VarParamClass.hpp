#pragma once
#include <iostream>
#include <cstdarg>


//方案1
class VarParamClass 
{
public:
    VarParamClass() {};
    ~VarParamClass() {};
    virtual void PrintNumbers(int count, ...); 
};



class C_TestVarParam : public VarParamClass 
{
public:
    C_TestVarParam() {};
    ~C_TestVarParam() {};

    void PrintNumbers(int count, ...) override;

};


// 方案2

template<typename... Args>
void PrintValues(Args... args) {
    //(std::cout << ... << args) << std::endl;
    ((std::cout << args << ' '), ...) << std::endl;
}


// 示例 1 
// C++ dong printf 这个功能
inline void mPrint()    //有bug 后面再改吧，去掉inline报错重定义
{
    std::cout << std::endl;
}

template <typename T> 
void mPrint(const T& t) 
{
    std::cout << t << std::endl;
}

template <typename First, typename... Rest> 
void mPrint(const First& first, const Rest&... rest) 
{
    std::cout << first << ", ";
    mPrint(rest...); // recursive call using pack expansion syntax
}
