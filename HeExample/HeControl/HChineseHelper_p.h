#pragma once

#include "HChineseHelper.h"
#include <QtCore/QStringList>

HE_CONTROL_BEGIN_NAMESPACE

class HChineseHelperPrivate
{
public:
    QStringList pinYins;
    QString jianPins;
};

HE_CONTROL_END_NAMESPACE
