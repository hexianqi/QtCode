/***************************************************************************************************
**      2019-05-27  IMemento 备忘录接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IMemento : public IInitializeable
{
public:
    // 读取文件
    virtual bool readFile(QString fileName) = 0;
    // 写入文件
    virtual bool writeFile() = 0;

public:
    // 设置保存项
    virtual void setDataTypes(QStringList) = 0;

public:
    // 保存
    virtual void save() = 0;
    // 还原
    virtual void restore() = 0;
};

HE_END_NAMESPACE
