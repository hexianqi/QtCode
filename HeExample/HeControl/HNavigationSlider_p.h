#pragma once

#include "HNavigationSlider.h"

class QSlider;
class QToolButton;

HE_CONTROL_BEGIN_NAMESPACE

class HNavigationSliderPrivate
{
public:
    QSlider *slider;
    QToolButton *first;
    QToolButton *previous;
    QToolButton *next;
    QToolButton *last;
    QListWidget *listWidget = nullptr;
};

HE_CONTROL_END_NAMESPACE
