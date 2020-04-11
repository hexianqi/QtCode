#include "HChromatismEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HChromatismEditWidget.h"
#include "HeData/IConfigManage.h"
#include "HeData/IChromatismCollection.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HChromatismEditHandler::HChromatismEditHandler(QObject *parent) :
    HAbstractConfigHandler(*new HChromatismEditHandlerPrivate, parent)
{
}

HChromatismEditHandler::~HChromatismEditHandler()
{
    qDebug() << __func__;
}

void HChromatismEditHandler::initialize(QVariantMap /*param*/)
{
}

QString HChromatismEditHandler::typeName()
{
    return "HChromatismEditHandler";
}

void HChromatismEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HChromatismEditHandler);
    HDataDetail<IChromatism> detail;
    detail.setEditWidget(new HChromatismEditWidget);
    detail.setData(d->configManage->chromatismCollection());
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("色容差数据配置"));
    dlg.setDataDetail(&detail);
    dlg.resize(1000, 600);
    dlg.exec();
    d->model->addAction(ACT_RESET_CHROMATISM);
}

HE_GUI_END_NAMESPACE
