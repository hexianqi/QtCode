/***************************************************************************************************
**      2019-04-26  IAdjust 调整数据接口。
***************************************************************************************************/

#pragma once

#include "HeCore/HCollection.h"

namespace QXlsx {
class Worksheet;
}

using namespace QXlsx;

HE_BEGIN_NAMESPACE

class IAdjustItem;

class IAdjust : public HCollection<IAdjustItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    virtual void readContent(Worksheet *) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;
    virtual void writeContent(Worksheet *) = 0;

public:
    // 还原默认
    virtual void restoreDefault() = 0;
    // 纠正
    virtual QVariantMap correct(QVariantMap value) = 0;
};

HE_END_NAMESPACE
