#include "stumainwindow.h"
#include "ui_stumainwindow.h"
#include <QSqlQuery>
#include <QDate>
#include <QMessageBox>
#include "mainwindow.h"
#include <QDebug>

int isMySelect = 0; // 用于禁止学生自主还书的额外参数，避免程序进入窗口对话死循环
int cancel = 0;
int flag = 0;



StuMainWindow::StuMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StuMainWindow)
{
    ui->setupUi(this);

    QPixmap pixmap(":/Action/Library++.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);  //避免其余空间继承StyleSheet


    ui->searchButton->setStyleSheet("QPushButton{background-color:black;\
                                    color: white;   border-radius: 10px;  border: 2px groove gray;\
                                    border-style: outset;font:15pt 隶书}"
                                   "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                                  "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                                                   border-style: inset; }"
                                   );
     ui->clearButton->setStyleSheet("QPushButton{background-color:black;\
                                color: white;   border-radius: 10px;  border: 2px groove gray;\
                                border-style: outset;font:15pt 隶书}"
                               "QPushButton:hover{background-color:rgb(255,255,255,65%); color: black;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255,65%);\
                                               border-style: inset; }"
                               );


                                //////////////////////////////////////
                                /// \brief querytype
                                ///目录生成
    ui->treeWidget->setFrameShape(QFrame::NoFrame);

    //ui->treeWidget->setStyleSheet("QTreeWidget::item{height:45px}");
    ui->treeWidget->setStyleSheet( "QTreeWidget::item{height:45px}""QTreeView::item:hover{background-color:rgb(85, 170, 255,65%)}"
                               "QTreeView::item:selected{background-color:rgb85, 170, 255,65%)}" );
    QSqlQuery querytype;
    int typecount = 0;
    QString book_type = "全部";
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<book_type);
    ui->treeWidget->addTopLevelItem(item);

    querytype.exec(QString("select type from booktype "));
    while(querytype.next())
    {
        QString book_type = querytype.value(0).toString();
        QTreeWidgetItem * item = new QTreeWidgetItem(QStringList()<<book_type);
        ui->treeWidget->addTopLevelItem(item);
    }
    //////////////////////////////////////////////
    /// 表格设置
    ///
    QSqlQuery query,childquery,myquery;
    int count = 0;
    int mycount = 0;
    int rows;
    //表格格式形状的一些设定
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //只读
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidget->setColumnCount(7);//设置列
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("序列号")<<tr("书名")<<tr("出版社")<<tr("作者")<<tr("库存总量")<<tr("在库数量")<<tr("借阅"));

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

    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 180);
    ui->tableWidget->setColumnWidth(2, 140);
    ui->tableWidget->setColumnWidth(3, 180);
    ui->tableWidget->setColumnWidth(4, 40);
    ui->tableWidget->setColumnWidth(5, 70);
    ui->tableWidget->setColumnWidth(6, 40);



    ui->mybook->setEditTriggers(QAbstractItemView::NoEditTriggers); //只读
    ui->mybook->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->mybook->setColumnCount(3);//设置列
    ui->mybook->setRowCount(0);
    ui->mybook->setHorizontalHeaderLabels(QStringList()<<tr("书名")<<tr("作者")<<tr("借书时间"));

    ui->mybook->verticalHeader()->hide();
    ui->mybook->horizontalHeader()->setSectionsClickable(false);
    ui->mybook->horizontalHeader()->setStretchLastSection(true);
    ui->mybook->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mybook->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->mybook->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mybook->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->mybook->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->mybook->setShowGrid(false);  // disable the table grid.
    ui->mybook->verticalHeader()->setDefaultSectionSize(45);  // set row height.
    ui->mybook->horizontalHeader()->setHighlightSections(false);
    ui->mybook->setFrameShape(QFrame::NoFrame);

    ui->mybook->setColumnWidth(0, 120);
    ui->mybook->setColumnWidth(1, 120);
    ui->mybook->setColumnWidth(2, 120);

    myquery.exec(QString("select title, author, loan_date from book natural join loan where username = '"+user_id+"' "));
    while(myquery.next())// UI界面显示表格
    {
        rows = ui->mybook->rowCount();
        ui->mybook->insertRow(rows);
        QString myele0 = myquery.value(0).toString();
        QString myele1 = myquery.value(1).toString();
        QString myele2 = myquery.value(2).toString();

        ui->mybook->setItem(mycount, 0, new QTableWidgetItem(myele0));
        ui->mybook->setItem(mycount, 1, new QTableWidgetItem(myele1));
        ui->mybook->setItem(mycount, 2, new QTableWidgetItem(myele2));

        mycount++;
    }



    query.exec(QString("select bno,title,press,author,total,stock from book order by category"));
    while(query.next())// UI界面显示表格
    {
        rows = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rows);
        QString ele0 = query.value(0).toString();
        QString ele1 = query.value(1).toString();
        QString ele2 = query.value(2).toString();
        QString ele3 = query.value(3).toString();
        QString ele4 = query.value(4).toString();
        QString ele5 = query.value(5).toString();

        ui->tableWidget->setItem(count, 0, new QTableWidgetItem(ele0));
        ui->tableWidget->setItem(count, 1, new QTableWidgetItem(ele1));
        ui->tableWidget->setItem(count, 2, new QTableWidgetItem(ele2));
        ui->tableWidget->setItem(count, 3, new QTableWidgetItem(ele3));
        ui->tableWidget->setItem(count, 4, new QTableWidgetItem(ele4));
        ui->tableWidget->setItem(count, 5, new QTableWidgetItem(ele5));

        QTableWidgetItem *item = new QTableWidgetItem;    //每个课程后有选择框
        item->setText("");
        item->setTextAlignment (Qt::AlignCenter);
        ui->tableWidget->setItem(count, 6, item);


        childquery.exec(QString("select * from loan where username = '"+user_id+"' and bno = '"+ele0+"'"));
        if(childquery.next())
        {
            ui->tableWidget->item(count,6)->setCheckState(Qt::Checked);
        }
        else
        {
            ui->tableWidget->item(count,6)->setCheckState(Qt::Unchecked);
        }



        count++;
    }
    ui->tableWidget->setSortingEnabled(true);

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(BorrowBook(int,int)));
}

