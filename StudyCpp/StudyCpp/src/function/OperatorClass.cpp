#include "OperatorClass.h"
#include <vector>
#include <algorithm>
int testOperator() 
{
    OperatorClass p1(3, 4);
    OperatorClass p2(1, 2);

    OperatorClass p3 = p1 + p2; // 使用重载的 + 运算符

    std::cout << "p3.x = " << p3.x << ", p3.y = " << p3.y << std::endl;

    std::cout << p1 << std::endl; // 输出为 (3, 4)


    std::vector<MyTestStruct> vec = {{3.5f,2.0f,"a"}, {1.2f,12.3f,"b"}, {4.8f,0.0f,"c"}, {2.0f,22.0f,"d"}};
    // 使用 std::sort 进行排序
    std::sort(vec.begin(), vec.end());
    // 输出排序结果
    for (const auto& item : vec) {
        std::cout << item.value << " ";
    }
    std::cout << std::endl;

    return 0;

    return 0;
}
