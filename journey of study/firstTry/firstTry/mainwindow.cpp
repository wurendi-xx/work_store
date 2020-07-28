#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "meanshift_segmentation.h"

#if _MSC_VER >= 1600
# pragma execution_character_set(“utf-8”)
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //水平布局
    ui->horizontalLayout->setMargin(10);
    ui->horizontalLayout->setStretch(1,2);
    //scroll区域中放一个用于储存图片的label
    ui->scrollArea->setWidget(ui->pic_show);

    //标识符初始化
    canny_bool = ui->check_canny->checkState();
    rec_bool = 0;




    frame=imread("C:/Users/wurendi/Desktop/task.jpg");
    displayResult(ui->pic_show);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//用来显示mat类型的图片
void MainWindow::displayResult(QLabel *label)
{

    //调用算法
    if(canny_bool){
        cvtColor(frame,frame, CV_BGR2GRAY );
        Canny(frame, frame, 0, 30, 3);
        cvtColor(frame,frame,CV_GRAY2BGR);//这里是为了能够写入视频文件 所以转回了BGR格式
        putText(frame,"hello",Point(50,60),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
    }

    Mat rgb;
    QImage img;
    if(frame.channels() == 3)    // RGB image
    {
        cv::cvtColor(frame,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)
                     rgb.cols,rgb.rows,
                     rgb.cols*rgb.channels(),   //new add
                     QImage::Format_RGB888);
    }else                     // gray image
    {
        img = QImage((const uchar*)(frame.data),
                     frame.cols,frame.rows,
                     frame.cols*frame.channels(),    //new add
                     QImage::Format_Indexed8);
    }
    label->setPixmap(QPixmap::fromImage(img));
    label->resize(label->pixmap()->size());

}

//用来刷新图片
void MainWindow::nextFrame()
{
    capture >> frame;
    if (!frame.empty())
    {
        displayResult(ui->pic_show);
        if(rec_bool)
        {
         writer.write(frame);
        }
    }


}

//打开单个文件
void MainWindow::on_action_file_open_triggered()
{
    if (capture.isOpened())
           { capture.release();}//如果摄像头打开了 就关闭它

    file_path = QFileDialog::getOpenFileName(this,
                                             tr("打开一个文件"),
                                            "./",
                                            tr("All Files (*);;Picture Files (*.jpg *.bmp *.png);;Video Files (*.avi *.mp4)"));
//    qDebug()<<file_path;
    char ext[5] ;//后缀
    string s=file_path.toStdString();//QString转String
    const char *path = s.data();//string转char
    _splitpath(path, NULL, NULL, NULL, ext);//分解路径


    //打开图片
    if(!strcmp(ext,".jpg")
            ||!strcmp(ext,".bmp")
            ||!strcmp(ext,".png")
            ||!strcmp(ext,".JPG")
            ||!strcmp(ext,".PNG")
            ||!strcmp(ext,".BMP"))
    {
        frame = imread(s);
        displayResult(ui->pic_show);
    }

    //打开视频
    if(!strcmp(ext,".avi")
            || !strcmp(ext,".mp4")
            || !strcmp(ext,".AVI")
            || !strcmp(ext,".MP4"))
    {
        capture.open(s);
        if (capture.isOpened())
        {
            rate= capture.get(CV_CAP_PROP_FPS);
            capture >> frame;
            if (!frame.empty())
            {

                displayResult(ui->pic_show);
                timer = new QTimer(this);
                timer->setInterval(1000/rate);   //set timer match with FPS
                connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
                timer->start();
            }
        }
        else
            qDebug()<<"无法打开";
    }


}

//打开文件夹
void MainWindow::on_action_dir_open_triggered()
{
    dir_path= QFileDialog::getExistingDirectory(this,
                                tr("获取文件夹"),
                                "./");
}

//打开多个文件
void MainWindow::on_action_files_open_triggered()
{
    files_path= QFileDialog::getOpenFileNames(
                this, tr("打开多个文件"),
                "./",
                tr("All Files (*);;Text Files (*.txt)"));
}

//调用算法
void MainWindow::on_check_canny_toggled(bool checked)
{
    canny_bool = checked;
}

//调用摄像头
void MainWindow::on_action_cam_open_triggered()
{
    if (capture.isOpened())
         capture.release();     //存在就销毁 初始化
    //寻找可用摄像头
    int index = 0;
    while(index<5)
    {
        if(!capture.open(index))index++;
        else
            break;
    }


//    capture.open(0);           //open the default camera
     if (capture.isOpened())
     {
         rate= capture.get(CV_CAP_PROP_FPS);
         capture >> frame;
         if (!frame.empty())
         {

             displayResult(ui->pic_show);
             timer = new QTimer(this);
             timer->setInterval(1000/rate);   //set timer match with FPS
             connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
             timer->start();
         }
     }
}

//启动录制
void MainWindow::on_pushButton_start_rec_clicked()
{
    if(capture.isOpened()){
        rec_bool = 1;
        //准备视频文件，因为是固定颜色格式的，所以当变成二值通道的时候就不能写入了
        writer.open("./myrec.avi",
                    cv::VideoWriter::fourcc('M','P','4','2'),
                    rate,
                    cv::Size(frame.cols, frame.rows),true);
        ui->pushButton_start_rec->setDisabled(true);


    }
    else
        errorMessage.showMessage(tr("并没有视频可以录制"));

}

//关闭录制
void MainWindow::on_pushButton_stop_rec_clicked()
{
    if(rec_bool)
    {
        rec_bool = 0;
        writer.release();
        ui->pushButton_start_rec->setEnabled(true);
    }
    else
        errorMessage.showMessage(tr("没有正在录制的视频"));
}


void MainWindow::on_action_meanshift_triggered()
{
    meanshift_segmentation(frame);
}
