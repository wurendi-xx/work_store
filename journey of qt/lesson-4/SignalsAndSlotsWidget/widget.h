#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void signShowVal(const QString&);

public slots:
    void sliderLineEditChanged(const QString& text);

    void LabelEditChanged(int value);


private slots:
    void on_pushButton_toggled(bool checked);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
