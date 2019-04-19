#ifndef HCHROMATICITY_P_H
#define HCHROMATICITY_P_H

#include "HChromaticity.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HChromaticityPrivate
{
public:
    HChromaticityPrivate();

public:
    std::shared_ptr<HCie1931> cie1931;
    std::shared_ptr<HCieDay> cieDay;
    std::shared_ptr<HIsotherm> isotherm;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HCHROMATICITY_P_H
