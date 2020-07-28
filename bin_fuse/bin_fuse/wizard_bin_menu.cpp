#include "wizard_bin_menu.h"

Wizard_bin_menu::Wizard_bin_menu(QWidget *parent):
    QWizard(parent),
    page_main(new QWizardPage_main),
    page_season(new QWizardPage_season),
    page_state(new QWizardPage_state)
{
    //三个引导界面，分别用来填写主要，调料和状态信息
    page_main->setTitle("主要信息");
    page_season->setTitle("调料信息");
    page_state->setTitle("状态信息");


    //引导界面添加
    setPage(Wizard_bin_menu::Page_First,page_main);
    setPage(Wizard_bin_menu::Page_Second,page_season);
    setPage(Wizard_bin_menu::Page_Third,page_state);
    setWindowTitle("菜谱制作");

}

bool Wizard_bin_menu::validateCurrentPage()
{

    if(-1 == this->currentPage()->nextId())
    {
        return bin_maker();
    }

    return true;
}


bool Wizard_bin_menu::bin_maker()
{

    QString file_path = "menu.bin";
    QFile file(file_path);
    if(file.exists())
    {
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    }
    else
    {
        file.open(QIODevice::WriteOnly);
    }
    QDataStream out(&file);


    QByteArray tmp;
    //空常量
    char blank0[4];
    memset(blank0,'\0',4*sizeof(char));
    char blank1[20];
    memset(blank1,'\0',20*sizeof(char));
    char blank2[40];
    memset(blank2,'\0',40*sizeof(char));
    char blank3[1];
    memset(blank3,'\0',sizeof(char));
    int tmpInt;

    //开始写入数据

    tmp = field("menu_name").toByteArray();
    out.writeRawData(toGBK(tmp),tmp.size());
    for(int i = 0;i < 20-tmp.size();i++)
    {
        out.writeRawData(blank3,1);
    }



    tmp.clear();
    tmpInt = field("total_time").toInt();
    out.writeRawData((const char *)&tmpInt,4);
    tmp.clear();
    tmpInt = field("season_steps").toInt()+1;
    out.writeRawData((const char *)&tmpInt,4);
    tmp.clear();
    tmpInt = field("state_steps").toInt()+1;
    out.writeRawData((const char *)&tmpInt,4);
    tmp.clear();

    for(int i = 0;i < 5;i++)
    {
        tmp.clear();
        tmpInt = field("season_count"+QString::number(i)).toInt();
        if(tmp != nullptr)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        for(int j = 0;j < 5;j ++)
        {
            tmp.clear();
            tmp = field("season_detail"+QString::number(i)+QString::number(j)).toByteArray();
            if(tmp != nullptr)
            {
                out.writeRawData(toGBK(tmp),tmp.size());
                for(int i = 0;i < 20-tmp.size();i++)
                {
                    out.writeRawData(blank3,1);
                }
            }
            else
                out.writeRawData(blank1,20);
            tmp.clear();
            tmpInt = field("season_weight"+QString::number(i)+QString::number(j)).toInt();
            if(tmp != nullptr)
                out.writeRawData((const char *)&tmpInt,4);
            else
                out.writeRawData(blank0,4);
        }
    }

    tmp.clear();
    tmp = field("main_season_name").toByteArray();
    if(tmp != nullptr)
    {
        out.writeRawData(toGBK(tmp),tmp.size());
        for(int i = 0;i < 40-tmp.size();i++)
        {
            out.writeRawData(blank3,1);
        }

    }
    else
        out.writeRawData(blank2,40);

    for(int i = 0;i < 36;i ++)
    {
        int tmpInt;
        tmp.clear();
        tmpInt = field("run_state"+QString::number(i)).toInt();
        tmp = convert_state(tmpInt);
        if(tmp != nullptr)
            out.writeRawData(tmp,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpInt = field("run_cover"+QString::number(i)).toInt();
        tmp = convert_state(tmpInt);
        if(tmp != nullptr)
            out.writeRawData(tmp,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpInt = field("run_stir"+QString::number(i)).toInt();
        tmp = convert_state(tmpInt);
        if(tmp != nullptr)
            out.writeRawData(tmp,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpInt = field("run_power"+QString::number(i)).toInt()+1;
        if(tmp != nullptr)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpInt = field("run_time"+QString::number(i)).toInt();
        if(tmp != nullptr)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpInt = field("run_temperature"+QString::number(i)).toInt();
        if(tmp != nullptr)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmp = field("run_detail"+QString::number(i)).toByteArray();
        if(tmp != nullptr)
        {
            out.writeRawData(toGBK(tmp),tmp.size());
            for(int i = 0;i < 40 - tmp.size();i++)
            {
                out.writeRawData(blank3,1);
            }

        }
        else
            out.writeRawData(blank2,40);

    }

    file.close();
    return true;
}

QByteArray Wizard_bin_menu::convert_state(int input)
{
    QByteArray result;
    result.resize(4);
    switch(input)
    {
        case 0 : result[0] = 0x00;break;//"Preparation"
        case 1: result[0] = 0x01;break;//"CoverControl"
        case 2: result[0] = 0x02;break;//"Heating"
        case 3: result[0] = 0x03;break;//"Feeding"
        case 4: result[0] = 0x04;break;//"Cleaning"
        case 5: result[0] = 0x05;break;//"Waitting"
        case 6: result[0] = 0x06;break;//"PowerOn"
        case 7: result[0] = 0x07;break;//"NetCheck"
        case 8: result[0] = 0x08;break;//"ModeSet"
        case 9: result[0] = 0x09;break;//"MenuSelect"
        case 10: result[0] = 0x0A;break;//"Suspend"
        case 11: result[0] = 0x0B;break;//"Testing"
        case 12: result[0] = 0x0C;break;//"SeasonList"
        case 13: result[0] = 0x0D;break;//"CheckPreparation"
        case 14: result[0] = 0x0E;break;//"FixedModeSelect"
        case 15: result[0] = 0x0F;break;//"FixedModeWork"
    }
    result[1] = 0x00;
    result[2] = 0x00;
    result[3] = 0x00;
    return result;
}


QByteArray Wizard_bin_menu::toGBK(QString input)
{
    QTextCodec* gbk = QTextCodec::codecForName("gbk");
    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    QByteArray tmp_Qbit ;
    QString strUnicode;

    strUnicode= utf8->toUnicode(input.toLocal8Bit().data());
    tmp_Qbit= gbk->fromUnicode(strUnicode);
    return tmp_Qbit;

}
Wizard_bin_menu::~Wizard_bin_menu()
{

}
