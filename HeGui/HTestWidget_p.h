#ifndef HTESTWIDGET_P_H
#define HTESTWIDGET_P_H

#include "HTestWidget.h"
#include "HAbstractTestWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITextStream;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HTestWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    HTestWidgetPrivate();

public:
    ITextStream *stream = nullptr;

public:
    QAction *actionStart = nullptr;
    QAction *actionStop = nullptr;
    QAction *actionExportExcel = nullptr;
    QAction *actionClear = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HTESTWIDGET_P_H
