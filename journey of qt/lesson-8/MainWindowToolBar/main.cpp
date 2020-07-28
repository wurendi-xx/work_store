#include "mainwindowtoolbar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowToolBar w;
    w.show();

    return a.exec();
}
