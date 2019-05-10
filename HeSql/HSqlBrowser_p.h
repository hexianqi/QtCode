#ifndef HSQLBROWSER_P_H
#define HSQLBROWSER_P_H

#include "HSqlBrowser.h"

HE_SQL_BEGIN_NAMESPACE


class HSqlTableView;

class HSqlBrowserPrivate
{
public:
    HSqlTableView *view = nullptr;
    ISqlRecordHandle *recordHandle = nullptr;
    QAction *actionRevert;
    QAction *actionFind;
    QAction *actionRemove;
    QAction *actionExportExcel;
    QAction *actionExportPdf;
    QAction *actionPrint;
    QAction *actionPrintPreview;
};

HE_SQL_END_NAMESPACE

#endif // HSQLBROWSER_P_H
