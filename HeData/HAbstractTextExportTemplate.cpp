#include "HAbstractTextExportTemplate_p.h"

HE_DATA_BEGIN_NAMESPACE

HAbstractTextExportTemplate::HAbstractTextExportTemplate(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractTextExportTemplatePrivate)
{
}

HAbstractTextExportTemplate::HAbstractTextExportTemplate(HAbstractTextExportTemplatePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractTextExportTemplate::~HAbstractTextExportTemplate()
{
}

void HAbstractTextExportTemplate::initialize(QVariantMap /*param*/)
{

}

QStringList HAbstractTextExportTemplate::dataType()
{
    return d_ptr->types;
}

void HAbstractTextExportTemplate::setDataType(QStringList value)
{
    if (d_ptr->types == value)
        return;
    d_ptr->types = value;
}

void HAbstractTextExportTemplate::setData(QVariant value)
{
    d_ptr->data = value;
}

HE_DATA_END_NAMESPACE
