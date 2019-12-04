#include "HElecCalibrateHandler_p.h"
#include "IMainWindow.h"
#include "HElecCalibrateDialog.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HElecCalibrateHandler::HElecCalibrateHandler(QObject *parent) :
    HAbstractGuiHandler(*new HElecCalibrateHandlerPrivate, parent)
{
}

HElecCalibrateHandler::HElecCalibrateHandler(HElecCalibrateHandlerPrivate &p, QObject *parent) :
    HAbstractGuiHandler(p, parent)
{
}

HElecCalibrateHandler::~HElecCalibrateHandler()
{
    qDebug() << __func__;
}

void HElecCalibrateHandler::initialize(QVariantMap /*param*/)
{

}

QString HElecCalibrateHandler::typeName()
{
    return "HElecCalibrateHandler";
}

void HElecCalibrateHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HElecCalibrateHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)
    HElecCalibrateDialog dlg(d->mainWindow);
    d->mainWindow->openDialog(&dlg);
    d->model->addAction(ACT_RESET_ELEC);
}

HE_GUI_END_NAMESPACE
