#include "managermainwindow.h"
#include "ui_managermainwindow.h"
#include <QSqlQuery>
#include <QString>
#include "returnbook.h"
#include <QFileDialog>
#include <QMessageBox>
#include <qtextstream.h>
#include <QDebug>
#include <qfile.h>
#include <QObject>
#include <qsqlrecord.h>
#include "singleinputwindow.h"
#include <usermanage.h>
#include <QBrush>
#include <QColor>

ManagerMainWindow::ManagerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerMainWindow)
{
    ui->setupUi(this);

    int count = 0;

    QPixmap pixmap(":/Action/Library.png"); // 背景美化
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);  //避免其余空间继承StyleSheet


    // 以下均为按键的样式美化
    ui->ReturnBook->setStyleSheet("QPushButton{background-color:rgb(241,193,118,80%);\
                                    color: white;   border-radius: 10px;  border: 2px groove gray;\
                                    border-style: outset;font:15pt 隶书}"
                                   "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                                                   border-style: inset; }"
                                   );
     ui->ReturnBook->setStyleSheet("QPushButton{background-color:rgb(241,193,118,80%);\
                                color: white;   border-radius: 10px;  border: 2px groove gray;\
                                border-style: outset;font:15pt 隶书}"
                               "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                                               border-style: inset; }"
                               );

    ui->SingleInput->setStyleSheet("QPushButton{background-color:rgb(241,193,118,80%);\
                               color: white;   border-radius: 10px;  border: 2px groove gray;\
                                border-style: outset;font:15pt 隶书}"
                                "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                                "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                                border-style: inset; }"
                               );
    ui->MultiInput->setStyleSheet("QPushButton{background-color:rgb(241,193,118,80%);\
                               color: white;   border-radius: 10px;  border: 2px groove gray;\
                               border-style: outset;font:15pt 隶书}"
                               "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                                "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                               border-style: inset; }"
                               );
    ui->UserManage->setStyleSheet("QPushButton{background-color:rgb(241,193,118,80%);\
                                color: white;   border-radius: 10px;  border: 2px groove gray;\
                                border-style: outset;font:15pt 隶书}"
                                "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                               "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                               border-style: inset; }"
                               );

    //表格美化
                                ui->stu_tableWidget->clearContents();
                                ui->stu_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //只读
                                ui->stu_tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
                                ui->stu_tableWidget->setColumnCount(5);//设置列
                                ui->stu_tableWidget->setRowCount(0);
                                ui->stu_tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("借书人")<<tr("学号")<<tr("书名")<<tr("书号")<<tr("借书时间"));

                                ui->stu_tableWidget->verticalHeader()->hide();
                                ui->stu_tableWidget->horizontalHeader()->setSectionsClickable(false);
                                ui->stu_tableWidget->horizontalHeader()->setStretchLastSection(true);
                                ui->stu_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                                ui->stu_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
                                ui->stu_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
                                ui->stu_tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
                                ui->stu_tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
                                ui->stu_tableWidget->setShowGrid(false);  // disable the table grid.
                                ui->stu_tableWidget->verticalHeader()->setDefaultSectionSize(35);  // set row height.
                                ui->stu_tableWidget->horizontalHeader()->setHighlightSections(false);
                                ui->stu_tableWidget->setFrameShape(QFrame::NoFrame);

                                ui->stu_tableWidget->setColumnWidth(0, 70);
                                ui->stu_tableWidget->setColumnWidth(1, 100);
                                ui->stu_tableWidget->setColumnWidth(2, 100);
                                ui->stu_tableWidget->setColumnWidth(3, 100);
                                ui->stu_tableWidget->setColumnWidth(4, 140);


                                ui->book_tableWidget->clearContents();
                                ui->book_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //只读
                                ui->book_tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
                                ui->book_tableWidget->setColumnCount(5);//设置列
                                ui->book_tableWidget->setRowCount(0);
                                ui->book_tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("借书人")<<tr("学号")<<tr("书名")<<tr("书号")<<tr("借书时间"));

                                ui->book_tableWidget->verticalHeader()->hide();
                                ui->book_tableWidget->horizontalHeader()->setSectionsClickable(false);
                                ui->book_tableWidget->horizontalHeader()->setStretchLastSection(true);
                                ui->book_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                                ui->book_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
                                ui->book_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
                                ui->book_tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
                                ui->book_tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
                                ui->book_tableWidget->setShowGrid(false);  // disable the table grid.
                                ui->book_tableWidget->verticalHeader()->setDefaultSectionSize(35);  // set row height.
                                ui->book_tableWidget->horizontalHeader()->setHighlightSections(false);
                                ui->book_tableWidget->setFrameShape(QFrame::NoFrame);

                                ui->book_tableWidget->setColumnWidth(0, 70);
                                ui->book_tableWidget->setColumnWidth(1, 100);
                                ui->book_tableWidget->setColumnWidth(2, 100);
                                ui->book_tableWidget->setColumnWidth(3, 100);
                                ui->book_tableWidget->setColumnWidth(4, 140);


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //只读
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidget->setColumnCount(5);//设置列
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("借书ID")<<tr("书序列号")<<tr("借书码")<<tr("借书日期")<<tr("借书时间"));

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

    ui->tableWidget->setColumnWidth(0, 70);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 240);
    ui->tableWidget->setColumnWidth(3, 100);
    ui->tableWidget->setColumnWidth(4, 40);

    //管理员实时可以看见借书流水表
    QSqlQuery query;
    query.exec(QString("select username, bno, loan_number, loan_date, loan_time from loan"));
    while(query.next())
    {
        int rows = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rows);
        QString ele0 = query.value(0).toString();
        QString ele1 = query.value(1).toString();
        QString ele2 = query.value(2).toString();
        QString ele3 = query.value(3).toString();
        QString ele4 = query.value(4).toString();

        ui->tableWidget->setItem(count, 0, new QTableWidgetItem(ele0));
        ui->tableWidget->setItem(count, 1, new QTableWidgetItem(ele1));
        ui->tableWidget->setItem(count, 2, new QTableWidgetItem(ele2));
        ui->tableWidget->setItem(count, 3, new QTableWidgetItem(ele3));
        ui->tableWidget->setItem(count, 4, new QTableWidgetItem(ele4));

        count++;
    }
}

