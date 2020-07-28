#ifndef MAINWINDOWTOOLBAR_H
#define MAINWINDOWTOOLBAR_H

#include <QMainWindow>
#include<QListWidgetItem>

namespace Ui {
class MainWindowToolBar;
}

class QListWidgetItem;

class MainWindowToolBar : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowToolBar(QWidget *parent = 0);
    ~MainWindowToolBar();

//    void onBtnStyleChanged(QListWidgetItem *item);

private slots:
    void on_listWidget_area_itemChanged(QListWidgetItem *item);

    void on_check_floatable_toggled(bool checked);

    void on_check_movable_toggled(bool checked);

    void onBtnStyleChanged(QListWidgetItem *item);

private:
    Ui::MainWindowToolBar *ui;
};

#endif // MAINWINDOWTOOLBAR_H
