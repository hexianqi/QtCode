#ifndef HSTYLEDITEMDELEGATE_P_H
#define HSTYLEDITEMDELEGATE_P_H

#include "HStyledItemDelegate.h"

class QDESIGNER_WIDGET_EXPORT HStyledItemDelegatePrivate
{
public:
    QPoint origin;
    Qt::Orientation orientation = Qt::Horizontal;
    QStringList typeList;
};

#endif // HSTYLEDITEMDELEGATE_P_H
