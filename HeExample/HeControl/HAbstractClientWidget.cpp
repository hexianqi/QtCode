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

QString HAbstractClientWidget::serverIP() const
{
    Q_D(const HAbstractClientWidget);
    return d->serverIP;
}

int HAbstractClientWidget::serverPort() const
{
    Q_D(const HAbstractClientWidget);
    return d->serverPort;
}

void HAbstractClientWidget::setServerIP(const QString &value)
{
    Q_D(HAbstractClientWidget);
    if (d->serverIP == value)
        return;
    d->serverIP = value;
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
    d->serverIP = settings->value("sServerIP", "127.0.0.1").toString();
    d->serverPort = settings->value("iServerPort", 6000).value<int>();
    settings->endGroup();
}

void HAbstractClientWidget::writeSettings()
{
    Q_D(HAbstractClientWidget);
    HAbstractNetworkWidget::writeSettings();
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup(groupName());
    settings->setValue("sServerIP", d->serverIP);
    settings->setValue("iServerPort", d->serverPort);
    settings->endGroup();
}

HE_CONTROL_END_NAMESPACE
