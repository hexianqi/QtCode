#ifndef HVERNIERTRACKING_P_H
#define HVERNIERTRACKING_P_H

#include "HVernierTracking.h"
#include "HAbstractVernierTracking_p.h"
#include <QColor>
#include <QVector>

class HVernierTrackingPrivate : public HAbstractVernierTrackingPrivate
{
public:
    HVernierTrackingPrivate(Qt::Orientation o, QWidget *p);

public:
    void paintVernier();
};

#endif // HVERNIERTRACKING_P_H
