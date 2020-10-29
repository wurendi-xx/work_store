#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFont f("微软雅黑",12);
    a.setFont(f);
    a.setWindowIcon(QPixmap(":/tineco.ico"));
    a.setStyle(QStyleFactory::create("Fusion"));

    w.show();

    return a.exec();
}
