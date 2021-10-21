#include "HGradeSelectHandler_p.h"
#include "IMainWindow.h"
#include "HeData/IConfigManage.h"
#include "HeData/IGradeCollection.h"
#include "HeController/IModel.h"
#include "HePlugin/HSelectDialog.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGradeSelectHandler::HGradeSelectHandler(QObject *parent) :
    HAbstractConfigHandler(*new HGradeSelectHandlerPrivate, parent)
{
}

HGradeSelectHandler::~HGradeSelectHandler()
{
    qDebug() << __func__;
}

QString HGradeSelectHandler::typeName()
{
    return "HGradeSelectHandler";
}

void HGradeSelectHandler::execute(QObject */*sender*/, QVariantMap /*param*/)
{
    Q_D(HGradeSelectHandler);
    auto data = d->configManage->gradeCollection();
    if (data == nullptr || data->keys().size() < 2)
        return;
    HSelectDialog dlg(d->mainWindow);
    dlg.setOptionals(data->keys());
    dlg.setCurrentText(data->useIndex());
    if (!dlg.exec())
        return;
    data->setUseIndex(dlg.currentText());
    d->model->addAction(ACT_RESET_GRADE);
}

HE_GUI_END_NAMESPACE
