#include <iostream>


class MyBaseClass
{
public:
    MyBaseClass() = default;  // 禁止默认构造，。
    MyBaseClass(std::string str):name(str) {};  // 禁止默认构造，。
    // 把父类的析构函数定义成虚函数，保证子类的析构能执行    
    virtual ~MyBaseClass() = default;   // 使用默认构造,可以把=default理解成{}

    int func()  = delete; // 函数被删除，不能使用

    virtual void runWork()  // 函数执行
    {
        std::cout << "MyBaseClass runing work..." << std::endl;
    }

protected:  //子类可以访问
    std::string name;
private:    // 子类无法访问
    int * ptr_a = nullptr; //空指针常量（C++11引入）
};


class MyTestClass : public MyBaseClass
{
public:
    MyTestClass() = default; //
    MyTestClass(std::string strs) : MyBaseClass(name) {};

    ~MyTestClass();
    void runWork() override         // 会检查函数名和父类时候一样
    {
        std::cout << "MyTestClass runing work..." << std::endl;
    }  
private:
    std::string sName;

};