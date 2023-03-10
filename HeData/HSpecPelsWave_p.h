#pragma once

#include "HSpecPelsWave.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class IDataFactory;
class ILinearStrategy;

class HSpecPelsWavePrivate : public HAbstractDataItemPrivate
{
public:
    HSpecPelsWavePrivate();

public:
    IDataFactory *factory = nullptr;
    ILinearStrategy *strategy = nullptr;
    QPolygonF points;
};

HE_END_NAMESPACE

