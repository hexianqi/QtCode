#include "HDBUtil.h"
#include "HConnectionPool.h"
#include "HDBConfig.h"
#include <QtCore/QDateTime>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

int HDBUtil::insert(const QString &sql, const QVariantMap &param)
{
    int id = -1;
    execute(sql, param, [&id](QSqlQuery *query) { id = query->lastInsertId().toInt(); });
    return id;
}

bool HDBUtil::update(const QString &sql, const QVariantMap &param)
{
    bool result;
    execute(sql, param, [&result](QSqlQuery *query) { result = query->lastError().type() == QSqlError::NoError; });
    return result;
}

int HDBUtil::selectInt(const QString &sql, const QVariantMap &param)
{
    return selectVariant(sql, param).toInt();
}

qint64 HDBUtil::selectInt64(const QString &sql, const QVariantMap &param)
{
    return selectVariant(sql, param).toLongLong();
}

QString HDBUtil::selectString(const QString &sql, const QVariantMap &param)
{
    return selectVariant(sql, param).toString();
}

QStringList HDBUtil::selectStrings(const QString &sql, const QVariantMap &param)
{
    QStringList list;

    execute(sql, param, [&list](QSqlQuery *query) {
        while (query->next())
            list << query->value(0).toString();
    });
    return list;
}

QDate HDBUtil::selectDate(const QString &sql, const QVariantMap &param)
{
    return selectVariant(sql, param).toDate();
}

QDateTime HDBUtil::selectDateTime(const QString &sql, const QVariantMap &param)
{
    return selectVariant(sql, param).toDateTime();
}

QVariant HDBUtil::selectVariant(const QString &sql, const QVariantMap &param)
{
    QVariant result;
    execute(sql, param, [&result](QSqlQuery *query) {
        if (query->next())
            result = query->value(0);
    });
    return result;
}

QVariantMap HDBUtil::selectMap(const QString &sql, const QVariantMap &param)
{
    return selectMaps(sql, param).value(0);
}

QList<QVariantMap> HDBUtil::selectMaps(const QString &sql, const QVariantMap &param)
{
    QList<QVariantMap> maps;
    execute(sql, param, [&maps](QSqlQuery *query) { maps = toMaps(query); });
    return maps;
}

void HDBUtil::execute(const QString &sql, const QVariantMap &param, const std::function<void (QSqlQuery *)> &func)
{
    auto db = HConnectionPool::instance()->openConnection();
    auto query = new QSqlQuery(db);
    query->prepare(sql);

    bindValue(query, param);
    if (query->exec())
        func(query);
    debug(query, param);
    delete query;
}

QStringList HDBUtil::getFieldNames(QSqlQuery *query)
{
    QStringList list;
    auto record = query->record();
    for (int i = 0; i < record.count(); ++i)
        list << record.fieldName(i);
    return list;
}

void HDBUtil::debug(QSqlQuery *query, const QVariantMap &param)
{
    if (!HDBConfig::instance()->isDebug())
        return;
    if (query->lastError().type() != QSqlError::NoError)
        qDebug().noquote() << "==> SQL Error: " << query->lastError().text().trimmed();
    qDebug().noquote() << "==> SQL Query:" << query->lastQuery();
    if (!param.isEmpty())
        qDebug().noquote() << "==> SQL Params: " << param;
}

void HDBUtil::bindValue(QSqlQuery *query, const QVariantMap &param)
{
    for (auto i = param.begin(); i != param.end(); ++i)
        query->bindValue(":" + i.key(), i.value());
}

QList<QVariantMap> HDBUtil::toMaps(QSqlQuery *query)
{
    QList<QVariantMap> list;
    auto fieldNames = getFieldNames(query);

    while (query->next())
    {
        QVariantMap row;
        for (const auto &name : fieldNames)
            row.insert(name, query->value(name));
        list << row;
    }
    return list;
}

HE_CONTROL_END_NAMESPACE
