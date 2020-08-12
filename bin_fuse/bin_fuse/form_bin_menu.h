#ifndef FORM_BIN_MENU_H
#define FORM_BIN_MENU_H

#include <QWidget>
#include <QWizard>
#include <QWizardPage>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QTabWidget>
#include <QVector>

/**
 * @brief The form_bin_menu class 菜谱制作页的预留类
 */
class form_bin_menu : public QWizardPage
{
public:
    form_bin_menu();

};

/**
 * @brief The QWizardPage_main class 菜谱制作第一页主要信息的引导页界面
 */
class QWizardPage_main : public QWizardPage
{
public:
    QWizardPage_main();

    QString menu_name;
    int menu_total_time;
    int menu_senson_step;
    int menu_state_step;
private:
//    bool validatePage();
};

/**
 * @brief The QWizardPage_season class 菜谱制作第二页调料信息的引导页界面
 */
class QWizardPage_season : public QWizardPage
{
public:
    QWizardPage_season();
    void initializePage();
    void cleanupPage();


private:
    //用于排版tabWidget界面
    QVBoxLayout* hLayout;

};

/**
 * @brief The QWizardPage_state class 菜谱制作第三页状态信息的引导页界面
 */
class QWizardPage_state : public QWizardPage
{
public:
    QWizardPage_state();
    void initializePage();
    void cleanupPage();


private:
    //用于排版tabWidget界面
    QHBoxLayout* hLayout;

};

#endif // FORM_BIN_MENU_H
