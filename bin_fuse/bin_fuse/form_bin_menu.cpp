/** @file form_bin_menu.cpp
 * @brief 菜谱bin文件的引导页对象
 * @note 因为菜谱引导页之间存在耦合，需要实现动态生成控件，所以不能使用UI直接绘制控件
 * @author Wu Rendi
 * @version 0.0.1.0
 * @date 2020-7-31
 */
#include "form_bin_menu.h"

form_bin_menu::form_bin_menu()
{

}


/**
 * @brief QWizardPage_main::QWizardPage_main 主要信息的引导页
 */

QWizardPage_main::QWizardPage_main()
{
    //主要信息界面布局和控件生成
    QFormLayout* layout = new QFormLayout;
    this->setLayout(layout);


    //菜谱ID
    QLineEdit* menu_id = new QLineEdit;

    //正则仅仅匹配汉字
    QRegExp regExp2("[0-9]{0,9}");
    menu_id->setValidator(new QRegExpValidator(regExp2,this));

    //菜谱名字
    QLineEdit* name = new QLineEdit;

    //正则仅仅匹配汉字、数字、字母、下划线(限定9个）
    QRegExp regExp1("[\u4e00-\u9fa5_a-zA-Z0-9]{1,9}");
    name->setValidator(new QRegExpValidator(regExp1,this));

    //总时间
    QLineEdit* total_time = new QLineEdit;

    //正则仅仅匹配数字
    //QRegExp regExp2("[0-9]{0,9}");
    total_time->setValidator(new QRegExpValidator(regExp2,this));

    //主料种类个数
    QStringList textList;
    QComboBox* ingredients = new QComboBox;
    for(int i = 1; i < 11 ;i++)
        textList<<QString::number(i);
    ingredients->addItems(textList);

    //调料步骤
    textList.clear();
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
    layout->addRow("菜谱ID",menu_id);
    layout->addRow("菜谱名字",name);
    layout->addRow("运行总时间",total_time);
    layout->addRow("主料种类",ingredients);
    layout->addRow("调料步骤",season_step);
    layout->addRow("状态步骤",state_step);

    QObject::connect(name,&QLineEdit::editingFinished,[=](){menu_name = name->text();});
    QObject::connect(total_time,&QLineEdit::editingFinished,this,[=](){menu_total_time = total_time->text().toInt();});
    QObject::connect(season_step,&QComboBox::currentTextChanged,this,[=](){menu_senson_step = season_step->currentText().toInt();});
    QObject::connect(state_step,&QComboBox::currentTextChanged,this,[=](){menu_state_step = state_step->currentText().toInt();});

    registerField("menu_id*",menu_id);
    registerField("menu_name*",name);
    registerField("total_time*",total_time);
    registerField("ingredients",ingredients);
    registerField("season_steps",season_step);
    registerField("state_steps",state_step);
}

//---------------------------------------------------------------------------------QWizardPage_Ingredients的实现

QWizardPage_ingredients::QWizardPage_ingredients()
{


}

/**
 * @brief QWizardPage_ingredients::initializePage 主料引导页的刷新入口程序
 * @note 调用主要信息页中的主料种类信息来动态生成当前界面的输入控件
 */
void QWizardPage_ingredients::initializePage()
{
    //不知道为何返回的数字少了1，暂时先加1
    int count = field("ingredients").toInt()+1;

    //主料信息界面布局和控件生成
    layout = new QFormLayout;
    this->setLayout(layout);

    QLabel* label_illustration = new QLabel;
    label_illustration->setText("主料的描述限定10个字符");
    layout->addWidget(label_illustration);

    //QVector<QLineEdit*> season_count(count);

    //调料的详情和重量输入
    QVector<QLineEdit*> ingredient_detail(count);
    QVector<QLineEdit*> ingredient_weight(count);
    for(int i = 0;i < count;i++)
    {
        ingredient_detail[i] = new QLineEdit;
        QRegExp regExp2("[\u4e00-\u9fa5_a-zA-Z0-9，,:：。.]{0,10}");
        ingredient_detail[i]->setValidator(new QRegExpValidator(regExp2,this));
        ingredient_weight[i] = new QLineEdit;
        QRegExp regExp3("[0-9]{0,9}");
        ingredient_weight[i]->setValidator(new QRegExpValidator(regExp3,this));
        layout->addRow("主料描述"+QString::number(i+1),ingredient_detail[i]);
        layout->addRow("重量描述"+QString::number(i+1),ingredient_weight[i]);
        registerField("ingredient_detail"+QString::number(i),ingredient_detail[i]);
        registerField("ingredient_weight"+QString::number(i),ingredient_weight[i]);
    }
}



