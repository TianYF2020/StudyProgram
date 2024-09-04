#include "StudyC.h"
#include "VarParamClass.h"
#include "TempLateClass.h"
StudyC::StudyC(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    TestC();
}

StudyC::~StudyC()
{

}

void StudyC::TestC()
{
    C_TestVarParam temp;
    temp.PrintNumbers(1,2,3,4,6);

    PrintValues(42, 3.14, "hello");
    PrintValues("world", 123, 9.81);

    C_TempLateClass<int> temp1;
    temp1.Compare(1,2);

}