void ManagerMainWindow::on_ReturnBook_clicked()
{
    ReturnBook * r = new ReturnBook;
    r->setWindowTitle("归还书籍");
    r->show();
}




void ManagerMainWindow::on_MultiInput_clicked()
{
    qDebug("进入打开文件函数");

    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        QString CantOpen = "Can't write %1：/n %2";
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning",CantOpen.arg(fileName).arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        QSqlQuery query;
        QString sql;
        QString bno , category, title , press , author ;
        int  total, stock , year;
        float price;
        bool isok,flag;
        flag = true;
        int n;
        in >> n;
        for(int i = 0;i < n;i++){

            in >> bno >> category >> title >> press >> year >> author >> price >> total  ;
            query.exec(QString("select * from book where bno = '"+bno+"' "));
            if(query.next() != NULL)
            {
                isok = query.exec(QString("update book set total = total + %1, stock = stock + %2 where bno = '%3' ").arg(total).arg(total).arg(bno));
                if(isok == false)
                    flag = false;
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
                 if(isok == false)
                     flag = false;
            }
        }
        if(flag == true)
            QMessageBox::about(NULL,"提示!", "书籍增加成功!");
        else
            QMessageBox::about(NULL,"提示!", "书籍增加失败!");
     }
}


void ManagerMainWindow::on_SingleInput_clicked()
{
    SingleInputWindow *inputp = new SingleInputWindow;
    inputp->setWindowTitle("单册管理");
    inputp->show();
}

void ManagerMainWindow::on_UserManage_clicked()
{
    UserManage *user = new UserManage;
    user->setWindowTitle("用户管理");
    user->show();
}

void ManagerMainWindow::on_Update_clicked()
{
    ManagerMainWindow *a = new ManagerMainWindow;
    a->setWindowTitle("管理员您好");
    a->show();
    this->close();
}

