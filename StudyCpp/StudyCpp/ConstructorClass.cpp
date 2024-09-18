#include "ConstructorClass.h"



int testConstructor()
{
	std::vector<ConstructorClass> vec;
	std::cout << "\n使用push_back" << std::endl;

	ConstructorClass obj(1, "First");
	std::cout << "Single ConstructorClass" << std::endl;

	vec.push_back(obj);   //1.在vector中构建一个，调用构建 
	//2、调用拷贝构造
	//3、调用析构

	vec.push_back(ConstructorClass(2, "Second"));
	//和上边比少了个拷贝构造

	std::cout << "\nemplace_back" << std::endl;
	//使用emplace_back 减少构造拷贝
	vec.emplace_back(3, "Third");
	 //

	std::cout << "end ___________________ " << std::endl << std::endl;
	return 0;
}