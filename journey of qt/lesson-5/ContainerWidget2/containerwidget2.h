#ifndef CONTAINERWIDGET2_H
#define CONTAINERWIDGET2_H

#include <QWidget>

namespace Ui {
class ContainerWidget2;
}

class ContainerWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerWidget2(QWidget *parent = 0);
    ~ContainerWidget2();

private slots:
    void on_combo_elide_currentIndexChanged(int index);

    void on_combo_tabposition_currentIndexChanged(int index);

    void on_combo_tabshape_currentIndexChanged(int index);

    void on_check_document_toggled(bool checked);

    void on_check_autohide_toggled(bool checked);

    void on_check_moveable_toggled(bool checked);

    void on_check_closable_toggled(bool checked);

    void on_check_scrollBtns_toggled(bool checked);

    void on_btn_addItem_clicked();

    void on_btn_delItem_clicked();

    void on_pushButton_clicked();

    void on_check_flat_stateChanged(int arg1);


private:
    Ui::ContainerWidget2 *ui;
};

#endif // CONTAINERWIDGET2_H
