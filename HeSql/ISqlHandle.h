/***************************************************************************************************
**      2019-05-10  ISqlHandle 数据库记录处理接口。
***************************************************************************************************/

#ifndef ISQLHANDLE_H
#define ISQLHANDLE_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel;
class IProductInfo;

class ISqlHandle : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 设置模型
    virtual void setModel(ISqlTableModel *) = 0;
    // 设置可查询字段
    virtual void setFieldFind(QStringList value) = 0;
    // 设置产品信息
    virtual void setProductInfo(IProductInfo *) = 0;
    // 字段
    virtual QStringList field() = 0;

public:
    // 添加记录
    virtual bool addRecord(QVariantMap value, bool edit = true) = 0;
    // 删除记录
    virtual void removeRecord() = 0;
    virtual void removeRecord(int row, int count) = 0;
    // 还原记录
    virtual void revertRecord() = 0;
    // 查找记录
    virtual void findRecord() = 0;
    // 编辑产品信息
    virtual void editProductInfo() = 0;
};

HE_SQL_END_NAMESPACE

#endif // ISQLHANDLE_H
