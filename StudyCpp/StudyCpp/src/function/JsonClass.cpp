#include "JsonClass.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>
#include "rfl.hpp"
#include "rfl/json.hpp"


JsonClass::JsonClass()
{
    // std::filesystem::path path("config");
    // if(!std::filesystem::exists(path))
    // {
    //     std::filesystem::create_directory(path);
    // }
    // for (const auto & entry : std::filesystem::directory_iterator(path))
    // {
    //     std::cout << entry.path() << std::endl;
    // }


    // // 复制和移动文件
    // std::filesystem::copy("source.txt", "destination.txt");
    // std::filesystem::rename("old_name.txt", "new_name.txt");
    // // 删除文件或目录：
    // std::filesystem::remove("file_to_delete.txt");
    // std::filesystem::remove_all("directory_to_delete");
    // // 获取文件大小
    // auto file_size = std::filesystem::file_size("example.txt");
    // // 获取最后修改时间
    // auto ftime = std::filesystem::last_write_time("example.txt");

}

// 写入 JSON 示例
void JsonClass::writeJsonFileTest(const std::string& filename)
{
    Json::Value root;  // Json对象
    root["name"] = "Alice";  // 添加数据
    root["age"] = 30;
    root["isStudent"] = false;

    Json::Value hobbies(Json::arrayValue);  // 创建数组
    hobbies.append("reading");
    hobbies.append("traveling");
    hobbies.append("swimming");
    root["hobbies"] = hobbies;  // 添加数组到对象中

    // 打开文件并写入JSON
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }
    Json::StreamWriterBuilder writer;
    file << Json::writeString(writer, root);  // 将JSON对象写入文件
    file.close();
}

// 读取 JSON 示例
void JsonClass::readJsonFileTest(const std::string& filename)
{
    std::ifstream file(filename, std::ifstream::binary);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    Json::Value root;
    file >> root;  // 读取文件中的JSON数据
    file.close();

    // 读取并输出 JSON 数据
    std::cout << "Name: " << root["name"].asString() << std::endl;
    std::cout << "Age: " << root["age"].asInt() << std::endl;
    std::cout << "Is Student: " << (root["isStudent"].asBool() ? "Yes" : "No") << std::endl;

    std::cout << "Hobbies: ";
    for (const auto& hobby : root["hobbies"]) {
        std::cout << hobby.asString() << " ";
    }
    std::cout << std::endl;
}

enum class DEV_TYPE
{
    DEV_NT68830,
    DEV_NT68400,
    DEV_3683,
    DEV_V53,
    DEV_V56,
};

enum class ADJUST_TYPE
{
    ADJUST_GAIN,
    ADJUST_GAMMA,
    ADJUST_BRIGHT,
    ADJUST_GAMUT,
    ADJUST_HSB,
    ADJUST_3DLUT
};

struct AdjustCapability
{
    bool gain = false;
    bool gamma = false;
    bool bright = false;
    bool gamut = false;
    bool hsb = false;
    bool lut3d = false;
};




void JsonClass::writeNlohmannJsonFileTest(const std::string& filename)
{
    nlohmann::json json;

    // 创建 adjust 节点
    nlohmann::json adjust;

    // auto enumerators_named_tuple = rfl::get_enumerators<DEV_TYPE>();
    auto enumerator_array = rfl::get_enumerator_array<DEV_TYPE>();  
    std::vector<std::string> deviceTypes;
    for(int i=0; i<enumerator_array.size(); i++)
    {
        deviceTypes.emplace_back(enumerator_array[i].first);
        std::cout << enumerator_array[i].first << " ";
    }
    // for(const auto& enumValue : enumerator_array)
    // {
    //     deviceTypes.emplace_back(enumValue.first);
    //     // std::cout << "111111111111111" << (*enumValue.first) << std::endl;
    // } 

    AdjustCapability temp;
    const std::string json_string = rfl::json::write(temp);

    // 为每个设备类型添加色温、色域、亮度和值
    for (const auto &type : deviceTypes) {
        // adjust[type] = {
        //     {"Gain", false},
        //     {"Gamma", false},
        //     {"Gamut", false},
        //     {"Bright", false},
        //     {"HSB", false},
        //     {"Lut", false},
        // };
        for (const auto& f : rfl::fields<AdjustCapability>()) 
        {
            adjust[type][f.name()] = false;
            // std::cout << "name: " <<  << ", type: " << f.type() << std::endl;
        }

    }
    // 创建 serial 节点
    json["adjust"] = adjust;
    json["serial"] = {
        {"串口号", "COM1"},  // 示例串口号
        {"波特率", 9600}     // 示例波特率
    };

    // 写入文件
    std::ofstream file(filename);
    file << json.dump(4); // 4表示缩进
    file.close();



}
#include <map>
std::map<DEV_TYPE,AdjustCapability> m_AdjustCapability;

void JsonClass::readNlohmannJsonFileTest(const std::string& filename)
{
    nlohmann::json json;
    // 读取文件
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
    file >> json;
    file.close();

    auto enumerator_array = rfl::get_enumerator_array<DEV_TYPE>();  
    std::vector<std::string> deviceTypes;
    for(const auto& enumValue : enumerator_array)
    {
        deviceTypes.emplace_back(enumValue.first);
    } 

    // 读取 adjust 节点
    for (const auto &item : json["adjust"].items()) {
        std::string type = item.key();
        std::string text = item.value().dump();     // 转字符串
        AdjustCapability temp = rfl::json::read<AdjustCapability>(text).value();
        // auto dev = rfl::string_to_enum<DEV_TYPE>(type);
        DEV_TYPE dev = rfl::string_to_enum<DEV_TYPE>(type).value(); 
        m_AdjustCapability.insert(std::make_pair(dev, temp));
    }

    // 读取 serial 节点
    auto serial = json["serial"];
    std::cout << "串口号: " << serial["串口号"] << std::endl;
    std::cout << "波特率: " << serial["波特率"] << std::endl;

}