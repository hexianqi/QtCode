#include "HMainWindow_p.h"
#include "ui_HMainWindow.h"
#include "qextserialport.h"
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtCore/QTextStream>
#include <QtCore/QTimer>
#include <QtCore/QThread>

HMainWindowPrivate::HMainWindowPrivate()
{
    configFileName = QString("Ini\\%1.ini").arg(QApplication::applicationName());
    sendFileName = QString("Data\\send.txt");
    deviceFileName = QString("Data\\device.txt");
}

void HMainWindowPrivate::readSendData(const QString &fileName)
{
    if (!fileName.isEmpty())
        sendFileName = fileName;
    sendDatas.clear();

    QFile file(sendFileName);
    if (file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            auto line = file.readLine();
            line = line.trimmed();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            if (!line.isEmpty())
                sendDatas << line;
        }
        file.close();
    }

    if (sendDatas.isEmpty())
        sendDatas << "16 FF 01 01 E0 E1" << "16 FF 01 01 E1 E2";
}

void HMainWindowPrivate::readDeviceData(const QString &fileName)
{
    if (!fileName.isEmpty())
        deviceFileName = fileName;
    deviceDatas.clear();

    QFile file(deviceFileName);
    if (file.size() > 0 && file.open(QFile::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            auto line = file.readLine();
            line = line.trimmed();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            if (!line.isEmpty())
            {
                auto list = line.split(';');
                auto key = list.first();
                list.removeFirst();
                auto value = list.join(';');
                deviceDatas.insert(key, value);
            }
        }
        file.close();
    }
}

HMainWindow::HMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HMainWindow),
    d_ptr(new HMainWindowPrivate)
{
    ui->setupUi(this);
    readSettings();
    init();
}

HMainWindow::~HMainWindow()
{
    writeSettings();
    if (d_ptr->com)
    {
        d_ptr->com->close();
        d_ptr->com->deleteLater();
    }
    delete ui;
}

