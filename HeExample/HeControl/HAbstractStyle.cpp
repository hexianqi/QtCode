#include "HAbstractStyle_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractStyle::HAbstractStyle(QObject *parent) :
    IStyle(parent),
    d_ptr(new HAbstractStylePrivate)
{
}

HAbstractStyle::HAbstractStyle(HAbstractStylePrivate &p, QObject *parent) :
    IStyle(parent),
    d_ptr(&p)
{
}

HAbstractStyle::~HAbstractStyle()
{
}

void HAbstractStyle::initialize(QVariantMap param)
{
    d_ptr->globalParam = param;
}

QVariant HAbstractStyle::data(QString type, QVariantMap param, QVariant defaultValue)
{
    if (param.contains(type))
        return param.value(type);
    return d_ptr->globalParam.value(type, defaultValue);
}

HE_CONTROL_END_NAMESPACE
