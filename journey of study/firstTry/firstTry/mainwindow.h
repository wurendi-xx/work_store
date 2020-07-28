#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QErrorMessage>

#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#if _MSC_VER >= 1600
# pragma execution_character_set(“utf-8”)
#endif


using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //用来显示mat类型的图片
    void displayResult(QLabel *label);
    QErrorMessage errorMessage;


private slots:

    void nextFrame();

    void on_action_file_open_triggered();

    void on_action_dir_open_triggered();

    void on_action_files_open_triggered();

    void on_check_canny_toggled(bool checked);

    void on_action_cam_open_triggered();

    void on_pushButton_start_rec_clicked();

    void on_pushButton_stop_rec_clicked();

    void on_action_meanshift_triggered();

private:
    Ui::MainWindow *ui;
public:

    QString file_path;
    QString dir_path;
    QStringList files_path;

    bool rec_bool ;//是否录制
    bool canny_bool;//是否调用算法
    Mat frame;//帧
    VideoCapture capture;//cap
    QImage  image;//QImage格式
    QTimer *timer;//定时器
    double rate; //FPS
    VideoWriter writer;//保存使用
};

#endif // MAINWINDOW_H
