#ifndef FORM_BIN_FUSE_H
#define FORM_BIN_FUSE_H

#include <QWizardPage>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class Form_bin_fuse;
}

/**
 * @brief The Form_bin_fuse class bin文件融合的引导页界面
 */
class Form_bin_fuse : public QWizardPage
{
    Q_OBJECT

public:
    explicit Form_bin_fuse(QWizardPage *parent = 0);
    ~Form_bin_fuse();
    QStringList files;

private slots:
    void on_pushButton_file_select_clicked();

private:
    Ui::Form_bin_fuse *ui;
};

#endif // FORM_BIN_FUSE_H
