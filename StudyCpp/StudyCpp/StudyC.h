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
    void TestThreadFuntion();
    void TestCompileProperty();
private:
    Ui::StudyCClass ui;
};
