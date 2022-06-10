#include "HAdjustSetWidget_p.h"
#include "ui_HAdjustSetWidget.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"

HE_BEGIN_NAMESPACE

HAdjustSetWidget::HAdjustSetWidget(QWidget *parent) :
    HAbstractTestSetWidget(*new HAdjustSetWidgetPrivate, parent),
    ui(new Ui::HAdjustSetWidget)
{
    ui->setupUi(this);
    init();
}

HAdjustSetWidget::~HAdjustSetWidget()
{
    delete ui;
}

QString HAdjustSetWidget::typeName()
{
    return "HAdjustSetWidget";
}

void HAdjustSetWidget::handleAction(HActionType action)
{
    Q_D(HAdjustSetWidget);
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_GET_SPECTRUM:
        emit resultChanged(action, false);
        if (!d->testState)
            break;
        adjustIntegralTime();
        d->model->addAction(ACT_GET_SPECTRUM, 100);
        break;
    default:
        break;
    }
}

bool HAdjustSetWidget::setTestState(bool b)
{
    Q_D(HAdjustSetWidget);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;
    ui->checkBox_02->setChecked(b);
    if (b)
    {
        d->testData->handleOperation("<清空光谱采样缓存>");
        d->model->addAction(ACT_GET_SPECTRUM);
    }
    return true;
}

void HAdjustSetWidget::on_checkBox_01_clicked(bool b)
{
    Q_D(HAdjustSetWidget);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HAdjustSetWidget::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

bool HAdjustSetWidget::adjustIntegralTime()
{
    Q_D(HAdjustSetWidget);
    if (!d->autoIntegralTime)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HAdjustSetWidget::init()
{
    Q_D(HAdjustSetWidget);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
    connect(ui->doubleSpinBox_01, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[积分时间]", value, ACT_SET_INTEGRAL_TIME); });

}

HE_END_NAMESPACE
