#include "bluetooth.h"
#include "ui_bluetooth.h"

bluetooth::bluetooth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bluetooth)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_ShowModal, true);

    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
      ui->combox_comDisplay->addItem(info.portName());
    }
    BTstate =initMode;

}



bluetooth::~bluetooth()
{
    if (serial->isOpen())
    {
        serial->clear();
        serial->close();
        serial->deleteLater();
    }
    //delete serial;

    delete ui;
}

/*--------------------------------------------------------UI控件触发事件区-----------------------------------------------------------------*/
/**
 * @brief bluetooth::on_button_comSelected_clicked 打开串口
 */
void bluetooth::on_button_comSelected_clicked()
{
    //ui->textBrowser->append(ui->button_comSelected->text());
    if(ui->button_comSelected->text() == tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->combox_comDisplay->currentText());
        //打开串口
        if(!serial->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
        {
            ui->textBrowser->append(ui->combox_comDisplay->currentText() + "打开失败!");
            return;
        }
        else {
            ui->textBrowser->append(ui->combox_comDisplay->currentText() + "打开成功!");
        }
        //设置波特率
        serial->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
        //设置数据位数
        serial->setDataBits(QSerialPort::Data8);//设置数据位8
        //设置校验位
        serial->setParity(QSerialPort::NoParity);
        //设置停止位
        serial->setStopBits(QSerialPort::OneStop);//停止位设置为1
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制

        //关闭设置菜单使能
        ui->combox_comDisplay->setEnabled(false);
        ui->combox_comDisplay->clear();
        ui->button_comSelected->setText(tr("关闭串口"));

        //连接信号槽,接受到信号触发
        connect(serial,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
        //连接信号槽,串口故障触发
        connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),  this, &bluetooth::handleSerialError);

        //测试蓝牙模块是否在线
        sendATCommand("AT");
        serial->waitForBytesWritten();
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->combox_comDisplay->setEnabled(true);

        ui->button_comSelected->setText(tr("打开串口"));

        //查找可用的串口
        foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        {
          ui->combox_comDisplay->addItem(info.portName());
        }
    }
}


/**
 * @brief bluetooth::on_button_refresh_clicked 刷新串口设备
 */
void bluetooth::on_button_refresh_clicked()
{
    ui->combox_comDisplay->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
      ui->combox_comDisplay->addItem(info.portName());
    }
}

/**
 * @brief bluetooth::on_button_menuSelect_clicked 选择要发送的菜谱文件
 */
void bluetooth::on_button_menuSelect_clicked()
{
    QString file = QFileDialog::getOpenFileName(
                                this, tr("打开单个菜谱文件"),
                                "./",
                                tr("Bin Files (*.bin)"));
    if(file.isEmpty())
      {
        ui->label_menuSelected->setText(tr("未选择菜谱文件"));
        tmp_menuData.clear();
        return;
      }
      else
      {
        //显示文件名
        QFileInfo inf = QFileInfo(file);
        ui->label_menuSelected->setText(inf.fileName());
        //打开文件
        QFile menuFile(file);
        menuFile.open(QIODevice::ReadOnly);
        tmp_menuData = menuFile.readAll();
        menuFile.close();
      }
}

/**
 * @brief bluetooth::on_button_send_clicked 发送指定区域内的数据
 */
void bluetooth::on_button_send_clicked()
{
    QByteArray extra ;
    extra.resize(2);
    extra[0] = 0x0D;
    extra[1] = 0x0A;
    QString sendData = ui->edit_command->text();
    serial->write(sendData.toLocal8Bit() + extra);
    serial->waitForReadyRead(100);
}

/**
 * @brief bluetooth::on_button_clearDisplay_clicked 清空展示区
 */
void bluetooth::on_button_clearDisplay_clicked()
{
    ui->textBrowser->clear();
}


/**
 * @brief bluetooth::on_button_bluetoothSearch_clicked 开始搜索蓝牙
 */
