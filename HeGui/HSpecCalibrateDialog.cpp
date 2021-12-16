#include "HSpecCalibrateDialog_p.h"
#include "HSpecCalibrateWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include <QtWidgets/QGridLayout>

HE_BEGIN_NAMESPACE

HSpecCalibrateDialog::HSpecCalibrateDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HSpecCalibrateDialogPrivate)
{
    init();
}

HSpecCalibrateDialog::~HSpecCalibrateDialog() = default;

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
    d_ptr->widget->setCalibrate(calibrate);
    d_ptr->widget->start();
    layout->addWidget(d_ptr->widget);
    setMinimumSize(745, 436);
    setWindowTitle(tr("光谱参数定标"));
}

HE_END_NAMESPACE
