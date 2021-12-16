#pragma once

#include "HBreakoutWidget.h"

class QOpenGLFunctions_3_3_Core;

HE_BEGIN_NAMESPACE

class HGameManager;

class HBreakoutWidgetPrivate
{
public:
    QTimer *timer = nullptr;
    QOpenGLFunctions_3_3_Core *funcs = nullptr;
    HGameManager *game = nullptr;
};

HE_END_NAMESPACE

