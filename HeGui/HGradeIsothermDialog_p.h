#ifndef HGRADEISOTHERMDIALOG_P_H
#define HGRADEISOTHERMDIALOG_P_H

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

#endif // HGRADEISOTHERMDIALOG_P_H
