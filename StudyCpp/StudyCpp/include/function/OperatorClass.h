#pragma once
#include <iostream>

struct MyStruct
{
    int r,g,b;
    int& operator[](int index) {
        switch (index) {
        case 0: return r;  // 访问红色分量
        case 1: return g;  // 访问绿色分量
        case 2: return b;  // 访问蓝色分量
        default: throw std::out_of_range("Index out of range! Valid indices are 0, 1, or 2.");
        }
    }
};


class OperatorClass {
public:
    int x, y;

    OperatorClass(int x = 0, int y = 0) : x(x), y(y) {}

    // 重载加法运算符
    OperatorClass operator+(const OperatorClass& other) {
        return OperatorClass(this->x + other.x, this->y + other.y);
    }

    // 友元函数重载 << 运算符
    friend std::ostream& operator<<(std::ostream& os, const OperatorClass& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    
    // 重载 [] 运算符，返回数组元素
    int& operator[](int index) {
        // 可以添加越界检查
        if (index < 0 || index >= 10) {
            std::cerr << "Index out of bounds!" << std::endl;
            exit(1);
        }
        return arr[index];  // 返回引用以便可以修改
    }

    // 重载 [] 运算符，返回引用以便修改 RGB 值
    int& operator[](const std::string& component) {
        if (component == "R" || component == "r") {
            return rgb[0];  // 访问红色分量
        }
        else if (component == "G" || component == "g") {
            return rgb[1];  // 访问绿色分量
        }
        else if (component == "B" || component == "b") {
            return rgb[2];  // 访问蓝色分量
        }
        else {
            throw std::out_of_range("Invalid component! Use 'R', 'G', or 'B'.");
        }
    }

    // 为 const 对象提供重载版本
    const int& operator[](int index) const {
        if (index < 0 || index >= 10) {
            std::cerr << "Index out of bounds!" << std::endl;
            exit(1);
        }
        return arr[index];  // 返回 const 引用，防止修改
    }


    // 重载 & 运算符
    OperatorClass* operator&() {
        std::cout << "Address of object requested" << std::endl;
        return this;
    }

    // 重载 -> 运算符，返回 this 指针
    OperatorClass* operator->() {
        return this;
    }

    // 重载 * 运算符，返回成员变量
    int& operator*() {
        return value;
    }



private:
    int value;
    int arr[10];  // 固定大小的数组
    int rgb[3];  // 0: R, 1: G, 2: B
};

extern int testOperator();


//常见的运算符重载
//1、二元运算符（如 + 、 - 、 * 、 / 等）：
//  这些运算符通常需要两个操作数，其中一个可以是类对象。
//2、一元运算符（如 ++、--）：
//  这些运算符只操作一个对象。
//3、赋值运算符（如 = 、 += 、 -= ）：
//  常用于修改对象的内部状态。
//注意事项
//1、不能重载的运算符：
//.（成员访问运算符）
//.*（成员指针访问运算符）
//::（域运算符）
//? : （三元运算符）
//sizeof（大小运算符）
//2、重载为成员函数还是全局函数：
//二元运算符可以重载为成员函数或全局函数，但如果是全局函数，通常需要将类的对象作为参数。
//3、重载输入 / 输出运算符：
//需要将 << 和 >> 重载为友元函数，因为它们的
