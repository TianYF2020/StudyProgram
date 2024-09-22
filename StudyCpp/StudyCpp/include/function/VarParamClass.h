#pragma once
#include <iostream>
#include <cstdarg>
#include "stdio.h"
#include "iostream"
using namespace std;


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


