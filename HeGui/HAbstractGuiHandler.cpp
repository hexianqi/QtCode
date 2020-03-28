#include "HAbstractGuiHandler_p.h"
#include "HeCore/HAppContext.h"

HE_GUI_BEGIN_NAMESPACE

HAbstractGuiHandlerPrivate::HAbstractGuiHandlerPrivate()
{
    mainWindow = HAppContext::getContextPointer<IMainWindow>("IMainWindow");

}

HAbstractGuiHandler::HAbstractGuiHandler(QObject *parent) :
    IGuiHandler(parent),
    d_ptr(new HAbstractGuiHandlerPrivate)
{
}

HAbstractGuiHandler::HAbstractGuiHandler(HAbstractGuiHandlerPrivate &p, QObject *parent) :
    IGuiHandler(parent),
    d_ptr(&p)
{
}

HAbstractGuiHandler::~HAbstractGuiHandler()
{
}

HE_GUI_END_NAMESPACE
