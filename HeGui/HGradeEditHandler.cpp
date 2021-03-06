#include "HGradeEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HDataDetail.h"
#include "HGradeEditWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeController/IModel.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeEditHandlerPrivate::HGradeEditHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HGradeEditHandler::HGradeEditHandler(QObject *parent) :
    HAbstractGuiHandler(*new HGradeEditHandlerPrivate, parent)
{
}

HGradeEditHandler::~HGradeEditHandler()
{
    qDebug() << __func__;
}

void HGradeEditHandler::initialize(QVariantMap /*param*/)
{
}

QString HGradeEditHandler::typeName()
{
    return "HGradeEditHandler";
}

void HGradeEditHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HGradeEditHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)
    auto detail = new HDataDetail<IGrade>();
    detail->setEditWidget(new HGradeEditWidget);
    detail->setData(d->configManage->gradeCollection());
    HListCollectionDialog dlg(d->mainWindow);
    dlg.setWindowTitle(tr("分级数据配置"));
    dlg.setDataDetail(detail);
    dlg.resize(1000, 600);
    dlg.exec();
    d->model->addAction(ACT_RESET_GRADE);
}

HE_GUI_END_NAMESPACE
