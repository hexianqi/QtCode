#include "HGradeSelectHandler_p.h"
#include "IMainWindow.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeSelectHandlerPrivate::HGradeSelectHandlerPrivate()
{
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
}

HGradeSelectHandler::HGradeSelectHandler(QObject *parent) :
    HAbstractGuiHandler(*new HGradeSelectHandlerPrivate, parent)
{
}

HGradeSelectHandler::~HGradeSelectHandler()
{
    qDebug() << __func__;
}

void HGradeSelectHandler::initialize(QVariantMap /*param*/)
{
}

QString HGradeSelectHandler::typeName()
{
    return "HGradeSelectHandler";
}

void HGradeSelectHandler::execute(QObject *sender, QVariantMap param)
{
    Q_D(HGradeSelectHandler);
    Q_UNUSED(sender)
    Q_UNUSED(param)

    auto data = d->configManage->gradeCollection();
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
