#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wizard_bin_fuse.h"
#include "wizard_bin_menu.h"


namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class 主界面对象
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_bin_fuse_clicked();

    void on_pushButton_menu_generate_clicked();

    void on_action_2_triggered();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
