/***************************************************************************************************
**      2019-03-04  HCallorHelper 访问者帮助类。
***************************************************************************************************/

#ifndef HCALLORHELPER_H
#define HCALLORHELPER_H

#include "IConstructorCall.h"

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HCallorHelper
{
public:
    HCallorHelper();
    ~HCallorHelper();

public:
    void initialize(IConstructorCall *) const;

private:
    mutable IConstructorCall *_p;
};

HE_CORE_END_NAMESPACE

#endif // HCALLORHELPER_H
