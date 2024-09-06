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
private:
    Ui::StudyCClass ui;
};
