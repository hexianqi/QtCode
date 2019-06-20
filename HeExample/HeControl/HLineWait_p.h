#ifndef HLINEWAIT_P_H
#define HLINEWAIT_P_H

#include "HLineWait.h"
#include "HAbstractWait_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLineWaitPrivate : public HAbstractWaitPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
};

HE_CONTROL_END_NAMESPACE

#endif // HLINEWAIT_P_H
