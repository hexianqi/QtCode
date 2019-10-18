#include "HSpecCalibrateDialog_p.h"
#include "IGuiFactory.h"
#include "HSpecCalibrateWidget.h"
#include "HSpecCalibrateSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecCalibrateDialogPrivate::HSpecCalibrateDialogPrivate()
{
    factory = HAppContext::getContextPointer<IGuiFactory>("IGuiFactory");
    type = HAppContext::getContextValue<QString>("SpecCalibrateType");
    if (type.isEmpty())
        type = "HSpecCalibrateSetWidget";
}

HSpecCalibrateDialog::HSpecCalibrateDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HSpecCalibrateDialogPrivate)
{
    init();
}

HSpecCalibrateDialog::~HSpecCalibrateDialog()
{
    qDebug() << __func__;
}

void HSpecCalibrateDialog::done(int result)
{
    d_ptr->widget->stop();
    QDialog::done(result);
}

void HSpecCalibrateDialog::init()
{
    auto calibrate = HAppContext::getContextPointer<IConfigManage>("IConfigManage")->specCalibrate("1");
    auto layout = new QGridLayout(this);
    auto set = d_ptr->factory->createTestSetWidget(d_ptr->type);
    d_ptr->widget = new HSpecCalibrateWidget;
    d_ptr->widget->setTestSetWidget(set);
    d_ptr->widget->setCalibrate(calibrate);
    d_ptr->widget->start();
    layout->addWidget(d_ptr->widget);
}

HE_GUI_END_NAMESPACE
