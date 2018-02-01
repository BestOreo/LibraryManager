#ifndef MANAGERMAINWINDOW_H
#define MANAGERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ManagerMainWindow;
}

class ManagerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerMainWindow(QWidget *parent = 0);
    ~ManagerMainWindow();

private:
    Ui::ManagerMainWindow *ui;
private slots:
    void on_ReturnBook_clicked(); //按键分别对应的槽函数
    void on_SingleInput_clicked();
    void on_MultiInput_clicked();
    void on_UserManage_clicked();
    void on_Update_clicked();
    void on_StuQueryButton_clicked();
    void on_BookQueryButton_clicked();
};

#endif // MANAGERMAINWINDOW_H
