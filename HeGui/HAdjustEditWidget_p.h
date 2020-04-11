#ifndef HADJUSTEDITWIDGET_P_H
#define HADJUSTEDITWIDGET_P_H

#include "HAdjustEditWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustEditWidgetPrivate
{
public:
    HAdjustEditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IAdjust *data = nullptr;
    QAction *actionEdit = nullptr;
    QStringList optionals;
    QStringList selecteds;
    QStringList unselecteds;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITWIDGET_P_H
