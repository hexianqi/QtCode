/***************************************************************************************************
**      2018-06-19  IHandler 处理者接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE

class IHandler : public IInitializeable
{
public:
    // 执行
    virtual void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) = 0;
};

HE_CORE_END_NAMESPACE
