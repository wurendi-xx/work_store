#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    int max=100;
    int min=0;
    ui->horizontalSlider->setMaximum(max);
    ui->horizontalSlider->setMinimum(min);

    //设置QlineEdit只能输入数字，且在0-100之间
    QIntValidator* validator = new QIntValidator(min,max,this);
    ui->lineEdit->setValidator(validator);

//    connect(ui->lineEdit,SIGNAL(textChanged(QString)),ui->label,SLOT(setText(QString)));

    connect(ui->lineEdit,&QLineEdit::textChanged,this, &Widget::sliderLineEditChanged);

//    connect(this,SIGNAL(signShowVal(QString)),ui->label,SLOT(setText(QString)));

      connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this, SLOT(LabelEditChanged(int)));

//    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this, &Widget::LabelEditChanged(int));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::sliderLineEditChanged(const QString &text)
{
    int val=text.toInt();
    ui->horizontalSlider->setValue(val);//设置slider的当前值
    emit signShowVal(text);//通知label显示文字
}
void Widget::LabelEditChanged(int value)
{
    int pos = ui->horizontalSlider->value();
    QString str=QString("%1").arg(pos);
    ui->label->setText(str);
    ui->lineEdit->setText(str);
}

void Widget::on_pushButton_toggled(bool checked)
{
    if(checked)
    {
        ui->pushButton->setText("隐藏进度条");
    }
    else
    {
        ui->pushButton->setText("显示进度条");
    }
}
