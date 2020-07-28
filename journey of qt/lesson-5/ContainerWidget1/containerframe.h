#ifndef CONTAINERFRAME_H
#define CONTAINERFRAME_H

#include <QFrame>

namespace Ui {
class ContainerFrame;
}

class ContainerFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ContainerFrame(QWidget *parent = 0);
    ~ContainerFrame();

private slots:
    void on_combo_h_currentIndexChanged(int index);
    void on_combo_v_currentIndexChanged(int index);
    void on_combo_size_currentIndexChanged(int index);
    void on_comboBox_aligment_currentIndexChanged(int index);
    void on_checkBox_flat_toggled(bool checked);

private:
    Ui::ContainerFrame *ui;
};


#endif // CONTAINERFRAME_H