void HMainWindow::readSettings()
{
    auto settings = new QSettings(d_ptr->configFileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("ComConfig");
    d_ptr->portName = settings->value("PortName", "COM1").toString();
    d_ptr->baudRate = settings->value("BaudRate", 9600).toInt();
    d_ptr->dataBit = settings->value("DataBit", 8).toInt();
    d_ptr->parity = settings->value("Parity", "无").toString();
    d_ptr->stopBit = settings->value("StopBit", 1).toInt();
    d_ptr->hexSend = settings->value("HexSend", false).toBool();
    d_ptr->hexReceive = settings->value("HexReceive", false).toBool();
    d_ptr->debug = settings->value("Debug", false).toBool();
    d_ptr->autoClear = settings->value("AutoClear", false).toBool();
    d_ptr->autoSend = settings->value("AutoSend", false).toBool();
    d_ptr->autoSave = settings->value("AutoSave", false).toBool();
    d_ptr->sendInterval = settings->value("SendInterval", 1000).toInt();
    d_ptr->saveInterval = settings->value("SaveInterval", 5000).toInt();
    settings->endGroup();
}

void HMainWindow::writeSettings()
{
    auto settings = new QSettings(d_ptr->configFileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("ComConfig");
    settings->setValue("PortName", ui->cboxPortName->currentText());
    settings->setValue("BaudRate", ui->cboxBaudRate->currentText());
    settings->setValue("DataBit", ui->cboxDataBit->currentText());
    settings->setValue("Parity", ui->cboxParity->currentText());
    settings->setValue("StopBit", ui->cboxStopBit->currentText());
    settings->setValue("HexSend", ui->ckHexSend->isChecked());
    settings->setValue("HexReceive", ui->ckHexReceive->isChecked());
    settings->setValue("Debug", ui->ckDebug->isChecked());
    settings->setValue("AutoClear", ui->ckAutoClear->isChecked());
    settings->setValue("AutoSend", ui->ckAutoSend->isChecked());
    settings->setValue("AutoSave", ui->ckAutoSave->isChecked());
    settings->setValue("SendInterval", d_ptr->timerSend->interval());
    settings->setValue("SaveInterval", d_ptr->timerSave->interval());
    settings->endGroup();
}

void HMainWindow::init()
{
    int i;
    d_ptr->readSendData();
    d_ptr->readDeviceData();
    d_ptr->timerRead = new QTimer(this);
    d_ptr->timerRead->setInterval(100);
    d_ptr->timerSend = new QTimer(this);
    d_ptr->timerSend->setInterval(d_ptr->sendInterval);
    d_ptr->timerSave = new QTimer(this);
    d_ptr->timerSave->setInterval(d_ptr->saveInterval);
    if (d_ptr->autoSend)
        d_ptr->timerSend->start();
    if (d_ptr->autoSave)
        d_ptr->timerSave->start();

    QStringList com, baudRate, dataBit, parity, stopBit, sendInterval, saveInterval;
    for (i = 1; i <= 20; i++)
        com << QString("COM%1").arg(i);
    com << "ttyUSB0" << "ttyS0" << "ttyS1" << "ttyS2" << "ttyS3" << "ttyS4";
    com << "ttymxc1" << "ttymxc2" << "ttymxc3" << "ttymxc4";
    com << "ttySAC1" << "ttySAC2" << "ttySAC3" << "ttySAC4";
    baudRate << "50" << "75" << "100" << "134" << "150" << "200" << "300" << "600" << "1200"
         << "1800" << "2400" << "4800" << "9600" << "14400" << "19200" << "38400"
         << "56000" << "57600" << "76800" << "115200" << "128000" << "256000";
    dataBit << "5" << "6" << "7" << "8";
    parity << "无" << "奇" << "偶";
    stopBit<< "1";
#ifdef Q_OS_WIN
    parity << "标志";
    stopBit << "1.5";
#endif
    parity << "空格";
    stopBit << "2";
    sendInterval << "100" << "300" << "500";
    for (i = 1000; i <= 10000; i += 1000)
    {
        sendInterval << QString::number(i);
        saveInterval << QString::number(i);
    }

    ui->cboxData->addItems(d_ptr->sendDatas);
    ui->cboxPortName->addItems(com);
    ui->cboxPortName->setCurrentIndex(ui->cboxPortName->findText(d_ptr->portName));
    ui->cboxBaudRate->addItems(baudRate);
    ui->cboxBaudRate->setCurrentIndex(ui->cboxBaudRate->findText(QString::number(d_ptr->baudRate)));
    ui->cboxDataBit->addItems(dataBit);
    ui->cboxDataBit->setCurrentIndex(ui->cboxDataBit->findText(QString::number(d_ptr->dataBit)));
    ui->cboxParity->addItems(parity);
    ui->cboxParity->setCurrentIndex(ui->cboxParity->findText(d_ptr->parity));
    ui->cboxStopBit->addItems(stopBit);
    ui->cboxStopBit->setCurrentIndex(ui->cboxStopBit->findText(QString::number(d_ptr->stopBit)));
    ui->ckHexSend->setChecked(d_ptr->hexSend);
    ui->ckHexReceive->setChecked(d_ptr->hexReceive);
    ui->ckDebug->setChecked(d_ptr->debug);
    ui->ckAutoClear->setChecked(d_ptr->autoClear);
    ui->ckAutoSend->setChecked(d_ptr->autoSend);
    ui->ckAutoSave->setChecked(d_ptr->autoSave);
    ui->cboxSendInterval->addItems(sendInterval);
    ui->cboxSaveInterval->addItems(saveInterval);
    ui->cboxSendInterval->setCurrentIndex(ui->cboxSendInterval->findText(QString::number(d_ptr->sendInterval)));
    ui->cboxSaveInterval->setCurrentIndex(ui->cboxSaveInterval->findText(QString::number(d_ptr->saveInterval)));

    connect(d_ptr->timerRead, &QTimer::timeout, this, &HMainWindow::readData);
    connect(d_ptr->timerSend, &QTimer::timeout, this, &HMainWindow::sendData);
    connect(d_ptr->timerSave, &QTimer::timeout, this, &HMainWindow::saveData);
    connect(ui->btnSend, &QPushButton::clicked, this, &HMainWindow::sendData);
    connect(ui->btnSave, &QPushButton::clicked, this, &HMainWindow::saveData);
    connect(ui->btnClear, &QPushButton::clicked, this, &HMainWindow::clear);
    connect(ui->cboxSendInterval, &QComboBox::currentTextChanged, this, [=] (QString value) { d_ptr->timerSend->setInterval(value.toInt()); });
    connect(ui->cboxSaveInterval, &QComboBox::currentTextChanged, this, [=] (QString value) { d_ptr->timerSave->setInterval(value.toInt()); });
    updateUI(false);
}

void HMainWindow::updateUI(bool b)
{
    ui->cboxBaudRate->setEnabled(!b);
    ui->cboxDataBit->setEnabled(!b);
    ui->cboxParity->setEnabled(!b);
    ui->cboxPortName->setEnabled(!b);
    ui->cboxStopBit->setEnabled(!b);
    ui->btnSend->setEnabled(b);
    ui->ckAutoSend->setEnabled(b);
    ui->ckAutoSave->setEnabled(b);
}

void HMainWindow::readData()
{
    if (d_ptr->com == nullptr || !d_ptr->com->isOpen() || d_ptr->com->bytesAvailable() <= 0)
        return;

    QThread::msleep(d_ptr->sleepTime);

    auto data = d_ptr->com->readAll();
    auto len = data.length();
    if (len <= 0 || !d_ptr->show)
        return;

    QString buffer = ui->ckHexReceive->isChecked() ? data.toHex(' ') : data;
    if (ui->ckDebug->isChecked())
    {
        for (auto it = d_ptr->deviceDatas.cbegin(); it != d_ptr->deviceDatas.cend(); it++)
        {
            if (buffer.startsWith(it.key()))
            {
                writeData(it.value());
                break;
            }
        }
    }

    append(1, buffer);
    d_ptr->receiveCount += data.size();
    ui->btnReceiveCount->setText(tr("接收 : %1 字节").arg(d_ptr->receiveCount));
}

void HMainWindow::writeData(QString data)
{
    if (d_ptr->com == nullptr || !d_ptr->com->isOpen())
        return;

    // 短信猫调试
    if (data.startsWith("AT"))
        data += "\r";

    auto buffer = ui->ckHexSend->isChecked() ? QByteArray::fromHex(data.remove(' ').toLatin1()) : data.toLatin1();
    d_ptr->com->write(buffer);
    append(0, data);
    d_ptr->sendCount += buffer.size();
    ui->btnSendCount->setText(tr("发送 : %1 字节").arg(d_ptr->sendCount));
}

void HMainWindow::sendData()
{
    auto text = ui->cboxData->currentText();
    if (text.isEmpty())
    {
        ui->cboxData->setFocus();
        return;
    }

    writeData(text);

    if (ui->ckAutoClear->isChecked())
    {
        ui->cboxData->setCurrentIndex(-1);
        ui->cboxData->setFocus();
    }
}

void HMainWindow::saveData()
{
    QString text = ui->txtMain->toPlainText();
    if (text.isEmpty())
        return;

    auto fileName = QString("Data/%1.txt").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
    QFile file(fileName);
    file.open(QFile::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << text;
    file.close();
    clear();
}

void HMainWindow::append(int type, const QString &data)
{
    if (!d_ptr->show)
        return;

    if (d_ptr->currentCount >= d_ptr->maxCount)
        clear();

    QString text = data;
    text = text.replace("\r", "");
    text = text.replace("\n", "");

    QString strType;
    if (type == 0)
    {
        strType = "串口发送 >>";
        ui->txtMain->setTextColor(QColor("dodgerblue"));
    }
    else if (type == 1)
    {
        strType = "串口接收 <<";
        ui->txtMain->setTextColor(QColor("red"));
    }
    else if (type == 2)
    {
        strType = "处理延时 >>";
        ui->txtMain->setTextColor(QColor("gray"));
    }
    else if (type == 3)
    {
        strType = "正在校验 >>";
        ui->txtMain->setTextColor(QColor("green"));
    }
    else if (type == 6)
    {
        strType = "提示信息 >>";
        ui->txtMain->setTextColor(QColor(100, 184, 255));
    }

    text = QString("时间[%1] %2 %3").arg(QTime::currentTime().toString("HH:mm:ss zzz")).arg(strType).arg(text);
    ui->txtMain->append(text);
    d_ptr->currentCount++;
}

void HMainWindow::clear()
{
    ui->txtMain->clear();
    d_ptr->currentCount = 0;
}

void HMainWindow::on_btnOpen_clicked()
{
    if (d_ptr->opened)
    {
        d_ptr->opened = false;
        d_ptr->timerRead->stop();
        d_ptr->com->close();
        ui->btnOpen->setText("打开串口");
        updateUI(false);
        clear();
    }
    else
    {
        if (d_ptr->com == nullptr)
            d_ptr->com = new QextSerialPort(ui->cboxPortName->currentText(), QextSerialPort::Polling);
        if (d_ptr->com->open(QIODevice::ReadWrite))
        {
            d_ptr->opened = true;
            d_ptr->com->flush();
            d_ptr->com->setBaudRate((BaudRateType)ui->cboxBaudRate->currentText().toInt());
            d_ptr->com->setDataBits((DataBitsType)ui->cboxDataBit->currentText().toInt());
            d_ptr->com->setParity((ParityType)ui->cboxParity->currentIndex());
            d_ptr->com->setStopBits((StopBitsType)ui->cboxStopBit->currentIndex());
            d_ptr->com->setFlowControl(FLOW_OFF);
            d_ptr->com->setTimeout(10);
            ui->btnOpen->setText("关闭串口");
            updateUI(true);
            d_ptr->timerRead->start();
        }
    }
}

void HMainWindow::on_btnSendCount_clicked()
{
    d_ptr->sendCount = 0;
    ui->btnSendCount->setText("发送 : 0 字节");
}

void HMainWindow::on_btnReceiveCount_clicked()
{
    d_ptr->receiveCount = 0;
    ui->btnReceiveCount->setText("接收 : 0 字节");
}

void HMainWindow::on_btnStopShow_clicked()
{
    d_ptr->show = !d_ptr->show;
    ui->btnStopShow->setText(d_ptr->show ? "停止显示" : "开始显示");
}

void HMainWindow::on_btnData_clicked()
{
    QFile file(d_ptr->sendFileName);
    if (!file.exists())
        return;

    if (ui->btnData->text() == "管理数据")
    {
        ui->txtMain->setReadOnly(false);
        ui->txtMain->clear();
        file.open(QFile::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        ui->txtMain->setText(in.readAll());
        file.close();
        ui->btnData->setText("保存数据");
    }
    else
    {
        ui->txtMain->setReadOnly(true);
        file.open(QFile::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << ui->txtMain->toPlainText();
        file.close();
        ui->txtMain->clear();
        ui->btnData->setText("管理数据");
    }
}

void HMainWindow::on_ckAutoSend_stateChanged(int arg)
{
    if (arg == 0)
    {
        ui->cboxSendInterval->setEnabled(false);
        d_ptr->timerSend->stop();
    }
    else
    {
        ui->cboxSendInterval->setEnabled(true);
        d_ptr->timerSend->start();
    }
}

void HMainWindow::on_ckAutoSave_stateChanged(int arg)
{
    if (arg == 0)
    {
        ui->cboxSaveInterval->setEnabled(false);
        d_ptr->timerSave->stop();
    }
    else
    {
        ui->cboxSaveInterval->setEnabled(true);
        d_ptr->timerSave->start();
    }
}


