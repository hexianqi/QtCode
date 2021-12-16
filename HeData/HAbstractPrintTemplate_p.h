#pragma once

#include "HAbstractPrintTemplate.h"

HE_BEGIN_NAMESPACE

class HAbstractPrintTemplatePrivate
{
public:
    QString prefix;
    QStringList types;
    QVariantMap datas;
    QVariantMap params;
};

HE_END_NAMESPACE