void StuMainWindow::BorrowBook(int row, int col)
{
    if(flag == 1)
        return;

    if( isMySelect == 1)
    {
        isMySelect = 0;
        return;
    }

    if( cancel == 1 )
    {
        cancel = 0;
        return;
    }
    QDate d = QDate::currentDate();
    QString date = d.toString("yyyy-MM-dd");


    QTime t =QTime::currentTime() ;
    QString time = t.toString("hh:mm:ss");

    QSqlQuery query,queryupdate;

    QString loannumber;

    loannumber = user_id;
    loannumber = loannumber.append(ui->tableWidget->item(row,0)->text()).append(date).append(time);


    QString bookid = ui->tableWidget->item(row,0)->text();
    if(ui->tableWidget->item(row, col)->checkState() == Qt::Checked && isMySelect == 0)
    {
        QMessageBox msg(QMessageBox::Warning, tr("借书确认"), tr("你确定要借阅这本书吗？"), QMessageBox::Yes | QMessageBox::No, NULL);
        if(msg.exec() == QMessageBox::Yes)
        {
            qDebug("%s", qPrintable( user_id ) );
           if(ui->tableWidget->item(row,5)->text().toInt() >= 1  &&   query.exec(QString("insert into loan values('"+user_id+"', '"+bookid+"', '"+loannumber+"' , '"+date+"' , '"+time+"')"))){
                //插入一条借书记录，必须库存大于等于1的时候才能借出书籍
                {

                    if( query.exec(QString("update book set stock = stock-1 where bno = '" + bookid + "'")))
                        //debug 调试用
                    {
                        qDebug("%s", qPrintable( "update success" ) );
                        qDebug("%s", qPrintable( time ) );
                    }


                    QMessageBox msg(QMessageBox::Warning, tr(" 借书成功！"), tr("已通过借书申请，请在40天内归还！"), QMessageBox::Yes, NULL);
                    msg.exec();

                    StuMainWindow *updatewindow = new StuMainWindow;
                    updatewindow->show();
                    this->close();
                }
            }
            else
            {
                QMessageBox msg(QMessageBox::Warning, tr(" 借书失败"), tr("库存不足，借书失败"), QMessageBox::Yes, NULL);
                msg.exec();
            }
         }
        else{
            // 禁止自助还书，需要由管理员检查书籍保护情况，以及延期还书虚补交费用
             cancel = 1;
             ui->tableWidget->item(row, col)->setCheckState(Qt::Unchecked);  //取消选择
             return;
        }
    }
    else if(ui->tableWidget->item(row, col)->checkState() == Qt::Unchecked && cancel == 0)
    {
        QMessageBox msg(QMessageBox::Warning, tr("客户端无权限"), tr("请前台还书！谢谢"), QMessageBox::Yes, NULL);
        msg.exec();
        isMySelect = 1; //避免借书还书对话框进入死循环
        ui->tableWidget->item(row, col)->setCheckState(Qt::Checked);  //取消选择

        return;
    }
}