void bluetooth::on_button_bluetoothSearch_clicked()
{
    //进入主设备模式之后，在串口接受槽函数中收到反馈再搜索
    if(serial->isOpen())
    {
        sendATCommand("AT+ROLE=1");
        serial->waitForBytesWritten();
    }
    else {
        ui->textBrowser->append("串口没有打开");
    }

    //sendATCommand("AT+SINQ");
    //serial->waitForBytesWritten();
    //sendATCommand("AT+INQ");
}
/**
 * @brief bluetooth::on_button_bluetoothSelected_clicked 连接到蓝牙
 */
void bluetooth::on_button_bluetoothSelected_clicked()
{
    if(BTstate == searchMode)
    {
        sendATCommand("AT+CONN=" + QString::number((ui->combox_bluetoothDisplay->currentIndex()),10));
        ui->combox_bluetoothDisplay->clear();
        ui->combox_bluetoothDisplay->setEnabled(false);
    }
    else {
        ui->textBrowser->append("没有找到蓝牙");
    }
}

/**
 * @brief bluetooth::on_button_uploadMenu_clicked 进入透传模式并上传菜谱
 */
void bluetooth::on_button_uploadMenu_clicked()
{
    if(tmp_menuData.isEmpty())
    {
        ui->textBrowser->append("没有选择菜谱文件");
        return;
    }

    flashPage = 1;

    QByteArray extra ;
    extra.resize(6);
    extra[0] = 0xF1;
    extra[1] = 0xAA;
    extra[2] = 0x00;
    extra[3] = 0x01;
    extra[4] = 0x03;
    extra[5] = extra[1]+ extra[2]+ extra[3]+ extra[4];

    serial->write(extra);
    serial->waitForReadyRead(100);

    ui->button_uploadMenu->setText("传输中");
    ui->button_uploadMenu->setEnabled(false);
}

/**
 * @brief bluetooth::on_button_programUpdate_clicked OTA更新入口
 */
void bluetooth::on_button_programUpdate_clicked()
{
    if(tmp_menuData.isEmpty())
    {
        ui->textBrowser->append("没有选择文件");
        return;
    }

    flashPage = 1;

    QByteArray extra ;
    extra.resize(6);
    extra[0] = 0xF1;
    extra[1] = 0xAA;
    extra[2] = 0x00;
    extra[3] = 0x01;
    extra[4] = 0x01;
    extra[5] = extra[1]+ extra[2]+ extra[3]+ extra[4];

    serial->write(extra);
    serial->waitForReadyRead(100);

    ui->button_programUpdate->setText("传输中");
    ui->button_programUpdate->setEnabled(false);
}

/*--------------------------------------------------------辅助函数区-----------------------------------------------------------------*/
/**
 * @brief bluetooth::receiveInfo 接受串口传来的数据
 */
