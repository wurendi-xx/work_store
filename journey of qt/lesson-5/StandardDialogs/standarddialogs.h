#ifndef STANDARDDIALOGS_H
#define STANDARDDIALOGS_H

#include <QWidget>
#include <QInputDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QProgressDialog>
#include <QWizard>
#include <QErrorMessage>

namespace Ui {
class StandardDialogs;
}

class StandardDialogs : public QWidget
{
    Q_OBJECT

public:
    explicit StandardDialogs(QWidget *parent = 0);
    ~StandardDialogs();
    QErrorMessage message;

private slots:
    void on_getint_3_clicked();

    void on_getdouble_clicked();

    void on_geiitem_clicked();

    void on_gettext_clicked();

    void on_getmtext_clicked();

    void on_btn_getcolor_clicked();

    void on_btn_font_clicked_clicked();

    void on_btn_dir_clicked();

    void on_btn_file_clicked();

    void on_btn_files_clicked();

    void on_btn_savefile_clicked();

    void on_btn_critical_clicked();

    void on_btn_info_clicked();

    void on_btn_question_clicked();

    void on_btn_warning_clicked();

    void on_btn_message_clicked();

    void on_btn_progress_clicked();

    void on_btn_wizard_clicked();

private:
    Ui::StandardDialogs *ui;
};

#endif // STANDARDDIALOGS_H
