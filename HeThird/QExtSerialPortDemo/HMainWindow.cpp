#include "HMainWindow_p.h"
#include "ui_HMainWindow.h"
#include "qextserialport.h"
#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtCore/QThread>

HMainWindowPrivate::HMainWindowPrivate()
{
    configFileName = QString("Ini\\%1.ini").arg(QApplication::applicationName());
    sendFileName = QString("Data\\send.txt");
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
    d_ptr->sendInterval = settings->value("SendInterval", 1000).toInt();
    d_ptr->autoSave = settings->value("AutoSave", false).toBool();
    d_ptr->saveInterval = settings->value("SaveInterval", 5000).toInt();
    settings->endGroup();
}

void HMainWindow::writeSettings()
{
    auto settings = new QSettings(d_ptr->configFileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("ComConfig");
    settings->setValue("PortName", d_ptr->portName);
    settings->setValue("BaudRate", d_ptr->baudRate);
    settings->setValue("DataBit", d_ptr->dataBit);
    settings->setValue("Parity", d_ptr->parity);
    settings->setValue("StopBit", d_ptr->stopBit);
    settings->setValue("HexSend", d_ptr->hexSend);
    settings->setValue("HexReceive", d_ptr->hexReceive);
    settings->setValue("Debug", d_ptr->debug);
    settings->setValue("AutoClear", d_ptr->autoClear);
    settings->setValue("AutoSend", d_ptr->autoSend);
    settings->setValue("SendInterval", d_ptr->sendInterval);
    settings->setValue("AutoSave", d_ptr->autoSave);
    settings->setValue("SaveInterval", d_ptr->saveInterval);
    settings->endGroup();
}

void HMainWindow::init()
{
    int i;
    d_ptr->readSendData();
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
    connect(ui->btnSend, &QPushButton::click, this, &HMainWindow::sendData);
    connect(ui->btnSave, &QPushButton::click, this, &HMainWindow::saveData);
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
    if (len <= 0 || !d_ptr->isShow)
        return;



        QString buffer;
        if (ui->ckHexReceive->isChecked()) {
            buffer = QUIHelperData::byteArrayToHexStr(data);
        } else {
            //buffer = QUIHelperData::byteArrayToAsciiStr(data);
            buffer = QString::fromLocal8Bit(data);
        }

        //启用调试则模拟调试数据
        if (ui->ckDebug->isChecked()) {
            int count = AppData::Keys.count();
            for (int i = 0; i < count; i++) {
                if (buffer.startsWith(AppData::Keys.at(i))) {
                    sendData(AppData::Values.at(i));
                    break;
                }
            }
        }

        append(1, buffer);
        receiveCount = receiveCount + data.size();
        ui->btnReceiveCount->setText(QString("接收 : %1 字节").arg(receiveCount));

        //启用网络转发则调用网络发送数据
        if (tcpOk) {
            socket->write(data);
            append(4, QString(buffer));
        }
    }


}


