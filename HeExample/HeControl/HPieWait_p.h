#ifndef HPIEWAIT_P_H
#define HPIEWAIT_P_H

#include "HPieWait.h"
#include "HAbstractWait_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPieWaitPrivate : public HAbstractWaitPrivate
{
public:
    QColor background = QColor(97, 117, 118);
    QColor foreground = QColor(46, 194, 163);
    int spanAngle = 60;
};

HE_CONTROL_END_NAMESPACE

#endif // HPIEWAIT_P_H
