#pragma once

#include "HScreenWidget.h"

class QMenu;

HE_CONTROL_BEGIN_NAMESPACE

class HScreenObject;

class HScreenWidgetPrivate
{
public:
    HScreenObject *screen;
    QMenu *menu;

    QPoint lastPos;
    bool pressed = false;
//    QPixmap *bgScreen;      //模糊背景图
};

HE_CONTROL_END_NAMESPACE
