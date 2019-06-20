#ifndef HDONUTWAIT_P_H
#define HDONUTWAIT_P_H

#include "HDonutWait.h"
#include "HAbstractWait_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HDonutWaitPrivate : public HAbstractWaitPrivate
{
public:
    QColor background = QColor(97, 117, 118);
    QColor foreground = QColor(46, 194, 163);
    int spanAngle = 60;
};

HE_CONTROL_END_NAMESPACE

#endif // HDONUTWAIT_P_H
