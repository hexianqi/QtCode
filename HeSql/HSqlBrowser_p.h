#pragma once

#include "HSqlBrowser.h"

class QToolBar;

HE_BEGIN_NAMESPACE

class HSqlTableView;

class HSqlBrowserPrivate
{
public:
    QToolBar *toolBar = nullptr;
    HSqlTableView *view = nullptr;
    ISqlTableModel *model = nullptr;
    ISqlHandle *handle = nullptr;
    ISqlOutput *output = nullptr;
    QAction *actionRevert;
    QAction *actionFind;
    QAction *actionRemove;
    QAction *actionOutputExcel;
    QAction *actionPrintPdf;
    QAction *actionPrint;
    QAction *actionPrintPreview;
};

HE_END_NAMESPACE
