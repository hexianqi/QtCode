#pragma once

#include "HIconFontFactory.h"

HE_BEGIN_NAMESPACE

class HIconFontFactoryPrivate
{
public:
    QMap<QString, QString> fontResource;
    QMap<QString, QPoint> fontRange;
};

HE_END_NAMESPACE
