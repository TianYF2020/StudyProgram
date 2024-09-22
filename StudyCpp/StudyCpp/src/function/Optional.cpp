#include <CommonTest.h>
#include <optional>

std::optional<int> opt;         // 默认构造，无值状态
 
std::optional<int> opt1(10);     // 有值状态，包含值10



std::optional<int> getValue(bool condition) 
{
    if (condition) {
        return 42;
    } else {
        return std::nullopt;
    }
}

int testOptioal() 
{
    std::cout << "\n Test Optional function" << std::endl;
    std::optional<int> result = getValue(true);
    if (result) 
        std::cout << "Value: " << *result << std::endl;
    
    if(result.has_value()) 
    {
        std::cout << "Value: " << *result << std::endl;
    }

    result = getValue(false);
    if (result ==std::nullopt)   // !result
        std::cout << "No value available" << std::endl;
    return 0;
}