#ifndef POPWIDGET_H
#define POPWIDGET_H

#include <QWidget>

namespace Ui {
class PopWidget;
}

class PopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PopWidget(QWidget *parent = 0);
    ~PopWidget();

private slots:
    void on_pushButton_toggled(bool checked);

private:
    Ui::PopWidget *ui;
};

#endif // POPWIDGET_H
