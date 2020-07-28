#include "spliterwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpliterWidget w;
    w.show();

    return a.exec();
}
