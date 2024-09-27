#include "ReflectFun.h"
#include "rfl.hpp"
// #include "rfl/yaml.hpp"
#include "rfl/json.hpp"


int testRefectFuntion()
{
    auto homer =
        Person{.first_name = "Homer",
            .last_name = "Simpson",
            .age = 45,
            .longth = {25,28,21}};

    // We can now write into and read from a JSON string.
    const std::string json_string = rfl::json::write(homer);
    //反射出来
    std::cout << " json :"<<json_string << std::endl;
    homer.age = 100;
    //序列化出来
    auto homer2 = rfl::json::read<Person>(json_string).value();
    std::cout << "Origin: "<< homer << std::endl;
    std::cout << homer2 << std::endl;



    // const std::string yaml_string = rfl::yaml::write(homer);
    // cout << "yaml :" << yaml_string << std::endl
    // auto homer2 = rfl::yaml::read<Person>(yaml_string).value();
    return 0;
}

