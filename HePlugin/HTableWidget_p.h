#ifndef HTABLEWIDGET_P_H
#define HTABLEWIDGET_P_H

#include "HTableWidget.h"

class QDESIGNER_WIDGET_EXPORT HTableWidgetPrivate
{
public:
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionExport;
    QAction *actionImport;
    bool exportImport = true;
};

#endif // HTABLEWIDGET_P_H
