#ifndef HCARDLAYOUT_P_H
#define HCARDLAYOUT_P_H

#include "HCardLayout.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCardLayoutPrivate
{
public:
    QList<QLayoutItem *> items;
};

HE_CONTROL_END_NAMESPACE

#endif // HCARDLAYOUT_P_H
