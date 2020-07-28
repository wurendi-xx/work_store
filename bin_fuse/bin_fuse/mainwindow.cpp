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
    QMessageBox::about(this,"about","关于QT");
}
