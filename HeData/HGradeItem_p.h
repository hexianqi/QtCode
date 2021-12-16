#pragma once

#include "HGradeItem.h"
#include "HAbstractDataItem_p.h"

HE_BEGIN_NAMESPACE

class HGradeItemPrivate : public HAbstractDataItemPrivate
{
public:
    HGradeItemPrivate();

public:
    QList<QPointF> levels;
};

HE_END_NAMESPACE
