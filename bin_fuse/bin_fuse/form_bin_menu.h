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

    QString menu_name;/**< 记录菜谱名称（unused）*/
    int menu_total_time;/**< 记录菜谱总用时（unused）*/
    int menu_senson_step;/**< 记录菜谱用料步骤数（unused）*/
    int menu_state_step;/**< 记录菜谱状态步骤数（unused）*/
private:
//    bool validatePage();
};

/**
 * @brief The QWizardPage_season class 菜谱制作第二页主料信息的引导页界面
 */
class QWizardPage_ingredients : public QWizardPage
{
public:
    QWizardPage_ingredients();
    void initializePage();
    void cleanupPage();


private:
    /** @brief 用于排版formlayout界面*/
    QFormLayout* layout;

};

/**
 * @brief The QWizardPage_season class 菜谱制作第三页调料信息的引导页界面
 */
class QWizardPage_season : public QWizardPage
{
public:
    QWizardPage_season();
    void initializePage();
    void cleanupPage();


private:
    /** @brief 用于排版tabWidget界面*/
    QVBoxLayout* hLayout;

};

/**
 * @brief The QWizardPage_state class 菜谱制作第四页状态信息的引导页界面
 */
class QWizardPage_state : public QWizardPage
{
public:
    QWizardPage_state();
    void initializePage();
    void cleanupPage();


private:
    /** @brief 用于排版tabWidget界面*/
    QHBoxLayout* hLayout;

};

#endif // FORM_BIN_MENU_H
