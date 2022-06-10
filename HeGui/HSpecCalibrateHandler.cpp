#include "HSpecCalibrateHandler_p.h"
#include "IMainWindow.h"
#include "HDecoratorDialog.h"
#include "HSpecCalibrateWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HSpecCalibrateHandler::HSpecCalibrateHandler(QObject *parent) :
    HAbstractConfigHandler(*new HSpecCalibrateHandlerPrivate, parent)
{
}

HSpecCalibrateHandler::~HSpecCalibrateHandler() = default;

QString HSpecCalibrateHandler::typeName()
{
    return "HSpecCalibrateHandler";
}

void HSpecCalibrateHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HSpecCalibrateHandler);
    auto calibrate = HAppContext::getContextPointer<IConfigManage>("IConfigManage")->specCalibrate("1");
    auto w = new HDecoratorDialog(d->mainWindow);
    auto t = new HSpecCalibrateWidget;
    t->setCalibrate(calibrate);
    t->setWindowTitle(tr("光谱参数定标"));
    w->run(t);
    d->model->addAction(ACT_RESET_SPECTRUM);
}

HE_END_NAMESPACE
