/***************************************************************************************************
**      2019-04-12  ISqlDatabase Sql数据库接口。
***************************************************************************************************/

#ifndef ISQLDATABASE_H
#define ISQLDATABASE_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel;

class ISqlDatabase : public IInitializeable
{
public:
    // 打开数据库
    virtual bool openDatabase(QString dbName) = 0;
    // 添加数据库表格模型
    virtual void insertTableModel(QString name, ISqlTableModel *model) = 0;
    // 获取数据库表格模型
    virtual ISqlTableModel *tableModel(QString name) = 0;
};

HE_SQL_END_NAMESPACE

#endif // ISQLDATABASE_H
