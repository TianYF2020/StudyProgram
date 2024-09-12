#include "StudyC.h"
#include "VarParamClass.h"
#include "TempLateClass.h"
#include "FunCallBack.h"
#include "SmartPointer.h"
#include "NamespaceClass.h"
#include "VariantClass.h"
#include "OperatorClass.h"
#include "ThreadClass.h"
#include "CompileClass.h"
#include "ThreadAsync.h"

StudyC::StudyC(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //TestC();
    TestThreadFuntion();

    //TestCompileProperty();
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

 
}


void StudyC::TestThreadFuntion()
{
    cout << "------Test thread function" << endl;
    TestThreadFunction();
    cout << "------Test thread class function" << endl;
    TestThreadClassFunction();
    cout << "\n------Test async thread function" << endl;
    testThreadAsync();
}


void StudyC::TestCompileProperty()
{
    testCompile();
}