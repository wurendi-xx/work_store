#include "inputwidget.h"
#include "ui_inputwidget.h"

InputWidget::InputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputWidget)
{
    ui->setupUi(this);
    //单文本输入的初始化
    initLineEditTab();
    //多文本输入的初始化
    initTextEditTab();
    //combo box下拉列表
    //initLineEditTab();
    initComboBoxTab();

}

InputWidget::~InputWidget()
{
    delete ui;
}


//-----------------------------单文本输入-------------------------------------------
void InputWidget::on_checkBox_clearBtn_toggled(bool checked)
{
    ui->lineEdit->setClearButtonEnabled(checked);

}

void InputWidget::on_checkBox_readOnly_toggled(bool checked)
{
    ui->lineEdit->setReadOnly(checked);

}

void InputWidget::on_combo_inputH_currentIndexChanged(int index)
{
    ui->lineEdit->setAlignment((Qt::Alignment) (Qt::AlignLeft<<index));

}

void InputWidget::on_combo_inputV_currentIndexChanged(int index)
{
    ui->lineEdit->setAlignment((Qt::Alignment) (Qt::AlignTop<<index));

}

void InputWidget::on_combo_echoMode_currentIndexChanged(int index)
{
    ui->lineEdit->setEchoMode((QLineEdit::EchoMode)index);

}

void InputWidget::on_combo_validator_currentIndexChanged(int index)
{
    //删除当前验证器
        ui->lineEdit->setValidator(0);
        if (index == 1)
        {
            //整数验证器，0-80
            QIntValidator* validator = new QIntValidator(20, 80);
            ui->lineEdit->setValidator(validator);
        }
        else if (index == 2)
        {
            //双精度验证器，0.-1000.
            QDoubleValidator* validator = new QDoubleValidator();
            validator->setBottom(0.);
            validator->setTop(100.);
            ui->lineEdit->setValidator(validator);
        }
        else  if (index == 3)
        {
            //匹配0-99的整数
            QRegExpValidator* validator = new QRegExpValidator(QRegExp("^\\d\\d?$"));
            ui->lineEdit->setValidator(validator);
        }

}

void InputWidget::on_lineEdit_inputMask_textChanged(const QString &arg1)
{
    ui->lineEdit->setInputMask(arg1);

}

void InputWidget::initLineEditTab()
{
    //输入方向-水平
    QStringList textList;
    textList << "AlignLeft" <<"AlignRight" << "AlignHCenter" << "AlignJustify";
    ui->combo_inputH->addItems(textList);

    //输入方向-垂直
    textList.clear();
    textList << "AlignTop" <<"AlignBottom" << "AlignVCenter" << "AlignBaseline";
    ui->combo_inputV->addItems(textList);

    //输入模式
    textList.clear();
    textList << "Normal" <<"NoEcho" << "Password" << "PasswordEchoOnEdit";
    ui->combo_echoMode->addItems(textList);

    //验证器
    textList.clear();
    textList << "无验证器" << "Int" <<"Double" << "Reqexp";
    ui->combo_validator->addItems(textList);
}
//-----------------------------单文本输入-------------------------------------------

//-------------------------多文本输入-------------------------------------------------
void InputWidget::on_spinBox_cursorWidth_valueChanged(int arg1)
{
    ui->textEdit->setCursorWidth(arg1);

}

void InputWidget::on_spinBox_lineWrapColumnOrWidth_valueChanged(int arg1)
{
    ui->textEdit->setLineWrapColumnOrWidth(arg1);

}

void InputWidget::on_spinBox_tabStopWidth_valueChanged(int arg1)
{
    ui->textEdit->setTabStopWidth(arg1);

}

void InputWidget::on_checkBox_overwriteMode_toggled(bool checked)
{
    ui->textEdit->setOverwriteMode(checked);

}

void InputWidget::on_checkBox_tabChangesFocus_toggled(bool checked)
{
    ui->textEdit->setTabChangesFocus(checked);

}

