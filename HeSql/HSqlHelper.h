/***************************************************************************************************
**      2019-04-12  HSqlHelper SQL帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtSql/QSqlDatabase>

HE_BEGIN_NAMESPACE

class ISqlDatabase;

class HSqlHelper
{
public:
    // 添加表格
    static bool createTable(const QString &tableName, const QStringList &fields, QSqlDatabase db = QSqlDatabase());
    // 清空数据表
    static bool truncateTable(const QString &tableName, QSqlDatabase db = QSqlDatabase());
    // 添加列
    static bool addColumn(const QString &tableName, const QString &field, QSqlDatabase db = QSqlDatabase());
    static void addColumn(const QString &tableName, const QStringList &fields, QSqlDatabase db = QSqlDatabase());
    // 设置表格版本
    static bool setVersion(const QString &tableName, int version, QSqlDatabase db = QSqlDatabase());
    // 获取表格版本
    static int getVersion(const QString &tableName, QSqlDatabase db = QSqlDatabase());
    // 更新光谱表格
    static void updateSpecTable(ISqlDatabase *db);
    // 更新光强角表格
    static void updateAngleTable(ISqlDatabase *db);
};

HE_END_NAMESPACE
