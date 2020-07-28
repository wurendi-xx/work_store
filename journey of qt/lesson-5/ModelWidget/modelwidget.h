#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>

namespace Ui {
class ModelWidget;
}

class ModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelWidget(QWidget *parent = 0);
    ~ModelWidget();



private slots:
    void on_btnWindow_clicked();

    void on_btnApp_clicked();

    void on_btnCustom_clicked();

private:
    Ui::ModelWidget *ui;
};

#endif // MODELWIDGET_H
