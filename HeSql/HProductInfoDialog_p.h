#ifndef HPRODUCTINFODIALOG_P_H
#define HPRODUCTINFODIALOG_P_H

#include "HProductInfoDialog.h"

HE_SQL_BEGIN_NAMESPACE

class HProductInfoDialogPrivate
{
public:
    IProductInfo *data = nullptr;
};

HE_SQL_END_NAMESPACE

#endif // HPRODUCTINFODIALOG_P_H
