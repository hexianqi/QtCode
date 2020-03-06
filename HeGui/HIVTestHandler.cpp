#include "HIVTestHandler_p.h"
#include "HIVTestWidget.h"
#include "IMainWindow.h"
#include <QtCore/QDebug>

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
    qDebug() << __func__;
}

void HIVTestHandler::initialize(QVariantMap /*param*/)
{

}

QString HIVTestHandler::typeName()
{
    return "HIVTestHandler";
}

void HIVTestHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HIVTestHandler);
    d->mainWindow->openWidget(new HIVTestWidget);
}

HE_GUI_END_NAMESPACE
