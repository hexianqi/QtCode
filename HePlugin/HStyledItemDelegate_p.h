#pragma once

#include "HStyledItemDelegate.h"

class QDESIGNER_WIDGET_EXPORT HStyledItemDelegatePrivate
{
public:
    QPoint origin;
    Qt::Orientation orientation = Qt::Horizontal;
    QStringList typeList;
};
