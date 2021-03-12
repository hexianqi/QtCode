#pragma once

#include "HSpecPelsWave.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_DATA_BEGIN_NAMESPACE

class HSpecPelsWavePrivate : public HAbstractDataItemPrivate
{
public:
    QPolygonF pelsWave;
};

HE_DATA_END_NAMESPACE
