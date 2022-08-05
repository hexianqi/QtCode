/***************************************************************************************************
**      2019-04-16  IGradeCollection 分级数据集合接口。
***************************************************************************************************/

#pragma once

#include "HDataCollection.h"

HE_BEGIN_NAMESPACE

class IGrade;

class IGradeCollection : public HDataCollection<IGrade>
{
public:
    using HDataCollection::HDataCollection;

public:
    // 计算分级
    virtual int calcLevel(QVariantMap value, QString *text = nullptr) = 0;
};

HE_END_NAMESPACE
