#include "HTcpServerWidget_p.h"
#include "ui_HTcpServerWidget.h"
#include "HTcpServer.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtCore/QDateTime>

HE_CORE_USE_NAMESPACE
HE_CONTROL_BEGIN_NAMESPACE

HTcpServerWidgetPrivate::HTcpServerWidgetPrivate()
{
    groupName = "TcpServer";
}

HTcpServerWidget::HTcpServerWidget(QWidget *parent) :
    HAbstractNetworkWidget(*new HTcpServerWidgetPrivate, parent),
    ui(new Ui::HTcpServerWidget)
{
    ui->setupUi(this);
    readSettings();
    init();
}

HTcpServerWidget::~HTcpServerWidget()
{
    writeSettings();
    delete ui;
}

void HTcpServerWidget::setListenPort(int value)
{
    Q_D(HTcpServerWidget);
    if (d->listenPort == value)
        return;
    d->listenPort = value;
}

void HTcpServerWidget::clearData()
{
    Q_D(HTcpServerWidget);
    ui->textEdit->clear();
    d->currentCount = 0;
}

void HTcpServerWidget::sendData()
{
    Q_D(HTcpServerWidget);
    if (!d->connect)
        return;

    auto text = ui->lineEdit_201->text();
    if (text.length() <= 0)
        return;

    auto data = toByteArray(text);
    if (!ui->checkBox_105->isChecked())
    {
        auto row = ui->listWidget_101->currentRow();
        if (row >= 0)
        {
            auto list = ui->listWidget_101->item(row)->text().split(":");
            d->tcpServer->sendData(list.at(0), list.at(1).toInt(), data);
            append(0, QString("[%1:%2] %3").arg(list.at(0)).arg(list.at(1)).arg(text));
        }
    }
    else
    {
        d->tcpServer->sendData(data);
        append(0, QString("[All] %1").arg(text));
    }
}

void HTcpServerWidget::on_pushButton_101_clicked()
{
    Q_D(HTcpServerWidget);
    if (ui->pushButton_101->text() == "监听")
    {
        d->tcpServer->setListenPort(d->listenPort);
        d->connect = d->tcpServer->start();
        if (d->connect)
        {
            append(0, tr("监听成功"));
            ui->pushButton_101->setText("关闭");
        }
    }
    else
    {
        d->connect = false;
        d->tcpServer->stop();
        append(0, tr("监听关闭"));
        ui->pushButton_101->setText("监听");
    }
}

void HTcpServerWidget::on_pushButton_102_clicked()
{
    if (saveData(ui->textEdit->toPlainText()))
        clearData();
}

void HTcpServerWidget::handleReceiveData(QString ip, int port, QByteArray data)
{
    auto text = fromByteArray(data);
    append(1, QString("[%1:%2] %3").arg(ip).arg(port).arg(text));
}

void HTcpServerWidget::handleClientConnected(QString ip, int port)
{
    auto text = QString("%1:%2").arg(ip).arg(port);
    ui->listWidget_101->addItem(text);
    ui->label_102->setText(tr("已连接客户端共 %1 个").arg(ui->listWidget_101->count()));
    append(1, tr("[%1:%2] 客户端上线").arg(ip).arg(port));
}

void HTcpServerWidget::handleClientDisconnected(QString ip, int port)
{
    int row = -1;
    QString text = QString("%1:%2").arg(ip).arg(port);
    for (int i = 0; i < ui->listWidget_101->count(); i++)
    {
        if (ui->listWidget_101->item(i)->text() == text)
        {
            row = i;
            break;
        }
    }
    if (row != -1)
    {
        ui->listWidget_101->takeItem(row);
        ui->label_102->setText(tr("已连接客户端共 %1 个").arg(ui->listWidget_101->count()));
        append(1, tr("[%1:%2] 客户端下线").arg(ip).arg(port));
    }
}

void HTcpServerWidget::append(int type, QString data)
{
    Q_D(HTcpServerWidget);
    if (d->currentCount >= d->maxCount)
        clearData();

    auto text = data.replace("\r", "").replace("\n", "");
    QString strType;
    if (type == 0)
    {
        strType = "发送";
        ui->textEdit->setTextColor(Qt::darkGreen);
    }
    else
    {
        strType = "接收";
        ui->textEdit->setTextColor(Qt::red);
    }
    ui->textEdit->append(tr("[%1][%2]: %3").arg(QTime::currentTime().toString("HH:mm:ss.zzz")).arg(strType).arg(text));
    d->currentCount++;
}

void HTcpServerWidget::readSettings()
{
    Q_D(HTcpServerWidget);
    HAbstractNetworkWidget::readSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d->groupName);
    d->listenPort = settings->value("iListenPort", 6000).toInt();
    settings->endGroup();
}

void HTcpServerWidget::writeSettings()
{
    Q_D(HTcpServerWidget);
    HAbstractNetworkWidget::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d->groupName);
    settings->setValue("iListenPort", d->listenPort);
    settings->endGroup();
}

void HTcpServerWidget::init()
{
    Q_D(HTcpServerWidget);
    d->tcpServer = new HTcpServer(this);
    d->timer->setInterval(d->interval);
    d->autoSend ? d->timer->start() : d->timer->stop();
    ui->checkBox_101->setChecked(d->hexSend);
    ui->checkBox_102->setChecked(d->hexReceive);
    ui->checkBox_103->setChecked(d->ascii);
    ui->checkBox_104->setChecked(d->autoSend);
    ui->spinBox_101->setValue(d->interval);
    ui->spinBox_102->setValue(d->listenPort);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HTcpServerWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HTcpServerWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HTcpServerWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HTcpServerWidget::setAutoSend);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setListenPort(int)));
    connect(ui->pushButton_103, &QPushButton::clicked, this, &HTcpServerWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HTcpServerWidget::sendData);
    connect(d->tcpServer, &HTcpServer::receiveData, this, &HTcpServerWidget::handleReceiveData);
    connect(d->tcpServer, &HTcpServer::clientConnected, this, &HTcpServerWidget::handleClientConnected);
    connect(d->tcpServer, &HTcpServer::clientDisconnected, this, &HTcpServerWidget::handleClientDisconnected);
    setWindowTitle(tr("TCP服务端"));
}

HE_CONTROL_END_NAMESPACE
