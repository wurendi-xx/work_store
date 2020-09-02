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
#include <QTableView>
#include <QStandardItemModel>
#include <QFile>
#include <QTextCodec>
#include <QPushButton>
#include <cstring>
#include <QFileInfo>

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
    QVBoxLayout* hLayout;

};

/**
 * @brief The QTableView_menu class 查看菜谱并显示
 */
class QTableView_menu : public QTableView //继承至QTableView
{
    Q_OBJECT
public:
    explicit QTableView_menu(QWidget *parent = 0,QString file_path = 0);
    ~QTableView_menu();

    QString menu_path;
    QString toUTF(QByteArray input);
    QByteArray toGBK(QString input);

public slots:
    void save_menu();

private:
    typedef struct
    {
        uint8_t Name[20];
        uint32_t Weight;
    }SeasoningInformation_t;

    typedef struct
    {
        uint32_t SeasoningNum;
        SeasoningInformation_t SeasoningInf[5];
    }Seasoning_t;

    typedef struct
    {
        uint32_t State;
        uint32_t Cover;
        uint32_t Stir;
        uint32_t Power;
        uint32_t Time;
        uint32_t Temperature;
        uint8_t  Txt[40];
    }Running_Step_t;

  typedef struct
    {
        uint32_t                ID;
        uint8_t                 DishName[20];
        uint32_t                AllTime;
        uint32_t                SeasoningStepNum;
        uint32_t                RunStepNum;
        Seasoning_t             Seasoning[5];
        uint32_t                MainSeasoningNum;
        SeasoningInformation_t  MainSeasoning[10];
        Running_Step_t			RunStep[36];
    }Menu1_t;

  Menu1_t* Menu;

  QStandardItemModel* model;

  QFile* menu_read;

  QByteArray tmp;

};

#endif // FORM_BIN_MENU_H
