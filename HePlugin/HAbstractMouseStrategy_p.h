#ifndef HABSTRACTMOUSESTRATEGY_P_H
#define HABSTRACTMOUSESTRATEGY_P_H

#include "HAbstractMouseStrategy.h"
#include <QRectF>

class HAbstractMouseStrategyPrivate
{
public:
    HAbstractMouseStrategyPrivate(QWidget *p);

public:
    bool isValid(QPointF pos);

public:
    QWidget *parent;
    bool enable = true;
    QRectF validRegion;
};

#endif // HABSTRACTMOUSESTRATEGY_P_H
