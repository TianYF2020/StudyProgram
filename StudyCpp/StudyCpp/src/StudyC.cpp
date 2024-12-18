﻿#include "StudyC.h"



StudyC::StudyC(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); 

    TestThreadBlock();

    // testOperator();

    // TestC();

    // TestBarrier();
    
    // TestCommonThread();
    
    // TestThreadFuntion();

    //TestCompileProperty();

    // TestJson();


    //测试构造
    // TestConstructor();

    // TestSTL();
    
    // TestTemplate();

    // TestReflectFun();

    // TestKeyword();

    // mPrint("first", 2, "third", 3.14159);
}

StudyC::~StudyC()
{

}

void StudyC::TestC()
{
 

    //多参数输入
    C_TestVarParam temp;
    temp.PrintNumbers(1,2,3,4,6);

    PrintValues(42, 3.14, "hello");
    PrintValues("world", 123, 9.81);

    //模版类
    C_TempLateClass<int> temp1;
    temp1.Compare(1,2);

    //回调函数
    testCallBack();

    //智能指针
    testSmartPtr();

    //测试命名空间
    testNamespace();

    //测试赛variant变量
    testVariant();

    //测试运算符
    testOperator();

    //测试lambda函数
    LambdaClass lamb;
    lamb.testLambdaFuntion();

    //测试枚举转字符和索引  会增加代码行数
    testMagicEnum();


}


void StudyC::TestThreadFuntion()
{
    std::cout << "------Test thread function" << std::endl;
    TestThreadFunction();
    std::cout << "------Test thread class function" << std::endl;
    TestThreadClassFunction();
    std::cout << "\n------Test async thread function" << std::endl;
    testThreadAsync();

    std::cout << "\n------Test mutex " << std::endl;
    TestMutex();
}


void StudyC::TestCompileProperty()
{
    testCompile();
}

void StudyC::TestJson()
{
    JsonClass testJson;
    testJson.writeJsonFileTest("test.json");
    testJson.readJsonFileTest("test.json");

    string path = "./config/";
    createDirectory(path);
    testJson.writeNlohmannJsonFileTest(path+"nlohmann.json");
    testJson.readNlohmannJsonFileTest(path+"nlohmann.json");
}


void StudyC::TestConstructor()
{
    testConstructor();
}


void StudyC::TestSTL()
{
    testPair();
}

void StudyC::TestTemplate()
{
    testTempLate();
}

void StudyC::TestReflectFun()
{
    testRefectFuntion();
}


void StudyC::TestKeyword()
{
    testAllKeyWord();
}

