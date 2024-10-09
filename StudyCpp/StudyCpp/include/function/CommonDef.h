#pragma once
// #操作符：用于将宏参数转换为字符串常量
// ##操作符：用于将两个宏参数拼接成一个标识符
#include <iostream>

// 类型和内容 转成 字符串
#define GET_TYPE(a) #a

#define CONCAT(a, b) a##b
#define LINK_MULTIPLE(a,b,c,d) a##_##b##_##c##_##d

#define STRING_CONCAT(a, b) (std::string(a) + std::string(b))

//字符连接
#define SOFTWARE_VERSION     "Software：V1.00"
#define HARDWARE_VERSION     "Hardware：V1.00"
#define SYSTEM_VERSION       SOFTWARE_VERSION HARDWARE_VERSION
//例子1
// “#”的功能是将其后面的宏参数进行字符串化操作（Stringfication），
//简单说就是在对它所引用的宏变量，通过替换后在其左右各加上一个双引号。比如下面代码中的宏：
#define WARN_IF(EXP)                                  \
do {                                                  \
    if (EXP) {                                        \
        fprintf(stderr, "Warning: " #EXP "/n");       \
    }                                                 \
} while(0);

// 那么实际使用中会出现下面所示的替换过程：
// WARN_IF (divider == 0);
// do {
//     if (divider == 0) {
//         fprintf(stderr, "Warning" "divider == 0" "/n");
//     }
// } while(0);



//例子2
// ##：连接两个参数
// “##”被称为连接符（concatenator），用来将两个Token连接为一个Token。注意这里连接的对象是Token就行，而不一定是宏的变量。
//比如你要做一个菜单项命令名和函数指针组成的结构体的数组，并且希望在函数名和菜单项命令名之间有直观的、名字上的关系。那么下面的代码就非常实用：

void quit_command();
void help_command();


#define COMMAND(NAME) {#NAME, NAME##_command}

struct command
{
    std::string name;
    void (*function) (void);
};

// 然后你就用一些预先定义好的命令来方便的初始化一个command结构的数组了：

static struct command commands[10] = {
    COMMAND(quit),
    COMMAND(help)
    // ...
};

