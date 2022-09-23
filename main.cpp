// -------------------------------------------------------
// main.cpp
// 创建者： 姚钰茗
// 创建时间： 2022/4/24
// 功能描述： 窗口显示
// Copyright 2022 YaoYuming
// -------------------------------------------------------

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
