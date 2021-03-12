#include "HAdjust2EditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HAdjust2EditWidget.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjust2Collection.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjust2EditHandler::HAdjust2EditHandler(QObject *parent) :
    HAbstractConfigHandler(*new HAdjust2EditHandlerPrivate, parent)
{
}

HAdjust2EditHandler::~HAdjust2EditHandler()
{
    qDebug() << __func__;
}

void HAdjust2EditHandler::initialize(QVariantMap /*param*/)
{
}

QString HAdjust2EditHandler::typeName()
{
    return "HAdjust2EditHandler";
}

void HAdjust2EditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAdjust2EditHandler);
    HDataDetail<IAdjust2> detail;
    detail.setEditWidget(new HAdjust2EditWidget);
    detail.setData(d->configManage->adjust2Collection());
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("调整数据配置"));
    dlg.setDataDetail(&detail);
    dlg.setMinimumSize(1200, 600);
    d->mainWindow->openDialog(&dlg);
    d->model->addAction(ACT_RESET_ADJUST);
}

HE_GUI_END_NAMESPACE
