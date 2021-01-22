#ifndef HTESTWIDGET_P_H
#define HTESTWIDGET_P_H

#include "HTestWidget.h"
#include "HAbstractTestWidget_p.h"

HE_GUI_BEGIN_NAMESPACE

class HTestWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    QAction *actionStart = nullptr;
    QAction *actionStop = nullptr;
    QAction *actionExportExcel = nullptr;
    QAction *actionClear = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HTESTWIDGET_P_H
