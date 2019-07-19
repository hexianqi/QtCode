#include "HUdpServerWidget_p.h"
#include "ui_HUdpServerWidget.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtNetwork/QUdpSocket>

HE_CORE_USE_NAMESPACE
HE_CONTROL_BEGIN_NAMESPACE

HUdpServerWidgetPrivate::HUdpServerWidgetPrivate()
{
    groupName = "UdpServer";
}

HUdpServerWidget::HUdpServerWidget(QWidget *parent) :
    HAbstractNetworkWidget(*new HUdpServerWidgetPrivate, parent),
    ui(new Ui::HUdpServerWidget)
{
    ui->setupUi(this);
    readSettings();
    init();
}

HUdpServerWidget::~HUdpServerWidget()
{
    writeSettings();
    delete ui;
}

void HUdpServerWidget::setServerIp(QString value)
{
    Q_D(HUdpServerWidget);
    if (d->serverIp == value)
        return;
    d->serverIp = value;
}

void HUdpServerWidget::setServerPort(int value)
{
    Q_D(HUdpServerWidget);
    if (d->serverPort == value)
        return;
    d->serverPort = value;
}

void HUdpServerWidget::setListenPort(int value)
{
    Q_D(HUdpServerWidget);
    if (d->listenPort == value)
        return;
    d->listenPort = value;
}

void HUdpServerWidget::clearData()
{
    Q_D(HUdpServerWidget);
    ui->textEdit->clear();
    d->currentCount = 0;
}

void HUdpServerWidget::sendData()
{
    Q_D(HUdpServerWidget);
    auto text = ui->lineEdit_201->text();
    if (text.length() <= 0)
        return;

    auto data = toByteArray(text);
    d->udpSocket->writeDatagram(data, QHostAddress(d->serverIp), d->serverPort);
    append(0, QString("[%1:%2] %3").arg(d->serverIp).arg(d->serverPort).arg(text));
}

void HUdpServerWidget::on_pushButton_101_clicked()
{
    Q_D(HUdpServerWidget);
    if (ui->pushButton_101->text() == "监听")
    {
        if (d->udpSocket->bind(QHostAddress::AnyIPv4, d->listenPort))
        {
            ui->pushButton_101->setText("关闭");
            append(0, "监听成功");
        }
    }
    else
    {
        d->udpSocket->abort();
        ui->pushButton_101->setText("监听");
    }
}

void HUdpServerWidget::on_pushButton_102_clicked()
{
    if (saveData(ui->textEdit->toPlainText()))
        clearData();
}

void HUdpServerWidget::handleReadyRead()
{
    Q_D(HUdpServerWidget);
    QHostAddress host;
    quint16 port;
    QByteArray data;
    QString text;

    while (d->udpSocket->hasPendingDatagrams())
    {
        data.resize(d->udpSocket->pendingDatagramSize());
        d->udpSocket->readDatagram(data.data(), data.size(), &host, &port);

        auto ip = host.toString();
        if (ip.isEmpty())
            continue;
        auto text = fromByteArray(data);
        append(1, QString("[%1:%2] %3").arg(ip).arg(port).arg(text));
    }
}

void HUdpServerWidget::append(int type, QString data)
{
    Q_D(HUdpServerWidget);
    if (d->currentCount >= d->maxCount)
        clearData();

    auto text = data.replace("\r", "").replace("\n", "");
    QString strType;
    if (type == 0)
    {
        strType = tr("发送");
        ui->textEdit->setTextColor(Qt::darkGreen);
    }
    else
    {
        strType = tr("接收");
        ui->textEdit->setTextColor(Qt::red);
    }
    ui->textEdit->append(tr("[%1][%2]: %3").arg(QTime::currentTime().toString("HH:mm:ss.zzz")).arg(strType).arg(text));
    d->currentCount++;
}

void HUdpServerWidget::readSettings()
{
    Q_D(HUdpServerWidget);
    HAbstractNetworkWidget::readSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d->groupName);
    d->serverIp = settings->value("sServerIp", "127.0.0.1").toString();
    d->serverPort = settings->value("iServerPort", 6000).toInt();
    d->listenPort = settings->value("iListenPort", 6000).toInt();
    settings->endGroup();
}

void HUdpServerWidget::writeSettings()
{
    Q_D(HUdpServerWidget);
    HAbstractNetworkWidget::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d->groupName);
    settings->setValue("sServerIp", d->serverIp);
    settings->setValue("iServerPort", d->serverPort);
    settings->setValue("iListenPort", d->listenPort);
    settings->endGroup();
}


void HUdpServerWidget::init()
{
    Q_D(HUdpServerWidget);
    d->udpSocket = new QUdpSocket(this);
    d->timer->setInterval(d->interval);
    d->autoSend ? d->timer->start() : d->timer->stop();
    ui->checkBox_101->setChecked(d->hexSend);
    ui->checkBox_102->setChecked(d->hexReceive);
    ui->checkBox_103->setChecked(d->ascii);
    ui->checkBox_104->setChecked(d->autoSend);
    ui->spinBox_101->setValue(d->interval);
    ui->spinBox_102->setValue(d->serverPort);
    ui->spinBox_103->setValue(d->listenPort);
    ui->lineEdit_101->setText(d->serverIp);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HUdpServerWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HUdpServerWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HUdpServerWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HUdpServerWidget::setAutoSend);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setServerPort(int)));
    connect(ui->spinBox_103, SIGNAL(valueChanged(int)), this, SLOT(setListenPort(int)));
    connect(ui->lineEdit_101, &QLineEdit::editingFinished, this, [=]{ setServerIp(ui->lineEdit_101->text()); });
    connect(ui->pushButton_103, &QPushButton::clicked, this, &HUdpServerWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HUdpServerWidget::sendData);
    connect(d->udpSocket, &QUdpSocket::readyRead, this, &HUdpServerWidget::handleReadyRead);
    setWindowTitle(tr("Udp服务端"));
}

HE_CONTROL_END_NAMESPACE
