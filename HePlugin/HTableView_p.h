#ifndef HTABLEVIEW_P_H
#define HTABLEVIEW_P_H

#include "HTableView.h"

class QDESIGNER_WIDGET_EXPORT HTableViewPrivate
{
public:
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionExport;
    QAction *actionImport;
    bool exportImport = true;
};

#endif // HTABLEVIEW_P_H
