#ifndef HCIRCLEWAIT_P_H
#define HCIRCLEWAIT_P_H

#include "HCircleWait.h"
#include "HAbstractWait_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCircleWaitPrivate : public HAbstractWaitPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCLEWAIT_P_H
