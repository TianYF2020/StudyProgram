#include "OperatorClass.h"


int testOperator() 
{
    OperatorClass p1(3, 4);
    OperatorClass p2(1, 2);

    OperatorClass p3 = p1 + p2; // 使用重载的 + 运算符

    std::cout << "p3.x = " << p3.x << ", p3.y = " << p3.y << std::endl;

    std::cout << p1 << std::endl; // 输出为 (3, 4)
    return 0;
}
