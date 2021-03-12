/***************************************************************************************************
**      2019-12-25  HQuotedPrintable
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"

HE_CONTROL_BEGIN_NAMESPACE

class HQuotedPrintable
{
public:
    static QString encode(const QByteArray &value);
    static QByteArray decode(const QString &value);
};

HE_CONTROL_END_NAMESPACE
