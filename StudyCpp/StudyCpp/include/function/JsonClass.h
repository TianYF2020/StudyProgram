#pragma once
#include  <json.h>     // 引用
#include <iostream>
#include <fstream>
using namespace std;

class JsonClass
{
public:
	JsonClass();

	~JsonClass() = default;

	void writeJsonFileTest(const std::string& filename);
	void readJsonFileTest(const std::string& filename);
	void writeNlohmannJsonFileTest(const std::string& filename);
	void readNlohmannJsonFileTest(const std::string& filename);
};

