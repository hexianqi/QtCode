/***************************************************************************************************
**      2019-04-12  ISqlFactory 数据库工厂接口。
***************************************************************************************************/

#ifndef ISQLFACTORY_H
#define ISQLFACTORY_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlDatabase;
class ISqlTableModel;

class ISqlFactory : public IInitializeable
{
public:
    // 创建数据库
    virtual ISqlDatabase *createDatabase(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建表格模型
    virtual ISqlTableModel *createTableModel(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_SQL_END_NAMESPACE

#endif // ISQLFACTORY_H
