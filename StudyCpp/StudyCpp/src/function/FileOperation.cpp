#include "CommonTest.h"
#include "filesystem"




// 复制目录及其内容
void copyDirectory(const std::filesystem::path& source, const std::filesystem::path& destination) {
    try {
        // 确保目标目录存在
        std::filesystem::create_directories(destination);

        // 复制所有文件和目录
        for (const auto& entry : std::filesystem::directory_iterator(source)) {
            const auto& path = entry.path();
            std::filesystem::copy(path, destination / path.filename(), std::filesystem::copy_options::recursive);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "复制错误: " << e.what() << std::endl;
    }
}

// 删除目录及其内容
void clearDirectory(const std::filesystem::path& dir) {
    try {
        std::filesystem::remove_all(dir);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "删除错误: " << e.what() << std::endl;
    }
}

void createDirectory(const std::filesystem::path& path)
{
    if(!std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);
    }
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        std::cout << entry.path() << std::endl;
    }
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
