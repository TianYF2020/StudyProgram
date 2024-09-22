#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StudyC.h"

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
private:
    Ui::StudyCClass ui;
};
