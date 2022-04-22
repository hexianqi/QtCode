#include "HAbstractPrintTemplate_p.h"
#include "HDataHelper.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCoreHelper.h"
#include <QtCore/QSettings>

HE_BEGIN_NAMESPACE

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
    readSettings();
}

QStringList HAbstractPrintTemplate::dataType()
{
    return d_ptr->types;
}

void HAbstractPrintTemplate::setData(QVariantMap value)
{
    d_ptr->datas = value;
}

bool HAbstractPrintTemplate::checkData(QStringList list)
{
    for (auto type : list)
    {
        if (!HDataHelper::derive(type, d_ptr->datas).isValid())
            return false;
    }
    return true;
}

QString HAbstractPrintTemplate::toString(QString type)
{
    auto value = HDataHelper::derive(type, d_ptr->datas);
    return HCore::toString(type, value);
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

HE_END_NAMESPACE
