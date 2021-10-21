#include "HSpecLuminousHandler_p.h"
#include "IMainWindow.h"
#include "HSpecLuminousDialog.h"
#include "HeData/IConfigManage.h"
#include "HeData/ISpecCalibrate.h"
#include "HeData/HSpecLuminous.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecLuminousHandler::HSpecLuminousHandler(QObject *parent) :
    HAbstractConfigHandler(*new HSpecLuminousHandlerPrivate, parent)
{
}

HSpecLuminousHandler::~HSpecLuminousHandler()
{
    qDebug() << __func__;
}

QString HSpecLuminousHandler::typeName()
{
    return "HSpecLuminousHandler";
}

void HSpecLuminousHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HSpecLuminousHandler);
    HSpecLuminousDialog dlg(d->mainWindow);
    dlg.setData(dynamic_cast<HSpecLuminous *>(d->configManage->specCalibrate("1")->item(Luminous)));
    dlg.exec();
}

HE_GUI_END_NAMESPACE
