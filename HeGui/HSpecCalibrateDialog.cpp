#include "HSpecCalibrateDialog_p.h"
#include "HSpecCalibrateWidget.h"
#include "HSpecCalibrateSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include <QtWidgets/QGridLayout>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

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
    d_ptr->widget = new HSpecCalibrateWidget;
    d_ptr->widget->setTestSetWidget(new HSpecCalibrateSetWidget);
    d_ptr->widget->setSpecCalibrate(calibrate);
    layout->addWidget(d_ptr->widget);
    d_ptr->widget->start();
}

HE_GUI_END_NAMESPACE
