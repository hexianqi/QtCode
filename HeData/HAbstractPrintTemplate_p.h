#pragma once

#include "HAbstractPrintTemplate.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractPrintTemplatePrivate
{
public:
    QString prefix;
    QStringList types;
    QVariantMap datas;
    QVariantMap params;
};

HE_DATA_END_NAMESPACE

