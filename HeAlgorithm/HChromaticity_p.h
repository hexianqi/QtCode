#pragma once

#include "HChromaticity.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HChromaticityPrivate
{
public:
    HChromaticityPrivate();

public:
    std::shared_ptr<HCie1931> cie1931;
    std::shared_ptr<HCieDaylight> cieDay;
    std::shared_ptr<HIsotherm> isotherm;
};

HE_ALGORITHM_END_NAMESPACE
