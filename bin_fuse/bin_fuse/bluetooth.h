#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class bluetooth;
}

class bluetooth : public QWidget
{
    Q_OBJECT

public:
    explicit bluetooth(QWidget *parent = nullptr);
    ~bluetooth();


private slots:
    /** 选择串口按钮入口程序 */
    void on_button_comSelected_clicked();
    /** 刷新串口设备*/
    void on_button_refresh_clicked();
    /** 接受数据槽函数*/
    void receiveInfo();
    /** 串口故障槽函数*/
    void handleSerialError(QSerialPort::SerialPortError error);
    /** 菜谱选择*/
    void on_button_menuSelect_clicked();

    void on_button_send_clicked();

    void on_button_clearDisplay_clicked();

    void on_button_bluetoothSearch_clicked();

    void on_button_bluetoothSelected_clicked();

    void on_button_uploadMenu_clicked();

    void on_button_programUpdate_clicked();

private:
    Ui::bluetooth *ui;
    /** 串口设备*/
    QSerialPort *serial;
    /** 菜谱数据*/
    QByteArray tmp_menuData;
    /** bin文件的页数索引*/
    uint32_t flashPage;

    enum bluetoothState
    {
        initMode,
        searchMode,
        selectMode,
        normalMode,
        transferMode,
    };

    bluetoothState BTstate;
    /** char转16位hex*/
    char ConvertHexChar(char ch);
    /** QString转16位hex*/
    QByteArray QString2Hex(QString str);
    /** 发送指令给蓝牙模块*/
    void sendATCommand(QString input);

    void SendProgramdata(QByteArray &input, uint32_t FlashPage);

};

#endif // BLUETOOTH_H
