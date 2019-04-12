/***************************************************************************************************
**      2019-04-12  SQL各种转换函数。
***************************************************************************************************/

#ifndef HSQL_H
#define HSQL_H

#include "HSqlGlobal.h"

class QStringList;

HE_SQL_BEGIN_NAMESPACE

QString toCreateStyle(QString field);
QStringList toCreateStyle(QStringList field);

HE_SQL_END_NAMESPACE

#endif // HSQL_H
