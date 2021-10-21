#include "HLoginOutHandler_p.h"
#include "IMainWindow.h"
#include <QtWidgets/QMessageBox>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HLoginOutHandler::HLoginOutHandler(QObject *parent) :
    HAbstractGuiHandler(*new HLoginOutHandlerPrivate, parent)
{
}

HLoginOutHandler::~HLoginOutHandler()
{
    qDebug() << __func__;
}

QString HLoginOutHandler::typeName()
{
    return "HLoginOutHandler";
}

void HLoginOutHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HLoginOutHandler);
    if (QMessageBox::question(d->mainWindow, tr("提示"), tr("是否要登出？")) == QMessageBox::Yes)
        d->mainWindow->setAuthority(0);
}


HE_GUI_END_NAMESPACE
