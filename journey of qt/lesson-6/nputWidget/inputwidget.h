#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QHash>
#include <QMessageBox>
#include <QUuid>

namespace Ui {
class InputWidget;
}
//combo box 下拉列表用
class Student
{
public:
    Student()
    {
        m_age = 0;
    }
    bool isValid() const//任何不会修改数据成员的函数都应该声明为const类型,这里的const用来修饰this指针指向的当前类，
    {
        return !id().isEmpty();
    }

    QString id() const {return m_id;}
    void setId(const QString &id) {m_id = id;}

    QString name() const{return m_name;}
    void setName(const QString &name){m_name = name;}

    uint age() const{return m_age;}
    void setAge(uint age){m_age = age;}

    QString getDisplayText() const
    {
        QString ret;
        if (isValid())
        {
            ret =  QString("姓名：%1\n年龄：%2").arg(name()).arg(age());
        }
        return ret;
    }

private:
    QString m_id;
    QString m_name;
    uint m_age;
};


class InputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InputWidget(QWidget *parent = 0);
    ~InputWidget();


private slots:
     //------------------------------单文本输入----------------------------------------
    void on_checkBox_clearBtn_toggled(bool checked);

    void on_checkBox_readOnly_toggled(bool checked);

    void on_combo_inputH_currentIndexChanged(int index);

    void on_combo_inputV_currentIndexChanged(int index);

    void on_combo_echoMode_currentIndexChanged(int index);

    void on_combo_validator_currentIndexChanged(int index);

    void on_lineEdit_inputMask_textChanged(const QString &arg1);

    //------------------------------多文本输入----------------------------------------
    void on_spinBox_cursorWidth_valueChanged(int arg1);

    void on_spinBox_lineWrapColumnOrWidth_valueChanged(int arg1);

    void on_spinBox_tabStopWidth_valueChanged(int arg1);

    void on_checkBox_overwriteMode_toggled(bool checked);

    void on_checkBox_tabChangesFocus_toggled(bool checked);

    void on_comboBox_lineWrapMode_currentIndexChanged(int index);

    void on_comboBox_wordWrapMode_currentIndexChanged(int index);

    //----------------------------------combo box下拉列表用-------------------------------------------------
    void on_combo_student_activated(int index);

    void on_combo_insertPolicy_currentIndexChanged(int index);

    void on_check_editable_toggled(bool checked);

    void on_check_duplicatesEnabled_toggled(bool checked);

    void on_spinBox_maxCount_valueChanged(int arg1);

    void on_spinBox_maxVisibleItems_valueChanged(int arg1);

    //----------------------------------combo box下拉列表用-------------------------------------------------
private:
    void initLineEditTab();

    void initTextEditTab();

    void initComboBoxTab();
    Student addStudent();
    void showStudent(int index);
    bool hasAddStudentItem();

private:
    QHash<QString, Student> m_studentHash;//用来保存学生信息，key-id，value-学生类


private:
    Ui::InputWidget *ui;
};

#endif // INPUTWIDGET_H
