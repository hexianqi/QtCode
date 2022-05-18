#include "HAngleTestHandler_p.h"
#include "IMainWindow.h"
#include "HAngleTestWidget.h"
#include "HDecoratorMainWindow.h"

HE_BEGIN_NAMESPACE

HAngleTestHandler::HAngleTestHandler(QObject *parent) :
    HAbstractGuiHandler(*new HAngleTestHandlerPrivate, parent)
{
}

HAngleTestHandler::~HAngleTestHandler() = default;

QString HAngleTestHandler::typeName()
{
    return "HAngleTestHandler";
}

void HAngleTestHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAngleTestHandler);
    auto w = new HDecoratorMainWindow(d->mainWindow);
    w->run(new HAngleTestWidget);
}

HE_END_NAMESPACE
