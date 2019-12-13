#ifndef HCONTROLDEMOWIDGET_P_H
#define HCONTROLDEMOWIDGET_P_H

#include "HControlDemoWidget.h"

class QTabWidget;

HE_CONTROL_BEGIN_NAMESPACE

class IIconFontFactory;

class HControlDemoWidgetPrivate
{
public:
    IIconFontFactory *iconFacuory;
    QHash<QString, QTabWidget *> tabWidgets;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLDEMOWIDGET_P_H
