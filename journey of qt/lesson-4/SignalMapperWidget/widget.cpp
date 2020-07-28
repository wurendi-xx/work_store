#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建垂直布局，将垂直布局作为主布局
    QVBoxLayout* vLayout = new QVBoxLayout(this);

    //创建编辑框，用于显示点击按钮的文字，并且文字在右边显示
    QLineEdit* edit = new QLineEdit;
    edit->setAlignment(Qt::AlignRight);
    vLayout->addWidget(edit);

    //创建信号匹配器
    QSignalMapper* signalMapper = new QSignalMapper(this);

    //创建0-9数字键，并加入到网格布局中
    QGridLayout *gridLayout = new QGridLayout;
    for(int i=0;i<10;++i)
    {
        QString text = QString::number(i);
        QPushButton *button = new QPushButton(text);
        connect(button,SIGNAL(clicked(bool)),signalMapper,SLOT(map()));
        signalMapper->setMapping(button,text);
        gridLayout->addWidget(button,i/3,i%3);

    }

    connect(signalMapper,SIGNAL(mapped(QString)),edit,SLOT(setText(QString)));

    vLayout->addLayout(gridLayout);
    resize(200,200);




}

Widget::~Widget()
{
    delete ui;
}
