#pragma once

#include "HControlDemoWidget.h"

class QStackedWidget;
class QTabWidget;

HE_BEGIN_NAMESPACE

class IIconFontFactory;
class HFlatStyle;
class HNavigationWidget;


class HControlDemoWidgetPrivate
{
public:
    HFlatStyle *style;
    IIconFontFactory *iconFactory;
    HNavigationWidget *navigationWidget;
    QStackedWidget *stackedWidget;
    QHash<QString, QTabWidget *> tabWidgets;
};

HE_END_NAMESPACE
