#pragma once

#include "HTableWidget.h"

class QDESIGNER_WIDGET_EXPORT HTableWidgetPrivate
{
public:
    quint32 actionContain = HTableWidget::ActionAll;
    QHash<quint32, QAction *> actions;
};
