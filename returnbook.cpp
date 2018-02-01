#include "returnbook.h"
#include "ui_returnbook.h"
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>

ReturnBook::ReturnBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);
}

void ReturnBook::on_Enter_clicked()
{
    QSqlQuery query,queryupdate,queryfind;
    QString lenderid,bookid;
    lenderid = ui->ID->text();
    bookid = ui->BookID->text();

    queryfind.prepare("select username, bno from loan where username = :username and bno = :bookid");
    queryfind.addBindValue(ui ->ID ->text());
    queryfind.addBindValue(ui ->BookID -> text());
    queryfind.exec();
    if(queryfind.next() == NULL){
        QMessageBox msg(QMessageBox::Warning, tr("信息错误"), tr("错误"), QMessageBox::Yes, NULL);
        msg.exec();
     }


    else
    {
         if(query.exec(QString("delete from loan where username = '"+lenderid+"' and bno = '"+bookid+"' ")))
         {

             qDebug ("%s", "delete succeed");
             queryupdate.exec(QString("update book set stock = stock+1 where  bno = '"+bookid+"' "));
             QMessageBox msg(QMessageBox::Warning, tr("归还成功"), tr("书籍归还成功"), QMessageBox::Yes, NULL);
             msg.exec();
             this->close();
         }
         else
         {
             QMessageBox msg(QMessageBox::Warning, tr("信息输入错误"), tr("可能您的ID或者书序列号不正确。"), QMessageBox::Yes, NULL);
             msg.exec();
         }
    }
}

ReturnBook::~ReturnBook()
{
    delete ui;
}
