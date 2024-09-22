#include "LambdaClass.h"


LambdaClass::LambdaClass()
{

}

LambdaClass::~LambdaClass()
{

}

//相当于创建时候定义一个传参，定义一个+x的函数
std::function<int(int)> tadd_x(int x)
{
	return [=](int a) { return x + a; };
	// 	return [&](int a) { return x + a; };
};



void LambdaClass::testLambdaFuntion()
{
	// 定义了一个函数并执行了  // NOLINT
	std::cout << " Test lambda******" <<std::endl;
	auto basic = [] {std::cout << " Hellow world" << std::endl; };
	basic();

	auto add = [](int a,int b) -> int { return a+b;};

	int sum = add(2,5);
	std::cout << "sum " << sum << std::endl;

    int x = 3;
	auto add_x = [x](int a) { return a+x;};
	auto multiply_x = [&x](int a) { x = 20; return a * x; };  // 引用捕捉x
	std::cout << "copy value " << add_x(10)<< " " << multiply_x(10)  << " x = " << x << std::endl;

 	auto add_five = tadd_x(20);
	std::cout << add_five(100) << std::endl;

	// 利用表达式捕获，可以更灵活地处理作用域内的变量
	int s = 4;
	auto y = [&r = s, s = s + 1] { r += 2; return s * s; }();
	// 此时 x 更新为6，y 为25

	// 直接用字面值初始化变量
	auto z = [str = "string"]{ return str; }();
	// 此时z是const char* 类型，存储字符串 string


	auto myPi = std::make_unique<double>(3.1415);

	auto circle_area = [pi = std::move(myPi)](double r) { return *pi * r * r; };
	std::cout << circle_area(1.0) << std::endl; // 3.1415

	// 泛型自动推导
	auto Genericity = [](auto x, auto y) { return x + y; };
	int valuex = Genericity(2, 3);   // 5
	double valuey = Genericity(2.5, 3.5);  // 6.0
}

class Person
{
public:
	Person(int value) : age(value) {}
    Person() = default;
    int age;
};



void LambdaClass::testLambdaSTL()
{
	int value = 3;
	std::vector<int> v {1, 3, 5, 2, 6, 10};  // 序列号构造
	// std::vector<int> v {1, 3, 5, 2, 6, 10};  // 拷贝构造不推荐，编译器可能会解释成第一种
	int count = std::count_if(v.begin(), v.end(), [value](int x) { return x > value; });
    std::cout << "大于 " << value << " 的元素个数: " << count << std::endl;

	std::vector<int> v1(10);
	int a = 0;
	int b = 1;
	std::generate(v.begin(), v.end(), [&a, &b]() { int value = b; b = b + a; a = value; return value; });
	// 此时v {1, 1, 2, 3, 5, 8, 13, 21, 34, 55}


	//结构体对象排列
    std::vector<Person> vp= {{10}, {20}, {30}};
    std::sort(vp.begin(), vp.end(), [](const Person& p1, const Person& p2)
		{ 
			//返回值是真假
				return p1.age < p2.age;
		}
	);

}




// []：默认不捕获任何变量；
// [=]：默认以值捕获所有变量；
// [&]：默认以引用捕获所有变量；
// [x]：仅以值捕获x，其它变量不捕获；
// [&x]：仅以引用捕获x，其它变量不捕获；
// [=, &x]：默认以值捕获所有变量，但是x是例外，通过引用捕获；
// [&, x]：默认以引用捕获所有变量，但是x是例外，通过值捕获；
// [this]：通过引用捕获当前对象（其实是复制指针）；
// [*this]：通过传值方式捕获当前对象；