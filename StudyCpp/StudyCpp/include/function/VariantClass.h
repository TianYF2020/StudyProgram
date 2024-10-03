#pragma once
#include <iostream>
#include <variant>
#include <string>

// 定义多个结构体
struct Circle {
    float radius;
};

struct Rectangle {
    float width;
    float height;
};

struct Triangle {
    float base;
    float height;
};

// 使用 std::variant 整合结构体
using ShapeInvMonostate = std::variant<std::monostate, Circle, Rectangle, Triangle>;

using Shape = std::variant<Circle, Rectangle, Triangle>;

// 定义一个访问者，用于处理不同的形状
struct ShapePrinter {
    void operator()(const Circle& circle) const {
        std::cout << "这是一个圆，半径: " << circle.radius << std::endl;
    }

    void operator()(const Rectangle& rectangle) const {
        std::cout << "这是一个矩形，宽: " << rectangle.width << " 高: " << rectangle.height << std::endl;
    }

    void operator()(const Triangle& triangle) const {
        std::cout << "这是一个三角形，底: " << triangle.base << " 高: " << triangle.height << std::endl;
    }
};

int testVariant();

