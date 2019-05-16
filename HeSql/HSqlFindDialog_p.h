#ifndef HSQLFINDDIALOG_P_H
#define HSQLFINDDIALOG_P_H

#include "HSqlFindDialog.h"

class QStringListModel;

HE_SQL_BEGIN_NAMESPACE

class HSqlFindDialogPrivate
{
public:
    QStringList fields;
    QStringList compares;
    QString filter;
    QStringListModel *model;
};

HE_SQL_END_NAMESPACE

#endif // HSQLFINDDIALOG_P_H
