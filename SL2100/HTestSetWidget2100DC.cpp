#include "HTestSetWidget2100DC_p.h"
#include "ui_HTestSetWidget2100DC.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QTimer>

HTestSetWidget2100DC::HTestSetWidget2100DC(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget2100DCPrivate, parent),
    ui(new Ui::HTestSetWidget2100DC)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget2100DC::~HTestSetWidget2100DC()
{
    delete ui;
}

QString HTestSetWidget2100DC::typeName()
{
    return "HTestSetWidget2100DC";
}

void HTestSetWidget2100DC::handleAction(HActionType action)
{
    Q_D(HTestSetWidget2100DC);
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
    case ACT_SINGLE_TEST:
        if (adjustIntegralTime())
        {
            d->model->addAction(ACT_SINGLE_TEST);
            break;
        }
        emit resultChanged(action, true);
        if (!d->testState)
            break;
        if (d->testMode == 4)
            d->model->addAction(ACT_QUERY_STATE_TRIGGER);
        else
            setTestState(false);
        break;
    case ACT_GET_SPECTRUM_ELEC:
        emit resultChanged(action, d->testMode == 3 || d->first);
        d->first = false;
        if (!d->testState)
            break;
        adjustIntegralTime();
        if (d->testMode == 1 || d->testMode == 2)
            d->model->addAction(ACT_GET_SPECTRUM_ELEC, 100);
        break;
    default:
        break;
    }
}

bool HTestSetWidget2100DC::setTestState(bool b)
{
    Q_D(HTestSetWidget2100DC);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;

    if (b)
    {
        d->first = true;
        d->testData->handleOperation("<清空光谱采样缓存>");
        if (d->testMode == 0)
        {
            d->model->addAction(ACT_SINGLE_TEST);
        }
        else
        {
            d->testData->setData("[电源模式]", 1);
            d->model->addAction(ACT_SET_SOURCE_MODE);
            if (d->testMode == 1)
            {
                d->model->addAction(ACT_GET_SPECTRUM_ELEC);
            }
            if (d->testMode == 2)
            {
                auto t = ui->timeEdit_1->time();
                d->model->addAction(ACT_GET_SPECTRUM_ELEC);
                d->timerContinue->start((t.hour() * 3600 + t.minute() * 60 + t.second()) * 1000);
            }
            if (d->testMode == 3)
            {
                d->timerInterval->start(ui->spinBox_1->value() * 1000);
            }
        }
    }
    else
    {
        if (d->testMode >= 1 && d->testMode <= 3)
        {
            d->timerContinue->stop();
            d->timerInterval->stop();
            d->testData->setData("[电源模式]", 0);
            d->model->addAction(ACT_SET_SOURCE_MODE, 200);
        }
    }
    return true;
}

void HTestSetWidget2100DC::on_doubleSpinBox_1_valueChanged(double value)
{
    Q_D(HTestSetWidget2100DC);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidget2100DC::on_doubleSpinBox_2_valueChanged(double value)
{
    Q_D(HTestSetWidget2100DC);
    d->testData->setData("[输出电压]", value);
    d->model->addAction(ACT_SET_OUTPUT_VOLTAGE);
}

void HTestSetWidget2100DC::on_doubleSpinBox_3_valueChanged(double value)
{
    Q_D(HTestSetWidget2100DC);
    d->testData->setData("[输出电流]", value);
    d->model->addAction(ACT_SET_OUTPUT_CURRENT);
}

void HTestSetWidget2100DC::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidget2100DC);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidget2100DC::on_comboBox_1_currentIndexChanged(int value)
{
    if (setTestMode(value))
    {
        ui->timeEdit_1->setEnabled(value == 2);
        ui->spinBox_1->setEnabled(value == 3);
    }
}

bool HTestSetWidget2100DC::adjustIntegralTime()
{
    Q_D(HTestSetWidget2100DC);
    if (!d->autoIntegralTime)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HTestSetWidget2100DC::init()
{
    Q_D(HTestSetWidget2100DC);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    HPluginHelper::initWidget("[测试间隔]", ui->spinBox_1);
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->doubleSpinBox_2->setValue(d->testData->data("[输出电压]").toDouble());
    ui->doubleSpinBox_3->setValue(d->testData->data("[输出电流]").toDouble());
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  ") << tr("  持续测试  ") << tr("  间隔测试  "));
    d->timerContinue = new QTimer(this);
    d->timerInterval = new QTimer(this);
    connect(d->timerContinue, &QTimer::timeout, this, [=] { setTestState(false); });
    connect(d->timerInterval, &QTimer::timeout, this, [=] { d->model->addAction(ACT_GET_SPECTRUM_ELEC); });
}
