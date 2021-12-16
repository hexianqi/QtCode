#pragma once

#include "HGradeItem2D.h"
#include "HAbstractDataItem_p.h"

HE_BEGIN_NAMESPACE

class HGradeItem2DPrivate : public HAbstractDataItemPrivate
{
public:
    HGradeItem2DPrivate();

public:
    QList<QPolygonF> levels;
};

HE_END_NAMESPACE
