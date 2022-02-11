/***************************************************************************************************
**      2022-02-10  备忘录集合接口。
***************************************************************************************************/


#pragma once

#include "HeCore/HCollection.h"

HE_BEGIN_NAMESPACE

class IMemento;

class IMementoCollection : public HCollection<IMemento>
{
public:
    using HCollection::HCollection;

public:
    // 读取文件
    virtual bool readFile(QString fileName) = 0;
    // 写入文件
    virtual bool writeFile(QString fileName = QString()) = 0;
};

HE_END_NAMESPACE
