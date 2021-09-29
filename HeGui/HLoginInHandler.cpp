#include "HLoginInHandler_p.h"
#include "IMainWindow.h"
#include "HLoginDialog.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HLoginInHandler::HLoginInHandler(QObject *parent) :
    HAbstractGuiHandler(*new HLoginInHandlerPrivate, parent)
{
}

HLoginInHandler::~HLoginInHandler()
{
    qDebug() << __func__;
}

void HLoginInHandler::initialize(QVariantMap /*param*/)
{

}

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

HE_GUI_END_NAMESPACE
