#include <STLFuntion.h>
#include <stdio.h>
#include <random>

// #include <bits/stdc++.h> //涵盖C++所有库函数，用它就对了

int TestRandom()
{
    // 创建随机数生成器，使用当前时间作为种子
    std::random_device rd;  // 用于生成种子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 算法的随机数引擎

    // 生成一个范围在 [1, 100] 的随机整数
    std::uniform_int_distribution<> int_dis(1, 100);
    int random_int = int_dis(gen);
    std::cout << "随机整数: " << random_int << std::endl;

    // 生成一个范围在 [0.0, 1.0] 的随机浮点数
    std::uniform_real_distribution<> float_dis(0.0, 1.0);
    double random_float = float_dis(gen);
    std::cout << "随机浮点数: " << random_float << std::endl;

    return 0;
}

std::pair<std::string, int> getPreson()
{
    return std::make_pair("Sven", 25);
}

int cmp(std::pair<int, int> a, std::pair<int, int> b)
{
    if (a.first != b.first)
        return a.first > b.first;
    else
        return a.second < b.second;
}

struct Person {
    std::string name;
    int age;

    Person(const std::string& newName, int newAge) : name(newName), age(newAge) {}

    // 自定义比较函数
    struct Compare {
        bool operator() (const Person& a, const Person& b) const {
            return a.age < b.age;  // 按照年龄升序排列
        }
    };
};



int testPair()
{
    using namespace std;
    pair<int, double> p1;           // 使用默认构造函数
    pair<int, double> p2(1, 2.4);   // 用给定值初始化
    pair<int, double> p3(p2);       // 拷贝构
    pair<string, vector<int>> line; // 创建一个空对象line，两个元素类型分别是string和vector类型

    // 创建
    pair<int, double> p4 = make_pair(1, 1.2);
    pair<int, string> p5 = make_pair(1, "sttring");
    // 打印值
    cout << p1.first << ' ' << p1.second << endl;

    int ages;
    string name;
    // 在某些清况函数会以pair对象作为返回值时，可以直接通过std::tie进行接收。比如：
    std::tie(name, ages) = getPreson();
    std::cout << "name: " << name << ", ages: " << ages << std::endl;

    pair<int, int> pa[100];
    sort(pa, pa + 5);      // 默认排序
    sort(pa, pa + 5, cmp); // 自定义排序
    return 0;
}

#include <queue>

int testQueue()
{
    using namespace std;
    // q.front()	返回队首元素 O ( 1 ) O(1)O(1)
    // q.back()	返回队尾元素 O ( 1 ) O(1)O(1)
    // q.push(element)	尾部添加一个元素element 进队O ( 1 ) O(1)O(1)
    // q.pop()	删除第一个元素 出队 O ( 1 ) O(1)O(1)
    // q.resize(5); 调整大小
    // q.size()	返回队列中元素个数，返回值类型unsigned int O ( 1 ) O(1)O(1)
    // q.empty()	判断是否为空，队列为空，返回true O ( 1 ) O(1)O(1)
    // q.emplace(args); 构造元素并添加到队列末尾（C++11引入）
    // deque 是 double-ended queue（双端队列）的缩写，它允许在两端进行高效的插入和删除操作。也就是说，你可以在队列的前端和后端同时进行插入和删除操作。
    deque<int> myDeque({1, 3, 5, 7, 9, 11, 13, 15, 17, 19});
    
    // 访问
    myDeque[2] = 10;  // 修改第三个元素的值为10
    std::cout << myDeque.at(1) << " " <<  myDeque.at(2) << std::endl;  // 访问第二个元素
    
    // 增
    myDeque.push_back(100); // 入队尾部
    myDeque.push_front(0); // 入队尾部
    myDeque.insert(myDeque.begin() + 2, 6);    // 获取迭代器指向位置2

    //删
    myDeque.erase(myDeque.begin() + 3); // 删除指定位置的元素
    myDeque.pop_front();
    myDeque.pop_back();
    std::cout << "Deque:font " <<  myDeque.front() <<  " back " << myDeque.back() << std::endl;
    
    // 遍历
    for (auto it = myDeque.begin(); it != myDeque.end(); ++it) {
        std::cout << *it << " ";
    }

    for (const auto& element : myDeque) {
        std::cout << element << " ";
    }

    //排序
    std::sort(myDeque.begin(), myDeque.end(),[](int a,int b) {return abs(a) > abs(b);});

    //全部弹出
    queue<int> myQueue(myDeque);
    while (!myQueue.empty())
    {
        cout << myQueue.front() << " ";
        myQueue.pop();
    }
    myQueue.push(3);
     std::cout << "queue:font " <<  myQueue.front() <<  " back " << myQueue.back() << std::endl;
    
    
    return 0;
}

