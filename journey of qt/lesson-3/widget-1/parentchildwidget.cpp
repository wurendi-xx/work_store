#include<QPushButton>
#include "parentchildwidget.h"
#include "ui_parentchildwidget.h"

ParentChildWidget::ParentChildWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParentChildWidget)
{
    ui->setupUi(this);
    //设置窗口的背景颜色
    setAutoFillBackground(true);
    QPalette pa = this->palette();
    pa.setBrush(QPalette::Background, QBrush(Qt::green));
    setPalette(pa);

    //设置窗口透明度
    setWindowOpacity(0.9);

    //设置窗口标题
    setWindowTitle("窗口属性");

    //设置悬停提示
    setToolTip("悬停");

    //重设大小
    resize(600, 400);

    //移动
    move(0, 0);


/*third changed
    setGeometry(0,0,400,300);
    move(100, 100);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
*/

/*first changed
    QPushButton* buttonchild = new QPushButton(this);
    buttonchild->setText("这里是控件");
*/

/*second changed
    for (int i = 1; i <= 3; ++i)
        {
            QPushButton* buttonChild = new QPushButton(this);
            buttonChild->setText(QString("我是控件%1").arg(i));
            buttonChild->resize(100*i, 100);
            connect(buttonChild, SIGNAL(clicked()), buttonChild, SLOT(close()));
        }
*/

}

ParentChildWidget::~ParentChildWidget()
{
    delete ui;
}
