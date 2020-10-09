#ifndef WIZARD_BIN_MENU_H
#define WIZARD_BIN_MENU_H

#include "form_bin_menu.h"

#include <QWidget>
#include <QWizard>
#include <QWizardPage>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QFile>
#include <QTextCodec>
#include <cstring>

/**
 * @brief The Wizard_bin_menu class 菜谱制作引导功能实现
 */
class Wizard_bin_menu : public QWizard
{
    Q_OBJECT
public:
   explicit Wizard_bin_menu(QWidget *parent = 0);
    ~Wizard_bin_menu();
    bool validateCurrentPage();

    enum
    {
        Page_First,
        Page_Second,
        Page_Third,
        Page_Fourth
    };

private:
    QWizardPage_main* page_main;
    QWizardPage_ingredients* page_ingredients;
    QWizardPage_season* page_season;
    QWizardPage_state* page_state;

    /**
     * @brief bin_maker核心功能，制作菜谱bin文件
     */
    bool bin_maker();
    /**
     * @brief convert_state 将下拉列表的索引值转化为写入bin的格式
     */
    QByteArray convert_state(int input);
    /**
     * @brief toGBK 将UTF-8编码的字符改为GBK编码，以便MCU读取
     */
    QByteArray toGBK(QString input);





};



#endif // WIZARD_BIN_MENU_H
