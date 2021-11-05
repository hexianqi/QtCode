/***************************************************************************************************
**      2019-04-12  ISqlFactory 数据库工厂接口。
***************************************************************************************************/

#pragma once

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlDatabase;
class ISqlTableModel;
class ISqlHandle;
class ISqlOutput;
class ISqlPrint;
class ISqlBrowser;
class IProductInfo;

class ISqlFactory : public IInitializeable
{
public:
    // 创建数据库
    virtual ISqlDatabase *createDatabase(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建数据库表格模型
    virtual ISqlTableModel *createTableModel(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建数据库处理
    virtual ISqlHandle *createHandle(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建数据库输出
    virtual ISqlOutput *createOutput(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建数据库打印
    virtual ISqlPrint *createPrint(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建数据库浏览器
    virtual ISqlBrowser *createBrowser(QString type, QWidget *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建产品信息
    virtual IProductInfo *createProductInfo(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_SQL_END_NAMESPACE
