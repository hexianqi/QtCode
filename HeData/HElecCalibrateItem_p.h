#pragma once

#include "HElecCalibrateItem.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HElecCalibrateItemPrivate : public HAbstractDataItemPrivate
{
public:
    HElecCalibrateItemPrivate();

public:
    QPolygonF relation;
};

HE_END_NAMESPACE
