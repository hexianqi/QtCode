#include "HQualityEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HQualityEditWidget.h"
#include "HeData/IConfigManage.h"
#include "HeData/IQualityCollection.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HQualityEditHandler::HQualityEditHandler(QObject *parent) :
    HAbstractConfigHandler(*new HQualityEditHandlerPrivate, parent)
{
}

HQualityEditHandler::~HQualityEditHandler()
{
    qDebug() << __func__;
}

QString HQualityEditHandler::typeName()
{
    return "HQualityEditHandler";
}

void HQualityEditHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HQualityEditHandler);
    HDataDetail<IQuality> detail;
    detail.setEditer(new HQualityEditWidget);
    detail.setData(d->configManage->qualityCollection());
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("品质数据配置"));
    dlg.setDataDetail(&detail);
    dlg.resize(1200, 600);
    dlg.exec();
    d->model->addAction(ACT_RESET_QUALITY);
}

HE_GUI_END_NAMESPACE
