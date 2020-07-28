#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

/*    QPushButton buttonwindow;
    buttonwindow.setText("这里是窗口");
    buttonwindow.show();
    buttonwindow.resize(200,100);
*/
    QLabel label;
    QMovie *movie = new QMovie("./wait1.gif");
    movie->setSpeed(1000);
    movie->setBackgroundColor(QColor(10, 10, 10));
    label.setMovie(movie);
    label.resize(200,100);
    label.show();
    qDebug() << movie->isValid();
    movie->start();

    return a.exec();
}
