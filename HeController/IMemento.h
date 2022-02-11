/***************************************************************************************************
**      2019-05-27  IMemento 备忘录接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IMemento : public IInitializeable
{
public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 保存项
    virtual void setDataType(QStringList) = 0;
    virtual QStringList dataType() = 0;

public:
    // 保存
    virtual void save() = 0;
    // 还原
    virtual void restore() = 0;
};

HE_END_NAMESPACE
