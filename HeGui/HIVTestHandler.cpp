#include "HIVTestHandler_p.h"
#include "HIVTestWidget.h"
#include "IMainWindow.h"

HE_GUI_BEGIN_NAMESPACE

HIVTestHandler::HIVTestHandler(QObject *parent) :
    HAbstractGuiHandler(*new HIVTestHandlerPrivate, parent)
{
}

HIVTestHandler::HIVTestHandler(HIVTestHandlerPrivate &p, QObject *parent) :
    HAbstractGuiHandler(p, parent)
{
}

HIVTestHandler::~HIVTestHandler()
{
}

void HIVTestHandler::initialize(QVariantMap /*param*/)
{

}

QString HIVTestHandler::typeName()
{
    return "HIVTestHandler";
}

void HIVTestHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HIVTestHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)
    d->mainWindow->openWidget(new HIVTestWidget);
}

HE_GUI_END_NAMESPACE
