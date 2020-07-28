#include "containerframe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ContainerFrame w;
    w.show();

    return a.exec();
}
