#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QMovie>
#include <QDebug>

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

private slots:
    void on_lineEdit_editingFinished();

    void on_check_links_toggled(bool checked);

    void on_check_scaled_toggled(bool checked);

    void on_check_wordWrap_toggled(bool checked);

    void on_spin_indent_valueChanged(int arg1);

    void on_combo_format_currentIndexChanged(int index);

    void on_pushButton_showgif_clicked();

private:
    Ui::DisplayWidget *ui;
};

#endif // DISPLAYWIDGET_H
