/***************************************************************************************************
**      2019-03-01  HAbstractGuiHandler 抽象Gui处理者类。
***************************************************************************************************/

#ifndef HABSTRACTGUIHANDLER_H
#define HABSTRACTGUIHANDLER_H

#include "IGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HAbstractGuiHandlerPrivate;

class HAbstractGuiHandler : public IGuiHandler
{
public:
    explicit HAbstractGuiHandler(QObject *parent = nullptr);

protected:
    HAbstractGuiHandler(HAbstractGuiHandlerPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractGuiHandlerPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTGUIHANDLER_H
