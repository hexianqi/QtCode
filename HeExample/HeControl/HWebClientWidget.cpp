#include "HWebClientWidget_p.h"
#include "ui_HWebClientWidget.h"
#include <QtCore/QTimer>
#include <QtWebSockets/QWebSocket>

HE_BEGIN_NAMESPACE

HWebClientWidgetPrivate::HWebClientWidgetPrivate()
{
    serverAddress = "ws://127.0.0.1";
}

HWebClientWidget::HWebClientWidget(QWidget *parent) :
    HAbstractClientWidget(*new HWebClientWidgetPrivate, parent),
    ui(new Ui::HWebClientWidget)
{
    ui->setupUi(this);
    readSettings();
    init();
}

HWebClientWidget::~HWebClientWidget()
{
    Q_D(HWebClientWidget);
    d->socket->abort();
    writeSettings();
    delete ui;
}

void HWebClientWidget::sendData()
{
    Q_D(HWebClientWidget);
    if (!d->connected)
        return;

    auto text = ui->lineEdit_201->text();
    if (text.length() <= 0)
        return;

    if (isAscii())
    {
        if (d->socket->sendTextMessage(text) < 0)
            append(2, tr("发送失败"));
        else
            append(0, text);
    }
    else
    {
        auto data = toByteArray(text);
        if (d->socket->sendBinaryMessage(data) < 0)
            append(2, tr("发送失败"));
        else
            append(0, text);
    }
}

void HWebClientWidget::clearData()
{
    HAbstractClientWidget::clearData();
    ui->textEdit->clear();
}

void HWebClientWidget::on_pushButton_101_clicked()
{
    Q_D(HWebClientWidget);
    if (!d->connected)
    {
        auto url = QString("%1:%2").arg(d->serverAddress).arg(d->serverPort);
        d->socket->abort();
        d->socket->open(url);
    }
    else
        d->socket->abort();
}

void HWebClientWidget::on_pushButton_102_clicked()
{
    if (saveData(ui->textEdit->toPlainText()))
        clearData();
}

void HWebClientWidget::handleConnected()
{
    Q_D(HWebClientWidget);
    d->connected = true;
    ui->pushButton_101->setText(tr("断开"));
    append(3, tr("服务器连接"));
}

void HWebClientWidget::handleDisconnected()
{
    Q_D(HWebClientWidget);
    d->connected = false;
    ui->pushButton_101->setText(tr("连接"));
    append(3, tr("服务器断开"));
}

void HWebClientWidget::handleError()
{
    Q_D(HWebClientWidget);
    append(2, d->socket->errorString());
}

void HWebClientWidget::handleTextMessageReceived(QString data)
{
    append(1, data);
}

void HWebClientWidget::handleBinaryMessageReceived(QByteArray data)
{
    append(1, fromByteArray(data));
}

void HWebClientWidget::append(int type, QString data)
{
    Q_D(HWebClientWidget);
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

QString HWebClientWidget::groupName()
{
    return "WebClient";
}

void HWebClientWidget::init()
{
    Q_D(HWebClientWidget);
    d->socket = new QWebSocket("WebSocket", QWebSocketProtocol::VersionLatest, this);
    d->timer->setInterval(d->interval);
    d->autoSend ? d->timer->start() : d->timer->stop();
    ui->checkBox_101->setChecked(d->hexSend);
    ui->checkBox_102->setChecked(d->hexReceive);
    ui->checkBox_103->setChecked(d->ascii);
    ui->checkBox_104->setChecked(d->autoSend);
    ui->spinBox_101->setValue(d->interval);
    ui->spinBox_102->setValue(d->serverPort);
    ui->lineEdit_101->setText(d->serverAddress);
    connect(ui->checkBox_101, &QCheckBox::clicked, this, &HWebClientWidget::setHexSend);
    connect(ui->checkBox_102, &QCheckBox::clicked, this, &HWebClientWidget::setHexReceive);
    connect(ui->checkBox_103, &QCheckBox::clicked, this, &HWebClientWidget::setAscii);
    connect(ui->checkBox_104, &QCheckBox::clicked, this, &HWebClientWidget::setAutoSend);
    connect(ui->spinBox_101, SIGNAL(valueChanged(int)), this, SLOT(setInterval(int)));
    connect(ui->spinBox_102, SIGNAL(valueChanged(int)), this, SLOT(setServerPort(int)));
    connect(ui->lineEdit_101, &QLineEdit::editingFinished, this, [=]{ setServerAddress(ui->lineEdit_101->text()); });
    connect(ui->pushButton_103, &QPushButton::clicked, this, &HWebClientWidget::clearData);
    connect(ui->pushButton_201, &QPushButton::clicked, this, &HWebClientWidget::sendData);
    connect(d->socket, SIGNAL(connected()), this, SLOT(handleConnected()));
    connect(d->socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(d->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
    connect(d->socket, SIGNAL(textMessageReceived(QString)), this, SLOT(handleTextMessageReceived(QString)));
    connect(d->socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(handleBinaryMessageReceived(QByteArray)));
    setWindowTitle(tr("WEB客户端"));
}

HE_END_NAMESPACE
