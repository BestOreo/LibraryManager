#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include <QDebug>
#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include "stumainwindow.h"
#include "managermainwindow.h"
#include <QButtonGroup>>
#include <iostream>
#include <QDebug>



QString user_id;
QButtonGroup *btnGroup;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap pixmap(":/Action/background.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);  //避免其余空间继承StyleSheet



    QPixmap apixmap(":/Action/search.png");
    ui->search->setPixmap(apixmap);
    ui->search->show();



   // ui->name-setLayout(lay);
    //ui->name->setFrame(false);
    //ui->name->setStyleSheet("QLineEdit{ background-color: rgba(255,255,255,255); }QLineEdit:focus{background-color: rgb(255,255,255)}"); // 设置样式
    //ui->name->setTextMargins(0, 0, 30, 0); // 注意这里的30  因为图一的输入框最右边有个按钮。不能让光标在此区域出现。。需要设置文字显示范围
    ui->name->setPlaceholderText(tr("  用户名"));  // 设置默认文字
    ui->passward->setPlaceholderText(tr("  密码"));  // 设置默认文字


    ui->loginButton->setStyleSheet("QPushButton{background-color:rgb(55,111,166,80%);\
                                    color: white;   border-radius: 10px;  border: 2px groove gray;\
                                    border-style: outset;font:15pt 隶书}"
                                   "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                                                   border-style: inset; }"
                                   );

    btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->stuRadioButton, 0);
    btnGroup->addButton(ui->managerRadioButton, 1);
    ui->stuRadioButton->setChecked(true);



}

void MainWindow::on_loginButton_clicked()
{
    if(  btnGroup->checkedId()==0) // 表示是学生
    {
        QSqlQuery query;
        query.prepare("select Username, Password from user where Username = :Username and Password = :Password");
        query.addBindValue(ui ->name ->text());
        query.addBindValue(ui ->passward -> text());
        query.exec();
        if(query.next() == NULL){
            //ui->userLineEdit -> clear();
            ui->name->setFocus();
            ui->passward->clear();
            QMessageBox::about(this,"可不要调戏我哦~","苟利国家生死以，岂因祸福避趋之！\n"
                                           "我本将心向明月，奈何明月照沟渠！\n"
                                           "请问您是不是记混LOL的密码了？O(∩_∩)O哈哈~");
            this->show();
         }
        else
        {
            user_id = ui->name->text().trimmed();
            qDebug("%s", qPrintable( user_id ) );
            StuMainWindow *stuwindow = new StuMainWindow;
            stuwindow->setWindowTitle("欢迎使用浙江大学图书管理系统");
            stuwindow->show();
            this->close();
        }
    }
    else if (  btnGroup->checkedId() == 1) // 表示是管理员
    {
        if( ui->name->text() == tr("") && ui->passward->text() == tr("") )
        {
            ManagerMainWindow *ma = new ManagerMainWindow;
            ma->setWindowTitle("管理员您好");
            ma->show();
            this->close();
        }
        else
        {
            ui->name->setFocus();
            ui->passward->clear();
            QMessageBox::about(this,"可不要调戏我哦~","苟利国家生死以，岂因祸福避趋之！\n"
                                           "我本将心向明月，奈何明月照沟渠！\n"
                                           "请问管理员您是不是记混LOL的密码了？O(∩_∩)O哈哈~");
            this->show();
        }
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}
