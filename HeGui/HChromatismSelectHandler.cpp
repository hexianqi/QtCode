#include "HChromatismSelectHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/IChromatismCollection.h"
#include "HePlugin/HSelectDialog.h"
#include "HeController/IModel.h"

HE_BEGIN_NAMESPACE

HChromatismSelectHandler::HChromatismSelectHandler(QObject *parent) :
    HAbstractConfigHandler(*new HChromatismSelectHandlerPrivate, parent)
{
}

HChromatismSelectHandler::~HChromatismSelectHandler() = default;

QString HChromatismSelectHandler::typeName()
{
    return "HChromatismSelectHandler";
}

void HChromatismSelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HChromatismSelectHandler);
    auto data = d->configManage->chromatismCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptionals(data->keys());
    dlg.setCurrentText(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.currentText());
    d->model->addAction(ACT_RESET_CHROMATISM);
}

HE_END_NAMESPACE
