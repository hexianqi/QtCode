/***************************************************************************************************
**      2019-05-07  HCoreHelper 帮助类。
***************************************************************************************************/

#ifndef HCOREHELPER_H
#define HCOREHELPER_H

#include "HCoreGlobal.h"

class QStringList;

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HCoreHelper
{
public:
    static QStringList unselected(QStringList optional, QStringList selected);
    static void msleep(ulong msecs);
};

HE_CORE_END_NAMESPACE

#endif // HCOREHELPER_H
