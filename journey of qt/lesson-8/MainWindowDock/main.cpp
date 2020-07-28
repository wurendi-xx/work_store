#include "mainwindowdock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowDock w;
    w.show();

    return a.exec();
}
