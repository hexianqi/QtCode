#pragma once

#include "HSpecFitting.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HSpecFittingPrivate : public HAbstractDataItemPrivate
{
public:
    QPolygonF fittingPoints;
};

HE_END_NAMESPACE
