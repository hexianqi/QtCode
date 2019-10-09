#include "HTestSetWidgetDemo_p.h"
#include "ui_HTestSetWidgetDemo.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/ITestSpec.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HTestSetWidgetDemoPrivate::HTestSetWidgetDemoPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HTestSetWidgetDemo::HTestSetWidgetDemo(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidgetDemoPrivate, parent),
    ui(new Ui::HTestSetWidgetDemo)
{
    ui->setupUi(this);
    init();
}

HTestSetWidgetDemo::~HTestSetWidgetDemo()
{
    qDebug() << __func__;
    delete ui;
}

void HTestSetWidgetDemo::initialize(QVariantMap /*param*/)
{

}

QString HTestSetWidgetDemo::typeName()
{
    return "HTestSetWidgetDemo";
}

void HTestSetWidgetDemo::handleAction(HActionType action)
{
    Q_D(HTestSetWidgetDemo);
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_SET_SPECTRUM_AVG_TIMES:
        ui->spinBox_1->setValue(d->testData->data("[光谱平滑次数]").toInt());
        ui->spinBox_2->setValue(d->testData->data("[光谱平滑范围]").toInt());
        break;
    case ACT_GET_SPECTRUM:
    case ACT_GET_SPECTRUM_ENERGY:
        if (!d->testState)
            break;
        if (d->testMode == 0)
        {
            setTestState(false);
            break;
        }
        if (d->integralTimeAuto && d->testSpec->adjustIntegralTime())
            d->model->addAction(ACT_SET_INTEGRAL_TIME);
        d->model->addAction(d->energy ? ACT_GET_SPECTRUM_ENERGY : ACT_GET_SPECTRUM, 100);
        break;
    default:
        break;
    }
}

bool HTestSetWidgetDemo::setTestState(bool b)
{
    Q_D(HTestSetWidgetDemo);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;
    if (b)
    {
        d->testSpec->clearCache();
        d->model->addAction(d->energy ? ACT_GET_SPECTRUM_ENERGY : ACT_GET_SPECTRUM);
    }
    return true;
}

void HTestSetWidgetDemo::on_doubleSpinBox_1_valueChanged(double value)
{
    Q_D(HTestSetWidgetDemo);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testSpec->setIntegralTime(value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidgetDemo::on_spinBox_1_valueChanged(int value)
{
    Q_D(HTestSetWidgetDemo);
    if (value == d->testData->data("[光谱平滑次数]").toInt())
        return;
    d->testSpec->setData("[光谱平滑次数]", value);
    d->model->addAction(ACT_SET_SPECTRUM_AVG_TIMES);
}

void HTestSetWidgetDemo::on_spinBox_2_valueChanged(int value)
{
    Q_D(HTestSetWidgetDemo);
    if (value == d->testData->data("[光谱平滑范围]").toInt())
        return;
    d->testSpec->setData("[光谱平滑范围]", value);
    d->model->addAction(ACT_SET_SPECTRUM_AVG_TIMES);
}

void HTestSetWidgetDemo::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidgetDemo);
    if (d->integralTimeAuto == b)
        return;
    d->integralTimeAuto = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidgetDemo::on_checkBox_2_clicked(bool b)
{
    Q_D(HTestSetWidgetDemo);
    if (d->energy == b)
        return;
    d->energy = b;
}

void HTestSetWidgetDemo::on_comboBox_1_currentIndexChanged(int value)
{
    setTestMode(value);
}

void HTestSetWidgetDemo::init()
{
    Q_D(HTestSetWidgetDemo);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[光谱平滑次数]", ui->spinBox_1);
    HPluginHelper::initWidget("[光谱平滑范围]", ui->spinBox_2);
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->spinBox_1->setValue(2);
    ui->spinBox_2->setValue(2);
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  "));
}
