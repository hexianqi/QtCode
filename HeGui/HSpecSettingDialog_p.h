#ifndef HSPECSETTINGDIALOG_P_H
#define HSPECSETTINGDIALOG_P_H

#include "HSpecSettingDialog.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecSettingDialogPrivate
{
public:
    HSpecSettingDialogPrivate(HSpecSetting *);

public:
    HSpecSetting *data;
};

HE_GUI_END_NAMESPACE

#endif // HSPECSETTINGDIALOG_P_H