#include <iostream>
#include "queue"
#include <functional>
// 优先队列 只允许访问头
int testPriority_queue()
{
// push()	它将新元素插入优先队列。
// pop()	它将优先级最高的元素从队列中删除。
// top()	此函数用于寻址优先队列的最顶层元素。
// size()	返回优先队列的大小。
// empty()	它验证队列是否为空。基于验证，它返回队列的状态。
// swap()	它将优先队列的元素与具有相同类型和大小的另一个队列交换。
// emplace()	它在优先队列的顶部插入一个新元素。
    using namespace std;

    //构造
    priority_queue<int> p;  // 变量声明. 优先队列不支持序列化
    p.push(10); // 插入 10 到队列, top=10
    p.push(30); // 插入 30 到队列, top=30
    p.push(20); // 插入 20 到队列, top=20
    cout<<"可用元素的数量 到 'p' :"<<p.size()<<endl;
    while(!p.empty())
    {
        std::cout << p.top() << std::endl; 
        p.pop();
    }

    // 使用std::vector进行初始化
    std::vector<int> vec = {10, 30, 20};
    std::priority_queue<int> test(vec.begin(), vec.end());

    // 输出队列的最大元素
    std::cout << "最大元素: " << p.top() << std::endl;  // 输出 30

    //自定义排序规则的优先队列
    std::vector<int> vec1 = {10, 30, 20};
    std::priority_queue<int, std::vector<int>, std::greater<int>> custom(vec1.begin(), vec1.end());

    auto comparator = [](int a, int b) {
        return a > b;  // 降序
    };
    // 定义了一个
    priority_queue<int,vector<int>,decltype(comparator)> q(comparator);    //使用自定义比较方法


    struct CustomCompare {
    bool operator()(int a, int b) const {
            return a > b;  // 降序排序
        }
    };
    //第一个模板参数 T 是存储的元素类型（在你的例子中是 int）。第二个模板参数 Container 是用来存储元素的容器类型，第三个模板参数 Compare 是用来定义优先级队列的比较规则，
    std::priority_queue<int,vector<int>, CustomCompare> mySetCustomCompare;

    // 输出队列的最小元素
    std::cout << "最小元素: " << p.top() << std::endl;  // 输出 10

    return 0;
}






#include <stack>
//先进后出
int testStack()
{

    // s.front()	返回队首元素 O ( 1 ) O(1)O(1)
    // q.back()	返回队尾元素 O ( 1 ) O(1)O(1)
    // q.push(element)	尾部添加一个元素element 进队O ( 1 ) O(1)O(1)
    // q.pop()	删除第一个元素 出队 O ( 1 ) O(1)O(1)
    // q.resize(5); 调整大小
    // q.size()	返回队列中元素个数，返回值类型unsigned int O ( 1 ) O(1)O(1)
    // q.empty()	判断是否为空，队列为空，返回true O ( 1 ) O(1)O(1)
    // q.emplace(args); 构造元素并添加到队列末尾（C++11引入）
    using namespace std;
    stack<int> myStack({1, 3, 5, 7, 9, 11, 13, 15, 17, 19});
    int element = 100;
    myStack.push(element);
    myStack.pop();
    if (myStack.empty()) {
    // 栈为空
    }
    // 交换
    stack<int> myStack2;
    myStack2.swap(myStack);
    return 0;
}








