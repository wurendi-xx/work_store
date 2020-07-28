#include "containerwidget2.h"
#include "ui_containerwidget2.h"

ContainerWidget2::ContainerWidget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContainerWidget2)
{
    ui->setupUi(this);
    /*1  QTabWidget设置*/
        //标签省略策略
        QStringList textList;
        textList << "ElideLeft" <<"ElideRight" << "ElideMiddle" << "ElideNone";
        ui->combo_elide->addItems(textList);

        //标签位置
        textList.clear();
        textList << "North" << "South" << "West" << "East";
        ui->combo_tabposition->addItems(textList);

        //标签形状
        textList.clear();
        textList << "Rounded" << "Triangular";
        ui->combo_tabshape->addItems(textList);

        //连接关闭槽
        connect(ui->tabWidget, &QTabWidget::tabCloseRequested,
                     ui->tabWidget, &QTabWidget::removeTab);

        //添加一个标签
        ui->tabWidget->addTab(new QLabel("Add Tab"), tr("第三首歌"));


        //---------------------------------------按钮测试用----------------------------------
        //启动自动点击按钮
           ui->pushButton->setAutoRepeat(true);
           //按下按钮不松开，2秒后开始自动发送信号
           ui->pushButton->setAutoRepeatDelay(1000);
           //每隔1秒发送一次点击信号
           ui->pushButton->setAutoRepeatInterval(100);

}

ContainerWidget2::~ContainerWidget2()
{
    delete ui;
}
//省略模式
void ContainerWidget2::on_combo_elide_currentIndexChanged(int index)
{
    ui->tabWidget->setElideMode((Qt::TextElideMode)index);
}

void ContainerWidget2::on_combo_tabposition_currentIndexChanged(int index)
{
    ui->tabWidget->setTabPosition((QTabWidget::TabPosition)index);

}

void ContainerWidget2::on_combo_tabshape_currentIndexChanged(int index)
{
    ui->tabWidget->setTabShape((QTabWidget::TabShape)index);

}

void ContainerWidget2::on_check_document_toggled(bool checked)
{
    ui->tabWidget->setDocumentMode(checked);

}

void ContainerWidget2::on_check_autohide_toggled(bool checked)
{
    ui->tabWidget->setTabBarAutoHide(checked);

}

void ContainerWidget2::on_check_moveable_toggled(bool checked)
{
    ui->tabWidget->setMovable(checked);

}

void ContainerWidget2::on_check_closable_toggled(bool checked)
{
    ui->tabWidget->setTabsClosable(checked);
}

void ContainerWidget2::on_check_scrollBtns_toggled(bool checked)
{
    ui->tabWidget->setUsesScrollButtons(checked);
}

void ContainerWidget2::on_btn_addItem_clicked()
{
    ui->toolBox->addItem(new QLabel("新item"), tr("untitled"));

}

void ContainerWidget2::on_btn_delItem_clicked()
{
int index = ui->toolBox->currentIndex();
    if (index != -1)
    {
        ui->toolBox->removeItem(index);
    }
}

void ContainerWidget2::on_pushButton_clicked()
{
    int val = ui->spinBox->value();
        ui->spinBox->setValue(val+1);
}

void ContainerWidget2::on_check_flat_stateChanged(int arg1)
{
    ui->pushButton->setFlat(arg1==Qt::Checked);

}
