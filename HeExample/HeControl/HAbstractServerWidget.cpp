#include "HAbstractServerWidget_p.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>

HE_CORE_USE_NAMESPACE
HE_CONTROL_BEGIN_NAMESPACE

HAbstractServerWidget::HAbstractServerWidget(QWidget *parent) :
    HAbstractNetworkWidget(*new HAbstractServerWidgetPrivate, parent)
{
}

HAbstractServerWidget::HAbstractServerWidget(HAbstractServerWidgetPrivate &p, QWidget *parent) :
    HAbstractNetworkWidget(p, parent)
{
}

QString HAbstractServerWidget::listenAddress() const
{
    Q_D(const HAbstractServerWidget);
    return d->listenAddress;
}

int HAbstractServerWidget::listenPort() const
{
    Q_D(const HAbstractServerWidget);
    return d->listenPort;
}

void HAbstractServerWidget::setListenAddress(const QString &value)
{
    Q_D(HAbstractServerWidget);
    if (d->listenAddress == value)
        return;
    d->listenAddress = value;
}

void HAbstractServerWidget::setListenPort(int value)
{
    Q_D(HAbstractServerWidget);
    if (d->listenPort == value)
        return;
    d->listenPort = value;
}

void HAbstractServerWidget::handleSentData(const QString &address, int port, const QByteArray &data)
{
    auto text = fromByteArray(data);
    append(0, QString("[%1:%2] %3").arg(address).arg(port).arg(text));
}

void HAbstractServerWidget::handleReceiveData(const QString &address, int port, const QByteArray &data)
{
    auto text = fromByteArray(data);
    append(1, QString("[%1:%2] %3").arg(address).arg(port).arg(text));
}

void HAbstractServerWidget::readSettings()
{
    Q_D(HAbstractServerWidget);
    HAbstractNetworkWidget::readSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup(groupName());
    d->listenAddress = settings->value("ListenAddress", "127.0.0.1").toString();
    d->listenPort = settings->value("ListenPort", 6000).value<int>();
    settings->endGroup();
}

void HAbstractServerWidget::writeSettings()
{
    Q_D(HAbstractServerWidget);
    HAbstractNetworkWidget::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup(groupName());
    settings->setValue("ListenAddress", d->listenAddress);
    settings->setValue("ListenPort", d->listenPort);
    settings->endGroup();
}

HE_CONTROL_END_NAMESPACE
