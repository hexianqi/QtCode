#include "HAbstractNetworkWidget_p.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QTimer>

HE_CORE_USE_NAMESPACE
HE_CONTROL_BEGIN_NAMESPACE

HAbstractNetworkWidget::HAbstractNetworkWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAbstractNetworkWidgetPrivate)
{
    init();
}

HAbstractNetworkWidget::HAbstractNetworkWidget(HAbstractNetworkWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HAbstractNetworkWidget::~HAbstractNetworkWidget()
{
}

bool HAbstractNetworkWidget::isHexSend() const
{
    return d_ptr->hexSend;
}

bool HAbstractNetworkWidget::isHexReceive() const
{
    return d_ptr->hexReceive;
}

bool HAbstractNetworkWidget::isAscii() const
{
    return d_ptr->ascii;
}

bool HAbstractNetworkWidget::isAutoSend() const
{
    return d_ptr->autoSend;
}

int HAbstractNetworkWidget::interval() const
{
    return d_ptr->interval;
}

void HAbstractNetworkWidget::setHexSend(bool b)
{
    if (d_ptr->hexSend == b)
        return;
    d_ptr->hexSend = b;
}

void HAbstractNetworkWidget::setHexReceive(bool b)
{
    if (d_ptr->hexReceive == b)
        return;
    d_ptr->hexReceive = b;
}

void HAbstractNetworkWidget::setAscii(bool b)
{
    if (d_ptr->ascii == b)
        return;
    d_ptr->ascii = b;
}

void HAbstractNetworkWidget::setAutoSend(bool b)
{
    if (d_ptr->autoSend == b)
        return;
    d_ptr->autoSend = b;
    b ? d_ptr->timer->start() : d_ptr->timer->stop();
}

void HAbstractNetworkWidget::setInterval(int value)
{
    if (d_ptr->interval == value && value == d_ptr->timer->interval())
        return;
    d_ptr->interval = value;
    d_ptr->timer->setInterval(value);
}

void HAbstractNetworkWidget::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d_ptr->groupName);
    d_ptr->hexSend = settings->value("bHexSend", false).toBool();
    d_ptr->hexReceive = settings->value("bHexReceive", false).toBool();
    d_ptr->ascii = settings->value("bAscii", false).toBool();
    d_ptr->autoSend = settings->value("bAutoSend", false).toBool();
    d_ptr->interval = settings->value("iInterval", 1000).toInt();
    settings->endGroup();
}

void HAbstractNetworkWidget::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(d_ptr->groupName);
    settings->setValue("bHexSend", d_ptr->hexSend);
    settings->setValue("bHexReceive", d_ptr->hexReceive);
    settings->setValue("bAscii", d_ptr->ascii);
    settings->setValue("bAutoSend", d_ptr->autoSend);
    settings->setValue("iInterval", d_ptr->interval);
    settings->endGroup();
}

bool HAbstractNetworkWidget::saveData(QString value)
{
    if (value.length() <= 0)
        return false;

    auto fileName = QString("%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;
    file.write(value.toUtf8());
    file.close();
    return true;
}

QString HAbstractNetworkWidget::fromByteArray(QByteArray value)
{
    if (isHexReceive())
        return QString::fromLatin1(value.toHex(' '));
    if (isAscii())
        return QString::fromLatin1(value);
    return QString::fromUtf8(value);
}

QByteArray HAbstractNetworkWidget::toByteArray(QString value)
{
    QByteArray data;
    if (isHexSend())
        return QByteArray::fromHex(value.remove(' ').toLatin1());
    if (isAscii())
        return value.toLatin1();
    return value.toUtf8();
}

void HAbstractNetworkWidget::init()
{
    d_ptr->timer = new QTimer(this);
    connect(d_ptr->timer, &QTimer::timeout, this, &HAbstractNetworkWidget::sendData);
}

HE_CONTROL_END_NAMESPACE
