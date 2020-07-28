#ifndef SPLITERWIDGET_H
#define SPLITERWIDGET_H

#include <QWidget>
#include <QSettings>
#include <QDebug>

namespace Ui {
class SpliterWidget;
}

class SpliterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpliterWidget(QWidget *parent = 0);
    ~SpliterWidget();

protected:
    //重写关闭事件，关于事件我们以后再讲解
    void closeEvent(QCloseEvent* e);

private slots:
    void on_check_opaqueResize_toggled(bool checked);

    void on_check_collapsible_toggled(bool checked);

private:
    Ui::SpliterWidget *ui;
    QByteArray state;
    QSettings settings;
};

#endif // SPLITERWIDGET_H
