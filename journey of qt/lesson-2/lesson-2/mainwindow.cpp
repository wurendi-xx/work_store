#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("你好 qt");

    QPushButton* buttonchild = new QPushButton(this);
    buttonchild->setText("这里是控件");
}

MainWindow::~MainWindow()
{
    delete ui;
}
