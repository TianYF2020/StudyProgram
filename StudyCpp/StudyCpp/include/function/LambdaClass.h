#pragma once
#include "functional"
#include <algorithm>
#include <vector>
#include <iostream>

class LambdaClass
{
public:
	LambdaClass();
	~LambdaClass();

	void testLambdaFuntion();

	void testLambdaSTL();

    // 获取一个lambda函数，通过传this指针的方法来捕获的内容
	std::function<bool(int)> getFilter() 
	{
		return [this](int value) {return value % this->m_value == 0; };
	}
private:
	int m_value = 10;

};

