#include "HIVTestHandler_p.h"
#include "IMainWindow.h"
#include "HIVTestWidget.h"
#include "HGuiHelper.h"

HE_BEGIN_NAMESPACE

HIVTestHandler::HIVTestHandler(QObject *parent) :
    HAbstractGuiHandler(*new HIVTestHandlerPrivate, parent)
{
}

HIVTestHandler::~HIVTestHandler() = default;

QString HIVTestHandler::typeName()
{
    return "HIVTestHandler";
}

void HIVTestHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HIVTestHandler);
    auto w = HGuiHelper::decoratorInMainWindow(new HIVTestWidget, d->mainWindow);
    d->mainWindow->openWidget(w);
}

HE_END_NAMESPACE
