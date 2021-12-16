#pragma once

#include "HSequentialGradeWidget.h"
#include "HAbstractGradeWidget_p.h"

HE_BEGIN_NAMESPACE

class HSequentialGradeWidgetPrivate : public HAbstractGradeWidgetPrivate
{
public:
    QAction *actionExport;
    QAction *actionImport;
};

HE_END_NAMESPACE
