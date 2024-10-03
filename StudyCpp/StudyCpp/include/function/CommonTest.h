#include <iostream>
#include <filesystem>

extern int testOptioal();



// 复制目录及其内容
void copyDirectory(const std::filesystem::path& source, const std::filesystem::path& destination);
// 删除目录及其内容
void clearDirectory(const std::filesystem::path& dir);

void createDirectory(const std::filesystem::path& path);