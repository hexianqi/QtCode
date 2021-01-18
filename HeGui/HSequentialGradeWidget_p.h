#pragma once

#include "HSequentialGradeWidget.h"
#include "HAbstractGradeWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HSequentialGradeWidgetPrivate : public HAbstractGradeWidgetPrivate
{
public:
    QAction *actionExport;
    QAction *actionImport;
};

HE_GUI_END_NAMESPACE
