#include "HAbstractPrintTemplate_p.h"
#include "HeCore/HCore.h"

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
}

void HAbstractPrintTemplate::initialize(QVariantMap /*param*/)
{
}

void HAbstractPrintTemplate::setData(QVariantMap value)
{
    d_ptr->datas = value;
}

QString HAbstractPrintTemplate::toString(QString type)
{
    return HCore::toString(type, d_ptr->datas.value(type));
}

HE_DATA_END_NAMESPACE
