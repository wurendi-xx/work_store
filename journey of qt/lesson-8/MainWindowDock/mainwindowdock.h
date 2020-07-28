#ifndef MAINWINDOWDOCK_H
#define MAINWINDOWDOCK_H

#include <QMainWindow>

namespace Ui {
class MainWindowDock;
}

class QListWidgetItem;

class MainWindowDock : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowDock(QWidget *parent = 0);
    ~MainWindowDock();

private slots:
    void on_listWidget_areas_itemChanged(QListWidgetItem *item);

    void on_listWidget_features_itemChanged(QListWidgetItem *item);

private:
    Ui::MainWindowDock *ui;
};

#endif // MAINWINDOWDOCK_H
