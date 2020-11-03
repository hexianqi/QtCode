#ifndef HGRADEITEM2DDIALOG_P_H
#define HGRADEITEM2DDIALOG_P_H

#include "HGradeItem2DDialog.h"
#include "HAbstractGradeItemDialog_p.h"

class HCie1931Widget;

HE_GUI_BEGIN_NAMESPACE

class HGradeItem2DDialogPrivate : public HAbstractGradeItemDialogPrivate
{
public:
    HCie1931Widget *cieWidget;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEITEM2DDIALOG_P_H
