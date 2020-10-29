/** @file wizard_bin_fuse.cpp
 * @brief 合成bin文件的引导界面对象
 * @author Wu Rendi
 * @version 0.0.1.0
 * @date 2020-7-31
 */
#include "wizard_bin_fuse.h"
/**
 * @defgroup BIN_INFO
 * @brief bin文件的大小和结束地址
 * @{
 */
//bin文件结束地址
#define MENU_ADD 300
#define PIC_8K_ADD 1100
#define PIC_28K_ADD 3900
#define PIC_60K_ADD 6900
#define PIC_120K_ADD 8340
#define FONT_16_ADD 9240
#define FONT_32_ADD 12840
#define FONT_56_ADD 16240
#define AFONT_16_ADD 16252
#define AFONT_32_ADD 16300
#define AFONT_56_ADD 16340
//bin文件大小
#define MENU_SIZE 4
#define PIC_8K_SIZE 8
#define PIC_28K_SIZE 28
#define PIC_60K_SIZE 60
#define PIC_120K_SIZE 120
#define FONT_16_SIZE 300
#define FONT_32_SIZE 1200
#define FONT_56_SIZE 3400
#define AFONT_16_SIZE 4
#define AFONT_32_SIZE 16
#define AFONT_56_SIZE 40

/**
 *@}
 */

/**
 * @brief Wizard_bin_fuse::Wizard_bin_fuse 初始化引导界面，并且添加需要的引导页（菜单、图片、字库）
    @startuml bin文件融合引导页
    (*) -right> "
    {{
    salt
    {
    <b>菜谱bin
    文件地址
    [选择所有文件]
    [next] | [cancel]
    }
    }}
    " as first

    first -right> "
    {{
    salt
    {
    <b>图片8K
    文件地址
    [选择所有文件]
    [next] | [cancel]
    }
    }}
    " as second

    second -right> "
    {{
    salt
    {
    <b>图片28K
    文件地址
    [选择所有文件]
    [next] | [cancel]
    }
    }}
    " as thrid

    thrid -right> "
    {{
    salt
    {
    <b>图片60K
    文件地址
    [选择所有文件]
    [next] | [cancel]
    }
    }}
    " as fourth

    fourth -right> "
    {{
    salt
    {
    <b>图片120K
    文件地址
    [选择所有文件]
    [next] | [cancel]
    }
    }}
    " as fiveth

    fiveth -right> "
    {{
    salt
    {
    <b>字库bin
    文件地址
    [选择所有文件]
    [next] | [cancel]
    }
    }}
    " as sixth

    sixth -right>(*)

    @enduml
 */
Wizard_bin_fuse::Wizard_bin_fuse(QWidget *parent) :
    QWizard(parent),
    page_menu(new Form_bin_fuse),
    page_pic_8k(new Form_bin_fuse),
    page_pic_28k(new Form_bin_fuse),
    page_pic_60k(new Form_bin_fuse),
    page_pic_120k(new Form_bin_fuse),
    page_font(new Form_bin_fuse),
    page_font_ASCII(new Form_bin_fuse)
{

    page_menu->setTitle("菜谱融合");
    page_pic_8k->setTitle("8K图片融合");
    page_pic_28k->setTitle("28K图片融合");
    page_pic_60k->setTitle("60K图片融合");
    page_pic_120k->setTitle("120K图片融合");
    page_font->setTitle("BGK字体融合");
    page_font_ASCII->setTitle("ASCII字库融合");

    setPage(Wizard_bin_fuse::Page_Menu,page_menu);
    setPage(Wizard_bin_fuse::Page_Pic8K,page_pic_8k);
    setPage(Wizard_bin_fuse::Page_Pic28K,page_pic_28k);
    setPage(Wizard_bin_fuse::Page_Pic60K,page_pic_60k);
    setPage(Wizard_bin_fuse::Page_Pic120K,page_pic_120k);
    setPage(Wizard_bin_fuse::Page_Font,page_font);
    setPage(Wizard_bin_fuse::Page_Font_ASCII,page_font_ASCII);
    setWindowTitle("bin文件融合");

}
/**
 * @brief Wizard_bin_fuse::validateCurrentPage 引导界面的finish按钮触发入口
 * @param NONE
 * @return true 运行成功
 *         false 运行错误
 */
