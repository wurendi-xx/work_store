#include "popwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PopWidget w;
    w.show();

    return a.exec();
}
