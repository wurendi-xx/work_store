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
    /**
     * @brief on_pushButton_bin_fuse_clicked bin文件融合按钮的函数入口
     */
    void on_pushButton_bin_fuse_clicked();
    /**
     * @brief on_pushButton_menu_generate_clicked 菜谱制作按钮的函数入口
     */
    void on_pushButton_menu_generate_clicked();
    /**
     * @brief on_action_2_triggered 菜单栏中的关于函数入口
     */
    void on_action_2_triggered();
    /**
     * @brief on_action_triggered 菜单栏中的帮助函数入口
     */
    void on_action_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
