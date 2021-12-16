#pragma once

#include "HTestWidget.h"
#include "HAbstractTestWidget_p.h"

HE_BEGIN_NAMESPACE

class HTestWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    QAction *actionStart = nullptr;
    QAction *actionStop = nullptr;
    QAction *actionExportExcel = nullptr;
    QAction *actionClear = nullptr;
};

HE_END_NAMESPACE
