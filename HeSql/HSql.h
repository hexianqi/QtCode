/***************************************************************************************************
**      2019-04-12  SQL各种转换函数。
***************************************************************************************************/

#ifndef HSQL_H
#define HSQL_H

#include "HSqlGlobal.h"

class QStringList;
class QVariant;

HE_SQL_BEGIN_NAMESPACE

HE_SQL_EXPORT QString toType(QString field);
HE_SQL_EXPORT QStringList toType(QStringList field);

QString toCreateStyle(QString field);
QStringList toCreateStyle(QStringList field);

QString toString(QString field, QVariant value);
QString toCaptionUnit(QString field);

HE_SQL_END_NAMESPACE

#endif // HSQL_H
