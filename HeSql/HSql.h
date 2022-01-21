/***************************************************************************************************
**      2019-04-12  SQL各种转换函数。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

class QSqlRecord;

HE_BEGIN_NAMESPACE

class ITestData;

class HSql
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

public:
    static QStringList membership(const QString &name);
    static QStringList membership(const QStringList &name);

public:
    static QVariantMap toRecord(const QStringList &field, ITestData *);
    static QVariantMap toData(const QStringList &type, QSqlRecord);
};

HE_END_NAMESPACE
