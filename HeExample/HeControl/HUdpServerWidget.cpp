#include "HUdpServerWidget_p.h"
#include "ui_HUdpServerWidget.h"
#include "HNetworkHelper.h"
#include "HUdpServer.h"
#include <QtCore/QDateTime>
#include <QtCore/QTimer>

HE_BEGIN_NAMESPACE

HUdpServerWidget::HUdpServerWidget(QWidget *parent) :
    HAbstractServerWidget(*new HUdpServerWidgetPrivate, parent),
    ui(new Ui::HUdpServerWidget)
{
    ui->setupUi(this);
    readSettings();
    init();
}

HUdpServerWidget::~HUdpServerWidget()
{
    Q_D(HUdpServerWidget);
    d->server->stop();
    writeSettings();
    delete ui;
}

void HUdpServerWidget::sendData()
{
    Q_D(HUdpServerWidget);
    if (!d->server->isRunning())
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
            d->server->sendData(list.at(0), list.at(1).toUShort(), data);
        }
    }
    else
        d->server->sendData(data);
}

void HUdpServerWidget::clearData()
{
    HAbstractServerWidget::clearData();
    ui->textEdit->clear();
}

void HUdpServerWidget::on_pushButton_101_clicked()
{
    Q_D(HUdpServerWidget);
    if (d->server->isRunning())
    {
        d->server->stop();
        ui->pushButton_101->setText(tr("监听"));
        append(3, tr("关闭监听"));
    }
    else
    {
        d->server->setListenAddress(d->listenAddress);
        d->server->setListenPort(d->listenPort);
        if (d->server->start())
        {
            ui->pushButton_101->setText(tr("关闭"));
            append(3, tr("开始监听"));
        }
        else
            append(2, tr("监听失败：%1").arg(d->server->errorString()));
    }
}

void HUdpServerWidget::on_pushButton_102_clicked()
{
    if (saveData(ui->textEdit->toPlainText()))
        clearData();
}

void HUdpServerWidget::handleConnected(const QString &address, int port)
{
    auto text = QString("%1:%2").arg(address).arg(port);
    ui->listWidget_101->addItem(text);
    ui->label_104->setText(tr("共 %1 个客户端").arg(ui->listWidget_101->count()));
    append(1, tr("[%1:%2]客户端上线").arg(address).arg(port));
}

void HUdpServerWidget::handleDisconnected(const QString &address, int port)
{
    int row = -1;
    QString text = QString("%1:%2").arg(address).arg(port);
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
        ui->label_104->setText(tr("共 %1 个客户端").arg(ui->listWidget_101->count()));
        append(1, tr("[%1:%2]客户端下线").arg(address).arg(port));
    }
}

void HUdpServerWidget::append(int type, QString data)
{
    Q_D(HUdpServerWidget);
    if (d->currentCount >= d->maxCount)
        clearData();

    QString strType;
    if (type == 0)
    {
        strType = tr("发送");
        ui->textEdit->setTextColor(QColor("#22A3A9"));
    }
    else if (type == 1)
    {
        strType = tr("接收");
        ui->textEdit->setTextColor(QColor("#753775"));
    }
    else if (type == 2)
    {
        strType = tr("错误");
        ui->textEdit->setTextColor(Qt::red);
    }
    else
    {
        strType = tr("提示");
        ui->textEdit->setTextColor(Qt::black);
    }
    auto text = data.replace("\r", "").replace("\n", "");
    ui->textEdit->append(tr("[%1][%2]: %3").arg(QTime::currentTime().toString("HH:mm:ss.zzz"), strType, text));
    d->currentCount++;
}

QString HUdpServerWidget::groupName()
{
    return "UdpServer";
}

void HUdpServerWidget::init()
{
    Q_D(HUdpServerWidget);
    d->server = new HUdpServer(this);
    d->timer->setInterval(d->interval);
    d->autoSend ? d->timer->start() : d->timer->stop();
    ui->checkBox_101->setChecked(d->hexSend);
    ui->checkBox_102->setChecked(d->hexReceive);
    ui->checkBox_103->setChecked(d->ascii);
    ui->checkBox_104->setChecked(d->autoSend);
    ui->comboBox_101->addItems(HNetworkHelper::localIP());
    ui->comboBox_101->addItem("0.0.0.0");
    ui->comboBox_101->setCurrentText(d->listenAddress);
    ui->spinBox_101->setValue(d->interval);
    ui->spinBox_102->setValue(d->listenPort);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HUdpServerWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HUdpServerWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HUdpServerWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HUdpServerWidget::setAutoSend);
    connect(ui->comboBox_101, &QComboBox::currentTextChanged, this, &HUdpServerWidget::setListenAddress);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setListenPort(int)));
    connect(ui->pushButton_103, &QPushButton::clicked, this, &HUdpServerWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HUdpServerWidget::sendData);
    connect(d->server, &HUdpServer::connected, this, &HUdpServerWidget::handleConnected);
    connect(d->server, &HUdpServer::disconnected, this, &HUdpServerWidget::handleDisconnected);
    connect(d->server, &HUdpServer::error, this, &HUdpServerWidget::handleError);
    connect(d->server, &HUdpServer::sentData, this, &HUdpServerWidget::handleSentData);
    connect(d->server, &HUdpServer::receiveData, this, &HUdpServerWidget::handleReceiveData);
    setWindowTitle(tr("UDP服务端"));
}

HE_END_NAMESPACE
