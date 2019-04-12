#include "HSpecCalibrateDialog_p.h"
#include "HSpecCalibrateWidget.h"
#include "HSpecCalibrateSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include <QGridLayout>

HE_GUI_BEGIN_NAMESPACE

HSpecCalibrateDialog::HSpecCalibrateDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HSpecCalibrateDialogPrivate)
{
    init();
}

HSpecCalibrateDialog::~HSpecCalibrateDialog()
{

}

void HSpecCalibrateDialog::done(int result)
{
    d_ptr->widget->stop();
    QDialog::done(result);
}

void HSpecCalibrateDialog::init()
{
    auto config = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    auto layout = new QGridLayout(this);
    d_ptr->widget = new HSpecCalibrateWidget;
    d_ptr->widget->setTestSetWidget(new HSpecCalibrateSetWidget);
    d_ptr->widget->setSpecCalibrate(config->specCalibrate("1"));
    layout->addWidget(d_ptr->widget);
    d_ptr->widget->start();
}

HE_GUI_END_NAMESPACE
