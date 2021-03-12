/***************************************************************************************************
**      2019-04-16  IGrade 分级数据接口。
***************************************************************************************************/

#pragma once

#include "HDataGlobal.h"
#include "HeCore/HCollection.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class IGradeItem;

class IGrade : public HCollection<IGradeItem>
{
public:
    using HCollection::HCollection;

public:
    // 读取内容
    virtual void readContent(QDataStream &) = 0;
    // 写入内容
    virtual void writeContent(QDataStream &) = 0;

public:
    // 设置数据
    virtual void setData(QString name, QVariant value) = 0;
    // 获取数据
    virtual QVariant data(QString name) = 0;

public:
    // 获取某类型所有分级
    virtual QVariant levels(QString type) = 0;
    // 计算levels
    virtual int calcLevel(QVariantMap value, QString *text) = 0;
};

HE_DATA_END_NAMESPACE
