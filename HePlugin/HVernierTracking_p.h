#ifndef HVERNIERTRACKING_P_H
#define HVERNIERTRACKING_P_H

#include "HVernierTracking.h"
#include "HAbstractVernierTracking_p.h"
#include <QtCore/QVector>
#include <QtGui/QColor>

class HVernierTrackingPrivate : public HAbstractVernierTrackingPrivate
{
public:
    HVernierTrackingPrivate(Qt::Orientation o, QWidget *p);
};

#endif // HVERNIERTRACKING_P_H
