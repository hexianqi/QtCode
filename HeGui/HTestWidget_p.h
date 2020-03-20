#ifndef HTESTWIDGET_P_H
#define HTESTWIDGET_P_H

#include "HTestWidget.h"
#include "HAbstractTestWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class IExcelStream;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HTestWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    HTestWidgetPrivate();

public:
    IExcelStream *excelStream;

public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionExportExcel;
    QAction *actionClear;
};

HE_GUI_END_NAMESPACE

#endif // HTESTWIDGET_P_H
