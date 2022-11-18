#pragma once

#include "HHoverShowWidget.h"

class QFrame;
class QLabel;

HE_BEGIN_NAMESPACE

class HHoverShowWidgetPrivate
{
public:
    QTimer *timer = nullptr;
    QFrame *frame = nullptr;
    QLabel *textLabel = nullptr;
};

HE_END_NAMESPACE

