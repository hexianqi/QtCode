#pragma once

#include "HSpliteWidget.h"

class QGridLayout;
class QLabel;
class QMenu;

HE_CONTROL_BEGIN_NAMESPACE

class HSpliteWidgetPrivate
{
public:
    bool fullScreen = false;
    int totalCount = 16;
    QString type;
    QGridLayout *gridLayout;
    QList<QLabel *> labels;
    QMenu *menu;
};

HE_CONTROL_END_NAMESPACE
