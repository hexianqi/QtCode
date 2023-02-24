#pragma once

#include "HSpecPelsWave.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HSpecPelsWavePrivate : public HAbstractDataItemPrivate
{
public:
    QPolygonF points;
};

HE_END_NAMESPACE

