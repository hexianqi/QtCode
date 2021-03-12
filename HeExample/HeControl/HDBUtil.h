/***************************************************************************************************
**      2020-03-31  HDBUtil
**                  封装了一些操作数据库的通用方法，例如插入、更新操作、查询结果返回整数、时间类型。
**                  还可以把查询结果映射成 map，甚至通过传入的映射函数把 map 映射成对象等，也就是Bean，
**                  可以简化操作数据库的类的代码，参考 HDBBean.cpp.
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QVariantMap>

class QSqlQuery;

HE_CONTROL_BEGIN_NAMESPACE

class HDBUtil
{
public:
    static int insert(const QString &sql, const QVariantMap &param = QVariantMap());
    static bool update(const QString &sql, const QVariantMap &param = QVariantMap());
    static int selectInt(const QString &sql, const QVariantMap &param = QVariantMap());
    static qint64 selectInt64(const QString &sql, const QVariantMap &param = QVariantMap());
    static QString selectString(const QString &sql, const QVariantMap &param = QVariantMap());
    static QStringList selectStrings(const QString &sql, const QVariantMap &param = QVariantMap());
    static QDate selectDate(const QString &sql, const QVariantMap &param = QVariantMap());
    static QDateTime selectDateTime(const QString &sql, const QVariantMap &param = QVariantMap());
    static QVariant selectVariant(const QString &sql, const QVariantMap &param = QVariantMap());
    static QVariantMap selectMap(const QString &sql, const QVariantMap &param = QVariantMap());
    static QList<QVariantMap> selectMaps(const QString &sql, const QVariantMap &param = QVariantMap());

public:
    template <typename T>
    static T selectBean(T mapToBean(const QVariantMap &), const QString &sql, const QVariantMap &param = QVariantMap());
    template<typename T>
    static QList<T> selectBeans(T mapToBean(const QVariantMap &), const QString &sql, const QVariantMap &param = QVariantMap());

private:
    static void execute(const QString &sql, const QVariantMap &param, const std::function<void(QSqlQuery *)>& func);
    static QStringList getFieldNames(QSqlQuery *);
    static void debug(QSqlQuery *, const QVariantMap &);
    static void bindValue(QSqlQuery *query, const QVariantMap &);
    static QList<QVariantMap> toMaps(QSqlQuery *query);
};

template<typename T>
T HDBUtil::selectBean(T mapToBean(const QVariantMap &), const QString &sql, const QVariantMap &param)
{
    return mapToBean(selectMap(sql, param));
}

template<typename T>
QList<T> HDBUtil::selectBeans(T mapToBean(const QVariantMap &), const QString &sql, const QVariantMap &param)
{
    QList<T> list;
    for (auto row : selectMaps(sql, param))
        list << mapToBean(row);
    return list;
}

HE_CONTROL_END_NAMESPACE
