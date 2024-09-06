#include "VarParamClass.h"

// 方案1 使用省略号（Ellipsis）
void VarParamClass::PrintNumbers(int count, ...)
{
    cout << "This parent printf:";
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) 
    {
        int num = va_arg(args, int);
        //std::cout << va_arg(args, double) << " ";      // 支持的参数类型
        //std::cout << va_arg(args, const char*) << " "; // 支持的参数类型
        std::cout << num << " ";
    }
    va_end(args);
    std::cout << std::endl;
}

//2. 使用模板（Template）
void C_TestVarParam::PrintNumbers(int count, ...)
{
    va_list args;
    va_start(args, count);
    std::cout << "This son: ";
    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        std::cout << num << " ";
    }
    va_end(args);
    std::cout << std::endl;
}

