#ifndef HLISTCOLLECTIONDIALOG_P_H
#define HLISTCOLLECTIONDIALOG_P_H

#include "HListCollectionDialog.h"
#include <QModelIndex>

class QStringListModel;

HE_GUI_BEGIN_NAMESPACE

class HListCollectionDialogPrivate
{
public:
    QStringListModel *model;
    IItemDetailWidget *itemWidget;

public:
    QModelIndex currentIndex;

};

HE_GUI_END_NAMESPACE

#endif // HLISTCOLLECTIONDIALOG_P_H
