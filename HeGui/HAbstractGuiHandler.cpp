#include "HAbstractGuiHandler_p.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HAbstractGuiHandlerPrivate::HAbstractGuiHandlerPrivate()
{
    mainWindow = HAppContext::getContextPointer<IMainWindow>("IMainWindow");
}

HAbstractGuiHandler::HAbstractGuiHandler(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractGuiHandlerPrivate)
{
}

HAbstractGuiHandler::HAbstractGuiHandler(HAbstractGuiHandlerPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractGuiHandler::~HAbstractGuiHandler()
{
}

void HAbstractGuiHandler::initialize(QVariantMap /*param*/)
{
}

HE_END_NAMESPACE
