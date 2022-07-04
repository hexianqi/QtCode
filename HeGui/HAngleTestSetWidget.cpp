#include "HAngleTestSetWidget_p.h"
#include "ui_HAngleTestSetWidget.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"

HE_BEGIN_NAMESPACE

HAngleTestSetWidget::HAngleTestSetWidget(QWidget *parent) :
    HAbstractTestSetWidget(*new HAngleTestSetWidgetPrivate, parent),
    ui(new Ui::HAngleTestSetWidget)
{
    ui->setupUi(this);
    init();
}

HAngleTestSetWidget::~HAngleTestSetWidget()
{
    delete ui;
}

QString HAngleTestSetWidget::typeName()
{
    return "HAngleTestSetWidget";
}

QVariant HAngleTestSetWidget::handleOperation(QString type, QVariant value)
{
    Q_D(HAngleTestSetWidget);
    if (type == "<转动电机>")
    {
        if (d->testData->setData("[电机定位]", ui->spinBox_1->value()))
        {
            ui->spinBox_1->setEnabled(false);
            d->model->addAction(ACT_SET_MOTOR_LOCATION);
        }
        return true;
    }
    if (type == "<复位电机>")
    {
        ui->spinBox_1->setValue(0);
        ui->spinBox_1->setEnabled(false);
        d->testData->setData("[电机定位]", 0);
        d->model->addAction(ACT_RESET_MOTOR_LOCATION);
        return true;
    }
    return HAbstractTestSetWidget::handleOperation(type, value);
}

void HAngleTestSetWidget::handleAction(HActionType action)
{
    Q_D(HAngleTestSetWidget);
    switch(action)
    {
    case ACT_GET_MEASURED_VOLTAGE:
        if (!d->testState)
            emit resultChanged(action, false);
        break;
    case ACT_SET_OUTPUT_VOLTAGE:
        ui->doubleSpinBox_2->setValue(d->testData->data("[输出电压]").toDouble());
        break;
    case ACT_SET_OUTPUT_CURRENT:
        ui->doubleSpinBox_3->setValue(d->testData->data("[输出电流]").toDouble());
        break;
    case ACT_SET_GEARS_OUTPUT_CURRENT:
        ui->comboBox_2->setCurrentIndex(d->testData->data("[输出电流_档位]").toInt());
        break;
    case ACT_SET_LUMINOUS_GEARS:
        if (ui->comboBox_3->isEnabled() && !d->autoLuminousGears)
            ui->comboBox_3->setCurrentIndex(d->testData->data("[光档位]").toInt() + 1);
        break;
    case ACT_GET_LUMINOUS_DATA:
        if (!d->testState)
        {
            emit resultChanged(action, false);
            if (adjustLuminousGears())
                d->model->addAction(ACT_GET_LUMINOUS_DATA);
        }
        break;
    case ACT_START_ANGLE_TEST:
        d->model->addAction(ACT_QUERY_MOTOR_STATE, 1000);
        break;
    case ACT_GET_ANGLE_DISTRIBUTION:
        emit resultChanged(action, true);
        setTestState(false);
        break;
    case ACT_SET_MOTOR_LOCATION:
    case ACT_RESET_MOTOR_LOCATION:
        d->model->addAction(ACT_QUERY_MOTOR_STATE, 50);
        break;
    case ACT_QUERY_MOTOR_STATE:
        if (d->testData->data("[电机状态]").toInt() == 1)
        {
            if (d->testState)
                d->model->addAction(ACT_GET_ANGLE_DISTRIBUTION);
            ui->spinBox_1->setEnabled(true);
        }
        else
            d->model->addAction(ACT_QUERY_MOTOR_STATE, 50);
        break;
    default:
        break;
    }
}

bool HAngleTestSetWidget::setTestState(bool b)
{
    Q_D(HAngleTestSetWidget);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;

    if (b)
        d->model->addAction(ACT_START_ANGLE_TEST);
    updateUI();
    return true;
}

void HAngleTestSetWidget::setVoltage(double value)
{
    setTestData("[输出电压]", value, ACT_SET_OUTPUT_VOLTAGE);
}

void HAngleTestSetWidget::setCurrent(double value)
{
    setTestData("[输出电流]", value, ACT_SET_OUTPUT_CURRENT);
}

void HAngleTestSetWidget::setCurrentGears(int value)
{
    Q_D(HAngleTestSetWidget);
    if (setTestData("[输出电流_档位]", value, ACT_SET_GEARS_OUTPUT_CURRENT))
    {
        setTestData("[电源模式]", 0, ACT_SET_SOURCE_MODE);
        d->model->addAction(ACT_SET_OUTPUT_CURRENT);
        setTestData("[电源模式]", 1, ACT_SET_SOURCE_MODE);
    }
    setTestData("[实测电流_档位]", value, ACT_SET_GEARS_MEASURED_CURRENT);
}

void HAngleTestSetWidget::setLuminousGears(int value)
{
    Q_D(HAngleTestSetWidget);
    d->autoLuminousGears = value == 0;
    if (value == 0)
        return;
    setTestData("[光档位]", value - 1, ACT_SET_LUMINOUS_GEARS);
}

bool HAngleTestSetWidget::adjustLuminousGears()
{
    Q_D(HAngleTestSetWidget);
    if (!ui->comboBox_3->isEnabled() || !d->autoLuminousGears || !d->testData->handleOperation("<匹配光档位>").toBool())
        return false;
    d->model->addAction(ACT_SET_LUMINOUS_GEARS);
    return true;
}

void HAngleTestSetWidget::updateUI()
{
    Q_D(HAngleTestSetWidget);
    ui->comboBox_2->setEnabled(!d->testState);
    ui->comboBox_3->setEnabled(!d->testState);
    ui->spinBox_1->setEnabled(!d->testState);
    ui->doubleSpinBox_2->setEnabled(!d->testState);
    ui->doubleSpinBox_3->setEnabled(!d->testState);
}

void HAngleTestSetWidget::init()
{
    Q_D(HAngleTestSetWidget);
    int i;
    HPluginHelper::initWidget("[光强度角]", ui->spinBox_1);
    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    ui->spinBox_1->setValue(0);
    for (i = 0; i < d->testData->data("[输出电流_档位数]").toInt(); i++)
        ui->comboBox_2->addItem(tr("  %1档  ").arg(i+1));
    ui->comboBox_3->addItem(tr("  自动  "));
    for (i = 0; i < d->testData->data("[光档位数]").toInt(); i++)
        ui->comboBox_3->addItem(tr("  %1档  ").arg(i+1));

    connect(ui->doubleSpinBox_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &HAngleTestSetWidget::setVoltage);
    connect(ui->doubleSpinBox_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &HAngleTestSetWidget::setCurrent);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HAngleTestSetWidget::setCurrentGears);
    connect(ui->comboBox_3, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HAngleTestSetWidget::setLuminousGears);
}

HE_END_NAMESPACE
