#ifndef HABSTRACTGRADEITEMDIALOG_P_H
#define HABSTRACTGRADEITEMDIALOG_P_H

#include "HAbstractGradeItemDialog.h"

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HAbstractGradeItemDialogPrivate
{
public:
    IGradeItem *data;
    QString type;
    bool averageMode = false;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTGRADEITEMDIALOG_P_H
