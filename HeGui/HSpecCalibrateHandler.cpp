#include "HSpecCalibrateHandler_p.h"
#include "IMainWindow.h"
#include "HSpecCalibrateDialog.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecCalibrateHandler::HSpecCalibrateHandler(QObject *parent) :
    HAbstractConfigHandler(*new HSpecCalibrateHandlerPrivate, parent)
{
}

HSpecCalibrateHandler::~HSpecCalibrateHandler()
{
    qDebug() << __func__;
}

void HSpecCalibrateHandler::initialize(QVariantMap /*param*/)
{
}

QString HSpecCalibrateHandler::typeName()
{
    return "HSpecCalibrateHandler";
}

void HSpecCalibrateHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HSpecCalibrateHandler);
    HSpecCalibrateDialog dlg(d->mainWindow);
    d->mainWindow->openDialog(&dlg);
    d->model->addAction(ACT_RESET_SPECTRUM);
}

HE_GUI_END_NAMESPACE
