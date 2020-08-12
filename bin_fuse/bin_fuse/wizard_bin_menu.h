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
        Page_Third
    };

private:
    QWizardPage_main* page_main;
    QWizardPage_season* page_season;
    QWizardPage_state* page_state;

    bool bin_maker();
    QByteArray convert_state(int input);
    QByteArray toGBK(QString input);





};



#endif // WIZARD_BIN_MENU_H
