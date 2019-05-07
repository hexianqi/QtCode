#include "HGradeEditHandler_p.h"
#include "IMainWindow.h"
#include "HListCollectionDialog.h"
#include "HGradeDetailWidget.h"
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
    auto widget = new HGradeDetailWidget();
    widget->setData(d->configManage->gradeCollection());
    HListCollectionDialog dlg;
    dlg.setWindowTitle(tr("分级数据配置"));
    dlg.setDataDetailWidget(widget);
    dlg.resize(1000, 600);
    dlg.exec();
    d->model->addAction(ACT_RESET_GRADE);
}

HE_GUI_END_NAMESPACE
