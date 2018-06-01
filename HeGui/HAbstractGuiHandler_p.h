#ifndef HABSTRACTGUIHANDLER_P_H
#define HABSTRACTGUIHANDLER_P_H

#include "HAbstractGuiHandler.h"

class QWidget;

HE_GUI_BEGIN_NAMESPACE

class HAbstractGuiHandlerPrivate
{
public:
    HAbstractGuiHandlerPrivate();

public:
    QWidget *parent;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTGUIHANDLER_P_H