/**
 * @brief QWizardPage_ingredients::cleanupPage 调料引导页后退键触发的程序入口
 * @note 用来清除在当前layout中生成的输入控件
 */
void QWizardPage_ingredients::cleanupPage(){
    QLayoutItem *child;
    while((child = layout->takeAt(0))!=0)
    {
          layout->removeWidget(child->widget());
          child->widget()->setParent(0);
          delete child;
}

    delete layout;

}



//---------------------------------------------------------------------------------QWizardPage_season的实现


QWizardPage_season::QWizardPage_season()
{


}

/**
 * @brief QWizardPage_season::initializePage 调料引导页的刷新入口程序
 * @note 调用主要信息页中的调料步骤信息来动态生成当前界面的输入控件
 */
void QWizardPage_season::initializePage()
{
    //不知道为何返回的数字少了1，暂时先加1
    int count = field("season_steps").toInt()+1;

    hLayout = new QVBoxLayout(this);

    QLabel* label_illustration = new QLabel;
    label_illustration->setText("调料的描述限定10个字符，调料步骤中调料个数没有检测，请确保对应");
    hLayout->addWidget(label_illustration);

    QTabWidget* tabWidget;
    tabWidget = new QTabWidget;
    hLayout->addWidget(tabWidget);

    QVector<QWidget*> hWidget(count);
    QVector<QFormLayout*> layout(count);
    QVector<QComboBox*> season_count(count);

    for(int i = 0;i < count;i++)
    {
        //新建界面
        hWidget[i] = new QWidget;

        //新建FormLayout布局
        layout[i] = new QFormLayout;

        //配料个数输入
        QStringList textList;
        //使用QComboBox制成下拉菜单
        season_count[i] = new QComboBox;
        for(int i = 0; i < 6 ;i++)
            textList<<QString::number(i);
        season_count[i]->addItems(textList);

        //控件添加到布局
        layout[i]->addRow("配料个数",season_count[i]);

        //将输入控件注册到整个引导界面
        registerField("season_count"+QString::number(i),season_count[i]);

        //调料的详情和重量输入
        QVector<QLineEdit*> season_detail(5);
        QVector<QLineEdit*> season_weight(5);
        for(int j = 0;j < 5;j++)
        {
            season_detail[j] = new QLineEdit;
            QRegExp regExp2("[\u4e00-\u9fa5_a-zA-Z0-9，,:：。.]{0,10}");
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

}



/**
 * @brief QWizardPage_season::cleanupPage 调料引导页后退键触发的程序入口
 * @note 用来清除在当前layout中生成的输入控件
 */
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

//---------------------------------------------------------------------------------QWizardPage_state的实现


QWizardPage_state::QWizardPage_state()
{

}

/**
 * @brief QWizardPage_state::initializePage 状态引导页的刷新入口程序
 * @note 调用主要信息页中的状态步骤来动态生成输入控件
 */
void QWizardPage_state::initializePage()
{
    //这里返回的是comboBox的索引值，起始为0，所以需要+1
    int count = field("state_steps").toInt()+1;

    //水平布局实例化
    hLayout = new QVBoxLayout(this);

    //说明文字
    QLabel* label_illustration = new QLabel;
    label_illustration->setText("状态的描述限定20个字符");
    hLayout->addWidget(label_illustration);

    //tabWidget布局实例化
    QTabWidget* tabWidget;
    tabWidget = new QTabWidget;
    hLayout->addWidget(tabWidget);

    //批量布局和界面
    QVector<QWidget*> hWidget(count);
    QVector<QFormLayout*> layout(count);
    //批量输入控件声明
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
        textList.append({"备料过程0x00","锅盖控制过程0x01","加热过程0x02","加料过程0x03","清洗过程0x04","等待过程0x05","保温过程0x06","焖煮过程0x07"});
        run_state[i]->addItems(textList);
        textList.clear();

        //锅盖状态
        run_cover[i] = new QComboBox;
        textList.append({"维持状态0x00","开盖0x01","关盖0x02"});
        run_cover[i]->addItems(textList);
        textList.clear();

        //搅拌状态
        run_stir[i] = new QComboBox;
        textList.append({"不搅拌0x00","搅拌0x01"});
        run_stir[i]->addItems(textList);
        textList.clear();

        //火力力度
        run_power[i] = new QComboBox;
        for(int i = 0; i < 11 ;i++)
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
        QRegExp regExp3("[\u4e00-\u9fa5_a-zA-Z0-9，,:：。.]{0,20}");
        run_detail[i]->setValidator(new QRegExpValidator(regExp3,this));

        //输入控件添加到布局
        layout[i]->addRow("运行状态",run_state[i]);
        layout[i]->addRow("锅盖状态",run_cover[i]);
        layout[i]->addRow("搅动状态",run_stir[i]);
        layout[i]->addRow("火力功率(*200W)",run_power[i]);
        layout[i]->addRow("运行时间（s）",run_time[i]);
        layout[i]->addRow("运行温度(℃)",run_temperature[i]);
        layout[i]->addRow("文字描述",run_detail[i]);
        //输入控件注册到引导页
        registerField("run_state"+QString::number(i),run_state[i]);
        registerField("run_cover"+QString::number(i),run_cover[i]);
        registerField("run_stir"+QString::number(i),run_stir[i]);
        registerField("run_power"+QString::number(i),run_power[i]);
        registerField("run_time"+QString::number(i),run_time[i]);
        registerField("run_temperature"+QString::number(i),run_temperature[i]);
        registerField("run_detail"+QString::number(i),run_detail[i]);

        //局部布局添加到引导页布局
        hWidget[i]->setLayout(layout[i]);
        //输入控件添加到tabWidget布局
        tabWidget->addTab(hWidget[i],QString::number(i+1));

    }

}




/**
 * @brief QWizardPage_state::cleanupPage 状态引导页后退键触发的程序入口
 * @note 用来清除在当前layout中生成的输入控件
 */
void QWizardPage_state::cleanupPage(){
    QLayoutItem *child;
    while((child = hLayout->takeAt(0))!= 0)
    {
          hLayout->removeWidget(child->widget());
          child->widget()->setParent(0);
          delete child;
    }

    delete hLayout;

}

//---------------------------------------------------------------------------------QTableView_menu的实现

/**
 * @brief QTableView_menu::QTableView_menu 读取菜谱bin文件的信息
 * @param parent 父对象
 * @param file_path 菜谱文件地址
 */
QTableView_menu::QTableView_menu(QWidget *parent,QString file_path):
    QTableView(parent),
    menu_path(file_path)
{
    setWindowFlags(Qt::Window);
    //保存按钮
    QPushButton* save_button = new QPushButton(this);
    save_button->setText(tr("保存为一个new后缀的新文件"));
    connect(save_button,SIGNAL(clicked()),this,SLOT(save_menu()));
    //读取文件
    menu_read = new QFile(menu_path);
    menu_read->open(QIODevice::ReadOnly);
    tmp = menu_read->readAll();
    Menu = (Menu1_t*) (tmp.data());
    //memcpy(Menu,(Menu1_t*)tmp.data(),sizeof(tmp.data()));
    model = new QStandardItemModel(this);

    //int tableIndex = 0;

    model->setHorizontalHeaderItem(0, new QStandardItem("描述") );
    model->setHorizontalHeaderItem(1, new QStandardItem("内容") );

    model->setItem(0, 0, new QStandardItem("菜谱ID"));
    model->setItem(0, 1, new QStandardItem(QString::number(Menu->ID, 10)));

    model->setItem(1, 0, new QStandardItem("菜名"));
    model->setItem(1, 1, new QStandardItem(toUTF((char*)Menu->DishName)));

    model->setItem(2, 0, new QStandardItem("总时间"));
    model->setItem(2, 1, new QStandardItem(QString::number(Menu->AllTime, 10)));

    model->setItem(3, 0, new QStandardItem("主料个数"));
    model->setItem(3, 1, new QStandardItem(QString::number(Menu->MainSeasoningNum, 10)));

    model->setItem(4, 0, new QStandardItem("加料步骤"));
    model->setItem(4, 1, new QStandardItem(QString::number(Menu->SeasoningStepNum, 10)));

    model->setItem(5, 0, new QStandardItem("运行步骤"));
    model->setItem(5, 1, new QStandardItem(QString::number(Menu->RunStepNum, 10)));

    int tableIndex = 5;

    for(int j = 0;j < Menu->MainSeasoningNum;j ++)
    {
        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("主料"+QString::number(j + 1,10)+"描述"));
        model->setItem(tableIndex, 1, new QStandardItem(toUTF((char*)Menu->MainSeasoning[j].Name)));

        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("主料"+QString::number(j + 1,10)+"重量（g）"));
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->MainSeasoning[j].Weight, 10)));
    }


    for(int i = 0 ;i < Menu->SeasoningStepNum ;i++)
    {
        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "料盒的调料个数"));
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->Seasoning[i].SeasoningNum, 10)));
        model->item(tableIndex,0)->setForeground(QBrush(QColor(255, 0, 0)));

        for(int j = 0;j < 5;j ++)
        {
            tableIndex ++;
            model->setItem(tableIndex, 0, new QStandardItem("料盒调料描述" + QString::number(j + 1,10)));
            model->setItem(tableIndex, 1, new QStandardItem(toUTF((char*)Menu->Seasoning[i].SeasoningInf[j].Name)));

            tableIndex ++;
            model->setItem(tableIndex, 0, new QStandardItem("料盒调料重量(g)"+QString::number(j + 1,10)));
            model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->Seasoning[i].SeasoningInf[j].Weight, 10)));
        }
    }

    QString state_display;
    for(int i = 0;i < Menu->RunStepNum;i++)
    {
        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "次运行状态"));
        switch (Menu->RunStep[i].State)
        {
            case 0:state_display = "备料过程";break;
            case 1:state_display = "锅盖控制过程";break;
            case 2:state_display = "加热过程";break;
            case 3:state_display = "加料过程";break;
            case 4:state_display = "清洗过程";break;
            case 5:state_display = "等待过程";break;
            case 6:state_display = "保温过程";break;
            case 7:state_display = "焖煮过程";break;
            default:state_display = "错误数据";break;
        }
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->RunStep[i].State, 10)));
        model->setItem(tableIndex, 2, new QStandardItem(state_display));
        model->item(tableIndex,0)->setForeground(QBrush(QColor(255, 0, 0)));

        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "次锅盖状态"));
        switch (Menu->RunStep[i].Cover)
        {
            case 0:state_display = "维持状态";break;
            case 1:state_display = "开盖";break;
            case 2:state_display = "关盖";break;
            default:state_display = "错误数据";break;
        }
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->RunStep[i].Cover, 10)));
        model->setItem(tableIndex, 2, new QStandardItem(state_display));

        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "次搅拌状态"));
        switch (Menu->RunStep[i].Stir)
        {
            case 0:state_display = "不搅拌";break;
            case 1:state_display = "搅拌";break;
            default:state_display = "错误数据";break;
        }
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->RunStep[i].Stir, 10)));
        model->setItem(tableIndex, 2, new QStandardItem(state_display));

        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "次加热功率(*200W)"));
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->RunStep[i].Power, 10)));

        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "次运行时间(s)"));
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->RunStep[i].Time, 10)));

        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "次运行温度(℃)"));
        model->setItem(tableIndex, 1, new QStandardItem(QString::number(Menu->RunStep[i].Temperature, 10)));

        tableIndex ++;
        model->setItem(tableIndex, 0, new QStandardItem("第" + QString::number(i + 1,10) + "次运行描述"));
        model->setItem(tableIndex, 1, new QStandardItem(toUTF((char*)Menu->RunStep[i].Txt)));
    }


    this->setModel(model);
    //this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    menu_read->close();
}

