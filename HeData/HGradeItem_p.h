#ifndef HGRADEITEM_P_H
#define HGRADEITEM_P_H

#include "HGradeItem.h"
#include "HAbstractGradeItem_p.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeItemPrivate : public HAbstractGradeItemPrivate
{
public:
    QList<QPointF> levels;
};

HE_DATA_END_NAMESPACE

#endif // HGRADEITEM_P_H