#include <list>
int testList()
{
    using namespace std;

    // 构造
    std::list<int> list1 = {1, 2, 3};
    std::list<int> list2;
    list2 = list1; // 使用 operator= 进行赋值

    list2.assign(list1.begin(), list1.end()); // 使用 assign() 方法进行赋值

    // 交换
    std::list<int> list3 = {1, 2, 3};
    std::list<int> list4 = {4, 5, 6};
    list3.swap(list4); // 

    // 插入
    std::list<int> myList = {1, 2, 3};
    auto it = myList.begin();
    ++it; // 移动到第二个位置
    myList.insert(it, 4); // 在第二个位置插入元素 4
    myList.push_back(4); // 在末尾插入元素 4
    myList.push_front(0); // 在头部插入元素 0


    // 删除
    myList.pop_back(); // 删除末尾的元素
    myList.pop_front(); // 删除头部的元
    myList.erase(std::next(myList.begin(), 2)); // 删除第二个位置的元素

    std::list<int> myList1 = {1, 2, 2, 3, 2};
    myList1.remove(2); // 删除

    // 遍历 - 只能用迭代器访问
    for (auto it = myList.begin(); it != myList.end(); ++it) {
    std::cout << *it << " ";
    }

    for (auto value : myList) {
        std::cout << value << " ";  // 直接访问元素的值
    }

    // 列表移动
    std::list<int>::iterator it1;
    std::advance(it, 2); // `it` 被移动了2步，`it` 的值发生了改变

    std::list<int>::iterator it2 = std::next(it, 2); // `it` 不变，返回新的迭代器 `it2`

    // 翻转列表
    myList.reverse();

    // 排序列表（升序）
    myList.sort();
    
    return 0;
}



#include <set>
#include <map>
// 在C++中，std::set是一个用于存储唯一元素的有序集合容器  插入重复元素会被忽略。
// multiset 允许存储重复元素，即可以插入相同的元素多次。
int testSet()
{
    // begin()          // 返回指向set头部的迭代器
    // clear()         // 删除所有元素
    // count()          // 返回指定元素出现的次数
    // empty()         // 如果set为空则返回true
    // end()             // 返回指向set末尾的迭代器
    // erase()          // 删除一个元素
    // find()              // 查找一个元素
    // insert()           // 插入元素
    // max_size()     // 返回可以容纳的最大元素个数
    // size()              // 返回set中元素的个数
    // swap()            // 交换两个set
    using namespace std;

    //构造
    std::set<int> numbers = {1, 2, 3, 4, 5};

    std::vector<int> vec = {9, 8, 7};
    std::set<int> mySet(vec.begin(), vec.end()); // 使用迭代器范围进行构造

    std::set<int> set1 = {1, 2, 3};
    std::set<int> set2;
    set2 = std::move(set1);  // 移动set1的内容给set2，set1变为空

    //自定义排序
    auto comparator = [](int a, int b) {
        return a > b;  // 降序
    };
    std::set<Person, Person::Compare> personSet;

    //decltype ，用于推断表达式的类型,它可以在编译时自动获取变量或表达式的类型，而无需显式声明
    //auto 更加适合简化日常变量的声明，而 decltype 则在复杂的类型推断和模板编程中发挥了强大的作用。
    std::set<int, decltype(comparator)> customSet(comparator);
    customSet.insert(3);
    customSet.insert(1);
    customSet.insert(2);

    // 交换
    set1 = {1, 2, 3};
    set2 = {5,6,7};
    set1.swap(set2); // 交换set1和set2的内容

    //插入
    mySet.insert(4); // 插

    // 删除
    std::set<int> mySetValue = {1, 2, 3, 4};
    auto it = mySet.find(2);
    if (it != mySet.end()) {
        mySet.erase(it); // 通过迭代器 it 删除元素
    }
    mySetValue.erase(3); // 从 set 中删除值为 3 的元素
    mySetValue.clear(); // 清空 set 中的所有元素

    // 迭代
    std::set<int> mySetTemp = {1, 2, 2, 3, 3, 3};
    std::map<int, int> elementCount;
    for (int elem : mySetTemp) {
        elementCount[elem]++;
    }

    for (const auto& pair : elementCount) {
        std::cout << "元素 " << pair.first << " 出现次数为 " << pair.second << std::endl;
    }
    return 0;
}




