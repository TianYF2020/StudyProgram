#include "FunCallBack.h"

// 定义一个接受回调函数的函数
void processData(int a, int b, void (*callback)(int))
{
    int result = a + b; // 简单的加法运算
    callback(result);   // 调用回调函数，传递结果
}


// 定义一个回调函数
void callbackFunction(int result) {
    std::cout << "function callBack: " << result << std::endl;
}

float testBindFuntion(int a, float b)
{
    cout << "test bind callback" << a << " " << b << endl;
    return b;
}


int testCallBack() 
{
    // 调用函数，并将回调函数作为参数传递
    processData(5, 3, callbackFunction);
    MyClass obj;
    // 调用processData，传入静态成员函数作为回调
    obj.processData(5, 7, MyClass::staticCallback);

    //把函数注册进函数了
    obj.setCallBack(callbackFunction);

    obj.setBindCallBack(testBindFuntion);  // 设置回调
    obj.bindcallback(1, 2.0);
     //类中绑定普通函数 ， std::placeholders::_1 可以使用占位符或者直接定义值夜可以
    obj.bindcallback = std::bind(testBindFuntion, std::placeholders::_1, std::placeholders::_2);
    obj.bindcallback(1, 3.0);
    MyBindClass bindobj;

    // 使用std::bind绑定成员函数和对象
    std::function<void(int)> testcallback = std::bind(&MyBindClass::memberCallback, &bindobj, std::placeholders::_1);
    // 调用processData，传入绑定的成员函数作为回调
    bindobj.processData(5, 7, testcallback);

    return 0;

}