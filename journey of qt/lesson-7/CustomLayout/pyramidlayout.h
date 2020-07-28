#ifndef PYRAMIDLAYOUT_H
#define PYRAMIDLAYOUT_H

#include <QLayout>
#include <QWidget>

class PyramidLayout: public QLayout
{
public:
    PyramidLayout(QWidget *parent, int margin = 9,
                  int hSpacing = 9, int vSpacing = 9);
    PyramidLayout(int margin = 9, int hSpacing = 9, int vSpacing = 9);
    ~PyramidLayout();

    void addItem(QLayoutItem *item) override ;
    void setGeometry(const QRect &rect) override ;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index)  override;
    int count() const;

    QSize minimumSize() const override;
    QSize sizeHint() const override;
    int rowCount() const;

private:
    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;
};

#endif // PYRAMIDLAYOUT_H
