#ifndef HTESTWIDGET_P_H
#define HTESTWIDGET_P_H

#include "HTestWidget.h"
#include "HAbstractTestWidget_p.h"
#include "HeData/HDataGlobal.h"
#include "HeSql/ISqlTableModel.h"

HE_DATA_BEGIN_NAMESPACE
class IExcelStream;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE
class ISqlHandle;
HE_SQL_END_NAMESPACE
HE_SQL_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HTestWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    HTestWidgetPrivate();

public:
    IExcelStream *excelStream;
    ISqlHandle *sqlHandle;

public:
    QStringList displays;
    QStringList tableSelecteds;

public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionExportExcel;
    QAction *actionExportDatabase;
};

HE_GUI_END_NAMESPACE

#endif // HTESTWIDGET_P_H
