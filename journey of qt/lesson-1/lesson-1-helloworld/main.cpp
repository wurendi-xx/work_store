#include <QCoreApplication>
#include <QtDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("Hello Qt World! My %d application.",1);

    Mat image = imread("G:\\gitTUT\\journey of study\\just_test\\opencv_test\\opencv_test\\1.jpg");
    qDebug()<<image.empty();
    namedWindow("window", WINDOW_NORMAL);
    imshow("window",image);
    waitKey(0);

    return a.exec();
}
