#include "HExportDeviceHandler_p.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HExportDeviceHandler::HExportDeviceHandler(QObject *parent) :
    HAbstractConfigHandler(*new HExportDeviceHandlerPrivate, parent)
{
}

HExportDeviceHandler::~HExportDeviceHandler()
{
    qDebug() << __func__;
}

void HExportDeviceHandler::initialize(QVariantMap /*param*/)
{

}

QString HExportDeviceHandler::typeName()
{
    return "HExportDeviceHandler";
}

void HExportDeviceHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HExportDeviceHandler);
    d->model->addAction(ACT_SET_RAM);
}

HE_GUI_END_NAMESPACE
