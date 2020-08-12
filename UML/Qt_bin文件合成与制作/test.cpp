/**
 * @file test.cpp
 * @author WuRendi (wurendikunn@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020 Tineco
 * 
 */

#include <studio.h>



/**
 * @brief 
 * 
 * @param input 
 * @return QByteArray 
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