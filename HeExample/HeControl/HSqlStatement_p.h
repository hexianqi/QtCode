#pragma once

#include "HSqlStatement.h"
#include <QtCore/QHash>

HE_BEGIN_NAMESPACE

class HXmlSqlHandler;

class HSqlStatementPrivate
{
public:
    HXmlSqlHandler *handler;
    QHash<QString, QString> statements;
};

HE_END_NAMESPACE
