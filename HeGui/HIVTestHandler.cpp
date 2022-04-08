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
    auto w = new HIVTestWidget;
    auto m = HGuiHelper::decoratorInMainWindow(w, d->mainWindow);
    d->mainWindow->blockAndConnect(m);
    w->start();
    m->show();
}

HE_END_NAMESPACE
