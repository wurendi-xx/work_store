#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QSignalMapper>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
