#include "HAdjustEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HAdjustEditWidget.h"
#include "HeData/IConfigManage.h"
#include "HeData/IAdjustCollection.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAdjustEditHandler::HAdjustEditHandler(QObject *parent) :
    HAbstractConfigHandler(*new HAdjustEditHandlerPrivate, parent)
{
}

HAdjustEditHandler::~HAdjustEditHandler()
{
    qDebug() << __func__;
}

void HAdjustEditHandler::initialize(QVariantMap /*param*/)
{
}

QString HAdjustEditHandler::typeName()
{
    return "HAdjustEditHandler";
}

void HAdjustEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HAdjustEditHandler);
    HDataDetail<IAdjust> detail;
    detail.setEditWidget(new HAdjustEditWidget);
    detail.setData(d->configManage->adjustCollection());
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("调整数据配置"));
    dlg.setDataDetail(&detail);
    d->mainWindow->openDialog(&dlg);
    d->model->addAction(ACT_RESET_ADJUST);
}

HE_GUI_END_NAMESPACE
