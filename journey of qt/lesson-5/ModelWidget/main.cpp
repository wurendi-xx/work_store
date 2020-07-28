#include <QDebug>
#include <QApplication>
#include <QDialog>
#include "modelwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModelWidget w;
    w.show();

    //非模态对话框
    QDialog modelLessDlg;
    modelLessDlg.setWindowTitle("非模态对话框");
    modelLessDlg.show();
    modelLessDlg.resize(200,100);
    qDebug()<<"显示非模态对话框之后，不需要等用户的操作就可以立即取回控制权";

    return a.exec();
}
