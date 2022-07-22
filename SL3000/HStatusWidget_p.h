#pragma once

#include "HStatusWidget.h"

class QLabel;

class HStatusWidgetPrivate
{
public:
    HStatusWidgetPrivate();

public:
    QPixmap grey;
    QPixmap green;
    QPixmap red;
    QHash<int, QLabel *> lamps;
};



