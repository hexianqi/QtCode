#pragma once

#include "HAbstractMouseStrategy.h"
#include <QtCore/QRectF>

class HAbstractMouseStrategyPrivate
{
public:
    HAbstractMouseStrategyPrivate(QWidget *p);

public:
    QWidget *parent;
    QRectF validRegion;
    bool enable = true;
};
