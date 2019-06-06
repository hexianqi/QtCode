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
    // 选择
    static QStringList unselected(QStringList optional, QStringList selected);
    // 延时
    static void msleep(int msecs);
    static void msleep2(int msecs);
};

HE_CORE_END_NAMESPACE

#endif // HCOREHELPER_H
