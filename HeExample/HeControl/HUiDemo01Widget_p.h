#pragma once

#include "HUiDemo01Widget.h"

class QAbstractButton;

HE_BEGIN_NAMESPACE

class HIconFontStyle;

class HUiDemo01WidgetPrivate
{
public:
    bool max = false;
    QColor border;
    QColor normalBackground;
    QColor normalText;
    QColor darkBackground;
    QColor darkText;
    QList<QAbstractButton *> btnMain;
    QList<QAbstractButton *> btnConfig;
    HIconFontStyle *style = nullptr;
};

HE_END_NAMESPACE

