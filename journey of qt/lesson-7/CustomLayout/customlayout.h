#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H

#include <QWidget>

#include <QLabel>

class CustomLayout : public QWidget
{
    Q_OBJECT

public:
    CustomLayout(QWidget *parent = 0);
    ~CustomLayout();
};

#endif // CUSTOMLAYOUT_H
