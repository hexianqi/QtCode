#include "HSimpleTestSetWidget_p.h"
#include "ui_HSimpleTestSetWidget.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSimpleTestSetWidget::HSimpleTestSetWidget(QWidget *parent) :
    HAbstractTestSetWidget(*new HSimpleTestSetWidgetPrivate, parent),
    ui(new Ui::HSimpleTestSetWidget)
{
    ui->setupUi(this);
    init();
}

HSimpleTestSetWidget::~HSimpleTestSetWidget()
{
    qDebug() << __func__;
    delete ui;
}

QString HSimpleTestSetWidget::typeName()
{
    return "HSimpleTestSetWidget";
}

void HSimpleTestSetWidget::handleAction(HActionType action)
{
    Q_D(HSimpleTestSetWidget);
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

bool HSimpleTestSetWidget::setTestState(bool b)
{
    Q_D(HSimpleTestSetWidget);
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

void HSimpleTestSetWidget::on_doubleSpinBox_01_valueChanged(double value)
{
    Q_D(HSimpleTestSetWidget);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HSimpleTestSetWidget::on_checkBox_01_clicked(bool b)
{
    Q_D(HSimpleTestSetWidget);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_01->setChecked(b);
    ui->doubleSpinBox_01->setEnabled(!b);
}

void HSimpleTestSetWidget::on_checkBox_02_clicked(bool b)
{
    setTestState(b);
}

bool HSimpleTestSetWidget::adjustIntegralTime()
{
    Q_D(HSimpleTestSetWidget);
    if (!d->autoIntegralTime)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HSimpleTestSetWidget::init()
{
    Q_D(HSimpleTestSetWidget);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_01);
    ui->doubleSpinBox_01->setValue(d->testData->data("[积分时间]").toDouble());
}

HE_GUI_END_NAMESPACE
