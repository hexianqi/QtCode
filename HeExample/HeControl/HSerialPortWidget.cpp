#include "HSerialPortWidget_p.h"
#include "ui_HSerialPortWidget.h"
#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

HE_CONTROL_BEGIN_NAMESPACE

HSerialPortWidget::HSerialPortWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HSerialPortWidget),
    d_ptr(new HSerialPortWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HSerialPortWidget::~HSerialPortWidget()
{
    if (d_ptr->isConnected)
        closePort();
    delete ui;
}

void HSerialPortWidget::on_pushButton_101_clicked()
{
    if (d_ptr->isConnected)
    {
        closePort();
        updateUi(false);
        ui->pushButton_101->setText(tr("打开串口"));
        ui->label_711->setText(tr("<font color=#FF0000>关闭</font>"));
        d_ptr->isConnected = false;
    }
    else
    {
        if (openPort())
        {
            updateUi(true);
            ui->pushButton_101->setText(tr("关闭串口"));
            ui->label_711->setText(tr("<font color=#00FF00>打开</font>"));
            d_ptr->isConnected = true;
        }
        else
            QMessageBox::critical(this, tr("提示"), tr("打开串口失败！"), QMessageBox::Ok);
    }
}

void HSerialPortWidget::on_pushButton_501_clicked()
{
    writeData();
}

void HSerialPortWidget::on_pushButton_601_clicked()
{
    d_ptr->sendCount = 0;
    ui->label_712->setText(tr("%1 字节").arg(d_ptr->sendCount));
}

void HSerialPortWidget::on_pushButton_602_clicked()
{
    d_ptr->receiveCount = 0;
    ui->label_713->setText(tr("%1 字节").arg(d_ptr->receiveCount));
}

void HSerialPortWidget::on_pushButton_603_clicked()
{
    d_ptr->isShow = !d_ptr->isShow;
    ui->pushButton_603->setText(d_ptr->isShow ? tr("停止显示") : tr("开始显示"));
}

void HSerialPortWidget::on_pushButton_604_clicked()
{
    d_ptr->sendTimes = 0;
    d_ptr->receiveTimes = 0;
    ui->textEdit_301->clear();
    ui->textEdit_401->clear();
}

void HSerialPortWidget::on_pushButton_605_clicked()
{
    saveData();
}

void HSerialPortWidget::showTime()
{
    auto n = QDateTime::currentDateTime();
    ui->label_714->setText(n.toString("yyyy-mm-dd"));
    ui->label_715->setText(n.toString("hh:mm:ss"));
}

void HSerialPortWidget::updateUi(bool b)
{
    ui->comboBox_101->setEnabled(!b);
    ui->comboBox_102->setEnabled(!b);
    ui->comboBox_103->setEnabled(!b);
    ui->comboBox_104->setEnabled(!b);
    ui->comboBox_105->setEnabled(!b);
    ui->groupBox_2->setEnabled(b);
    ui->groupBox_3->setEnabled(b);
    ui->groupBox_4->setEnabled(b);
    ui->groupBox_5->setEnabled(b);
    ui->groupBox_6->setEnabled(b);
    ui->pushButton_101->setEnabled(true);
}

bool HSerialPortWidget::openPort()
{
    d_ptr->port->setPortName(ui->comboBox_101->currentText());
    d_ptr->port->setBaudRate(ui->comboBox_102->currentData().toUInt());
    d_ptr->port->setDataBits(static_cast<QSerialPort::DataBits>(ui->comboBox_103->currentData().toInt()));
    d_ptr->port->setParity(static_cast<QSerialPort::Parity>(ui->comboBox_104->currentData().toInt()));
    d_ptr->port->setStopBits(static_cast<QSerialPort::StopBits>(ui->comboBox_105->currentData().toInt()));
    d_ptr->port->setFlowControl(QSerialPort::NoFlowControl);
    if (!d_ptr->port->open(QIODevice::ReadWrite))
        return false;
    d_ptr->readTimer->start(d_ptr->readInterval);
    return true;
}

bool HSerialPortWidget::closePort()
{
    d_ptr->readTimer->stop();
    d_ptr->port->close();
    return true;
}

void HSerialPortWidget::writeData()
{
    if (!d_ptr->isConnected)
        return;

    auto data = ui->textEdit_501->toPlainText();
    if (data.isEmpty())
        return;
    auto buff = ui->checkBox_201->isChecked() ? QByteArray::fromHex(data.remove(' ').toLatin1()) : data.toLatin1();
    auto ret = d_ptr->port->write(buff, buff.size());
    if (ret < 0)
    {
        QMessageBox::critical(this, tr("提示"), tr("写入数据失败！"), QMessageBox::Ok);
        return;
    }
    d_ptr->sendTimes++;
    d_ptr->sendCount += ret;
    ui->textEdit_401->append(QString("%1 ==================================").arg(d_ptr->sendTimes, 3, 10, QLatin1Char('0')));
    ui->textEdit_401->append(data);
    ui->label_712->setText(tr("%1 字节").arg(d_ptr->sendCount));
}

void HSerialPortWidget::readData()
{
    if (!d_ptr->isConnected)
        return;

    auto buff = d_ptr->port->readAll();
    if (buff.isEmpty() || !d_ptr->isShow)
        return;

    d_ptr->receiveTimes++;
    d_ptr->receiveCount += buff.size();
    ui->textEdit_301->append(QString("%1 ==================================").arg(d_ptr->receiveTimes, 3, 10, QLatin1Char('0')));
    ui->textEdit_301->append(ui->checkBox_202->isChecked() ? buff.toHex(' ').toUpper() : buff);
    ui->label_713->setText(tr("%1 字节").arg(d_ptr->receiveCount));
}

void HSerialPortWidget::autoSendData()
{
    if (ui->checkBox_203->isChecked())
    {
        writeData();
        d_ptr->sendTimer->setInterval(ui->spinBox_201->value() * 1000);
    }
}

void HSerialPortWidget::autoSaveData()
{
    if (ui->checkBox_204->isChecked())
    {
        saveData();
        d_ptr->saveTimer->setInterval(ui->spinBox_202->value() * 1000);
    }
}

void HSerialPortWidget::saveData()
{
    auto data1 = ui->textEdit_301->toPlainText();
    auto data2 = ui->textEdit_401->toPlainText();
    if (data1.isEmpty() && data2.isEmpty())
        return;

    QString fileName = QCoreApplication::applicationDirPath() + "/" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss") +".txt";
    QFile file(fileName);
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    out << "receive:" << endl;
    out << data1 << endl;
    out << "send:" << endl;
    out << data2 << endl;
    file.close();
}

void HSerialPortWidget::init()
{
    d_ptr->port = new QSerialPort(this);
    d_ptr->timeTimer = new QTimer(this);
    d_ptr->readTimer = new QTimer(this);
    d_ptr->sendTimer = new QTimer(this);
    d_ptr->saveTimer = new QTimer(this);
    for (const auto &info : QSerialPortInfo::availablePorts())
        ui->comboBox_101->addItem(info.portName());
    for (const auto &rate : QSerialPortInfo::standardBaudRates())
        ui->comboBox_102->addItem(QString("%1").arg(rate), rate);
    ui->comboBox_103->addItem("5", QSerialPort::Data5);
    ui->comboBox_103->addItem("6", QSerialPort::Data6);
    ui->comboBox_103->addItem("7", QSerialPort::Data7);
    ui->comboBox_103->addItem("8", QSerialPort::Data8);
    ui->comboBox_103->setCurrentIndex(3);
    ui->comboBox_104->addItem(tr("无"), QSerialPort::NoParity);
    ui->comboBox_104->addItem(tr("奇"), QSerialPort::OddParity);
    ui->comboBox_104->addItem(tr("偶"), QSerialPort::EvenParity);
    ui->comboBox_104->addItem(tr("空格"), QSerialPort::SpaceParity);
    ui->comboBox_104->addItem(tr("标志"), QSerialPort::MarkParity);
    ui->comboBox_104->setCurrentIndex(0);
    ui->comboBox_105->addItem("1", QSerialPort::OneStop);
    ui->comboBox_105->addItem("1.5", QSerialPort::OneAndHalfStop);
    ui->comboBox_105->addItem("2", QSerialPort::TwoStop);
    ui->comboBox_105->setCurrentIndex(0);
    updateUi(false);
    connect(d_ptr->timeTimer, &QTimer::timeout, this, &HSerialPortWidget::showTime);
    connect(d_ptr->readTimer, &QTimer::timeout, this, &HSerialPortWidget::readData);
    connect(d_ptr->sendTimer, &QTimer::timeout, this, &HSerialPortWidget::autoSendData);
    connect(d_ptr->saveTimer, &QTimer::timeout, this, &HSerialPortWidget::autoSaveData);
    d_ptr->timeTimer->start(1000);
    d_ptr->sendTimer->start(1000);
    d_ptr->saveTimer->start(1000);
}

HE_CONTROL_END_NAMESPACE
