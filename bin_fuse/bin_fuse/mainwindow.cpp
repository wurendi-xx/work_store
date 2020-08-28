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


void MainWindow::on_action_2_triggered()
{
    QMessageBox::about(this,"bin文件辅助制作","内部使用，没有泛用性\nby:WuRendi");
}

void MainWindow::on_action_triggered()
{
    QString str = "菜谱生成引导界面会在当前目录生成menu.bin文件\nbin文件融合会在当前目录生成bin_fues.bin文件和fuse_log.txt文件";
    QMessageBox::about(this,"教程",str);
}
