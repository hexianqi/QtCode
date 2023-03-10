#pragma once

#include "HAbstractLinearStrategy.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HAbstractLinearStrategyPrivate
{
public:
    QPolygonF points;
    QVariantMap datas;
};

HE_END_NAMESPACE

