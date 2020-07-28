#ifndef STDLAYOUTWIDGET_H
#define STDLAYOUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QDebug>

namespace Ui {
class StdLayoutWidget;
}

class StdLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StdLayoutWidget(QWidget *parent = 0);
    ~StdLayoutWidget();

private:
    void initHBoxLayout();
    void initGridLayout();

private:
    Ui::StdLayoutWidget *ui;

    QTabWidget* tabWidget;

};

#endif // STDLAYOUTWIDGET_H
