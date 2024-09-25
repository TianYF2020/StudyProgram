#include <CommonTest.h>

template <typename T1,typename T2>
class Student
{
    // 定义了一个友元函数，也是全局函数，卸载类里面了，友元函数的类内实现
    // 如果去掉friend 关键字会报错
    // 类内实现，不是类的成员函数了，不能使用this指针了 
    friend void PrintfS(Student<T1, T2>& p)
    {
        std::cout << "Student(" << p.m_name << ", " << p.m_age << ")" << std::endl;
        p.showme();
    }


public:
    Student(T1 name,T2 score)
    {
        this->m_name = name;
        this->m_score = score;
    }

    void showme()
    {
        std::cout << "我是:" << this->m_name << " 分值:" << this->m_score << std::endl;
    }

private:
    T1 m_name;
    T2 m_score;
};


//类外定义友元函数
//提前让编译器知道类的存在
template <typename T1,typename T2>
class StudentDetach;
//提前让编译器知道这个函数的存在
template <typename T1,typename T2>
void PrintfS(StudentDetach<T1, T2>& p);


template <typename T1,typename T2>
class StudentDetach
{
    // 定义了一个友元函数，也是全局函数，卸载类里面了，友元函数的类内实现
    // 如果去掉friend 关键字会报错
    // 类内实现，不是类的成员函数了，不能使用this指针了 
    friend void  PrintfS<>(StudentDetach<T1, T2>& p);
public:
    StudentDetach(T1 name,T2 score)
    {
        this->m_name = name;
        this->m_score = score;
    }

    void showme()
    {
        std::cout << "我是:" << this->m_name << " 分值:" << this->m_score << std::endl;
    }

private:
    T1 m_name;
    T2 m_score;
};

//类外定义
template <typename T1,typename T2>
void PrintfS(StudentDetach<T1, T2>& p)
{
    std::cout << "Student(" << p.m_name << ", " << p.m_age << ")" << std::endl;
    p.showme();
}
