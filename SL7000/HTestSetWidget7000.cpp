#include "HTestSetWidget7000_p.h"
#include "ui_HTestSetWidget7000.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"

HTestSetWidget7000::HTestSetWidget7000(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget7000Private, parent),
    ui(new Ui::HTestSetWidget7000)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget7000::~HTestSetWidget7000()
{
    delete ui;
}

QString HTestSetWidget7000::typeName()
{
    return "HTestSetWidget7000";
}

QVariant HTestSetWidget7000::handleOperation(QString type, QVariant value)
{
    Q_D(HTestSetWidget7000);
    if (type == "<启用光挡位>")
    {
        auto b = value.toBool();
        ui->comboBox_2->setEnabled(b);
        ui->comboBox_3->setEnabled(b);
        return true;
    }
    if (type == "<设置布局>")
    {
        d->polygon = value.value<QPolygon>();
        ui->comboBox_4->blockSignals(true);
        ui->comboBox_4->clear();
        ui->comboBox_4->addItem(tr("  原点  "), QPoint(99, 99));
        for (auto p : d->polygon)
            ui->comboBox_4->addItem(QString("  %1, %2  ").arg(p.x()).arg(p.y()), p);
        ui->comboBox_4->blockSignals(false);
        return true;
    }
    return HAbstractTestSetWidget::handleOperation(type, value);
}

void HTestSetWidget7000::handleAction(HActionType action)
{
    Q_D(HTestSetWidget7000);
    QPoint point;
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
        ui->comboBox_5->setCurrentIndex(d->testData->data("[输出电流_档位]").toInt());
        break;
    case ACT_SET_LUMINOUS_TYPE:
        if (ui->comboBox_2->isEnabled())
            ui->comboBox_2->setCurrentIndex(d->testData->data("[光测试类型]").toInt());
        break;
    case ACT_SET_LUMINOUS_GEARS:
        if (ui->comboBox_3->isEnabled() && !d->autoLuminousGears)
            ui->comboBox_3->setCurrentIndex(d->testData->data("[光档位]").toInt() + 1);
        break;
    case ACT_SET_MOTOR_LOCATION:
        point = d->testData->data("[电机定位]").toPoint();
        ui->comboBox_4->setCurrentIndex(d->polygon.indexOf(point) + 1);
        d->model->addAction(ACT_QUERY_MOTOR_STATE);
        break;
    case ACT_RESET_MOTOR_LOCATION:
        ui->comboBox_4->setCurrentIndex(0);
//        d->model->addAction(ACT_QUERY_MOTOR_STATE);
        break;
    case ACT_QUERY_MOTOR_STATE:
        if (d->testData->data("[电机状态]").toInt() == 1)
        {
            if (d->testState && d->testMode == 2)
            {
                if (d->prepare)
                {
                    d->prepare = false;
                    d->model->addAction(ACT_QUERY_NEXT_TEST);
                }
                else
                    d->model->addAction(ACT_SINGLE_TEST);
            }
        }
        else
            d->model->addAction(ACT_QUERY_MOTOR_STATE, 50);
        break;
    case ACT_SET_MOTOR_PREPARE_TEST:
        d->prepare = true;
        d->model->addAction(ACT_QUERY_MOTOR_STATE, 50);
        break;
    case ACT_SINGLE_TEST:
        if (!d->testState)
            break;
        emit resultChanged(action, false);
        if (d->testMode == 2)
            d->model->addAction(ACT_QUERY_NEXT_TEST);
        else
            setTestState(false);
        break;
    case ACT_INTEGRATE_TEST:
        emit resultChanged(action, false);
        if (!d->testState)
            break;
        adjustIntegralTime();
        adjustLuminousGears();
        d->model->addAction(ACT_INTEGRATE_TEST, 100);
        break;
    default:
        break;
    }
}