void ManagerMainWindow::on_StuQueryButton_clicked()
{
    ui->stu_tableWidget->clearContents();
    int count = 0;
    QString stuname = ui->stu_name->text();
    QString stuid = ui->stu_sno->text();
    QSqlQuery query;
    query.exec(QString("select card.name,loan.username,book.title,book.bno,loan.loan_date from book, loan, card where book.bno = loan.bno and card.cno = loan.username and loan.username like '%"+stuid+"%' and card.name like '%"+stuname+"%'  "));
    while(query.next())
    {
        int rows = ui->stu_tableWidget->rowCount();
        ui->stu_tableWidget->insertRow(rows);
        QString ele0 = query.value(0).toString();
        QString ele1 = query.value(1).toString();
        QString ele2 = query.value(2).toString();
        QString ele3 = query.value(3).toString();
        QString ele4 = query.value(4).toString();

        QTableWidgetItem *item0 = new QTableWidgetItem(ele0);
        QTableWidgetItem *item1 = new QTableWidgetItem(ele1);
        QTableWidgetItem *item2 = new QTableWidgetItem(ele2);
        QTableWidgetItem *item3 = new QTableWidgetItem(ele3);
        QTableWidgetItem *item4 = new QTableWidgetItem(ele4);



        if(count % 2 == 1)
        {
           item0->setBackground(QBrush(QColor(198,215,250)));
           item1->setBackground(QBrush(QColor(198,215,250)));
           item2->setBackground(QBrush(QColor(198,215,250)));
           item3->setBackground(QBrush(QColor(198,215,250)));
           item4->setBackground(QBrush(QColor(198,215,250)));
        }

        ui->stu_tableWidget->setItem(count, 0, item0);
        ui->stu_tableWidget->setItem(count, 1, item1);
        ui->stu_tableWidget->setItem(count, 2, item2);
        ui->stu_tableWidget->setItem(count, 3, item3);
        ui->stu_tableWidget->setItem(count, 4, item4);

        count++;
    }

}

void ManagerMainWindow::on_BookQueryButton_clicked()
{
    ui->book_tableWidget->clearContents();
    int count = 0;
    QString bookname = ui->bookname->text();
    QString bookid = ui->bookbno->text();
    QSqlQuery query;
    query.exec(QString("select card.name,loan.username,book.title,book.bno,loan.loan_date from book, loan, card where book.bno = loan.bno and card.cno = loan.username and book.title like '%"+bookname+"%' and loan.bno like '%"+bookid+"%'  "));
    while(query.next())
    {
        int rows = ui->book_tableWidget->rowCount();
        ui->book_tableWidget->insertRow(rows);
        QString ele0 = query.value(0).toString();
        QString ele1 = query.value(1).toString();
        QString ele2 = query.value(2).toString();
        QString ele3 = query.value(3).toString();
        QString ele4 = query.value(4).toString();

        QTableWidgetItem *item0 = new QTableWidgetItem(ele0);
        QTableWidgetItem *item1 = new QTableWidgetItem(ele1);
        QTableWidgetItem *item2 = new QTableWidgetItem(ele2);
        QTableWidgetItem *item3 = new QTableWidgetItem(ele3);
        QTableWidgetItem *item4 = new QTableWidgetItem(ele4);



        if(count % 2 == 1)
        {
           item0->setBackground(QBrush(QColor(198,215,250)));
           item1->setBackground(QBrush(QColor(198,215,250)));
           item2->setBackground(QBrush(QColor(198,215,250)));
           item3->setBackground(QBrush(QColor(198,215,250)));
           item4->setBackground(QBrush(QColor(198,215,250)));
        }

        ui->book_tableWidget->setItem(count, 0, item0);
        ui->book_tableWidget->setItem(count, 1, item1);
        ui->book_tableWidget->setItem(count, 2, item2);
        ui->book_tableWidget->setItem(count, 3, item3);
        ui->book_tableWidget->setItem(count, 4, item4);

        count++;
    }

}


ManagerMainWindow::~ManagerMainWindow()
{
    delete ui;
}
