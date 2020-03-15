#include "HAdjustSelectHandler_p.h"
#include "IMainWindow.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjustCollection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustSelectHandlerPrivate::HAdjustSelectHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HAdjustSelectHandler::HAdjustSelectHandler(QObject *parent) :
    HAbstractGuiHandler(*new HAdjustSelectHandlerPrivate, parent)
{
}

HAdjustSelectHandler::~HAdjustSelectHandler()
{
    qDebug() << __func__;
}

void HAdjustSelectHandler::initialize(QVariantMap /*param*/)
{
}

QString HAdjustSelectHandler::typeName()
{
    return "HAdjustSelectHandler";
}

void HAdjustSelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAdjustSelectHandler);
    auto data = d->configManage->adjustCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptionals(data->keys());
    dlg.setSelected(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.selected());
    d->model->addAction(ACT_RESET_GRADE);
}

HE_GUI_END_NAMESPACE
