#pragma once

#include "HTableWidget.h"

class QDESIGNER_WIDGET_EXPORT HTableWidgetPrivate
{
public:
    quint32 actionContain = HTableWidget::ActionAll;
    QAction *actionCopy = nullptr;
    QAction *actionPaste = nullptr;
    QAction *actionExport = nullptr;
    QAction *actionImport = nullptr;
};
