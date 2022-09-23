#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStack>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始话
void MainWindow::init()
{
    //表达式清空
    m_inputExpression.clear();
    m_endExpression.clear();
    //输入框初始化
    ui->Output->setText("0");
    m_isError = false;
    m_isDecimal  = false;
}

//获取后缀表达式
//将输入框中的中缀表达式转变成后缀表达式
//“ ”（空格）为分隔符
void MainWindow::setEndExpression()
{
    m_inputExpression = ui->Output->text();
    qDebug() << m_inputExpression;
    QStack<QChar> stack; //用于存符号
    int countBracketLift = 0; //用于左括号计数
    for(auto it=m_inputExpression.begin();it!=m_inputExpression.end();it++)
    {
        if( ((*it)>=QChar('0')&&(*it)<=QChar('9'))|| (*it)==QChar('.') ) //数字或者小数点，直接添加
        {
            m_endExpression.append(*it);
        }
        else if((*it)==QChar('(')) //左括号，直接入栈
        {
            countBracketLift++;
            stack.push(*it);
        }
        else if((*it)==QChar(')')) //右括号，弹出直到遇到左括号
        {
            if(countBracketLift<1)
            {
                m_isError = true; //错误
                break;
            }
            while(stack.top()!=QChar('('))
            {
                m_endExpression.append(' '+stack.pop()); //分隔符和弹出运算符
            }
            countBracketLift--;
            stack.pop(); //弹出左括号
        }
        else if((*it)==QChar('*')||(*it)==QChar('/')) //乘除号，直接入栈
        {
            stack.push(*it);
            m_endExpression.append(" "); //加入分割号
        }
        else //加减号
        {
            if(stack.empty()) //栈为空，直接入栈
            {
                m_endExpression.append(" ");
            }
            else //弹出优先级比加减高，或者同级的运算符
            {
                while(!stack.empty())
                {
                    if(stack.top()==QChar('(')) //左括号只能是遇到右括号才可以弹出
                    {
                        break;
                    }
                    else //否则，弹出栈前面乘除和加减的符号
                    {
                        m_endExpression.append(' '+stack.pop());
                    }
                }
                m_endExpression.append(" "); //最后加入分隔符
            }
            stack.push(*it); //入栈
        }
    }
    while(!stack.empty()) //最后弹出栈中剩下的符号
    {
        m_endExpression.append(' '+stack.pop());
    }
}

//计算后缀表达式，并输出到界面中
void MainWindow::calEndExpression()
{
    qDebug() << m_endExpression;
    if(m_isError) //如果错误
    {
        ui->Output->setText("错误");
        qDebug() << "括号合法";
        return;
    }
    QStack<double> stack; //用于存算数
    QStringList  endExpression = m_endExpression.split(" "); //以空格分隔
    for(int i=0;i<endExpression.count();i++)
    {
        if(endExpression[i]=="+") //加法
        {
            if(stack.size()<2)
            {
                ui->Output->setText("错误");
                qDebug() << "没有足够的数";
                return;
            }
            double ans = stack.pop() + stack.pop() ;
            stack.push(ans);
        }
        else if(endExpression[i]=="-") //减法
        {
            if(stack.size()<2)
            {
                ui->Output->setText("错误");
                qDebug() << "没有足够的数";
                return;
            }
            double a = stack.pop();
            double b = stack.pop();
            double ans = b - a; //栈的储存是相反的
            stack.push(ans);
        }
        else if(endExpression[i]=="*") //乘法
        {
            if(stack.size()<2)
            {
                ui->Output->setText("错误");
                qDebug() << "没有足够的数";
                return;
            }
            double ans = stack.pop() * stack.pop() ;
            stack.push(ans);
        }
        else if(endExpression[i]=="/") //除法
        {
            if(stack.size()<2)
            {
                ui->Output->setText("错误");
                qDebug() << "没有足够的数";
                return;
            }
            double a = stack.pop();
            double b = stack.pop();
            if(a==0)
            {
                ui->Output->setText("错误");
                qDebug() << "被除数不能为0";
                return;
            }
            double ans = b / a;
            stack.push(ans);
        }
        else
        {
            stack.push(endExpression[i].toDouble());
        }
    }
    if(stack.size()==1)
    {
        ui->Output->setText(QString::number(stack.pop(),'f',10));
        //表达式清空
        m_inputExpression.clear();
        m_endExpression.clear();
        m_isDecimal = true;
    }
    else
    {
        qDebug() << "不仅仅余省一个数字结果";
        ui->Output->setText("错误");
    }
}

//数字按钮实现逻辑
void MainWindow::numberBtn()
{
    QString num = ((QPushButton*)sender())->text(); //获取按钮txt数字
    QString s = ui->Output->text(); //获取现在输入框中的内容
    if(s=="0") //去0
        ui->Output->setText(num);
    else
        ui->Output->setText(s.append(num));
}

//符号按钮实现逻辑
void MainWindow::signBtn()
{
    QString sign = ((QPushButton*)sender())->text(); //获取按钮txt符号
    QString out = ui->Output->text();
    if(out.right(1) != "/" && out.right(1) != "*"&& out.right(1) != "-"&& out.right(1) != "+" && out.right(1) != "(")
    {
        ui->Output->setText(out.append(sign));
        m_isDecimal = false;
    }
}

//数字按钮的槽函数
void MainWindow::on_Btn1_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn2_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn3_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn4_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn5_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn6_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn7_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn8_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn9_clicked()
{
    numberBtn();
}

void MainWindow::on_Btn0_clicked()
{
    numberBtn();
}

//除按钮
void MainWindow::on_BtnDivision_clicked()
{
    signBtn();
}

//乘按钮
void MainWindow::on_BtnMultiplication_clicked()
{
    signBtn();
}

//减按钮
void MainWindow::on_BtnSubtraction_clicked()
{
    signBtn();
}

//加按钮
void MainWindow::on_BtnAdd_clicked()
{
    signBtn();
}

//删除后退一个按钮
void MainWindow::on_BtnDrawBack_clicked()
{
    QString out = ui->Output->text();
    if(out!="" && out!="0") //已经为空了不可以删除
    {
        QString del = out.right(1); //获取要删除的符号
        if(del==".")//如果要删除的是小数点
            m_isDecimal = false;
        ui->Output->setText(out.left(out.size()-1));
    }
}

//全部清除按钮
void MainWindow::on_BtnAC_clicked()
{
    init();
}

//左括号按钮
void MainWindow::on_BtnBracketLift_clicked()
{
    QString sign = "(";
    QString s = ui->Output->text();
    if(s=="0")
        ui->Output->setText(sign);
    else
        ui->Output->setText(s.append(sign));
}

//右括号按钮
void MainWindow::on_BtnBracketRight_clicked()
{
    QString sign = ")";
    QString out = ui->Output->text();
    if(out.right(1) != "/" && out.right(1) != "*"&& out.right(1) != "-"&& out.right(1) != "+" && out.right(1) != "("
            && out!="" && out!="0")
        ui->Output->setText(out.append(sign));
}

void MainWindow::on_BtnEqual_clicked()
{
    setEndExpression(); //表达式转成后缀表达式
    calEndExpression(); //后缀表达式的计算，并显示结果
}

void MainWindow::on_BtnDecimal_clicked()
{
    if(!m_isDecimal) //防止一个数字里面有两个小数点
    {
        m_isDecimal = true;
        QString s = ui->Output->text();
        ui->Output->setText(s.append("."));
    }
}
