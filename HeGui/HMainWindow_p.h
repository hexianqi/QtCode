#ifndef HMAINWINDOW_P_H
#define HMAINWINDOW_P_H

#include "HMainWindow.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HMainWindowPrivate
{
public:
    HMainWindowPrivate(HMainWindow *p);

public:
    HMainWindow *q_ptr;
    IModel *model;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_P_H
