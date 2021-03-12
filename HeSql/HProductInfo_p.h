#pragma once

#include "HProductInfo.h"

HE_SQL_BEGIN_NAMESPACE

class HProductInfoPrivate
{
public:
    HProductInfoPrivate();

public:
    QString relationTableName;
    QVariantMap datas;
};

HE_SQL_END_NAMESPACE
