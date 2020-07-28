#include "form_bin_menu.h"

form_bin_menu::form_bin_menu()
{

}


//----------------------QWizardPage_main类的实现

QWizardPage_main::QWizardPage_main()
{
    //主要信息界面布局和控件生成
    QFormLayout* layout = new QFormLayout;
    this->setLayout(layout);
    //菜谱名字
    QLineEdit* name = new QLineEdit;
    //正则仅仅匹配汉字、数字、字母、下划线(限定9个）
    QRegExp regExp1("[\u4e00-\u9fa5_a-zA-Z0-9]{1,9}");
    name->setValidator(new QRegExpValidator(regExp1,this));
    //总时间
    QLineEdit* total_time = new QLineEdit;
    //正则仅仅匹配汉字
    QRegExp regExp2("[0-9]{0,9}");
    total_time->setValidator(new QRegExpValidator(regExp2,this));
    //调料步骤
    QStringList textList;
    QComboBox* season_step = new QComboBox;
    for(int i = 1; i < 6 ;i++)
        textList<<QString::number(i);
    season_step->addItems(textList);
    //状态步骤
    QComboBox* state_step = new QComboBox;
    textList.clear();
    for(int i = 1; i < 37 ;i++)
        textList<<QString::number(i);
    state_step->addItems(textList);
    //添加到布局
    layout->addRow("菜谱名字",name);
    layout->addRow("运行总时间",total_time);
    layout->addRow("调料步骤",season_step);
    layout->addRow("状态步骤",state_step);

    QObject::connect(name,&QLineEdit::editingFinished,[=](){menu_name = name->text();});
    QObject::connect(total_time,&QLineEdit::editingFinished,this,[=](){menu_total_time = total_time->text().toInt();});
    QObject::connect(season_step,&QComboBox::currentTextChanged,this,[=](){menu_senson_step = season_step->currentText().toInt();});
    QObject::connect(state_step,&QComboBox::currentTextChanged,this,[=](){menu_state_step = state_step->currentText().toInt();});

    registerField("menu_name*",name);
    registerField("total_time*",total_time);
    registerField("season_steps",season_step);
    registerField("state_steps",state_step);
}
/*
bool QWizardPage_main::validatePage()
{
    if(menu_total_time<99999 &&
            menu_senson_step<20 &&
            menu_state_step<20)
    {

        return true;
    }
    else
    {
        QMessageBox::critical(NULL,"输入参数格式有误","请检查输入参数格式");
        return false;
    }

}
*/
//------------QWizardPage_seanson类的实现

QWizardPage_season::QWizardPage_season()
{


}

void QWizardPage_season::initializePage()
{
    //不知道为何返回的数字少了1，暂时先加1
    int count = field("season_steps").toInt()+1;

    hLayout = new QVBoxLayout(this);
    QTabWidget* tabWidget;
    tabWidget = new QTabWidget;
    hLayout->addWidget(tabWidget);

    QVector<QWidget*> hWidget(count);
    QVector<QFormLayout*> layout(count);
    QVector<QLineEdit*> season_count(count);

    for(int i = 0;i < count;i++)
    {
        //新建界面
        hWidget[i] = new QWidget;
        //新建布局
        layout[i] = new QFormLayout;
        //配料个数输入
        QStringList textList;
        QComboBox* season_step = new QComboBox;
        for(int i = 1; i < 6 ;i++)
            textList<<QString::number(i);
        season_step->addItems(textList);


        season_count[i] = new QLineEdit;
        QRegExp regExp1("[1-5]");
        season_count[i]->setValidator(new QRegExpValidator(regExp1,this));
        layout[i]->addRow("配料个数",season_count[i]);
        registerField("season_count"+QString::number(i),season_count[i]);
        //
        QVector<QLineEdit*> season_detail(5);
        QVector<QLineEdit*> season_weight(5);
        for(int j = 0;j < 5;j++)
        {
            season_detail[j] = new QLineEdit;
            QRegExp regExp2("[\u4e00-\u9fa5_a-zA-Z0-9]{0,9}");
            season_detail[j]->setValidator(new QRegExpValidator(regExp2,this));
            season_weight[j] = new QLineEdit;
            QRegExp regExp3("[0-9]{0,9}");
            season_weight[j]->setValidator(new QRegExpValidator(regExp3,this));
            layout[i]->addRow("文字描述"+QString::number(j+1),season_detail[j]);
            layout[i]->addRow("重量描述"+QString::number(j+1),season_weight[j]);
            registerField("season_detail"+QString::number(i)+QString::number(j),season_detail[j]);
            registerField("season_weight"+QString::number(i)+QString::number(j),season_weight[j]);

        }

        hWidget[i]->setLayout(layout[i]);
        tabWidget->addTab(hWidget[i],QString::number(i+1));

    }
    //添加主料输入
    QLineEdit* main_season_name = new QLineEdit;
    main_season_name->setPlaceholderText("输入主料名称");
    hLayout->addWidget(main_season_name);
    registerField("main_season_name*",main_season_name);


}

