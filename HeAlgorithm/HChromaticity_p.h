#pragma once

#include "HChromaticity.h"
#include "HIesTm30.h"

HE_BEGIN_NAMESPACE

class HChromaticityPrivate
{
public:
    HChromaticityPrivate();

public:
    std::shared_ptr<HCie1931> cie1931;
    std::shared_ptr<HCieDaylight> cieDay;
    std::shared_ptr<HIsotherm> isotherm;
    std::shared_ptr<HIesTm30> iesTm30;
};

HE_END_NAMESPACE