void StuMainWindow::on_searchButton_clicked() // 模糊匹配
{
    flag = 1; //global
    for(int i = ui->tableWidget->rowCount();i >= 0;i--)
     {
        ui->tableWidget->removeRow(i);
     }
    int rows=0, count = 0;
    QSqlQuery query,childquery;
    QString booktype = ui->treeWidget->currentItem()->text(0);
    if ( booktype == "全部")
        booktype = "";
    //if(ui->name->text().isEmpty() == 0 || ui->press->text().isEmpty() == 0|| ui->author->text().isEmpty() == 0 || ui->bno->text().isEmpty() == 0 )


         QString sqlsentence = "select bno,title,press,author,total,stock from book where title like '%"+ui->name->text()+"%' and press like '%"+ui->press->text()+"%' and author like '%"+ui->author->text()+"%' and bno like '%"+ui->bno->text()+"%' and category like '%"+booktype+"%' order by category";
         //if(ui->name->text().isEmpty() == 1)
         //   sqlsentence.append(" title like '%"+ui->name->text()+"%'" );

         query.exec(sqlsentence);

         while(query.next())// UI界面显示表格
         {
             rows = ui->tableWidget->rowCount();
             ui->tableWidget->insertRow(rows);
             QString ele0 = query.value(0).toString();
             QString ele1 = query.value(1).toString();
             QString ele2 = query.value(2).toString();
             QString ele3 = query.value(3).toString();
             QString ele4 = query.value(4).toString();
             QString ele5 = query.value(5).toString();

             ui->tableWidget->setItem(count, 0, new QTableWidgetItem(ele0));
             ui->tableWidget->setItem(count, 1, new QTableWidgetItem(ele1));
             ui->tableWidget->setItem(count, 2, new QTableWidgetItem(ele2));
             ui->tableWidget->setItem(count, 3, new QTableWidgetItem(ele3));
             ui->tableWidget->setItem(count, 4, new QTableWidgetItem(ele4));
             ui->tableWidget->setItem(count, 5, new QTableWidgetItem(ele5));

             QTableWidgetItem *item = new QTableWidgetItem;    //每个课程后有选择框
             item->setText("");
             item->setTextAlignment (Qt::AlignCenter);
             ui->tableWidget->setItem(count, 6, item);


             childquery.exec(QString("select * from loan where username = '"+user_id+"' and bno = '"+ele0+"'"));
             if(childquery.next())
             {
                 ui->tableWidget->item(count,6)->setCheckState(Qt::Checked);
             }
             else
             {
                 ui->tableWidget->item(count,6)->setCheckState(Qt::Unchecked);
             }
             count++;
         }

    flag = 0;
}

void StuMainWindow::on_clearButton_clicked()
{
    ui->name->clear();
    ui->author->clear();
    ui->bno->clear();
    ui->press->clear();
}

StuMainWindow::~StuMainWindow()
{
    delete ui;
}
