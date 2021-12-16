#pragma once

#include "HDataFormatInfo.h"

HE_BEGIN_NAMESPACE

class HDataFormatInfoPrivate : public QSharedData
{
public:
    QString typeName;
    QString unit;
    QColor color = Qt::red;
    int decimals = 0;
    double min = 0.0;
    double max = 65535.0;
    double singleStep = 1.0;
};

HE_END_NAMESPACE
