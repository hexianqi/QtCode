#pragma once

#include "HSqlBrowser.h"

class QToolBar;

HE_SQL_BEGIN_NAMESPACE

class HSqlTableView;

class HSqlBrowserPrivate
{
public:
    QToolBar *toolBar = nullptr;
    HSqlTableView *view = nullptr;
    ISqlTableModel *model = nullptr;
    ISqlHandle *handle = nullptr;
    ISqlPrint *print = nullptr;
    QAction *actionRevert;
    QAction *actionFind;
    QAction *actionRemove;
    QAction *actionExportExcel;
    QAction *actionExportPdf;
    QAction *actionPrint;
    QAction *actionPrintPreview;
};

HE_SQL_END_NAMESPACE
