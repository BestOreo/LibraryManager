#ifndef STUMAINWINDOW_H
#define STUMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class StuMainWindow;
}

class StuMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StuMainWindow(QWidget *parent = 0);
    ~StuMainWindow();


private slots:
    void BorrowBook(int, int);
   void on_searchButton_clicked();
   void on_clearButton_clicked();

private:
    Ui::StuMainWindow *ui;
};

#endif // STUMAINWINDOW_H
