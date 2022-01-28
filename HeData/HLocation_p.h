#pragma once

#include "HLocation.h"
#include "HAbstractDataItem_p.h"
#include <QtGui/QPolygon>

HE_BEGIN_NAMESPACE

class HLocationPrivate : public HAbstractDataItemPrivate
{
public:
    HLocationPrivate();

public:
    QVector<QVector<int>> layout;
    QPolygon polygon;
};

HE_END_NAMESPACE

