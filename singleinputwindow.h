#ifndef SINGLEINPUTWINDOW_H
#define SINGLEINPUTWINDOW_H

#include <QMainWindow>

namespace Ui {
class SingleInputWindow;
}

class SingleInputWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SingleInputWindow(QWidget *parent = 0);
    ~SingleInputWindow();

private:
    Ui::SingleInputWindow *ui;
private slots:
    void on_InputButton_clicked(); //按键分别对应的槽函数
    void on_CancelButton_clicked();

};

#endif // SINGLEINPUTWINDOW_H
