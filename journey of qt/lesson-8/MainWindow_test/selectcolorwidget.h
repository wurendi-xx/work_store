#ifndef SELECTCOLORWIDGET_H
#define SELECTCOLORWIDGET_H

#include <QWidget>

namespace Ui {
class SelectColorWidget;
}

class QButtonGroup;
class SelectColorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectColorWidget(QWidget *parent = 0);
    ~SelectColorWidget();

signals:
    void clrButtonClicked(const QColor& clr);

private:
    Ui::SelectColorWidget *ui;
    QButtonGroup* m_btnGroup;
};

#endif // SELECTCOLORWIDGET_H
