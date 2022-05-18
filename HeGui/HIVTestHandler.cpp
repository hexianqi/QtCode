#include "HIVTestHandler_p.h"
#include "IMainWindow.h"
#include "HIVTestWidget.h"
#include "HDecoratorMainWindow.h"

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
    auto w = new HDecoratorMainWindow(d->mainWindow);
    w->run(new HIVTestWidget);
}

HE_END_NAMESPACE
