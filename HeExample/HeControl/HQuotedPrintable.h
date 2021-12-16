/***************************************************************************************************
**      2019-12-25  HQuotedPrintable
***************************************************************************************************/

#pragma once

#include "HNamespace.h"

class QString;
class QByteArray;

HE_BEGIN_NAMESPACE

class HQuotedPrintable
{
public:
    static QString encode(const QByteArray &value);
    static QByteArray decode(const QString &value);
};

HE_END_NAMESPACE
