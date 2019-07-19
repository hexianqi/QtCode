#include "HTcpClientWidget_p.h"
#include "ui_HTcpClientWidget.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>

HE_CORE_USE_NAMESPACE
HE_CONTROL_BEGIN_NAMESPACE

HTcpClientWidgetPrivate::HTcpClientWidgetPrivate()
{
    groupName = "TcpClient";
}

HTcpClientWidget::HTcpClientWidget(QWidget *parent) :
    HAbstractNetworkWidget(*new HTcpClientWidgetPrivate, parent),
    ui(new Ui::HTcpClientWidget)
{
    ui->setupUi(this);    
    readSettings();
    init();
}

HTcpClientWidget::~HTcpClientWidget()
{
    writeSettings();
    delete ui;
}

void HTcpClientWidget::setServerIp(QString value)
{
    Q_D(HTcpClientWidget);
    if (d->serverIp == value)
        return;
    d->serverIp = value;
}

void HTcpClientWidget::setServerPort(int value)
{
    Q_D(HTcpClientWidget);
    if (d->serverPort == value)
        return;
    d->serverPort = value;
}

void HTcpClientWidget::clearData()
{
    Q_D(HTcpClientWidget);
    ui->textEdit->clear();
    d->currentCount = 0;
}

void HTcpClientWidget::sendData()
{
    Q_D(HTcpClientWidget);
    if (!d->connect)
        return;

    auto text = ui->lineEdit_201->text();
    if (text.length() <= 0)
        return;

    auto data = toByteArray(text);
    d->tcpSocket->write(data);
    append(0, text);
}

void HTcpClientWidget::on_pushButton_101_clicked()
{
    Q_D(HTcpClientWidget);
    d->tcpSocket->abort();
    if (ui->pushButton_101->text() == "连接")
        d->tcpSocket->connectToHost(d->serverIp, d->serverPort);
}

void HTcpClientWidget::on_pushButton_102_clicked()
{
    if (saveData(ui->textEdit->toPlainText()))
        clearData();
}

void HTcpClientWidget::handleConnected()
{
    Q_D(HTcpClientWidget);
    d->connect = true;
    ui->pushButton_101->setText("断开");
    append(0, tr("服务器连接"));
}

void HTcpClientWidget::handleDisconnected()
{
    Q_D(HTcpClientWidget);
    d->connect = false;
    d->tcpSocket->abort();
    ui->pushButton_101->setText("连接");
    append(1, tr("服务器断开"));
}

void HTcpClientWidget::handleReadyRead()
{
    Q_D(HTcpClientWidget);
    auto data = d->tcpSocket->readAll();
    if (data.length() <= 0)
        return;
    append(1, fromByteArray(data));
}

void HTcpClientWidget::append(int type, QString data)
{
    Q_D(HTcpClientWidget);
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

void HTcpClientWidget::readSettings()
{
    Q_D(HTcpClientWidget);
    HAbstractNetworkWidget::readSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d->groupName);
    d->serverIp = settings->value("sServerIp", "127.0.0.1").toString();
    d->serverPort = settings->value("iServerPort", 6000).toUInt();
    settings->endGroup();
}

void HTcpClientWidget::writeSettings()
{
    Q_D(HTcpClientWidget);
    HAbstractNetworkWidget::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d->groupName);
    settings->setValue("sServerIp", d->serverIp);
    settings->setValue("iServerPort", d->serverPort);
    settings->endGroup();
}

void HTcpClientWidget::init()
{
    Q_D(HTcpClientWidget);
    d->tcpSocket = new QTcpSocket(this);
    d->timer->setInterval(d->interval);
    d->autoSend ? d->timer->start() : d->timer->stop();
    ui->checkBox_101->setChecked(d->hexSend);
    ui->checkBox_102->setChecked(d->hexReceive);
    ui->checkBox_103->setChecked(d->ascii);
    ui->checkBox_104->setChecked(d->autoSend);
    ui->spinBox_101->setValue(d->interval);
    ui->spinBox_102->setValue(d->serverPort);
    ui->lineEdit_101->setText(d->serverIp);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HTcpClientWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HTcpClientWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HTcpClientWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HTcpClientWidget::setAutoSend);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setServerPort(int)));
    connect(ui->lineEdit_101, &QLineEdit::editingFinished, this, [=]{ setServerIp(ui->lineEdit_101->text()); });
    connect(ui->pushButton_103, &QPushButton::clicked, this, &HTcpClientWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HTcpClientWidget::sendData);
    connect(d->tcpSocket, &QTcpSocket::connected, this, &HTcpClientWidget::handleConnected);
    connect(d->tcpSocket, &QTcpSocket::disconnected, this, &HTcpClientWidget::handleDisconnected);
    connect(d->tcpSocket, &QTcpSocket::readyRead, this, &HTcpClientWidget::handleReadyRead);
    connect(d->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleDisconnected()));
    setWindowTitle(tr("TCP客户端"));
}

HE_CONTROL_END_NAMESPACE
