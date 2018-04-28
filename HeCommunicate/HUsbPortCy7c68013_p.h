#ifndef HUSBPORTCY7C68013_P_H
#define HUSBPORTCY7C68013_P_H

#include "HUsbPortCy7c68013.h"
#include "HAbstractPort_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUsbPortCy7c68013Private : public HAbstractPortPrivate
{
public:
    void *hand;
    bool isAsync;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUSBPORTCY7C68013_P_H
