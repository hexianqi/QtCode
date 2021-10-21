#include "HAdjust2SelectHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjust2Collection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjust2SelectHandler::HAdjust2SelectHandler(QObject *parent) :
    HAbstractConfigHandler(*new HAdjust2SelectHandlerPrivate, parent)
{
}

HAdjust2SelectHandler::~HAdjust2SelectHandler()
{
    qDebug() << __func__;
}

QString HAdjust2SelectHandler::typeName()
{
    return "HAdjust2SelectHandler";
}

void HAdjust2SelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAdjust2SelectHandler);
    auto data = d->configManage->adjust2Collection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptionals(data->keys());
    dlg.setCurrentText(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.currentText());
    d->model->addAction(ACT_RESET_ADJUST);
}

HE_GUI_END_NAMESPACE
