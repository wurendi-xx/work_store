#include "wizard_bin_fuse.h"

//bin文件结束地址
#define MENU_ADD 300
#define PIC_8K_ADD 1100
#define PIC_28K_ADD 2500
#define PIC_60K_ADD 3700
#define PIC_120K_ADD 5120
#define FONT_16_ADD 6020
#define FONT_32_ADD 9620
#define FONT_56_ADD 13020
//bin文件大小
#define MENU_SIZE 4
#define PIC_8K_SIZE 8
#define PIC_28K_SIZE 28
#define PIC_60K_SIZE 60
#define PIC_120K_SIZE 120
#define FONT_16_SIZE 300
#define FONT_32_SIZE 1200
#define FONT_56_SIZE 3400

Wizard_bin_fuse::Wizard_bin_fuse(QWidget *parent) :
    QWizard(parent),
    page_menu(new Form_bin_fuse),
    page_pic_8k(new Form_bin_fuse),
    page_pic_28k(new Form_bin_fuse),
    page_pic_60k(new Form_bin_fuse),
    page_pic_120k(new Form_bin_fuse),
    page_font(new Form_bin_fuse)
{

    page_menu->setTitle("菜谱融合");
    page_pic_8k->setTitle("8K图片融合");
    page_pic_28k->setTitle("28K图片融合");
    page_pic_60k->setTitle("60K图片融合");
    page_pic_120k->setTitle("120K图片融合");
    page_font->setTitle("字体融合");

    setPage(Wizard_bin_fuse::Page_Menu,page_menu);
    setPage(Wizard_bin_fuse::Page_Pic8K,page_pic_8k);
    setPage(Wizard_bin_fuse::Page_Pic28K,page_pic_28k);
    setPage(Wizard_bin_fuse::Page_Pic60K,page_pic_60k);
    setPage(Wizard_bin_fuse::Page_Pic120K,page_pic_120k);
    setPage(Wizard_bin_fuse::Page_Font,page_font);
    setWindowTitle("bin文件融合");

}

bool Wizard_bin_fuse::validateCurrentPage()
{
    //点击finish触发
    if(-1 == this->currentPage()->nextId())
    {
        return bin_fuse();
    }

    return true;
}

bool Wizard_bin_fuse::bin_fuse()
{
    //写入文件创建
    QString file_path = "fuse.bin";
    QFile fuse_file(file_path);
    if(fuse_file.exists())
    {
        fuse_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    }
    else
    {
        fuse_file.open(QIODevice::WriteOnly);
    }
    QDataStream out(&fuse_file);

    //读取文件地址
    QStringList menu_file =  page_menu->files;
    QStringList pic_8k_file =  page_pic_8k->files;
    QStringList pic_28K_file =  page_pic_28k->files;
    QStringList pic_60k_file =  page_pic_60k->files;
    QStringList pic_120k_file =  page_pic_120k->files;
    QStringList font_file =  page_font->files;

    //辅助确定当前写入指针位置
    int cur_index = 0;

    //进度条显示
    QProgressDialog* progressBar = new QProgressDialog;
    progressBar->setWindowModality(Qt::WindowModal);
    progressBar->setWindowTitle(tr("bin文件融合"));
    progressBar->setLabelText(tr("写入中"));
    progressBar->setRange(0,FONT_56_ADD);
    //connect(&cur_index,SIGNAL(valueChanged(int)),&progressBar,[=](){progressBar->setValue(cur_index);});
    progressBar->setValue(cur_index);

    //存放版本信息
/*
    QByteArray tmp = "";
    out.writeRawData(tmp,1024*4);
    cur_index += 4;
*/
    fill_rest(out,4,cur_index);

    //菜谱融合
    bin_write(out,menu_file,progressBar,MENU_SIZE,MENU_ADD,cur_index);

    //8k图片融合
    bin_write(out,pic_8k_file,progressBar,PIC_8K_SIZE,PIC_8K_ADD,cur_index);

    //28k图片融合
    bin_write(out,pic_28K_file,progressBar,PIC_28K_SIZE,PIC_28K_ADD,cur_index);

    //60k图片融合
    bin_write(out,pic_60k_file,progressBar,PIC_60K_SIZE,PIC_60K_ADD,cur_index);

    //120k图片融合
    bin_write(out,pic_120k_file,progressBar,PIC_120K_SIZE,PIC_120K_ADD,cur_index);

    //字库融合
    QStringList font_16_file;
    QStringList font_32_file;
    QStringList font_56_file;
    for(int i = 0;i < font_file.size();i ++)
    {
       QFileInfo fi = QFileInfo(font_file[i]);
       QString fi_name = fi.fileName();
       QRegExp regExp1("1616\S*.bin");
       QRegExp regExp2("3232\S*.bin");
       QRegExp regExp3("5656\S*.bin");
        if(regExp1.indexIn(fi_name) != -1)
            font_16_file<<font_file[i];
        if(regExp2.indexIn(fi_name) != -1)
            font_32_file<<font_file[i];
        if(regExp3.indexIn(fi_name) != -1)
            font_56_file<<font_file[i];
    }
    bin_write(out,font_16_file,progressBar,FONT_16_SIZE,FONT_16_ADD,cur_index);
    bin_write(out,font_32_file,progressBar,FONT_32_SIZE,FONT_32_ADD,cur_index);
    bin_write(out,font_56_file,progressBar,FONT_56_SIZE,FONT_56_ADD,cur_index);


    fuse_file.close();
    return true;
}

void Wizard_bin_fuse::fill_rest(QDataStream &out,int input_add,int &cur_index)
{
    int empty_space = input_add - cur_index;
    for(int i = 0;i < empty_space;i ++)
    {
        char none_ptr[1024];
        memset(none_ptr,'\0',1024*sizeof(char));
        out.writeRawData(none_ptr,1024);
    }
    cur_index = input_add;
}

bool Wizard_bin_fuse::bin_write(QDataStream &out,QStringList &input_file_list,QProgressDialog *progressBar,int bin_size,int bin_address,int &cur_index)
{

    for(int i = 0;i < input_file_list.size();i++)
    {
        QString str_path = input_file_list[i];
        QFile file(str_path);
        file.open(QIODevice::ReadOnly);
        auto file_size = file.size();
        QByteArray tmp = file.readAll();
        out.writeRawData(tmp,file_size);
        int deviation = bin_size*1024 - file_size;
        if(deviation >= 0)
        {
            int tmp = deviation/1024;
            int last = deviation - tmp*1024;
            for(int i = 0;i < tmp;i ++)
            {
                char none_ptr[1024];
                memset(none_ptr,'\0',1024*sizeof(char));
                out.writeRawData(none_ptr,1024);
            }
            if(last > 0)
            {
                char none_ptr[last];
                memset(none_ptr,'\0',last*sizeof(char));
                out.writeRawData(none_ptr,last);
            }
        }
        else
        {
            QMessageBox::critical(this,tr("错误"),tr("文件大小存在溢出，请检查！"),tr("返回"));
            return false;
        }
        cur_index += bin_size;
        progressBar->setValue(cur_index);
        file.close();
    }
    if(cur_index > bin_address)
    {
        QMessageBox::critical(this,tr("错误"),tr("文件数目存在溢出，请检查！"),tr("返回"));
        return false;
    }
    //剩余空间填满
    fill_rest(out,bin_address,cur_index);
    progressBar->setValue(cur_index);
    return true;
}

Wizard_bin_fuse::~Wizard_bin_fuse()
{

}
