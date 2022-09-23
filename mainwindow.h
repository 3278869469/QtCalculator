// -------------------------------------------------------
// mainwindow.h
// 创建者： 姚钰茗
// 创建时间： 2022/4/24
// 功能描述： 计数器的基本基本功能实现
// Copyright 2022 YaoYuming
// -------------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setEndExpression(); //获取后缀表达式
    void calEndExpression(); //计算后缀表达式
    void init();//初始化
    void numberBtn();//数字按钮
    void signBtn();//符号按钮

private slots:
    void on_Btn1_clicked();

    void on_Btn2_clicked();

    void on_Btn3_clicked();

    void on_Btn4_clicked();

    void on_Btn5_clicked();

    void on_Btn6_clicked();

    void on_Btn7_clicked();

    void on_Btn8_clicked();

    void on_Btn9_clicked();

    void on_Btn0_clicked();

    void on_BtnDivision_clicked();

    void on_BtnMultiplication_clicked();

    void on_BtnSubtraction_clicked();

    void on_BtnAdd_clicked();

    void on_BtnDrawBack_clicked();

    void on_BtnAC_clicked();

    void on_BtnBracketLift_clicked();

    void on_BtnBracketRight_clicked();

    void on_BtnEqual_clicked();

    void on_BtnDecimal_clicked();

private:
    Ui::MainWindow *ui;
    QString m_inputExpression; //输入的表达式
    QString m_endExpression; //后缀表达式
    bool m_isError; //记录错误，表达式错误为true，否则为false
    bool m_isDecimal; //记录小数点是否已经输入，一个数里面不可以有重复的小数点，当前输入为整数时为false，为小数时为true
};

#endif // MAINWINDOW_H
