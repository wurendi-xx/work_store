#include "popwidget.h"
#include "ui_popwidget.h"

PopWidget::PopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopWidget)
{
    ui->setupUi(this);

    ui->textEdit->hide();
    ui->verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
}

PopWidget::~PopWidget()
{
    delete ui;
}

void PopWidget::on_pushButton_toggled(bool checked)
{
    ui->textEdit->setVisible(checked);
   if (checked)
   {
       ui->pushButton->setText("收回");
   }
   else
   {
       ui->pushButton->setText("弹出");
   }
}
