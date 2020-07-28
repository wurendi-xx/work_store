#include "standarddialogs.h"
#include "ui_standarddialogs.h"

StandardDialogs::StandardDialogs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StandardDialogs)
{
    ui->setupUi(this);
    ui->label_input->adjustSize();
    ui->line_path->adjustSize();
    ui->line_path->setGeometry(QRect(10, 50, 250, 27*4));  //四倍行距
    ui->line_path->setAlignment(Qt::AlignTop);
}

StandardDialogs::~StandardDialogs()
{
    delete ui;
}
///////////-----------------------------------------------输入对话框-----------------------------------------------------------------------------------------------///////////

//输入整形
void StandardDialogs::on_getint_3_clicked()
{
    bool ok;
        int i = QInputDialog::getInt(this, tr("情况"),
                                     tr("几岁毕业"), 25, 16, 100, 1, &ok);
        if (ok)
            ui->label_input->setText(tr("你%1岁毕业").arg(i));

}

//输入多精度
void StandardDialogs::on_getdouble_clicked()
{
    bool ok;
       double d = QInputDialog::getDouble(this, tr("工作"),
                                          tr("一天挣多少钱"), 1000, 100, 10000, 5, &ok);
       if (ok)
           ui->label_input->setText(QString("你一天挣%1￥").arg(d));

}


//输入单选
void StandardDialogs::on_geiitem_clicked()
{
    QStringList items;
        items << tr("王者荣耀") << tr("Dota") << tr("Dota2") << tr("LOL");

        bool ok;
        QString item = QInputDialog::getItem(this, tr("游戏"),
                                             tr("你玩哪一个"), items, 0, false, &ok);
        if (ok && !item.isEmpty())
            ui->label_input->setText(item+"是你玩的游戏");

}

//输入文本
void StandardDialogs::on_gettext_clicked()
{
    bool ok;
        QString text = QInputDialog::getText(this, tr("发展"),
                                             tr("想跳槽吗"), QLineEdit::Normal,
                                             tr("懒"), &ok);
        if (ok && !text.isEmpty())
            ui->label_input->setText(text);

}

//输入多文本
void StandardDialogs::on_getmtext_clicked()
{
    bool ok;
        QString text = QInputDialog::getMultiLineText(this, tr("计划"),
                                                      tr("下一步怎么做"), "走着瞧", &ok);
        if (ok && !text.isEmpty())
            ui->label_input->setText(text);
}

///////////-----------------------------------------------输入对话框-----------------------------------------------------------------------------------------------///////////

///////////-----------------------------------------------颜色对话框-----------------------------------------------------------------------------------------------///////////
//颜色选择
void StandardDialogs::on_btn_getcolor_clicked()
{
    QColorDialog::ColorDialogOptions option;
       if (ui->check_alpha->isChecked())
       {
           option = QColorDialog::ShowAlphaChannel;
       }
       const QColor color = QColorDialog::getColor(Qt::green, this, "选择颜色", option);

       if (color.isValid())
       {
           ui->btn_getcolor->setText(color.name());
           ui->btn_getcolor->setPalette(QPalette(color));
           ui->btn_getcolor->setAutoFillBackground(true);
           ui->progressBar->setPalette(QPalette(color));
           ui->progressBar->setAutoFillBackground(true);
           QString danger = "QProgressBar::chunk "
                            "{background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,"
                            "stop: 0 #FF0350,"
                            "stop: 0.4999 #FF0020,"
                            "stop: 0.5 #FF0019,"
                            "stop: 1 #FF0000 );"
                            "border-bottom-right-radius: 5px;"
                            "border-bottom-left-radius: 5px;"
                            "border: .px solid black;}";
           ui->progressBar->setStyleSheet(danger);

       }
}

///////////-----------------------------------------------颜色对话框-----------------------------------------------------------------------------------------------///////////

///////////-----------------------------------------------字体对话框-----------------------------------------------------------------------------------------------///////////

