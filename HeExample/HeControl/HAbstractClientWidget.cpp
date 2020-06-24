#include "HAbstractClientWidget_p.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QSettings>

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

HAbstractClientWidget::HAbstractClientWidget(QWidget *parent) :
    HAbstractNetworkWidget(*new HAbstractClientWidgetPrivate, parent)
{
}

HAbstractClientWidget::HAbstractClientWidget(HAbstractClientWidgetPrivate &p, QWidget *parent) :
    HAbstractNetworkWidget(p, parent)
{
}

QString HAbstractClientWidget::serverAddress() const
{
    Q_D(const HAbstractClientWidget);
    return d->serverAddress;
}

int HAbstractClientWidget::serverPort() const
{
    Q_D(const HAbstractClientWidget);
    return d->serverPort;
}

void HAbstractClientWidget::setServerAddress(const QString &value)
{
    Q_D(HAbstractClientWidget);
    if (d->serverAddress == value)
        return;
    d->serverAddress = value;
}

void HAbstractClientWidget::setServerPort(int value)
{
    Q_D(HAbstractClientWidget);
    if (d->serverPort == value)
        return;
    d->serverPort = value;
}

void HAbstractClientWidget::readSettings()
{
    Q_D(HAbstractClientWidget);
    HAbstractNetworkWidget::readSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(groupName());
    d->serverAddress = settings->value("ServerAddress", "127.0.0.1").toString();
    d->serverPort = settings->value("ServerPort", 6000).value<int>();
    settings->endGroup();
}

void HAbstractClientWidget::writeSettings()
{
    Q_D(HAbstractClientWidget);
    HAbstractNetworkWidget::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(groupName());
    settings->setValue("ServerAddress", d->serverAddress);
    settings->setValue("ServerPort", d->serverPort);
    settings->endGroup();
}

HE_CONTROL_END_NAMESPACE
