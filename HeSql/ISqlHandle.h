/***************************************************************************************************
**      2019-05-10  ISqlHandle 数据库记录处理接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class ISqlTableModel;

class ISqlHandle : public IInitializeable
{
public:
    // 设置模型
    virtual void setModel(ISqlTableModel *) = 0;
    // 设置可查询字段
    virtual void setFieldFind(QStringList value) = 0;
    // 字段
    virtual QStringList field() = 0;

public:
    // 添加记录
    virtual bool addRecord(QVariantMap value) = 0;
    // 删除记录
    virtual void removeRecord() = 0;
    virtual void removeRecord(int row, int count) = 0;
    // 还原记录
    virtual void revertRecord() = 0;
    // 查找记录
    virtual void findRecord() = 0;
};

HE_END_NAMESPACE
