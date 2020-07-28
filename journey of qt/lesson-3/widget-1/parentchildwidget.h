#ifndef PARENTCHILDWIDGET_H
#define PARENTCHILDWIDGET_H

#include <QWidget>

namespace Ui {
class ParentChildWidget;
}

class ParentChildWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParentChildWidget(QWidget *parent = 0);
    ~ParentChildWidget();

private:
    Ui::ParentChildWidget *ui;
};

#endif // PARENTCHILDWIDGET_H
