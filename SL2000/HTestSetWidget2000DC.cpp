#include "HTestSetWidget2000DC_p.h"
#include "ui_HTestSetWidget2000DC.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QTimer>

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

QString HTestSetWidget2000DC::typeName()
{
    return "HTestSetWidget2000DC";
}

QVariant HTestSetWidget2000DC::handleOperation(QString type, QVariant value)
{
    if (type == "<启用光挡位>")
    {
        ui->comboBox_3->setEnabled(value.toBool());
        return true;
    }
    return HAbstractTestSetWidget::handleOperation(type, value);
}

void HTestSetWidget2000DC::handleAction(HActionType action)
{
    Q_D(HTestSetWidget2000DC);
    bool adjust = false;
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
        ui->doubleSpinBox_4->setValue(d->testData->data("[反向电压]").toDouble());
        break;
    case ACT_SET_GEARS_OUTPUT_CURRENT:
        ui->comboBox_2->setCurrentIndex(d->testData->data("[输出电流_档位]").toInt());
        break;
    case ACT_SET_LUMINOUS_GEARS:
        if (ui->comboBox_3->isEnabled() && !d->autoLuminousGears)
            ui->comboBox_3->setCurrentIndex(d->testData->data("[光档位]").toInt() + 1);
        break;
    case ACT_QUERY_STATE_TRIGGER:
        if (!d->testState)
            break;
        if (d->testData->data("[触发状态]").toInt() != 1)
            d->model->addAction(ACT_QUERY_STATE_TRIGGER, 50);
        else
            d->model->addAction(ACT_SINGLE_TEST, 100);
        break;
    case ACT_SINGLE_TEST:
        adjust = adjustIntegralTime();
        adjust = adjustLuminousGears() || adjust;
        if (adjust)
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
        adjustLuminousGears();
        if (d->testMode == 1 || d->testMode == 2)
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
        d->first = true;
        d->testData->handleOperation("<清空光谱采样缓存>");
        if (d->testMode == 0)
        {
            d->model->addAction(ACT_SINGLE_TEST);
        }
        else if (d->testMode == 4)
        {
            d->model->addAction(ACT_QUERY_STATE_TRIGGER);
        }
        else
        {
            d->testData->setData("[预配置测试]", true);
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
    ui->comboBox_1->setEnabled(!b);
    return true;
}

void HTestSetWidget2000DC::on_doubleSpinBox_1_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidget2000DC::on_doubleSpinBox_2_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    d->testData->setData("[输出电压]", value);
    d->model->addAction(ACT_SET_OUTPUT_VOLTAGE);
}

void HTestSetWidget2000DC::on_doubleSpinBox_3_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    d->testData->setData("[输出电流]", value);
    d->model->addAction(ACT_SET_OUTPUT_CURRENT);
}

void HTestSetWidget2000DC::on_doubleSpinBox_4_valueChanged(double value)
{
    Q_D(HTestSetWidget2000DC);
    d->testData->setData("[反向电压]", value);
    d->model->addAction(ACT_SET_REVERSE_VOLTAGE);
}

void HTestSetWidget2000DC::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidget2000DC);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidget2000DC::on_checkBox_2_clicked(bool b)
{
    setSaveMode(b ? 2 : 0);
}

void HTestSetWidget2000DC::on_comboBox_1_currentIndexChanged(int value)
{
    if (setTestMode(value))
    {
        ui->timeEdit_1->setEnabled(value == 2);
        ui->spinBox_1->setEnabled(value == 3);
    }
}

void HTestSetWidget2000DC::on_comboBox_2_currentIndexChanged(int value)
{
    Q_D(HTestSetWidget2000DC);
    d->testData->setData("[输出电流_档位]", value);
    d->testData->setData("[实测电流_档位]", value);
    d->model->addAction(ACT_SET_GEARS_OUTPUT_CURRENT);
    d->model->addAction(ACT_SET_OUTPUT_CURRENT);
}

void HTestSetWidget2000DC::on_comboBox_3_currentIndexChanged(int value)
{
    Q_D(HTestSetWidget2000DC);
    if (value == 0)
    {
        d->autoLuminousGears = true;
        return;
    }
    d->autoLuminousGears = false;
    d->testData->setData("[光档位]", value - 1);
    d->model->addAction(ACT_SET_LUMINOUS_GEARS);
}

bool HTestSetWidget2000DC::adjustIntegralTime()
{
    Q_D(HTestSetWidget2000DC);
    if (!d->autoIntegralTime || !d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

bool HTestSetWidget2000DC::adjustLuminousGears()
{
    Q_D(HTestSetWidget2000DC);
    if (!ui->comboBox_3->isEnabled() || !d->autoLuminousGears || !d->testData->handleOperation("<匹配光档位>").toBool())
        return false;
    d->model->addAction(ACT_SET_LUMINOUS_GEARS);
    return true;
}

void HTestSetWidget2000DC::init()
{
    Q_D(HTestSetWidget2000DC);
    int i;
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    HPluginHelper::initWidget("[反向电压]", ui->doubleSpinBox_4);
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->doubleSpinBox_2->setValue(d->testData->data("[输出电压]").toDouble());
    ui->doubleSpinBox_3->setValue(d->testData->data("[输出电流]").toDouble());
    ui->doubleSpinBox_4->setValue(d->testData->data("[反向电压]").toDouble());
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  ") << tr("  持续测试  ") << tr("  间隔测试  "));// << tr("  分选测试  "));

    for (i = 0; i < d->testData->data("[输出电流_档位数]").toInt(); i++)
        ui->comboBox_2->addItem(tr("  %1档  ").arg(i+1));
    ui->comboBox_3->addItem(tr("  自动  "));
    for (i = 0; i < d->testData->data("[光档位数]").toInt(); i++)
        ui->comboBox_3->addItem(tr("  %1档  ").arg(i+1));
    d->timerContinue = new QTimer(this);
    d->timerInterval = new QTimer(this);
    connect(d->timerContinue, &QTimer::timeout, this, [=] { setTestState(false); });
    connect(d->timerInterval, &QTimer::timeout, this, [=] { d->model->addAction(ACT_GET_SPECTRUM_ELEC); });
}

