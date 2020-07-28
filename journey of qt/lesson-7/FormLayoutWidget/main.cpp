#include "formlayoutwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormLayoutWidget w;
    w.show();

    return a.exec();
}
