#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidgetAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_separtors_toggled(bool checked);

    void on_checkBox_tear_toggled(bool checked);

    void on_checkBox_tips_toggled(bool checked);


//自定义菜单用
private slots:
    void setTextColor(const QColor& clr);//用于设置textedit中的文本颜色
private:
    void createTextColorMenu();//用于创建自定义颜色窗口
private:
    QMenu* m_menuColor;//颜色菜单栏


private:
    Ui::MainWindow *ui;
    QMenu* m_menu;

};

#endif // MAINWINDOW_H
