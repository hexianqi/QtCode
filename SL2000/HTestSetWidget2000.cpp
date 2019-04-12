#include "HTestSetWidget2000_p.h"
#include "ui_HTestSetWidget2000.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeController/ITestSpec.h"
#include "HePlugin/HPluginHelper.h"

HTestSetWidget2000Private::HTestSetWidget2000Private()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HTestSetWidget2000::HTestSetWidget2000(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget2000Private, parent),
    ui(new Ui::HTestSetWidget2000)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget2000::~HTestSetWidget2000()
{
    delete ui;
}

QString HTestSetWidget2000::typeName()
{
    return "HTestSetWidget2000";
}

void HTestSetWidget2000::handleAction(HActionType action)
{
    Q_D(HTestSetWidget2000);
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_GET_SPECTRUM:
        if (!d->testState)
            break;
        if (d->testMode == 0)
        {
            setTestState(false);
            break;
        }
        if (d->integralTimeAuto && d->testSpec->adjustIntegralTime())
            d->model->addAction(ACT_SET_INTEGRAL_TIME);
        d->model->addAction(ACT_GET_SPECTRUM, 100);
        break;
    default:
        break;
    }
}

bool HTestSetWidget2000::setTestState(bool b)
{
    Q_D(HTestSetWidget2000);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;
    if (b)
    {
        d->testSpec->clearCache();
        d->model->addAction(ACT_GET_SPECTRUM);
    }
    return true;
}

void HTestSetWidget2000::on_doubleSpinBox_1_editingFinished()
{
    Q_D(HTestSetWidget2000);
    auto value = ui->doubleSpinBox_1->value();
    d->testSpec->setIntegralTime(value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidget2000::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidget2000);
    if (d->integralTimeAuto == b)
        return;
    d->integralTimeAuto = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidget2000::on_comboBox_1_currentIndexChanged(int value)
{
    setTestMode(value);
}

void HTestSetWidget2000::init()
{
    Q_D(HTestSetWidget2000);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  "));
}

