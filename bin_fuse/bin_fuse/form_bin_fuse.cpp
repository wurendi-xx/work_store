#include "form_bin_fuse.h"
#include "ui_form_bin_fuse.h"

Form_bin_fuse::Form_bin_fuse(QWizardPage *parent) :
    QWizardPage(parent),
    ui(new Ui::Form_bin_fuse)
{
    ui->setupUi(this);
}

Form_bin_fuse::~Form_bin_fuse()
{
    delete ui;
}

/**
 * @brief Form_bin_fuse::on_pushButton_file_select_clicked 打开多个文件按钮的入口程序
 */
void Form_bin_fuse::on_pushButton_file_select_clicked()
{
    files = QFileDialog::getOpenFileNames(
                                this, tr("打开多个文件"),
                                "./",
                                tr("Bin Files (*.bin)"));
    if (files.count())
    {
        ui->textBrowser_file_list->setText(QString("%1").arg(files.join(",")));
    }

}
