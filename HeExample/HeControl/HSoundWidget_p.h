#pragma once

#include "HSoundWidget.h"

class QLabel;
class QAbstractSlider;
class QFrame;
class QMenu;

HE_CONTROL_BEGIN_NAMESPACE

class HSoundSlider;

class HSoundWidgetPrivate
{
public:
    bool muted = false;
    int volumeMax = 125;

public:
    QLabel *label = nullptr;
    QAbstractSlider *slider = nullptr;
    QFrame *frame = nullptr;
    QMenu *menu = nullptr;
};

HE_CONTROL_END_NAMESPACE

