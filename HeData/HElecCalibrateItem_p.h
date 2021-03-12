#pragma once

#include "HElecCalibrateItem.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_DATA_BEGIN_NAMESPACE

class HElecCalibrateItemPrivate : public HAbstractDataItemPrivate
{
public:
    HElecCalibrateItemPrivate();

public:
    QPolygonF relation;
};

HE_DATA_END_NAMESPACE
