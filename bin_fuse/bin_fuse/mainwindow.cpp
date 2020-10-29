#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////-----------------------------------------------向导对话框-----------------------------------------------------------------------------------------------///////////

void MainWindow::on_pushButton_bin_fuse_clicked()
{
    Wizard_bin_fuse w;


    w.exec();
}

///////////-----------------------------------------------向导对话框-----------------------------------------------------------------------------------------------///////////

void MainWindow::on_pushButton_menu_generate_clicked()
{
    Wizard_bin_menu w;

    w.exec();

}

///////////-----------------------------------------------查看菜谱-----------------------------------------------------------------------------------------------///////////

void MainWindow::on_pushButton_clicked()
{

    QString file = QFileDialog::getOpenFileName(
                                this, tr("打开单个菜谱文件"),
                                "./",
                                tr("Bin Files (*.bin)"));
    if(file.isEmpty())
      {
        return;
      }
      else
      {
        QWidget* menu_view =new QTableView_menu(this,file);
        menu_view->show();
      }

/*
    QWidget* menu_view =new QTableView_menu(this,"file");
    menu_view->show();*/
}


void MainWindow::on_action_2_triggered()
{
    QMessageBox::about(this,"bin文件辅助制作","菜谱制作及bin文件集成软件©Version0.0.0.1\n仅供内部使用，没有泛用性\nby:WuRendi\n");
}

void MainWindow::on_action_triggered()
{
    QString str = "bin文件融合：在当前目录生成bin_fues.bin文件和fuse_log.txt文件\n菜谱制作：在当前目录生成menu+时间戳+菜名+ID.bin文件\n查看菜谱：读取本地生成的菜谱和稍微修改\n上传菜谱：需要蓝牙模块支持，不推荐使用";
    QMessageBox::about(this,"教程",str);
}


void MainWindow::on_pushButton_2_clicked()
{
    bluetooth* b = new bluetooth();

    b->show();
}
