#pragma once

#include "HListCollectionDialog.h"
#include <QModelIndex>

class QStringListModel;

HE_BEGIN_NAMESPACE

class HListCollectionDialogPrivate
{
public:
    QStringListModel *model;
    IDataDetail *detail;

public:
    QModelIndex currentIndex;
};

HE_END_NAMESPACE
