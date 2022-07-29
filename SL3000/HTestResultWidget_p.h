#pragma once

#include "HTestResultWidget.h"

class HTestResultWidgetPrivate
{
public:
    HTestResultWidgetPrivate();

public:
    QStringList testItems;
    int ledCount = 0;
};
