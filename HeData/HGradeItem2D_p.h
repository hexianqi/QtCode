#ifndef HGRADEITEM2D_P_H
#define HGRADEITEM2D_P_H

#include "HGradeItem2D.h"
#include "HAbstractGradeItem_p.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeItem2DPrivate : public HAbstractGradeItemPrivate
{
public:
    QList<QPolygonF> levels;
};

HE_DATA_END_NAMESPACE

#endif // HGRADEITEM2D_P_H
