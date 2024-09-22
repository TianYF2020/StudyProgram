#include "MagicEnum.h"


int testMagicEnum()
{
    WeekDay day = WeekDay::WD_MONDAY;
    //枚举转索引
    std::cout << "enum value: " << static_cast<std::underlying_type<WeekDay>::type>(day) << "\n";
    //枚举转字符串 ，
    std::cout << "enum name:  " << magic_enum::enum_name(day) << "\n";

    return 0;
}


// magic_enum 是一个开源的、单头文件的、枚举操作工具箱
// magic_enum 可以实现枚举值到字符串、字符串到枚举值、获取所有枚举名等多种操作
// magic_enum 本身对枚举值有范围限制，默认是 [-128, 128], 可通过 MAGIC_ENUM_RANGE_MIN 和 MAGIC_ENUM_RANGE_MAX 修改
// 不建议将 magic_enum 默认枚举范围改的太大，这会明显拖慢编译时间