void InputWidget::on_comboBox_lineWrapMode_currentIndexChanged(int index)
{
    ui->textEdit->setLineWrapMode((QTextEdit::LineWrapMode)index);

}

void InputWidget::on_comboBox_wordWrapMode_currentIndexChanged(int index)
{
    ui->textEdit->setWordWrapMode((QTextOption::WrapMode)index);

}

void InputWidget::initTextEditTab()
{
    //输入方向-水平
    QStringList textList;
    textList << "NoWrap" <<"WidgetWidth" << "FixedPixelWidth" << "FixedColumnWidth";
    ui->comboBox_lineWrapMode->addItems(textList);

    //输入方向-垂直
    textList.clear();
    textList << "NoWrap" << "WordWrap" <<"ManualWrap" << "WrapAnywhere" << "WrapAtWordBoundaryOrAnywhere";
    ui->comboBox_wordWrapMode->addItems(textList);
}
//-------------------------多文本输入-------------------------------------------------

//----------------------------------combo box下拉列表用-------------------------------------------------
void InputWidget::initComboBoxTab()
{
    //插入模式
    QStringList textList;
    textList << "NoInsert" <<"InsertAtTop" << "InsertAtCurrent" << "InsertAtBottom"
               << "InsertAfterCurrent" << "InsertBeforeCurrent" << "InsertAlphabetically";
    ui->combo_insertPolicy->addItems(textList);
}

Student InputWidget::addStudent()
{
    Student stu;
    QString text = ui->combo_student->currentText();
    QStringList textList = text.split(",");
    if (textList.size() == 2)
    {
        bool ok;
        QString name = textList.at(0);
        uint age = textList.at(1).toUInt(&ok);
        if (ok)
        {
            //为每个学生创建唯一id
            stu.setId(QUuid::createUuid().toString());
            stu.setName(name);
            stu.setAge(age);
            m_studentHash.insert(stu.id(), stu);
        }
    }
    return stu;
}

void InputWidget::showStudent(int index)
{
    QString id = ui->combo_student->itemData(index).toString();
    Student stu = m_studentHash.value(id);
    if (stu.isValid())
    {
        ui->label_student->setText(stu.getDisplayText());
    }
}

bool InputWidget::hasAddStudentItem()
{
    return m_studentHash.size() < ui->combo_student->count();
}

void InputWidget::on_combo_student_activated(int index)
{
    if (hasAddStudentItem())//判断是否已经添加了学生item，此时的item并不一定合法，若不合法则要删除
    {
        Student stu = addStudent();
        if (stu.isValid())//如果输入正确，则添加学生条目
        {
            ui->combo_student->setItemData(index, stu.id());
        }
        else//如果是输入错误，则删除新增的item，并提示
        {
            ui->combo_student->removeItem(index);
            QMessageBox::information(this,
                                     tr("录入学生信息"),
                                     tr("输入错误，请重新输入，格式为：“姓名，年龄”。回车确认。"),
                                     "好滴");
        }
    }

    showStudent(index);
}

void InputWidget::on_combo_insertPolicy_currentIndexChanged(int index)
{
    ui->combo_student->setInsertPolicy((QComboBox::InsertPolicy)index);

}


void InputWidget::on_check_editable_toggled(bool checked)
{
    ui->combo_student->setEditable(checked);
    if (checked)
        ui->combo_student->setEditText("录入格式：姓名,年龄");
}

void InputWidget::on_check_duplicatesEnabled_toggled(bool checked)
{
    ui->combo_student->setDuplicatesEnabled(checked);

}

void InputWidget::on_spinBox_maxCount_valueChanged(int arg1)
{
    ui->combo_student->setMaxCount(arg1);

}

void InputWidget::on_spinBox_maxVisibleItems_valueChanged(int arg1)
{
    ui->combo_student->setMaxVisibleItems(arg1);

}
//----------------------------------combo box下拉列表用-------------------------------------------------
