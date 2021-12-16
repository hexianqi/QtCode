#include "HTestHandler_p.h"
#include "IMainWindow.h"
#include <QtWidgets/QMessageBox>

HE_BEGIN_NAMESPACE

HTestHandler::HTestHandler(QObject *parent) :
    HAbstractGuiHandler(*new HTestHandlerPrivate, parent)
{
}

HTestHandler::~HTestHandler() = default;

QString HTestHandler::typeName()
{
    return "HTestHandler";
}

void HTestHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HTestHandler);
    QMessageBox::information(d->mainWindow, "" , tr("敬请期待"));
}

HE_END_NAMESPACE