/**
 * @brief QTableView_menu::toUTF 如果想进行字符编码转化，一定要确保输入的参数是原始数据，不能经过QString强制转化，因为在char*转为QString的过程中就已经实现了一次解码。
 * @param input
 * @return
 */
QString QTableView_menu::toUTF(QByteArray input)
{

    QString  text = QTextCodec::codecForName( "GBK" )->toUnicode(input);

    return text;
}

/**
 * @brief Wizard_bin_menu::toGBK 将unicode转化为GBK
 * @param input
 * @return
 */
QByteArray QTableView_menu::toGBK(QString input)
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


void QTableView_menu::save_menu()
{
    //保存文件


    int tableIndex = 0;
    QModelIndex index = model->index(0,0);
    QString name = model->data(index).toString();

    tableIndex = 0;
    index = model->index(tableIndex,1);
    Menu->ID = model->data(index).toUInt();

    tableIndex ++;
    index = model->index(tableIndex,1);
    std::strncpy((char*)Menu->DishName,toGBK(model->data(index).toString()),20);


    tableIndex ++;
    index = model->index(tableIndex,1);
    Menu->AllTime = model->data(index).toUInt();

    tableIndex ++;
    index = model->index(tableIndex,1);
    Menu->MainSeasoningNum = model->data(index).toUInt();

    tableIndex ++;
    index = model->index(tableIndex,1);
    Menu->SeasoningStepNum = model->data(index).toUInt();

    tableIndex ++;
    index = model->index(tableIndex,1);
    Menu->RunStepNum = model->data(index).toUInt();


    for(int j = 0;j < Menu->MainSeasoningNum;j ++)
    {
        tableIndex ++;
        index = model->index(tableIndex,1);
        std::strncpy((char*)Menu->MainSeasoning[j].Name,toGBK(model->data(index).toString()),20);


        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->MainSeasoning[j].Weight = model->data(index).toUInt();
    }


    for(int i = 0 ;i < Menu->SeasoningStepNum ;i++)
    {
        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->Seasoning[i].SeasoningNum = model->data(index).toUInt();

        for(int j = 0;j < 5;j ++)
        {
            tableIndex ++;
            index = model->index(tableIndex,1);
            std::strncpy((char*)Menu->Seasoning[i].SeasoningInf[j].Name,toGBK(model->data(index).toString()),20);

            tableIndex ++;
            index = model->index(tableIndex,1);
            Menu->Seasoning[i].SeasoningInf[j].Weight = model->data(index).toUInt();
        }
    }

    QString state_display;
    for(int i = 0;i < Menu->RunStepNum;i++)
    {
        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->RunStep[i].State = model->data(index).toUInt();


        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->RunStep[i].Cover = model->data(index).toUInt();

        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->RunStep[i].Stir = model->data(index).toUInt();

        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->RunStep[i].Power = model->data(index).toUInt();

        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->RunStep[i].Time = model->data(index).toUInt();

        tableIndex ++;
        index = model->index(tableIndex,1);
        Menu->RunStep[i].Temperature = model->data(index).toUInt();


        tableIndex ++;
        index = model->index(tableIndex,1);
        std::strncpy((char*)Menu->RunStep[i].Txt,toGBK(model->data(index).toString()),40);


    }

    //QByteArray tmp = (char*)Menu;
    QFileInfo inf = QFileInfo(menu_path);
    QFile menu_save(inf.baseName()+"new.bin");
    menu_save.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream out(&menu_save);
    int impsize = tmp.size();
    out.writeRawData(tmp,tmp.size());
    menu_save.close();
}

QTableView_menu::~QTableView_menu()
{

}


