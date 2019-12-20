#ifndef HLINEEDITGROUP_P_H
#define HLINEEDITGROUP_P_H

#include "HLineEditGroup.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLineEditGroupPrivate
{
public:
    QList<QLineEdit *> lineEdits;
};

HE_CONTROL_END_NAMESPACE

#endif // HLINEEDITGROUP_P_H
