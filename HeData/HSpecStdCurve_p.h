#pragma once

#include "HSpecStdCurve.h"
#include "HAbstractDataItem_p.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HSpecStdCurvePrivate : public HAbstractDataItemPrivate
{
public:
    QVector<double> curve;
};

HE_END_NAMESPACE
