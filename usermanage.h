#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QMainWindow>

namespace Ui {
class UserManage;
}

class UserManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = 0);
    ~UserManage();
    void update();

private:
    Ui::UserManage *ui;
private slots:
    void on_addButton_clicked(); //按键分别对应的槽函数
    void on_searchButton_clicked();
    void on_deleteButton_clicked();
};

#endif // USERMANAGE_H
