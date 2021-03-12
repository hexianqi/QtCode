#pragma once

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
