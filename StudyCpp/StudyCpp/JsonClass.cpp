#include "JsonClass.h"


//void JsonClass::writeJsonFileTest()
//{
//	Json::Value root;   // 'root' will contain the root value after parsing.
//std::cin >> root;
//
//// You can also read into a particular sub-value.
//std::cin >> root["subtree"];
//
//// Get the value of the member of root named 'encoding',
//// and return 'UTF-8' if there is no such member.
//std::string encoding = root.get("encoding", "UTF-8").asString();
//
//// Get the value of the member of root named 'plug-ins'; return a 'null' value if
//// there is no such member.
//const Json::Value plugins = root["plug-ins"];
//
//// Iterate over the sequence elements.
//for (int index = 0; index < plugins.size(); ++index)
//   loadPlugIn(plugins[index].asString());
//
//// Try other datatypes. Some are auto-convertible to others.
//foo::setIndentLength(root["indent"].get("length", 3).asInt());
//foo::setIndentUseSpace(root["indent"].get("use_space", true).asBool());
//
//// Since Json::Value has an implicit constructor for all value types, it is not
//// necessary to explicitly construct the Json::Value object.
//root["encoding"] = foo::getCurrentEncoding();
//root["indent"]["length"] = foo::getCurrentIndentLength();
//root["indent"]["use_space"] = foo::getCurrentIndentUseSpace();
//
//// If you like the defaults, you can insert directly into a stream.
//std::cout << root;
//// Of course, you can write to `std::ostringstream` if you prefer.
//
//// If desired, remember to add a linefeed and flush.
//std::cout << std::endl;
//}

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
