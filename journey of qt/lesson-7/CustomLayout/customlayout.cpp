#include "customlayout.h"
#include "pyramidlayout.h"

CustomLayout::CustomLayout(QWidget *parent)
    : QWidget(parent)
{
    PyramidLayout* layout = new PyramidLayout(this, 0, 0, 0);
    for (int i = 0; i < 21; ++i)
    {
        layout->addWidget(new QLabel(tr("       ")));
    }
    //再给我们的每个label加个颜色，看起来像一块儿砖
    setStyleSheet("QLabel{background-color:#ffc000;border:2px solid #ff3000}");
}

CustomLayout::~CustomLayout()
{

}
