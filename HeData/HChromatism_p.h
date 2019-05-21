#ifndef HCHROMATISM_P_H
#define HCHROMATISM_P_H

#include "HChromatism.h"

HE_DATA_BEGIN_NAMESPACE

class HChromatismPrivate : public HCollectionPrivate<IChromatismItem>
{
public:
    IChromatismItem *selectItem = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HCHROMATISM_P_H
