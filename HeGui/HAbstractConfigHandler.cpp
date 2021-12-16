#include "HAbstractConfigHandler_p.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HAbstractConfigHandlerPrivate::HAbstractConfigHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    model = HAppContext::getContextPointer<IModel>("IModel");
}

HAbstractConfigHandler::HAbstractConfigHandler(QObject *parent) :
    HAbstractGuiHandler(*new HAbstractConfigHandlerPrivate, parent)
{
}

HAbstractConfigHandler::HAbstractConfigHandler(HAbstractConfigHandlerPrivate &p, QObject *parent) :
    HAbstractGuiHandler(p, parent)
{
}

HE_END_NAMESPACE
