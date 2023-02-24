#pragma once

#include "HSpecFitting.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HSpecFittingPrivate : public HAbstractDataItemPrivate
{
public:
    QPolygonF points;
};

HE_END_NAMESPACE
