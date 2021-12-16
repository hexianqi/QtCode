/***************************************************************************************************
**      2019-04-08  ICodec 编码器。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class ICodec : public IInitializeable
{
public:
    // 预解码
    virtual QVector<uchar> preDecode(QVector<uchar> value) = 0;
    // 编码
    virtual QVector<uchar> encode(QVector<uchar> value) = 0;
    // 解码
    virtual QVector<uchar> decode(QVector<uchar> value) = 0;
    // 检查
    virtual bool check(QVector<uchar> value) = 0;
};

HE_END_NAMESPACE
