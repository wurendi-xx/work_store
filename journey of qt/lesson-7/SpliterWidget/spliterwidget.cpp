#include "spliterwidget.h"
#include "ui_spliterwidget.h"

SpliterWidget::SpliterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpliterWidget),
    settings("MySofts", "SpliterWidget")
{
    ui->setupUi(this);

    //这里用来从注册表中加载分割器上一次关闭前的状态
    //注册表路径为：HKEY_CURRENT_USER\Software\MySofts\SpliterWidget
    if (settings.contains("splitterSizes"))
    {
        ui->splitter->restoreState(settings.value("splitterSizes").toByteArray());
        qDebug() << "is restored";
    }
    else
    {
        qDebug() << "first launch SpliterWidget";
    }
}

SpliterWidget::~SpliterWidget()
{
    delete ui;
}

void SpliterWidget::closeEvent(QCloseEvent *e)
{
    //关闭时保存分割器状态
    settings.setValue("splitterSizes", ui->splitter->saveState());
    QWidget::closeEvent(e);
}

void SpliterWidget::on_check_opaqueResize_toggled(bool checked)
{
    ui->splitter->setOpaqueResize(checked);

}

void SpliterWidget::on_check_collapsible_toggled(bool checked)
{
    //设置所有控件是否都可以被折叠，如果想设置某个控件，可以使用setCollapsible();
    ui->splitter->setChildrenCollapsible(checked);
}