void QWizardPage_state::cleanupPage(){
    QLayoutItem *child;
    while((child = hLayout->takeAt(0))!=0)
    {
          hLayout->removeWidget(child->widget());
          child->widget()->setParent(0);
          delete child;
}

    delete hLayout;

}

//---------------------------------------------------------------------------------QWizardPage_state的实现


QWizardPage_state::QWizardPage_state()
{

}

void QWizardPage_state::initializePage()
{
    //不知道为何返回的数字少了1，暂时先加1
    int count = field("state_steps").toInt()+1;

    hLayout = new QHBoxLayout(this);
    QTabWidget* tabWidget;
    tabWidget = new QTabWidget;
    hLayout->addWidget(tabWidget);

    QVector<QWidget*> hWidget(count);
    QVector<QFormLayout*> layout(count);

    QVector<QComboBox*> run_state(count);
    QVector<QComboBox*> run_cover(count);
    QVector<QComboBox*> run_stir(count);
    QVector<QComboBox*> run_power(count);
    QVector<QLineEdit*> run_time(count);
    QVector<QLineEdit*> run_temperature(count);
    QVector<QLineEdit*> run_detail(count);

    //QVector<QLineEdit*> season_name(count);
    //QVector<QLineEdit*> season_weight(count);
    for(int i = 0;i < count;i++)
    {
        //新建界面
        hWidget[i] = new QWidget;
        //新建布局
        layout[i] = new QFormLayout;

        //运行状态
        QStringList textList;
        run_state[i] = new QComboBox;
        textList<<"Preparation"<<"CoverControl"<<"Heating"
               <<"Feeding"<<"Cleaning"<<"Waitting"
              <<"PowerOn"<<"NetCheck"<<"ModeSet"
             <<"MenuSelect"<<"Suspend"<<"Testing"
            <<"SeasonList"<<"CheckPreparation"
           <<"FixedModeSelect"<<"FixedModeWork";
        run_state[i]->addItems(textList);
        textList.clear();
        //锅盖状态
        run_cover[i] = new QComboBox;
        textList<<"CoverReset"<<"CoverOpen"<<"CoverClose"<<"CoverStop";
        run_cover[i]->addItems(textList);
        textList.clear();
        //搅拌状态
        run_stir[i] = new QComboBox;
        textList<<"StirReset"<<"StirRun"<<"StirStop";
        run_stir[i]->addItems(textList);
        textList.clear();
        //火力力度
        run_power[i] = new QComboBox;
        for(int i = 1; i < 11 ;i++)
            textList<<QString::number(i);
        run_power[i]->addItems(textList);
        //运行时间
        run_time[i] = new QLineEdit;
        QRegExp regExp1("[0-9]{0,9}");
        run_time[i]->setValidator(new QRegExpValidator(regExp1,this));
        //运行温度
        run_temperature[i] = new QLineEdit;
        QRegExp regExp2("[0-9]{0,9}");
        run_temperature[i]->setValidator(new QRegExpValidator(regExp2,this));
        //文字描述
        run_detail[i] = new QLineEdit;
        QRegExp regExp3("[\u4e00-\u9fa5_a-zA-Z0-9]{0,9}");
        run_detail[i]->setValidator(new QRegExpValidator(regExp3,this));


        layout[i]->addRow("运行状态",run_state[i]);
        layout[i]->addRow("锅盖状态",run_cover[i]);
        layout[i]->addRow("搅动状态",run_stir[i]);
        layout[i]->addRow("火力功率",run_power[i]);
        layout[i]->addRow("运行时间",run_time[i]);
        layout[i]->addRow("运行温度",run_temperature[i]);
        layout[i]->addRow("文字描述",run_detail[i]);

        registerField("run_state"+QString::number(i),run_state[i]);
        registerField("run_cover"+QString::number(i),run_cover[i]);
        registerField("run_stir"+QString::number(i),run_stir[i]);
        registerField("run_power"+QString::number(i),run_power[i]);
        registerField("run_time"+QString::number(i),run_time[i]);
        registerField("run_temperature"+QString::number(i),run_temperature[i]);
        registerField("run_detail"+QString::number(i),run_detail[i]);

        hWidget[i]->setLayout(layout[i]);

        tabWidget->addTab(hWidget[i],QString::number(i+1));

    }



}

void QWizardPage_season::cleanupPage(){
    QLayoutItem *child;
    while((child = hLayout->takeAt(0))!=0)
    {
          hLayout->removeWidget(child->widget());
          child->widget()->setParent(0);
          delete child;
}

    delete hLayout;

}
