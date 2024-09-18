#pragma once
#include  <json.h>     // 引用
#include <iostream>
#include <fstream>
using namespace std;

class JsonClass
{
public:

	void writeJsonFileTest(const std::string& filename);
	void readJsonFileTest(const std::string& filename);
};

