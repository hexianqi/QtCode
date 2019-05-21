#include "HChromatismSelectHandler_p.h"
#include "IMainWindow.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IChromatismCollection.h"
#include "HePlugin/HSelectDialog.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HChromatismSelectHandlerPrivate::HChromatismSelectHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HChromatismSelectHandler::HChromatismSelectHandler(QObject *parent) :
    HAbstractGuiHandler(*new HChromatismSelectHandlerPrivate, parent)
{
}

HChromatismSelectHandler::~HChromatismSelectHandler()
{
    qDebug() << __func__;
}

void HChromatismSelectHandler::initialize(QVariantMap /*param*/)
{
}

QString HChromatismSelectHandler::typeName()
{
    return "HChromatismSelectHandler";
}

void HChromatismSelectHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HChromatismSelectHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)

    auto data = d->configManage->chromatismCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptionals(data->keys());
    dlg.setSelected(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.selected());
    d->model->addAction(ACT_RESET_CHROMATISM);
}

HE_GUI_END_NAMESPACE
