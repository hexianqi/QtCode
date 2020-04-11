#include "HUdpClientWidget_p.h"
#include "ui_HUdpClientWidget.h"
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

HE_CONTROL_BEGIN_NAMESPACE

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
    if (d->socket->writeDatagram(data, QHostAddress(d->serverIP), d->serverPort) == -1)
        append(0, tr("发送失败"));
    else
        append(0, QString("[%1:%2] %3").arg(d->serverIP).arg(d->serverPort).arg(text));
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
        auto ip = datagram.senderAddress().toString().replace("::ffff:", "");
        auto port = datagram.senderPort();
        auto data = datagram.data();
        if (ip.isEmpty() || data.isEmpty())
            continue;
        auto text = fromByteArray(data);
        append(1, QString("[%1:%2] %3").arg(ip).arg(port).arg(text));
    }
}

void HUdpClientWidget::append(int type, QString data)
{
    Q_D(HUdpClientWidget);
    if (d->currentCount >= d->maxCount)
        clearData();

    auto text = data.replace("\r", "").replace("\n", "");
    ui->textEdit->setTextColor(type == 0 ? Qt::darkGreen : Qt::red);
    ui->textEdit->append(tr("[%1][%2]: %3").arg(QTime::currentTime().toString("HH:mm:ss.zzz"), type == 0 ? tr("发送") : tr("接收"), text));
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
    ui->lineEdit_101->setText(d->serverIP);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HUdpClientWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HUdpClientWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HUdpClientWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HUdpClientWidget::setAutoSend);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setServerPort(int)));
    connect(ui->lineEdit_101, &QLineEdit::editingFinished, this, [=]{ setServerIP(ui->lineEdit_101->text()); });
    connect(ui->pushButton_102, &QPushButton::clicked, this, &HUdpClientWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HUdpClientWidget::sendData);
    connect(d->socket, &QUdpSocket::readyRead, this, &HUdpClientWidget::handleReadyRead);
    setWindowTitle(tr("UDP客户端"));
}

HE_CONTROL_END_NAMESPACE
