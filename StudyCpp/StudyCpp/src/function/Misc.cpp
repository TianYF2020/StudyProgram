#include "CommonTest.h"
#include <iostream>


// 基础类型（如 int、char）或轻量类型（如 std::string_view）: 传值更高效。
// 较大对象（如 std::vector、std::string）: 传引用更高效，尤其是 const 引用。
// 现代编译器优化: 对于小对象传值，通常会进行优化，不必担心性能问题

void testString_view() 
{
    std::string str = "Hello, World!";
    std::string_view sv = str;
    std::string_view view(str);
    std::cout << sv << sv.data() << std::endl;


    auto substr = sv.substr(0, 5); // "Hello", 无需复制
    const char* c_str = sv.data();  // 不保证以 '\0' 结尾// 使用 c_str 可能不安全

    std::string_view view1 = "apple";
    std::string_view view2 = "orange";
    if (view1 == view2) {
        std::cout << "The strings are equal." << std::endl;
    } else {
        std::cout << "The strings are different." << std::endl;
    }

}

