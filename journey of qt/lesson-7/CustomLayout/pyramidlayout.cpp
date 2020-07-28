#include "pyramidlayout.h"
#include <QtMath>

PyramidLayout::PyramidLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

PyramidLayout::PyramidLayout(int margin, int hSpacing, int vSpacing)
    : m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

PyramidLayout::~PyramidLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void PyramidLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

int PyramidLayout::count() const
{
    return itemList.size();
}

QSize PyramidLayout::minimumSize() const
{
    QLayoutItem *item = itemList.first();
    QSize size;
    if (item)
    {
        int r = rowCount();
        size.setWidth((item->sizeHint().width()+m_hSpace)*r- m_hSpace);
        size.setHeight((item->sizeHint().height()+m_vSpace)*r- m_vSpace);
    }

    size += QSize(2*margin(), 2*margin());
    return size;
}

QSize PyramidLayout::sizeHint() const
{
    return minimumSize();
}

//用于计算金字塔高度
int PyramidLayout::rowCount() const
{
    //(1+r)*r = cnt
    //r为金字塔高度，cnt为子控件总个数
    //求解一元二次方程
    double r = (qSqrt(1+8*count())-1)/2.;
    int ir = r;
    if (r > ir)
    {
        r = ir + 1;
    }
    return r;
}

QLayoutItem *PyramidLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem *PyramidLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    else
        return 0;
}

void PyramidLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = 0;
    int y = 0;
    int cnt = count();

    //i表示行，j表示列，k表示第k个子控件
    for (int i = 0, k = 0; k < cnt; ++i)
    {
        for (int j = 0; j < i+1 && k < cnt; ++j, ++k)
        {
            QLayoutItem *item = itemList.at(k);
            QLayoutItem *aboveItem = 0;//每个控件的头上控件，用于定位item
            if (i == j)//最右侧控件
            {
                if (i == 0)//第一个控件，水平居中
                {
                    double r = rowCount();
                    x = effectiveRect.center().x() - item->sizeHint().width()/2;
                    y = effectiveRect.center().y()-r/2*item->sizeHint().height()-(r-1)/2*m_vSpace;
                }
                else//选择它头上的左侧控件作为头控件
                {
                    aboveItem = itemList.at(k-i-1);
                    x = aboveItem->geometry().right()-item->sizeHint().width()/2+m_hSpace/2;
                    y = aboveItem->geometry().bottom()+m_vSpace;
                }
            }
            else//选择它头上的右侧控件作为头控件
            {
                aboveItem = itemList.at(k-i);
                x = aboveItem->geometry().left()-item->sizeHint().width()/2-m_hSpace/2;
                y = aboveItem->geometry().bottom()+m_vSpace;
            }
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        }
    }
}
