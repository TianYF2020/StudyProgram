#include "NameSpaceClass.h"
#include <iostream>

using namespace std;
using std::cout;
// 用std 把名
namespace std  //不建议用
{

// 第一个命名空间
namespace first_space {
    void func() {
        cout << "Inside first_space -1" << endl;
    }
}
// 第二个命名空间
namespace second_space {
    void func() {
        cout << "Inside second_space -2" << endl;
    }
}
int testNamespace()
{
    // 调用第一个命名空间中的函数
    first_space::func();

    // 调用第二个命名空间中的函数
    second_space::func();

    return 0;
}

}


namespace namespace_nest1 {
    // 代码声明
    namespace namespace_nest2 {
        // 代码声明
    }
}

// 访问 namespace_name2 中的成员
using namespace namespace_nest1::namespace_nest2;

// 访问 namespace_name1 中的成员
using namespace namespace_nest1;


// 定义一个类
class MyClass {
public:
    void show() {
        std::cout << "MyClass::show 被调用\n";
    }
};

// 使用 typedef 为 MyClass 创建别名
typedef MyClass AliasClass; //把myclass定义成 AliasClass

using AliasClass = MyClass; //使用AliasClass 替代MyClass

AliasClass obj;  // 使用重命名后的类型

//效果相同