#ifndef HMODEL2000_P_H
#define HMODEL2000_P_H

#include "HModel2000.h"
#include "HeController/HAbstractModel_p.h"

class HModel2000Private : public HAbstractModelPrivate
{
    Q_DECLARE_PUBLIC(HModel2000)

public:
    HModel2000Private(HModel2000 *q);

public:
    void init();
};

#endif // HMODEL2000_P_H
