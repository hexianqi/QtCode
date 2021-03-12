#pragma once

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
