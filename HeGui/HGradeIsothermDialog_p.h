#pragma once

#include "HGradeIsothermDialog.h"

HE_BEGIN_NAMESPACE

class HGradeIsothermDialogPrivate
{
public:
    QPointF tc;
    QPointF duv;
    QPoint count;
    QList<QPolygonF> levels;
};

HE_END_NAMESPACE
