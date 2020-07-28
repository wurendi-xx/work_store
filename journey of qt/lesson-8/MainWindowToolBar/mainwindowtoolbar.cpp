#include <QDebug>
#include "mainwindowtoolbar.h"
#include "ui_mainwindowtoolbar.h"

MainWindowToolBar::MainWindowToolBar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowToolBar)
{
    ui->setupUi(this);


    QIcon icon(":/image/头像.jpg");
    ui->actionAction1->setIcon(icon);
    ui->mainToolBar->setIconSize(QSize(30, 30));

    connect(ui->listWidget_button, SIGNAL(itemChanged(QListWidgetItem*)),
                 this, SLOT(onBtnStyleChanged(QListWidgetItem *)));
}

MainWindowToolBar::~MainWindowToolBar()
{
    delete ui;
}

void MainWindowToolBar::on_listWidget_area_itemChanged(QListWidgetItem *item)
{
    //获取该item所代表的位置flag
    int row = ui->listWidget_area->row(item);
    int flg = Qt::LeftToolBarArea << row;

    //获取工具栏原来的位置flag
    Qt::ToolBarAreas areas = ui->mainToolBar->allowedAreas();

    //areas为QFlags<Qt::ToolBarArea>类型，所以只需将该位置打开或关闭即可
    areas.setFlag((Qt::ToolBarArea)flg, item->checkState() == Qt::Checked);

    //设置新flags
    ui->mainToolBar->setAllowedAreas(areas);
}

void MainWindowToolBar::onBtnStyleChanged(QListWidgetItem *item)
{
    //这里是为了获取单选效果
    disconnect(ui->listWidget_button, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(onBtnStyleChanged(QListWidgetItem *)));

    static QListWidgetItem* lastItem = ui->listWidget_button->item(0);


    qDebug() << ui->listWidget_button->row(0);
    if (lastItem != item && item->checkState() == Qt::Checked)
    {
        int row = ui->listWidget_button->row(item);
        ui->mainToolBar->setToolButtonStyle((Qt::ToolButtonStyle)row);
        lastItem->setCheckState(Qt::Unchecked);
        lastItem = item;
    }
    else
    {
        item->setCheckState(Qt::Checked);
    }

    connect(ui->listWidget_button, SIGNAL(itemChanged(QListWidgetItem*)),
                 this, SLOT(onBtnStyleChanged(QListWidgetItem *)));
}



void MainWindowToolBar::on_check_floatable_toggled(bool checked)
{
    ui->mainToolBar->setFloatable(checked);

}

void MainWindowToolBar::on_check_movable_toggled(bool checked)
{
    ui->mainToolBar->setMovable(checked);

}
