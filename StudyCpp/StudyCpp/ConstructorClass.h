#pragma once
#include <iostream>
#include <vector>
class ConstructorClass
{
public:
	//无参数构造
	//ConstructorClass() {};

	//构造函数
	ConstructorClass(int x, const std::string& y) : num(x), str(y)
	{
		std::cout << "Constructor Class with num = " << num << " and str = " << str << std::endl;
	}

	//拷贝构造函数
	ConstructorClass(const ConstructorClass &other) : num(other.num), str(other.str)
	{
		std::cout << "Copying Constructor Class with num = " << num << " and str = " << str << std::endl;
	}
	//noexcept 是 C++11 引入的一个关键字，用于声明函数不会抛出异常。它的主要作用是告知编译器和程序员，该函数在执行过程中不会抛出任何异常，编译器可以进行一些优化。

	//移动构造函数
	ConstructorClass(ConstructorClass &&other) noexcept : num(std::move(other.num)), str(std::move(other.str))
	{
		std::cout << "Moving Constructor Class with num = " << num << " and str = " << str << std::endl;
	}


	//构造函数
	~ConstructorClass()
	{
		std::cout << "Destructing Class with num = " << num << " and str = " << str << std::endl;
	}

private:

	int num;
	std::string str;
};



extern int testConstructor();


