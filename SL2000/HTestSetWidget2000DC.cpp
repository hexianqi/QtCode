#include "HTestSetWidget2000DC_p.h"
#include "ui_HTestSetWidget2000DC.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/ITestSpec.h"
#include "HeData/ITestElec.h"
#include "HePlugin/HPluginHelper.h"

HTestSetWidget2000DCPrivate::HTestSetWidget2000DCPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
}

HTestSetWidget2000DC::HTestSetWidget2000DC(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget2000DCPrivate, parent),
    ui(new Ui::HTestSetWidget2000DC)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget2000DC::~HTestSetWidget2000DC()
{
    delete ui;
}

void HTestSetWidget2000DC::initialize(QVariantMap /*param*/)
{

}

QString HTestSetWidget2000DC::typeName()
{
    return "HTestSetWidget2000DC";
}

void HTestSetWidget2000DC::handleAction(HActionType action)
{
    Q_D(HTestSetWidget2000DC);
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_SET_OUTPUT_VOLTAGE:
        ui->doubleSpinBox_2->setValue(d->testData->data("[输出电压]").toDouble());
        break;
    case ACT_SET_OUTPUT_CURRENT:
        ui->doubleSpinBox_3->setValue(d->testData->data("[输出电流]").toDouble());
        break;
    case ACT_SET_REVERSE_VOLTAGE:
        ui->doubleSpinBox_3->setValue(d->testData->data("[反向电压]").toDouble());
        break;
    case ACT_SINGLE_TEST:
        if (!d->testState)
            break;
        if (adjustIntegralTime())
            d->model->addAction(ACT_SINGLE_TEST);
        else
            setTestState(false);
        break;
    case ACT_GET_SPECTRUM_ELEC:
        if (!d->testState)
            break;
        adjustIntegralTime();
        d->model->addAction(ACT_GET_SPECTRUM_ELEC, 100);
        break;
    default:
        break;
    }
}

bool HTestSetWidget2000DC::setTestState(bool b)
{
    Q_D(HTestSetWidget2000DC);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;
    if (b)
    {
        d->testSpec->clearCache();
        if (d->testMode == 0)
            d->model->addAction(ACT_SINGLE_TEST);
        if (d->testMode == 1)
        {
            d->testElec->setData("[电源模式]", 1);
            d->model->addAction(ACT_SET_SOURCE_MODE);
            d->model->addAction(ACT_GET_SPECTRUM_ELEC);
        }
    }
    else
    {
        if (d->testMode == 1)
        {
            d->testElec->setData("[电源模式]", 0);
            d->model->addAction(ACT_SET_SOURCE_MODE);
        }
    }
    return true;
}

void HTestSetWidget2000DC::on_doubleSpinBox_1_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testSpec->setIntegralTime(value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidget2000DC::on_doubleSpinBox_2_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    d->testElec->setParam(OutputVoltage, value);
    d->model->addAction(ACT_SET_OUTPUT_VOLTAGE);
}

void HTestSetWidget2000DC::on_doubleSpinBox_3_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    d->testElec->setParam(OutputCurrent, value);
    d->model->addAction(ACT_SET_OUTPUT_CURRENT);
}

void HTestSetWidget2000DC::on_doubleSpinBox_4_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    d->testElec->setParam(ReverseVoltage, value);
    d->model->addAction(ACT_SET_REVERSE_VOLTAGE);
}

void HTestSetWidget2000DC::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidget2000DC);
    if (d->integralTimeAuto == b)
        return;
    d->integralTimeAuto = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidget2000DC::on_comboBox_1_currentIndexChanged(int value)
{
    setTestMode(value);
}

bool HTestSetWidget2000DC::adjustIntegralTime()
{
    Q_D(HTestSetWidget2000DC);
    if (!d->integralTimeAuto)
        return false;
    if (!d->testSpec->adjustIntegralTime())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HTestSetWidget2000DC::init()
{
    Q_D(HTestSetWidget2000DC);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    HPluginHelper::initWidget("[反向电压]", ui->doubleSpinBox_4);
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->doubleSpinBox_2->setValue(d->testData->data("[输出电压]").toDouble());
    ui->doubleSpinBox_3->setValue(d->testData->data("[输出电流]").toDouble());
    ui->doubleSpinBox_4->setValue(d->testData->data("[反向电压]").toDouble());
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  "));
}