bool HTestSetWidget7000::setTestState(bool b)
{
    Q_D(HTestSetWidget7000);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;

    if (b)
    {
        d->testData->handleOperation("<清空光谱采样缓存>");
        if (d->testMode == 0)
        {
            d->model->addAction(ACT_SINGLE_TEST);
        }
        if (d->testMode == 1)
        {
            d->testData->setData("[预配置测试]", true);
            d->model->addAction(ACT_INTEGRATE_TEST);
        }
        if (d->testMode == 2)
        {
            d->model->addAction(ACT_SET_MOTOR_PREPARE_TEST);
        }
    }
    else
    {
        if (d->testMode == 1)
            setTestData("[电源模式]", 0, ACT_SET_SOURCE_MODE, 200);
        if (d->testMode == 2)
        {
            d->model->addAction(ACT_SET_MOTOR_CANCEL_TEST);
            d->model->addAction(ACT_RESET_MOTOR_LOCATION, 200);
        }
    }
    ui->comboBox_1->setEnabled(!b);
    ui->comboBox_4->setEnabled(!b);
    return true;
}

void HTestSetWidget7000::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidget7000);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidget7000::on_checkBox_2_clicked(bool b)
{
    setSaveMode(b ? 2 : 0);
}

void HTestSetWidget7000::setLuminousGears(int value)
{
    Q_D(HTestSetWidget7000);
    d->autoLuminousGears = value == 0;
    if (value == 0)
        return;
    setTestData("[光档位]", value - 1, ACT_SET_LUMINOUS_GEARS);
}

void HTestSetWidget7000::setMotorLocation(int /*value*/)
{
    Q_D(HTestSetWidget7000);
    if (d->testState)
        return;
    setTestData("[电机定位]", ui->comboBox_4->currentData(), ACT_SET_MOTOR_LOCATION);
}

void HTestSetWidget7000::setCurrentGears(int value)
{
    setTestData("[输出电流_档位]", value, ACT_SET_GEARS_OUTPUT_CURRENT);
    setTestData("[实测电流_档位]", value, ACT_SET_GEARS_MEASURED_CURRENT);
}

bool HTestSetWidget7000::adjustIntegralTime()
{
    Q_D(HTestSetWidget7000);
    if (!d->autoIntegralTime || !d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

bool HTestSetWidget7000::adjustLuminousGears()
{
    Q_D(HTestSetWidget7000);
    if (!ui->comboBox_3->isEnabled() || !d->autoLuminousGears || !d->testData->handleOperation("<匹配光档位>").toBool())
        return false;
    d->model->addAction(ACT_SET_LUMINOUS_GEARS);
    return true;
}

void HTestSetWidget7000::init()
{
    Q_D(HTestSetWidget7000);
    int i;
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    HPluginHelper::initWidget("[反向电压]", ui->doubleSpinBox_4);
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  ") << tr("  排测测试  "));
    ui->comboBox_2->addItem("  光通量  ", "[光通量]");
    ui->comboBox_2->addItem("  光强度  ", "[光强度]");
    ui->comboBox_4->addItem(tr("  原点  "), QPoint(99, 99));
    ui->comboBox_3->addItem(tr("  自动  "));
    for (i = 0; i < d->testData->data("[光档位数]").toInt(); i++)
        ui->comboBox_3->addItem(tr("  %1档  ").arg(i+1));
    for (i = 0; i < d->testData->data("[输出电流_档位数]").toInt(); i++)
        ui->comboBox_5->addItem(tr("  %1档  ").arg(i+1));

    connect(ui->doubleSpinBox_1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[积分时间]", value, ACT_SET_INTEGRAL_TIME); });
    connect(ui->doubleSpinBox_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[输出电压]", value, ACT_SET_OUTPUT_VOLTAGE); });
    connect(ui->doubleSpinBox_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[输出电流]", value, ACT_SET_OUTPUT_CURRENT); });
    connect(ui->doubleSpinBox_4, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[反向电压]", value, ACT_SET_REVERSE_VOLTAGE); });
    connect(ui->comboBox_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTestSetWidget7000::setTestMode);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=] { setTestData("[光测试类型]", ui->comboBox_2->currentData(), ACT_SET_LUMINOUS_TYPE); });
    connect(ui->comboBox_3, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTestSetWidget7000::setLuminousGears);
    connect(ui->comboBox_4, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTestSetWidget7000::setMotorLocation);
    connect(ui->comboBox_5, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTestSetWidget7000::setCurrentGears);
}
