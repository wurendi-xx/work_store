#include "parentchildwidget.h"
#include <QApplication>
#include<QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ParentChildWidget w;
    w.show();




/*first changed
    QPushButton buttonwindow;
    buttonwindow.setText("这里是窗口");
    buttonwindow.show();
    buttonwindow.resize(200,100);
*/
    return a.exec();
}
