#ifndef HITEMDELEGATE_P_H
#define HITEMDELEGATE_P_H

#include "HItemDelegate.h"

class QDESIGNER_WIDGET_EXPORT HItemDelegatePrivate
{
public:
    QPoint origin;
    Qt::Orientation orientation;
    QStringList typeList;
};

#endif // HITEMDELEGATE_P_H
