/** @file wizard_bin_menu.cpp
 * @brief 菜谱制作bin文件的引导界面对象
 * @author Wu Rendi
 * @version 0.0.1.0
 * @date 2020-7-31
 */

#include "wizard_bin_menu.h"

#define INGREDIENTS_COUNT 8
#define SEASON_COUNT 8
#define STATE_COUNT 36

/**
 * @brief Wizard_bin_menu::Wizard_bin_menu 初始化引导界面，添加引导页（主要信息、调料信息、状态信息）
    @startuml 菜谱制作引导页
    (*) -right> "
    {{
    salt
    {
    <b>主要信息
    菜谱名字 | "   "
    运行时间 | "   "
    调料步骤 | ^ 1 ^
    状态步骤 | ^ 1 ^
    [next] | [cancel]
    }
    }}
    " as first

    first -right> "
    {{
    salt
    {
    <b>调料信息
    配料个数 | "   "
    文字描述 | "   "
    主料名称 | ^ 1 ^
    文字描述 | ^ 1 ^
    [next] | [cancel]
    }
    }}
    " as second

    second -right> "
    {{
    salt
    {
    <b>状态信息
    运行状态 | "   "
    锅盖状态 | "   "
    搅动状态 | ^ 1 ^
    火力功率 | ^ 1 ^
    运行时间 | ^ 1 ^
    运行温度 | ^ 1 ^
    文字描述 | ^ 1 ^
    [next] | [cancel]
    }
    }}
    " as third

    third -right>(*)
    @enduml
 */
Wizard_bin_menu::Wizard_bin_menu(QWidget *parent):
    QWizard(parent),
    page_main(new QWizardPage_main),
    page_ingredients(new QWizardPage_ingredients),
    page_season(new QWizardPage_season),
    page_state(new QWizardPage_state)
{
    //三个引导界面，分别用来填写主要，调料和状态信息
    page_main->setTitle("主要信息");
    page_ingredients->setTitle("主料信息");
    page_season->setTitle("调料信息");
    page_state->setTitle("状态信息");


    //引导界面添加
    setPage(Wizard_bin_menu::Page_First,page_main);
    setPage(Wizard_bin_menu::Page_Second,page_ingredients);
    setPage(Wizard_bin_menu::Page_Third,page_season);
    setPage(Wizard_bin_menu::Page_Fourth,page_state);
    setWindowTitle("菜谱制作");

    //setWizardStyle(QWizard::MacStyle);

}

/**
 * @brief Wizard_bin_menu::validateCurrentPage 引导界面finish的触发入口
 * @return
 */
bool Wizard_bin_menu::validateCurrentPage()
{
    if(-1 == this->currentPage()->nextId())
    {
        return bin_maker();
    }

    return true;
}

/**
 * @brief Wizard_bin_menu::bin_maker 将引导界面的输入控件的值写入bin文件
 * @return
 */
