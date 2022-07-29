#include "HUdpClientWidget_p.h"
#include "ui_HUdpClientWidget.h"
#include "HNetworkHelper.h"
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

HE_BEGIN_NAMESPACE

HUdpClientWidget::HUdpClientWidget(QWidget *parent) :
    HAbstractClientWidget(*new HUdpClientWidgetPrivate, parent),
    ui(new Ui::HUdpClientWidget)
{
    ui->setupUi(this);
    readSettings();
    init();
}

HUdpClientWidget::~HUdpClientWidget()
{
    Q_D(HUdpClientWidget);
    d->socket->abort();
    writeSettings();
    delete ui;
}

void HUdpClientWidget::sendData()
{
    Q_D(HUdpClientWidget);
    auto text = ui->lineEdit_201->text();
    if (text.length() <= 0)
        return;

    auto data = toByteArray(text);
    if (d->socket->writeDatagram(data, QHostAddress(d->serverAddress), d->serverPort) == -1)
        append(2, tr("发送失败"));
    else
        append(0, QString("[%1:%2] %3").arg(d->serverAddress).arg(d->serverPort).arg(text));
}

void HUdpClientWidget::clearData()
{
    HAbstractClientWidget::clearData();
    ui->textEdit->clear();
}

void HUdpClientWidget::on_pushButton_101_clicked()
{
    if (saveData(ui->textEdit->toPlainText()))
        clearData();
}

void HUdpClientWidget::handleReadyRead()
{
    Q_D(HUdpClientWidget);
    while (d->socket->hasPendingDatagrams())
    {
        auto datagram = d->socket->receiveDatagram();
        auto address = HNetworkHelper::toString(datagram.senderAddress());
        auto port = datagram.senderPort();
        auto data = datagram.data();
        if (address.isEmpty() || data.isEmpty())
            continue;
        auto text = fromByteArray(data);
        append(1, QString("[%1:%2] %3").arg(address).arg(port).arg(text));
    }
}

void HUdpClientWidget::handleError()
{
    Q_D(HUdpClientWidget);
    append(2, d->socket->errorString());
}

void HUdpClientWidget::append(int type, QString data)
{
    Q_D(HUdpClientWidget);
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
    ui->textEdit->append(tr("[%1][%2]%3").arg(QTime::currentTime().toString("HH:mm:ss.zzz"), strType, text));
    d->currentCount++;
}

QString HUdpClientWidget::groupName()
{
    return "UdpClient";
}

void HUdpClientWidget::init()
{
    Q_D(HUdpClientWidget);
    d->socket = new QUdpSocket(this);
    d->timer->setInterval(d->interval);
    d->autoSend ? d->timer->start() : d->timer->stop();
    ui->checkBox_101->setChecked(d->hexSend);
    ui->checkBox_102->setChecked(d->hexReceive);
    ui->checkBox_103->setChecked(d->ascii);
    ui->checkBox_104->setChecked(d->autoSend);
    ui->spinBox_101->setValue(d->interval);
    ui->spinBox_102->setValue(d->serverPort);
    ui->lineEdit_101->setText(d->serverAddress);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HUdpClientWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HUdpClientWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HUdpClientWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HUdpClientWidget::setAutoSend);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setServerPort(int)));
    connect(ui->lineEdit_101, &QLineEdit::editingFinished, this, [=]{ setServerAddress(ui->lineEdit_101->text()); });
    connect(ui->pushButton_102, &QPushButton::clicked, this, &HUdpClientWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HUdpClientWidget::sendData);
    connect(d->socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(d->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
    setWindowTitle(tr("UDP客户端"));
}

HE_END_NAMESPACE
