#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QMainWindow>

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = 0);
    ~ReturnBook();
private slots:
    void on_Enter_clicked(); //按键分别对应的槽函数
private:
    Ui::ReturnBook *ui;
};

#endif // RETURNBOOK_H
