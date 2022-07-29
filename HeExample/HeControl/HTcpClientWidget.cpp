#include "HTcpClientWidget_p.h"
#include "ui_HTcpClientWidget.h"
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

HE_BEGIN_NAMESPACE

HTcpClientWidget::HTcpClientWidget(QWidget *parent) :
    HAbstractClientWidget(*new HTcpClientWidgetPrivate, parent),
    ui(new Ui::HTcpClientWidget)
{
    ui->setupUi(this);
    readSettings();
    init();
}

HTcpClientWidget::~HTcpClientWidget()
{
    Q_D(HTcpClientWidget);
    d->socket->abort();
    writeSettings();
    delete ui;
}

void HTcpClientWidget::sendData()
{
    Q_D(HTcpClientWidget);
    if (!d->connected)
        return;

    auto text = ui->lineEdit_201->text();
    if (text.length() <= 0)
        return;

    auto data = toByteArray(text);
    if (d->socket->write(data) == -1)
        append(2, tr("发送失败"));
    else
        append(0, text);
}

void HTcpClientWidget::clearData()
{
    HAbstractClientWidget::clearData();
    ui->textEdit->clear();
}

void HTcpClientWidget::on_pushButton_101_clicked()
{
    Q_D(HTcpClientWidget);
    if (!d->connected)
        d->socket->connectToHost(d->serverAddress, d->serverPort);
    else
        d->socket->abort();
}

void HTcpClientWidget::on_pushButton_102_clicked()
{
    if (saveData(ui->textEdit->toPlainText()))
        clearData();
}

void HTcpClientWidget::handleConnected()
{
    Q_D(HTcpClientWidget);
    d->connected = true;
    ui->pushButton_101->setText(tr("断开"));
    append(3, tr("服务器连接"));
}

void HTcpClientWidget::handleDisconnected()
{
    Q_D(HTcpClientWidget);
    d->connected = false;
    ui->pushButton_101->setText(tr("连接"));
    append(3, tr("服务器断开"));
}

void HTcpClientWidget::handleReadyRead()
{
    Q_D(HTcpClientWidget);
    auto data = d->socket->readAll();
    if (data.length() <= 0)
        return;
    append(1, fromByteArray(data));
}

void HTcpClientWidget::handleError()
{
    Q_D(HTcpClientWidget);
    append(2, d->socket->errorString());
}

void HTcpClientWidget::append(int type, QString data)
{
    Q_D(HTcpClientWidget);
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

QString HTcpClientWidget::groupName()
{
    return "TcpClient";
}

void HTcpClientWidget::init()
{
    Q_D(HTcpClientWidget);
    d->socket = new QTcpSocket(this);
    d->timer->setInterval(d->interval);
    d->autoSend ? d->timer->start() : d->timer->stop();
    ui->checkBox_101->setChecked(d->hexSend);
    ui->checkBox_102->setChecked(d->hexReceive);
    ui->checkBox_103->setChecked(d->ascii);
    ui->checkBox_104->setChecked(d->autoSend);
    ui->spinBox_101->setValue(d->interval);
    ui->spinBox_102->setValue(d->serverPort);
    ui->lineEdit_101->setText(d->serverAddress);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HTcpClientWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HTcpClientWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HTcpClientWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HTcpClientWidget::setAutoSend);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setServerPort(int)));
    connect(ui->lineEdit_101, &QLineEdit::editingFinished, this, [=]{ setServerAddress(ui->lineEdit_101->text()); });
    connect(ui->pushButton_103, &QPushButton::clicked, this, &HTcpClientWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HTcpClientWidget::sendData);
    connect(d->socket, SIGNAL(connected()), this, SLOT(handleConnected()));
    connect(d->socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(d->socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(d->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
    setWindowTitle(tr("TCP客户端"));
}

HE_END_NAMESPACE
