#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StudyC.h"
#include "iostream"
#include "TempLateClass.h"
#include "TempLateClass.hpp"
#include "FunCallBack.h"
#include "SmartPointer.h"
#include "NamespaceClass.h"
#include "VariantClass.h"
#include "OperatorClass.h"
#include "CompileClass.h"
#include "ConstructorClass.h"
#include "JsonClass.h"
#include "LambdaClass.h"
#include "MagicEnum.h"
#include "CommonTest.h"
#include "STLFuntion.h"
#include "ReflectFun.h"
#include "KeyWord.h"
#include "VarParamClass.hpp"
#include "CommonThread.h"

class StudyC : public QMainWindow
{
    Q_OBJECT

public:
    StudyC(QWidget *parent = nullptr);
    ~StudyC();
    void TestC();
    void TestJson();
    void TestThreadFuntion();
    void TestCompileProperty();
    void TestConstructor();

    void TestSTL();

    void TestTemplate();

    void TestReflectFun();

    void TestKeyword();
private:
    Ui::StudyCClass ui;
};