bool Wizard_bin_menu::bin_maker()
{

    QString file_path = "menu\\menu" + QString::number((field("menu_id").toInt()),10) + ".bin";
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
    int tmpInt;
    QByteArray tmpStr;
    //空常量,用于配合地址计数器填充空白区域
    char blank0[4];
    memset(blank0,'\0',4*sizeof(char));
    char blank1[20];
    memset(blank1,'\0',20*sizeof(char));
    char blank2[40];
    memset(blank2,'\0',40*sizeof(char));
    char blank3[1];
    memset(blank3,'\0',sizeof(char));


    //开始写入数据
    //写入菜谱ID

    tmpInt = field("menu_id").toInt();
    out.writeRawData((const char*)&tmpInt,4);
    //写入菜谱名
    tmp.clear();
    tmpStr.clear();
    tmp = field("menu_name").toByteArray();
    if(tmp != nullptr)
    {
        tmpStr = toGBK(tmp);
        out.writeRawData(tmpStr,tmpStr.size());
        for(int i = 0;i < 20 - tmpStr.size();i++)
        {
            out.writeRawData(blank3,1);
        }

    }
    else
        out.writeRawData(blank1,20);


    //写入总时间
    tmpInt = field("total_time").toInt();
    out.writeRawData((const char *)&tmpInt,4);

    //写入调料步骤数
    tmpInt = field("season_steps").toInt()+1;
    out.writeRawData((const char *)&tmpInt,4);

    //写入状态步骤数
    tmpInt = field("state_steps").toInt()+1;
    out.writeRawData((const char *)&tmpInt,4);


    //写入调料盒描述
    for(int i = 0;i < 5;i++)
    {
        //调料个数
        tmpInt = field("season_count"+QString::number(i)).toInt();
        if(tmpInt != 0)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        for(int j = 0;j < SEASON_COUNT;j ++)
        {
            tmp.clear();
            tmpStr.clear();
            tmp = field("season_detail"+QString::number(i)+QString::number(j)).toByteArray();
            if(tmp != nullptr)
            {
                tmpStr = toGBK(tmp);
                out.writeRawData(tmpStr,tmpStr.size());
                for(int i = 0;i < 20 - tmpStr.size();i++)
                {
                    out.writeRawData(blank3,1);
                }
            }
            else
                out.writeRawData(blank1,20);

            tmp.clear();
            tmpInt = field("season_weight"+QString::number(i)+QString::number(j)).toInt();
            if(tmpInt != 0)
                out.writeRawData((const char *)&tmpInt,4);
            else
                out.writeRawData(blank0,4);

            tmp.clear();
            tmpInt = field("season_unit"+QString::number(i)+QString::number(j)).toInt();
            if(tmpInt != 0)
                out.writeRawData((const char *)&tmpInt,4);
            else
                out.writeRawData(blank0,4);
        }
    }

    //写入主料描述
    //写入主料数量

    tmpInt = field("ingredients").toInt()+1;
    if(tmpInt != 0)
        out.writeRawData((const char *)&tmpInt,4);
    else
        out.writeRawData(blank0,4);
    //写入主料信息
    for(int i = 0;i < INGREDIENTS_COUNT;i++)
    {

        tmp.clear();
        tmpStr.clear();
        tmp = field("ingredient_detail"+QString::number(i)).toByteArray();
        if(tmp != nullptr)
        {
            tmpStr = toGBK(tmp);
            out.writeRawData(tmpStr,tmpStr.size());
            for(int i = 0;i < 20 - tmpStr.size();i++)
            {
                out.writeRawData(blank3,1);
            }
        }
        else
            out.writeRawData(blank1,20);

        tmp.clear();
        tmpInt = field("ingredient_weight"+QString::number(i)).toInt();
        if(tmpInt != 0)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);

        tmp.clear();
        tmpInt = field("ingredient_unit"+QString::number(i)).toInt();
        if(tmpInt != 0)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);

        tmp.clear();
        tmpInt = field("ingredient_category"+QString::number(i)).toInt();
        if(tmpInt != 0)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);

    }


    //写入运行状态描述
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
        tmpInt = field("run_power"+QString::number(i)).toInt();
        if(tmpInt != 0)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpInt = field("run_time"+QString::number(i)).toInt();
        if(tmpInt != 0)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpInt = field("run_temperature"+QString::number(i)).toInt();
        if(tmpInt != 0)
            out.writeRawData((const char *)&tmpInt,4);
        else
            out.writeRawData(blank0,4);
        tmp.clear();
        tmpStr.clear();
        tmp = field("run_detail"+QString::number(i)).toByteArray();
        if(tmp != nullptr)
        {
            tmpStr = toGBK(tmp);
            out.writeRawData(tmpStr,tmpStr.size());
            for(int i = 0;i < 40 - tmpStr.size();i++)
            {
                out.writeRawData(blank3,1);
            }

        }
        else
            out.writeRawData(blank2,40);
    }

    file.close();

    file.open(QIODevice::ReadWrite);

    QByteArray totalData = file.readAll();

    uint32_t sumCheck = 0;

    std::for_each(totalData.begin(),totalData.end(),[&sumCheck](auto a){sumCheck += a;});

//    foreach (uint8_t tmp, totalData) {
//        sumCheck += tmp;

//    }

    out.writeRawData((const char *)&sumCheck,4);

    file.close();


    return true;
}

/**
 * @brief Wizard_bin_menu::convert_state 将机器的状态映射到具体字节
 * @param[in] input 枚举类型的输入
 * @return QByteArray类型的二进制数据
 */
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

/**
 * @brief Wizard_bin_menu::toGBK 将QString类型的字符串转化为GBK编码的字符串
 * @note Qt中QString的默认字符编码为Unicode，写入MCU的字符串类型为GBK
 * @param input QString类型字符串
 * @return
 */
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
