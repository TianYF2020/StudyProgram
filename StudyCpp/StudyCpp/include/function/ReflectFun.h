#include <iostream>
#include <vector>
using namespace std;
struct Person {
    std::string first_name;
    std::string last_name;
    int age;
    std::vector<int> longth;


    // 友元函数重载 << 运算符
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "(" << p.first_name << ", " << p.last_name << "," << p.age <<")";
        return os;
    }
};


extern int testRefectFuntion();
