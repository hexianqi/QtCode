#pragma once

#include "HSpecFitting.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class IDataFactory;
class ILinearStrategy;

class HSpecFittingPrivate : public HAbstractDataItemPrivate
{
public:
    HSpecFittingPrivate();

public:
    IDataFactory *factory = nullptr;
    ILinearStrategy *strategy = nullptr;
    QPolygonF points;
};

HE_END_NAMESPACE
