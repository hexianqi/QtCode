#ifndef HSQLSTATEMENT_P_H
#define HSQLSTATEMENT_P_H

#include "HSqlStatement.h"
#include <QtCore/QHash>

HE_CONTROL_BEGIN_NAMESPACE

class HXmlSqlHandler;

class HSqlStatementPrivate
{
public:
    HXmlSqlHandler *handler;
    QHash<QString, QString> statements;
};

HE_CONTROL_END_NAMESPACE

#endif // HSQLSTATEMENT_P_H
