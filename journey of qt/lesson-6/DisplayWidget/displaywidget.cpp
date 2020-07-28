#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);

    QStringList textList;
    textList << "PlainText" <<"RichText" << "AutoText";
    ui->combo_format->addItems(textList);

}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

void DisplayWidget::on_lineEdit_editingFinished()
{
    ui->label_display->setText(ui->lineEdit->text());

}

void DisplayWidget::on_check_links_toggled(bool checked)
{
    ui->label_display->setOpenExternalLinks(checked);

}

void DisplayWidget::on_check_scaled_toggled(bool checked)
{
    ui->label_display->setScaledContents(checked);

}

void DisplayWidget::on_check_wordWrap_toggled(bool checked)
{
    ui->label_display->setWordWrap(checked);

}

void DisplayWidget::on_spin_indent_valueChanged(int arg1)
{
    ui->label_display->setIndent(arg1);

}

void DisplayWidget::on_combo_format_currentIndexChanged(int index)
{
    ui->label_display->setTextFormat((Qt::TextFormat)index);

}

void DisplayWidget::on_pushButton_showgif_clicked()
{
    QMovie *movie = new QMovie("./wait.gif");
    if(NULL==movie){
        qDebug()<<"movie is NULL";
    }else{
            qDebug()<<"movie is not NULL";
    }
    ui->label_display->setMovie(movie);

    movie->start();

}
