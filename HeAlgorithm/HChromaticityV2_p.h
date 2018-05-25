#ifndef HCHROMATICITYV2_P_H
#define HCHROMATICITYV2_P_H

#include "HChromaticityV2.h"
#include "HChromaticity_p.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HChromaticityV2Private : public HChromaticityPrivate
{
public:
    HChromaticityV2Private();

public:
    std::shared_ptr<HCieUcs> cieUcs;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HCHROMATICITYV2_P_H
