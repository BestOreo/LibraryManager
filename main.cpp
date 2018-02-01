#include <QApplication>
#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <QSqlQuery>
#include <QMessageBox>
#include <mainwindow.h>


int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    QSqlDatabase dbconn;

    dbconn = QSqlDatabase::addDatabase("QODBC");
    dbconn.setHostName("localhost");
    dbconn.setPort(3306);
    dbconn.setDatabaseName("my32");
    dbconn.setUserName("root");
    dbconn.setPassword("302899");


    if(!dbconn.open())
     {
       qDebug("数据库打开失败");
       exit(1);
      }
      else
      {
         qDebug()<<"成功连接数据库";
        // qDebug()<<dbconn.lastError()
      }

    MainWindow w;
    w.setWindowTitle("欢迎使用浙江大学图书管理系统");
    w.show();

    return a.exec();
}
