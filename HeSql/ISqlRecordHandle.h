/***************************************************************************************************
**      2019-05-10  ISqlRecordHandle 数据库记录处理接口。
***************************************************************************************************/

#ifndef ISQLRECORDHANDLE_H
#define ISQLRECORDHANDLE_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel;

class ISqlRecordHandle : public IInitializeable
{
public:
    // 设置模型
    virtual void setModel(ISqlTableModel *) = 0;

public:
    // 添加记录
    virtual bool addRecord(QVariantMap value) = 0;
    // 删除记录
    virtual void removeRecord() = 0;
    virtual void removeRecord(int index, int count) = 0;
    // 还原记录
    virtual void revertRecord() = 0;
    // 查找记录
    virtual void findRecord() = 0;
};

HE_SQL_END_NAMESPACE



#endif // ISQLRECORDHANDLE_H