bool Wizard_bin_fuse::validateCurrentPage()
{
    //点击finish触发
    if(-1 == this->currentPage()->nextId())
    {
        return bin_fuse();
    }

    return true;
}

/**
 * @brief Wizard_bin_fuse::bin_fuse 读取引导界面收集的所有bin文件路径，按照一定的规则整合为一个bin文件
 * @return true 运行成功
 *         false 运行错误
 */

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

    //写入文件记录
    QString log_file_path = "fuse_log.txt";
    QFile fuse_log_file(log_file_path);
    fuse_log_file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
    out_log.setDevice(&fuse_log_file);

    //读取文件地址
    QStringList menu_file =  page_menu->files;
    QStringList pic_8k_file =  page_pic_8k->files;
    QStringList pic_28K_file =  page_pic_28k->files;
    QStringList pic_60k_file =  page_pic_60k->files;
    QStringList pic_120k_file =  page_pic_120k->files;
    QStringList font_file =  page_font->files;
    QStringList fontA_file = page_font_ASCII->files;

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

    //GBK字库融合
    QStringList font_16_file;
    QStringList font_32_file;
    QStringList font_56_file;
    for(int i = 0;i < font_file.size();i ++)
    {
       QFileInfo fi = QFileInfo(font_file[i]);
       QString fi_name = fi.fileName();
       QRegExp regExp1("16x16[\\w\\W]*.bin");
       QRegExp regExp2("(20|24|32)x(20|24|32)[\\w\\W]*.bin");
       QRegExp regExp3("56x56[\\w\\W]*.bin");
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



    //ASCII字库融合
    QStringList fontA_16_file;
    QStringList fontA_32_file;
    QStringList fontA_56_file;
    for(int i = 0;i < fontA_file.size();i ++)
    {
       QFileInfo fi = QFileInfo(fontA_file[i]);
       QString fi_name = fi.fileName();
       QRegExp regExp1("16x16[\\w\\W]*.bin");
       QRegExp regExp2("(20|24|32)x(20|24|32)[\\w\\W]*.bin");
       QRegExp regExp3("56x56[\\w\\W]*.bin");
        if(regExp1.indexIn(fi_name) != -1)
            fontA_16_file<<fontA_file[i];
        if(regExp2.indexIn(fi_name) != -1)
            fontA_32_file<<fontA_file[i];
        if(regExp3.indexIn(fi_name) != -1)
            fontA_56_file<<fontA_file[i];
    }
    bin_write(out,fontA_16_file,progressBar,AFONT_16_SIZE,AFONT_16_ADD,cur_index);
    bin_write(out,fontA_32_file,progressBar,AFONT_32_SIZE,AFONT_32_ADD,cur_index);
    bin_write(out,fontA_56_file,progressBar,AFONT_56_SIZE,AFONT_56_ADD,cur_index);

    fuse_log_file.close();
    fuse_file.close();
    return true;
}

/**
 * @brief Wizard_bin_fuse::fill_rest
 * @param out bin文件输入流
 * @param input_add 文件结束地址
 * @param cur_index 当前地址辅助计数器
 */
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


/**
 * @brief Wizard_bin_fuse::bin_write
 * @param out bin文件输入流
 * @param input_file_list 文件名队列
 * @param progressBar 进度条控件
 * @param bin_size 写入文件大小
 * @param bin_address 文件结束地址
 * @param cur_index 当前地址辅助计数器
 * @return 是否运行成功
 */
bool Wizard_bin_fuse::bin_write(QDataStream &out,QStringList &input_file_list,QProgressDialog *progressBar,int bin_size,int bin_address,int &cur_index)
{
    out_log<<"//binSize"<<bin_size<<"K"<<endl;

    for(int i = 0;i < input_file_list.size();i++)
    {
        QString str_path = input_file_list[i];
        QFile file(str_path);
        file.open(QIODevice::ReadOnly);
        int file_size = int(file.size());
        QByteArray tmp = file.readAll();
        out.writeRawData(tmp,file_size);
        //写入输出文件地址记录
        QFileInfo fi = QFileInfo(str_path);
        QString fi_name = fi.fileName();
        out_log<<"#define "<<fi_name<<" "<<cur_index<<"*1024"<<endl;

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
            QMessageBox::critical(this,tr("错误"),str_path+tr("文件大小存在溢出，请检查！"),tr("返回"));
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
