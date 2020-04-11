#ifndef HSPECCALIBRATEDIALOG_P_H
#define HSPECCALIBRATEDIALOG_P_H

#include "HSpecCalibrateDialog.h"

HE_GUI_BEGIN_NAMESPACE

class IGuiFactory;
class HSpecCalibrateWidget;

class HSpecCalibrateDialogPrivate
{
public:
    HSpecCalibrateDialogPrivate();

public:
    IGuiFactory *factory = nullptr;
    HSpecCalibrateWidget *widget = nullptr;
    QString type;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATEDIALOG_P_H
