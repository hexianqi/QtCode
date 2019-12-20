#ifndef HCONTROLDEMOWIDGET_P_H
#define HCONTROLDEMOWIDGET_P_H

#include "HControlDemoWidget.h"

class QTabWidget;

HE_CONTROL_BEGIN_NAMESPACE

class IIconFontFactory;
class HFlatStyle;

class HControlDemoWidgetPrivate
{
public:
    HFlatStyle *style;
    IIconFontFactory *iconFactory;
    QHash<QString, QTabWidget *> tabWidgets;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLDEMOWIDGET_P_H
