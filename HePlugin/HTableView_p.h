#ifndef HTABLEVIEW_P_H
#define HTABLEVIEW_P_H

#include "HTableView.h"

class QDESIGNER_WIDGET_EXPORT HTableViewPrivate
{
public:
    quint32 actionContain = HTableView::ActionAll;
    QHash<quint32, QAction *> actions;
};

#endif // HTABLEVIEW_P_H
