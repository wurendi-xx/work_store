#include "formlayoutwidget.h"
#include "ui_formlayoutwidget.h"

FormLayoutWidget::FormLayoutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLayoutWidget)
{
    ui->setupUi(this);

    QFormLayout *layout = new QFormLayout;
    setLayout(layout);

    QStringList textList;
    //标签对齐方式
    {
        textList << "AlignLeft" <<"AlignRight" << "AlignHCenter" << "AlignJustify";
        QComboBox* combo = new QComboBox;
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        combo->setSizePolicy(sizePolicy);
        combo->addItems(textList);
        layout->addRow("labelAlignment", combo );

        //这里是一个Qt5connect时对于重载函数的写法，其实就是一个函数指针
        //虽然保留了参数检测，安全检查的功能，但我还是比较喜欢Qt4风格
        //槽函数是一个lambda表达式，主要为了省略槽函数定义，并且可以直接使用layout变量
        //static_cast<void(QComboBox::*)(int)>这里是强制类型转换
        connect(combo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                     [=](int val)
                    {
                        layout->setLabelAlignment((Qt::AlignmentFlag)(Qt::AlignLeft<<val));
                    }
                );
    }

    //表单对齐方式
    {
        textList.clear();
        textList << "AlignTop" <<"AlignBottom" << "AlignVCenter" << "AlignBaseline";
        QComboBox* combo = new QComboBox;
        combo->addItems(textList);
        layout->addRow("formAlignment",  combo);
        connect(combo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                     [=](int val)
                    {
                        layout->setFormAlignment((Qt::AlignmentFlag)(Qt::AlignTop<<val));
                    }
                );

    //字段栏增长策略
        {
            textList.clear();
            textList << "FieldsStayAtSizeHint" <<"ExpandingFieldsGrow" << "AllNonFixedFieldsGrow";
            QComboBox* combo = new QComboBox;
            combo->addItems(textList);
            layout->addRow("fieldGrowthPolicy",  combo);
            connect(combo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                         [=](int val)
                        {
                            layout->setFieldGrowthPolicy((QFormLayout::FieldGrowthPolicy)val);
                        }
            );
        }

        //换行策略
        {
            textList.clear();
            textList << "DontWrapRows" <<"WrapLongRows" << "WrapAllRows";
            QComboBox* combo = new QComboBox;
            combo->addItems(textList);
            layout->addRow("rowWrapPolicy",  combo);
            connect(combo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                         [=](int val)
                        {
                            layout->setRowWrapPolicy((QFormLayout::RowWrapPolicy) val);
                        }
            );
        }

        //水平和垂直间隔
        QSpinBox* hSpin = new QSpinBox;
        QSpinBox* vSpin = new QSpinBox;
        layout->addRow("&horizontalSpacing",  hSpin);//使用&，可以设置快捷键为Alt+l
        layout->addRow("&vecticalSpacing",  vSpin);

        /*connect(hSpin, SIGNAL(QSpinBox::valueChanged(int)),
                        layout, SLOT(setHorizontalSpacing(int)));
                        */

        connect(hSpin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     layout, &QFormLayout::setHorizontalSpacing);



        connect(vSpin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     layout, &QFormLayout::setVerticalSpacing);



    }
}

FormLayoutWidget::~FormLayoutWidget()
{
    delete ui;
}
