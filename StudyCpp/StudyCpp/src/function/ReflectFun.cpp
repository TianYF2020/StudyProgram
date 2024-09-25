#include "ReflectFun.h"


int testRefectFuntion()
{
    const auto homer =
        Person{.first_name = "Homer",
            .last_name = "Simpson",
            .age = 45};

    // We can now write into and read from a JSON string.
    const std::string json_string = rfl::json::write(homer);
    std::cout << " json :"<<json_string << std::endl;
    auto homer2 = rfl::json::read<Person>(json_string).value();
    return 0;
}