void bluetooth::receiveInfo()
{
    QByteArray info = serial->readAll();

    if(info[0].operator== (0xf2) &&  info[1].operator== (0xaa))
        ui->textBrowser->append("收<-" + info.toHex(':'));
    else {
        ui->textBrowser->append("收<-" + QString(info));
    }

    if(QString(info) == "OK\r\n")
    {
        ui->textBrowser->append("蓝牙模块正常");
        return;
    }
    else if(QString(info) == "+ROLE=1\r\nOK\r\n")
    {
        ui->textBrowser->append("本机蓝牙设置为主设备");
        //先关闭搜索使搜索使能
        sendATCommand("AT+SINQ");
        serial->waitForBytesWritten();
        //开始搜索
        sendATCommand("AT+INQ");
        serial->waitForBytesWritten();
        return;
    }
    else if(QString(info) == "+INQE\r\n")
    {
        ui->textBrowser->append("蓝牙搜索可用");
        return;
    }
    else if(QString(info) == "OK\r\n+INQS\r\n")
    {
        BTstate = searchMode;
        ui->combox_bluetoothDisplay->setEnabled(true);
        ui->combox_bluetoothDisplay->clear();
        ui->textBrowser->append("开始搜索蓝牙");
        return;
    }
    else if(QString(info) == "+CONNS\r\n")
    {
        BTstate = selectMode;
        ui->textBrowser->append("开始连接蓝牙");
        return;
    }
    else if(QString(info) == "+CONNECTION TIME OUT\r\n")
    {
        ui->textBrowser->append("连接超时");
        return;
    }
    else if(QString(info) == "INVALID CONNECTION COMMAND\r\n")
    {
        ui->textBrowser->append("非法指令");
        return;
    }
    else if (info[0].operator== (0xf2) &&  info[2].operator== (0x00) && info[4].operator==(0x02)) {
        ui->textBrowser->append("透传模式下");
        BTstate = normalMode;
        return;
    }
    else if (info[0].operator== (0xf2) &&  info[2].operator== (0x00) && (info[4].operator==(0x03) ||info[4].operator==(0x01) )) {
        ui->textBrowser->append("透传模式的传菜谱下");
        BTstate = transferMode;
    }

    /** 搜索模式下，将搜索到的设备添加到下拉列表中*/
    if(searchMode == BTstate)
    {
        ui->combox_bluetoothDisplay->addItem(QString(info));
        return;
    }

    /** 选择模式下，连接到蓝牙之后进入透传模式，准备传输*/
    if(selectMode == BTstate)
    {
        ui->textBrowser->append(QString(info));
        BTstate = transferMode;
        return;
    }

    /** 传输模式下，上传菜谱*/
    if(transferMode == BTstate)
    {
        ui->textBrowser->append("上传菜谱中");
        //ui->textBrowser->append(info.toHex(':'));

        //发送失败，重新发送
        if(info[4].operator!=(0x00))
        {
            flashPage++;
        }
        //文件是否发送完整
        if((flashPage) > ( (tmp_menuData.size()/1024) + 1 ) )
        {
            ui->textBrowser->append("文件上传完成");
            ui->button_uploadMenu->setText("上传菜谱");
            ui->button_uploadMenu->setEnabled(true);
            return;
        }
        //开始发送数据
        SendProgramdata(tmp_menuData,flashPage);

    }

}


void bluetooth::handleSerialError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        ui->textBrowser->append("串口异常，请重新插拔");
        serial->close();
    }
}

/**
 * @brief bluetooth::SendProgramdata 发送1k大小的flash数据，其中页数规定1k所在位置
 * @param input 发送的flash文件，完整数据
 * @param FlashPage 在flash中页的索引
 */
void bluetooth::SendProgramdata(QByteArray &input,uint32_t FlashPage)
{

    //QString flashnumstr;
    //发送数据缓冲区
    uint8_t FlashSend[1030];
    //bin文件当前页数的起始地址
    uint32_t FileBinAddress;
    //校验核
    uint8_t FlashChecksum = 0;

    if(transferMode == BTstate)
    {
        FlashSend[0] = 0xF1;
        FlashSend[1] = 0xAA;
        FlashSend[2] = 0x01;
        FlashSend[3] = 0xFF;
        FlashSend[4] = FlashPage;
        FlashChecksum = FlashSend[1]+FlashSend[2]+FlashSend[3]+FlashSend[4];

        FileBinAddress = (FlashPage-1)*1024;
        //需要发送bin文件的整体大小
        uint32_t binSize = input.size();


        //FlashChecksum = 0;
        for(uint16_t i =0;i<1024;i++)
        {
            if(FileBinAddress < binSize)
            {
                FlashSend[i+5] = input[FileBinAddress];
            }
            else
            {
                FlashSend[i+5] = 0xFF;
            }

            FileBinAddress++;

            FlashChecksum+=FlashSend[i+5];
        }

        FlashSend[1029] = FlashChecksum;

        ui->textBrowser->append("发送第" + QString::number(FlashPage,10) + "块数据");
        serial->write((const char *)FlashSend,1030);
        serial->waitForReadyRead(100);
        serial->waitForBytesWritten();


    }
    else {
        ui->textBrowser->append("蓝牙不在传输状态，无法发送");
    }

}


char bluetooth::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}

QByteArray bluetooth::QString2Hex(QString str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

void bluetooth::sendATCommand(QString input)
{
    QByteArray extra ;
    extra.resize(2);
    extra[0] = 0x0D;
    extra[1] = 0x0A;
    if(serial->isOpen())
    {
        serial->write(input.toLocal8Bit() + extra);
        serial->waitForReadyRead(100);
    }
    else {
        ui->textBrowser->append("串口没有打开");
    }
}



