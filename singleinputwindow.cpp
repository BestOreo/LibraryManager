#include "singleinputwindow.h"
#include "ui_singleinputwindow.h"
#include <QSqlQuery>
#include <QMessageBox>

SingleInputWindow::SingleInputWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingleInputWindow)
{
    ui->setupUi(this);
}

void SingleInputWindow::on_InputButton_clicked()
{
    QSqlQuery query;
    QString sql;
    QString bno , category, title , press , author ;
    int  total , year;
    float price;
    bool isok;

    bno = ui->lineEdit_bno->text();
    category = ui->lineEdit_category->text();
    title = ui->lineEdit_title->text();
    press = ui->lineEdit_press->text();
    author = ui->lineEdit_aurhor->text();
    total = ui->lineEdit_num->text().toInt();
    year = ui->lineEdit_year->text().toInt();
    price = ui->lineEdit_price->text().toFloat();

    if(query.next() != NULL)
    {
        isok = query.exec(QString("update book set total = total + %1, stock = stock + %2 where bno = '%3' ").arg(total).arg(total).arg(bno));
    }
    else
    {

         sql = QString("insert into book values('%1', '%2', '%3', '%4', %5 , '%6', %7, %8, %9)")
                 .arg(bno)
                 .arg(category)
                 .arg(title)
                 .arg(press)
                 .arg(year)
                 .arg(author)
                 .arg(price)
                 .arg(total)
                 .arg(total);
         isok = query.exec(sql);
    }
    if(isok == true)
        QMessageBox::about(NULL,"提示!", "书籍增加成功!");
    else
        QMessageBox::about(NULL,"提示!", "书籍增加失败!");

}

void SingleInputWindow::on_CancelButton_clicked()
{
    this->close();
}

SingleInputWindow::~SingleInputWindow()
{
    delete ui;
}
