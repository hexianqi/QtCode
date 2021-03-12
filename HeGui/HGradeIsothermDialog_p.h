#pragma once

#include "HGradeIsothermDialog.h"

HE_GUI_BEGIN_NAMESPACE

class HGradeIsothermDialogPrivate
{
public:
    QPointF tc;
    QPointF duv;
    QPoint count;
    QList<QPolygonF> levels;
};

HE_GUI_END_NAMESPACE
