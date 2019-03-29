#ifndef HABSTRACTMOUSESTRATEGY_P_H
#define HABSTRACTMOUSESTRATEGY_P_H

#include "HAbstractMouseStrategy.h"
#include <QRectF>

class HAbstractMouseStrategyPrivate
{
public:
    HAbstractMouseStrategyPrivate(QWidget *p);

public:
    QWidget *parent;
    QRectF validRegion;
    bool enable = true;
};

#endif // HABSTRACTMOUSESTRATEGY_P_H
