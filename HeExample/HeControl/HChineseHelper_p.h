#pragma once

#include "HChineseHelper.h"
#include <QtCore/QStringList>

HE_BEGIN_NAMESPACE

class HChineseHelperPrivate
{
public:
    QStringList pinYins;
    QString jianPins;
};

HE_END_NAMESPACE