void StandardDialogs::on_btn_font_clicked_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->label_font->font(), this, tr("选择字体"));
    if (ok)
    {
        ui->label_font->setFont(font);
    }
}
///////////-----------------------------------------------字体对话框-----------------------------------------------------------------------------------------------///////////

///////////-----------------------------------------------文件对话框-----------------------------------------------------------------------------------------------///////////

//打开文件夹
void StandardDialogs::on_btn_dir_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                tr("获取文件夹"),
                                "./");
    if (!directory.isEmpty())
        ui->line_path->setText(directory);
}

//打开单个文件
void StandardDialogs::on_btn_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("打开一个文件"),
                                "./",
                                tr("All Files (*);;Text Files (*.txt)"));
    if (!fileName.isEmpty())
        ui->line_path->setText(fileName);
}

//打开多个文件
void StandardDialogs::on_btn_files_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
                                this, tr("打开多个文件"),
                                "./",
                                tr("All Files (*);;Text Files (*.txt)"));
    if (files.count())
    {
        qDebug()<<"list ="<<files;
        ui->line_path->setText(QString("[%1]").arg(files.join(", ")));
    }
}

//保存文件
void StandardDialogs::on_btn_savefile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("保存文件"),
                                "./",
                                tr("All Files (*);;Text Files (*.txt)"));
    if (!fileName.isEmpty())
        ui->line_path->setText(fileName);
}
///////////-----------------------------------------------文件对话框-----------------------------------------------------------------------------------------------///////////

///////////-----------------------------------------------提示对话框-----------------------------------------------------------------------------------------------///////////



void StandardDialogs::on_btn_critical_clicked()
{
    QMessageBox::critical(this, tr("危险"), tr("修路危险"), tr("返回"), tr("步行"), tr("无视"));
}

void StandardDialogs::on_btn_info_clicked()
{
    QMessageBox::information(this, tr("通知"), tr("会有个女朋友吗"), tr("不可能"), tr("真不可能"));

}

void StandardDialogs::on_btn_question_clicked()
{
QMessageBox::question(this, tr("问题"),
                    "喜欢身材好的还是颜值高的",
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

}

void StandardDialogs::on_btn_warning_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("警告"),
                       "不要调戏女朋友", 0, this);
    msgBox.setDetailedText(tr("真的别"));
    msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        qDebug() << "accept";
}


void StandardDialogs::on_btn_message_clicked()
{
    message.showMessage(tr("恭喜你中了5个亿，不好意思，系统出错"));
}

///////////-----------------------------------------------提示对话框-----------------------------------------------------------------------------------------------///////////

///////////-----------------------------------------------进度对话框-----------------------------------------------------------------------------------------------///////////
void StandardDialogs::on_btn_progress_clicked()
{
    int numFiles = 50000;
    QProgressDialog progress("复制文件中...", "中断", 0, numFiles, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for (int i = 0; i < numFiles; i++)
    {
        progress.setValue(i);
        //这个函数告诉Qt处理所有那些还没有被处理的各类事件，
        //然后将控制权返还给调用者.
        QCoreApplication::processEvents();
        if (progress.wasCanceled())
            break;
    }
    progress.setValue(numFiles);
}

///////////-----------------------------------------------进度对话框-----------------------------------------------------------------------------------------------///////////

///////////-----------------------------------------------向导对话框-----------------------------------------------------------------------------------------------///////////
void StandardDialogs::on_btn_wizard_clicked()
{
    QWizard w(this);
    w.setWindowTitle("向导");

    QWizardPage* page1 = new QWizardPage();
    QWizardPage* page2 = new QWizardPage();
    QWizardPage* page3 = new QWizardPage();

    page1->setTitle("第1步");
    page2->setTitle("第2步");
    page3->setTitle("第3步");

    w.addPage(page1);
    w.addPage(page2);
    w.addPage(page3);
    w.exec();
}
///////////-----------------------------------------------向导对话框-----------------------------------------------------------------------------------------------///////////
