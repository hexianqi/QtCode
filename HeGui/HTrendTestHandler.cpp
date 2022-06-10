#include "HTrendTestHandler_p.h"
#include "IMainWindow.h"
#include "HTrendTestWidget.h"
#include "HDecoratorMainWindow.h"

HE_BEGIN_NAMESPACE

HTrendTestHandler::HTrendTestHandler(QObject *parent) :
    HAbstractGuiHandler(*new HTrendTestHandlerPrivate, parent)
{
}

HTrendTestHandler::~HTrendTestHandler() = default;

QString HTrendTestHandler::typeName()
{
    return "HIVTestHandler";
}

void HTrendTestHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HTrendTestHandler);
    auto w = new HDecoratorMainWindow(d->mainWindow);
    w->run(new HTrendTestWidget);
}


HE_END_NAMESPACE
