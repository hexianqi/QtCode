#include "HAbstractPrintTemplate_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCoreHelper.h"
#include <QtCore/QSettings>

HE_DATA_BEGIN_NAMESPACE

HAbstractPrintTemplate::HAbstractPrintTemplate(QObject *parent) :
    IPrintTemplate(parent),
    d_ptr(new HAbstractPrintTemplatePrivate)
{
}

HAbstractPrintTemplate::HAbstractPrintTemplate(HAbstractPrintTemplatePrivate &p, QObject *parent) :
    IPrintTemplate(parent),
    d_ptr(&p)
{
}

HAbstractPrintTemplate::~HAbstractPrintTemplate()
{
    writeSettings();
}

void HAbstractPrintTemplate::initialize(QVariantMap /*param*/)
{
}

QStringList HAbstractPrintTemplate::dataTypes()
{
    return d_ptr->types;
}

void HAbstractPrintTemplate::setData(QVariantMap value)
{
    d_ptr->datas = value;
}

QString HAbstractPrintTemplate::toString(QString type)
{
    return HCore::toString(type, d_ptr->datas.value(type));
}

QString HAbstractPrintTemplate::toStringWhole(QString type)
{
    return HCore::toCaption(type) + ": " + toString(type) + HCore::toUnit(type);
}

void HAbstractPrintTemplate::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    HCoreHelper::readSettings(fileName, d_ptr->prefix, d_ptr->params);
}

void HAbstractPrintTemplate::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    HCoreHelper::writeSettings(fileName, d_ptr->prefix, d_ptr->params);
}

HE_DATA_END_NAMESPACE
