#pragma once

#include "HControlDemoWidget.h"

class QTabWidget;

HE_BEGIN_NAMESPACE

class IIconFontFactory;
class HFlatStyle;

class HControlDemoWidgetPrivate
{
public:
    HFlatStyle *style;
    IIconFontFactory *iconFactory;
    QHash<QString, QTabWidget *> tabWidgets;
};

HE_END_NAMESPACE
