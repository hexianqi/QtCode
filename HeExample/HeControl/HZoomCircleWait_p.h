#ifndef HZOOMCIRCLEWAIT_P_H
#define HZOOMCIRCLEWAIT_P_H

#include "HZoomCircleWait.h"
#include "HAbstractWait_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HZoomCircleWaitPrivate : public HAbstractWaitPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
    int minimum = 10;
    bool bounce = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HZOOMCIRCLEWAIT_P_H
