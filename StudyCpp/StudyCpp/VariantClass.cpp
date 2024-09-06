#include "VariantClass.h"
#include "memory.h"
int testVariant() 
{
    // 将 variant 重置为空值
    ShapeInvMonostate test = std::monostate{};
    if (std::holds_alternative<std::monostate>(test))
    {
        std::cout << "The variant is empty (monostate)" << std::endl;
    }

    // 创建不同的形状并存入 variant
    Shape shape1 = Circle{ 5.0f };

    //你可以使用 std::holds_alternative<T>() 来判断 std::variant 中是否存储了某个特定类型的值。
    if (std::holds_alternative<Circle>(shape1))
    {
        std::shared_ptr<Shape> ptr = std::make_shared<Shape>();

        try 
        {
            Circle c = std::get<Circle>(*ptr);
            std::cout << "The variant holds a Circle" << std::endl;
        }
        catch (const std::bad_variant_access&) {
            std::cout << "Not a Circle" << std::endl;
        }  

        // 使用 std::get_if 获取
        if (auto rect = std::get_if<Rectangle>(&shape1))
        {
            std::cout << "Rectangle width: " << rect->width << std::endl;
        }
        else 
        {
            std::cout << "Not a Rectangle" << std::endl;
        }
    }
    else 
    {
        std::cout << "The variant does not hold a Circle" << std::endl;
    }


    Shape shape2 = Rectangle{ 4.0f, 6.0f };
    if (std::holds_alternative<Circle>(shape2)) 
    {
        std::cout << "The variant holds a Circle" << std::endl;
    }
    else {
        std::cout << "The variant does not hold a Circle" << std::endl;
    }

    Shape shape3 = Triangle{ 3.0f, 4.0f };

    // 使用 std::visit 来访问不同的形状
    std::visit(ShapePrinter{}, shape1);
    std::visit(ShapePrinter{}, shape2);
    std::visit(ShapePrinter{}, shape3);
    std::cout << std::endl;



    return 0;
}
//
//std::visit 的作用： 
// std::visit 根据 variant 当前存储的类型，
// 调用传入的访问者（如 ShapePrinter）。
// 访问者需要对 std::variant 中可能的每个类型都定义一个重载的 
// operator()，以便处理所有类型的情况。