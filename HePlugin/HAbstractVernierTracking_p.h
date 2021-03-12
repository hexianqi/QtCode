#pragma once

#include "HAbstractVernierTracking.h"
#include "HAbstractMouseStrategy_p.h"
#include <QtCore/QVector>
#include <QtGui/QColor>

class HAbstractVernierTrackingPrivate : public HAbstractMouseStrategyPrivate
{
public:
    HAbstractVernierTrackingPrivate(Qt::Orientation o, QWidget *p);

public:
    Qt::Orientation orientation;
    QColor color = Qt::blue;
    int pos = -1;
    QVector<QPointF> verniers;
};