#include <map>
int testMap()
{
    // begin()          // 返回指向map头部的迭代器
    // clear(）         // 删除所有元素
    // count()          // 返回指定元素出现的次数
    // empty()         // 如果map为空则返回true
    // end()             // 返回指向map末尾的迭代器
    // erase()          // 删除一个元素
    // find()              // 查找一个元素
    // insert()           // 插入元素
    // max_size()     // 返回可以容纳的最大元素个数
    // size()              // 返回map中元素的个数
    // swap()            // 交换两个map
    using namespace std;
    std::map<int, std::string> students = {{1, "Alice"}, {2, "Bob"}, {3, "Charlie"}};
    std::vector<std::pair<int, std::string>> studentList = {{1, "Alice"}, {2, "Bob"}, {3, "Charlie"}};
    students.insert(studentList.begin(), studentList.end());
    cout << students.size() << endl;

    // 自定义比较 lambda函数
    auto customCmp = [](int a,int b) {return a > b;};
    std::set<int, decltype(customCmp)> mySetCustom(customCmp);  // 不能构造了，只能插值了
     mySetCustom.insert(30);


    
    // 自定义比较，结构体
    struct CustomCompare {
        bool operator()(int a, int b) const {
            return a > b;  // 降序排序
        }
    };
    std::set<int, CustomCompare> mySetCustomCompare = {30, 10, 20, 50, 40};

    if (students.empty())
    {
        std::cout << "Map容器为空" << std::endl;
    }
    else
    {
        std::cout << "Map容器不为空" << std::endl;
    }


    // 自定义排序


    // map 交换
    std::map<int, std::string> students1 = {{1, "Alice"}, {2, "Bob"}};
    std::map<int, std::string> students2 = {{3, "Charlie"}, {4, "David"}};
    students1.swap(students2);
    // 打印交换后的结果
    for (const auto& student : students1)
    {
        std::cout << "学号: " << student.first << ", 姓名：" << student.second << std::endl;
    }

    for (const auto& student : students2)
    {
        std::cout << "学号: " << student.first << ", 姓名：" << student.second << std::endl;
    }

    // 使用insert函数插入元素
    students.insert(std::make_pair(1, "Alice"));
    students.insert(std::pair<int, std::string>(2, "Bob"));

    // 使用erase函数删除指定键的元素
    students.erase(1);

    // 使用迭代器遍历容器并删除特定条件的元素
    for (auto it = students.begin(); it != students.end();) {
        if (it->second == "Bob") {
            it = students.erase(it);
        } else {
            ++it;
        }
    }

    //查找
    auto it = students.find(2);
    if (it != students.end()) {
        std::cout << "学号为2的学生姓名是：" << it->second << std::endl;
    } else {
        std::cout << "未找到学号为2的学生" << std::endl;
    }

    // 排序
        std::vector<std::pair<int, std::string>> studentVector(students.begin(), students.end());
    // 按值排序vector
    std::sort(studentVector.begin(), studentVector.end(), [](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b)
        {   
            return a.second < b.second ;
        }
    );

    // 输出排序后的结果
    for (const auto& student : studentVector) {
        std::cout << "学号: " << student.first << ", 姓名: " << student.second << std::endl;
    }


    return 0;
}



