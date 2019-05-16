/***************************************************************************************************
**      2019-04-12  SQL各种转换函数。
***************************************************************************************************/

#ifndef HSQL_H
#define HSQL_H

#include "HSqlGlobal.h"

class QStringList;
class QVariant;

HE_SQL_BEGIN_NAMESPACE

class HE_SQL_EXPORT HSql
{
public:
    static QString toType(QString field);
    static QStringList toType(QStringList field);
    static QString toCreateStyle(QString field);
    static QStringList toCreateStyle(QStringList field);

public:
    static QString toString(QString field, QVariant value);
    static QString toCaption(QString field);
    static QStringList toCaption(QStringList field);
    static QString toUnit(QString field);
    static QString toCaptionUnit(QString field);
    static QStringList toCaptionUnit(QStringList field);
};

HE_SQL_END_NAMESPACE

#endif // HSQL_H
