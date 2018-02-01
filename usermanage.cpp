#include "usermanage.h"
#include "ui_usermanage.h"
#include <QSqlQuery>
#include <QMessageBox>

UserManage::UserManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
    int i;

    QSqlQuery query,childquery,myquery;
    int count = 0;
    int mycount = 0;
    int rows;
    //表格格式形状的一些设定
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //只读
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidget->setColumnCount(4);//设置列
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("学号")<<tr("姓名")<<tr("学院")<<tr("学位"));

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableWidget->setShowGrid(false);  // disable the table grid.
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(45);  // set row height.
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget->setFrameShape(QFrame::NoFrame);

    ui->tableWidget->setColumnWidth(0, 60);
    ui->tableWidget->setColumnWidth(1, 80);
    ui->tableWidget->setColumnWidth(2, 120);
    ui->tableWidget->setColumnWidth(3, 80);

    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //只读
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidget_2->setColumnCount(3);//设置列
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<tr("书号")<<tr("书名")<<tr("借书时间"));

    ui->tableWidget_2->verticalHeader()->hide();
    ui->tableWidget_2->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableWidget_2->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableWidget_2->setShowGrid(false);  // disable the table grid.
    ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(45);  // set row height.
    ui->tableWidget_2->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget_2->setFrameShape(QFrame::NoFrame);

    ui->tableWidget_2->setColumnWidth(0, 80);
    ui->tableWidget_2->setColumnWidth(1, 140);
    ui->tableWidget_2->setColumnWidth(2, 40);

    myquery.exec(QString("select cno, name, department, type from card, user where Username = cno  "));
    while(myquery.next())// UI界面显示表格
    {

        rows = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rows);
        QString myele0 = myquery.value(0).toString();
        QString myele1 = myquery.value(1).toString();
        QString myele2 = myquery.value(2).toString();
        QString myele3 = myquery.value(3).toString();

        ui->tableWidget->setItem(mycount, 0, new QTableWidgetItem(myele0));
        ui->tableWidget->setItem(mycount, 1, new QTableWidgetItem(myele1));
        ui->tableWidget->setItem(mycount, 2, new QTableWidgetItem(myele2));
        ui->tableWidget->setItem(mycount, 3, new QTableWidgetItem(myele3));

        mycount++;
    }



}

void UserManage::update()
{
    QSqlQuery myquery;
    int mycount = 0;
    int rows;
    myquery.exec(QString("select cno, name, department, type from card, user where Username = cno  "));
    while(myquery.next())// UI界面显示表格
    {

        rows = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rows);
        QString myele0 = myquery.value(0).toString();
        QString myele1 = myquery.value(1).toString();
        QString myele2 = myquery.value(2).toString();
        QString myele3 = myquery.value(3).toString();

        ui->tableWidget->setItem(mycount, 0, new QTableWidgetItem(myele0));
        ui->tableWidget->setItem(mycount, 1, new QTableWidgetItem(myele1));
        ui->tableWidget->setItem(mycount, 2, new QTableWidgetItem(myele2));
        ui->tableWidget->setItem(mycount, 3, new QTableWidgetItem(myele3));

        mycount++;
    }
}

void UserManage::on_addButton_clicked()
{
    QString cno = ui->id->text();
    QSqlQuery myquery;
    bool isok;
    myquery.exec(QString("select * from user where username = '%1'").arg(cno));
    if(myquery.next() != NULL)
    {
         QMessageBox::about(NULL,"警告!", "此人已存在!");
    }
    else
    {
        isok = myquery.exec(QString("insert into user values('%1','%2')").arg(cno).arg(cno));
        if(isok == true)
        {
            QMessageBox::about(NULL,"成功!", "新增用户成功!");

            int mycount = 0;
            int rows;
            myquery.exec(QString("select cno, name, department, type from card, user where Username = cno  "));
            while(myquery.next())// UI界面显示表格
            {

                rows = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rows);
                QString myele0 = myquery.value(0).toString();
                QString myele1 = myquery.value(1).toString();
                QString myele2 = myquery.value(2).toString();
                QString myele3 = myquery.value(3).toString();

                ui->tableWidget->setItem(mycount, 0, new QTableWidgetItem(myele0));
                ui->tableWidget->setItem(mycount, 1, new QTableWidgetItem(myele1));
                ui->tableWidget->setItem(mycount, 2, new QTableWidgetItem(myele2));
                ui->tableWidget->setItem(mycount, 3, new QTableWidgetItem(myele3));

                mycount++;
            }
        }
        else
            QMessageBox::about(NULL,"警告!", "新增用户失败!");
    }
}

void UserManage::on_deleteButton_clicked()
{
    QString cno = ui->id->text();
    QSqlQuery myquery;
    bool isok;

    myquery.exec(QString("select * from user where username = '%1'").arg(cno));

    if(myquery.next() == NULL)
    {
         QMessageBox::about(NULL,"警告!", "此人不存在!");
         return;
    }
    myquery.exec(QString("select * from loan where username = '%1'").arg(cno));
    if(myquery.next() != NULL)
    {
         QMessageBox::about(NULL,"警告!", "此用户尚有借书!不得删除!");
    }
    else
    {
        isok = myquery.exec(QString("delete from user where username = '%1'").arg(cno));
        if(isok == true)
        {
            QMessageBox::about(NULL,"成功!", "删除用户成功!");
            //UserManage::update();

        }
        else
            QMessageBox::about(NULL,"失败!", "删除用户失败!");
    }
}

void UserManage::on_searchButton_clicked()
{
    QSqlQuery myquery;
    QString cno = ui->id->text();
    int rows, mycount = 0;

    for (int i = ui->tableWidget_2->rowCount();i >= 0;i--)
     {
        ui->tableWidget_2->removeRow(i);
     }


    myquery.exec(QString("select loan.bno,book.title,loan.loan_date from loan,book where loan.bno = book.bno and loan.username = '%1'  ").arg(cno));
    while(myquery.next())// UI界面显示表格
    {
        rows = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rows);
        QString ele0 = myquery.value(0).toString();
        QString ele1 = myquery.value(1).toString();
        QString ele2 = myquery.value(2).toString();

        ui->tableWidget_2->setItem(mycount, 0, new QTableWidgetItem(ele0));
        ui->tableWidget_2->setItem(mycount, 1, new QTableWidgetItem(ele1));
        ui->tableWidget_2->setItem(mycount, 2, new QTableWidgetItem(ele2));

        mycount++;
    }

}

UserManage::~UserManage()
{
    delete ui;
}
