#include "HLoginInHandler_p.h"
#include "IMainWindow.h"
#include "HLoginDialog.h"

HE_BEGIN_NAMESPACE

HLoginInHandler::HLoginInHandler(QObject *parent) :
    HAbstractGuiHandler(*new HLoginInHandlerPrivate, parent)
{
}

HLoginInHandler::~HLoginInHandler() = default;

QString HLoginInHandler::typeName()
{
    return "HLoginInHandler";
}

void HLoginInHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HLoginInHandler);

    HLoginDialog dlg(d->mainWindow);
    if (!dlg.exec())
        return;
    d->mainWindow->setAuthority(1);
}

HE_END_NAMESPACE
