#include "SmartPointer.h"


int testSharePtrClass()
{
    std::shared_ptr<SharedPtrClass> ptr1 = std::make_shared<SharedPtrClass>(); // 创建智能指针
    {
        std::shared_ptr<SharedPtrClass> ptr2 = ptr1; // 共享同一个对象
        ptr2->show();
        std::cout << "ptr2 leave Area\n";
    }

    // ptr2 离开后，ptr1 仍然持有对象
    if (ptr1)
    {
        ptr1->show();
    }
    std::cout << "ShareUniquePtr Pragram finish\n";
    return 0;
}


int testUniqueClass()
{
    std::unique_ptr<UniquePtrClass> ptr1 = std::make_unique<UniquePtrClass>(); // 创建唯一智能指针
    ptr1->show();
    // 转移所有权
    std::unique_ptr<UniquePtrClass> ptr2 = std::move(ptr1);
    if (!ptr1) {
        std::cout << "ptr1 is empty\n";
    }
    std::cout << "error" << std::endl;
    ptr2->show();
    std::cout << "UniquePtr Pragram finish\n";
    return 0;
}

int testSmartPtr()
{
    testSharePtrClass();
    std::cout << std::endl;
    testUniqueClass();
    std::cout << std::endl;
    return 0;
}


