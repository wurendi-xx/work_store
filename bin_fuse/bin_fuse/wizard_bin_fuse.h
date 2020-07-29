#ifndef WIZARD_BIN_FUSE_H
#define WIZARD_BIN_FUSE_H

#include <QWizard>
#include <QProgressDialog>
#include <QMessageBox>
#include "ui_form_bin_fuse.h"
#include "form_bin_fuse.h"


namespace Ui {
class QWizard;
}

class Wizard_bin_fuse : public QWizard
{
    Q_OBJECT
public:
    explicit Wizard_bin_fuse(QWidget *parent = 0);
    ~Wizard_bin_fuse();
    bool validateCurrentPage();

    enum
    {
        Page_Menu,
        Page_Pic8K,
        Page_Pic28K,
        Page_Pic60K,
        Page_Pic120K,
        Page_Font,
    };


private:
    Form_bin_fuse* page_menu;
    Form_bin_fuse* page_pic_8k;
    Form_bin_fuse* page_pic_28k;
    Form_bin_fuse* page_pic_60k;
    Form_bin_fuse* page_pic_120k;
    Form_bin_fuse* page_font;

    bool bin_fuse();
    void fill_rest(QDataStream &out, int input_add, int &cur_index);
    bool bin_write(QDataStream &out,QStringList &input_file_list,QProgressDialog* progressBar,int bin_size,int bin_address,int &cur_index);

};

#endif // WIZARD_BIN_FUSE_H
