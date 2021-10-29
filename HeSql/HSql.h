/***************************************************************************************************
**      2019-04-12  SQL各种转换函数。
***************************************************************************************************/

#pragma once

#include "HSqlGlobal.h"

class QStringList;
class QVariant;

HE_SQL_BEGIN_NAMESPACE

class HE_SQL_EXPORT HSql
{
public:
    static QString toType(const QString &field);
    static QStringList toType(const QStringList &field);
    static QString toField(const QString &type);
    static QStringList toField(const QStringList &type);
    static QString toCreateStyle(const QString &field);
    static QStringList toCreateStyle(const QStringList &field);

public:
    static QString toString(const QString &field, const QVariant& value);
    static QString toCaption(const QString &field);
    static QStringList toCaption(const QStringList &field);
    static QString toUnit(const QString &field);
    static QString toCaptionUnit(const QString &field);
    static QStringList toCaptionUnit(const QStringList &field);
};

HE_SQL_END_NAMESPACE
