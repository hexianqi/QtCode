#include "HIVTestSetWidget_p.h"
#include "ui_HIVTestSetWidget.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/ITestElec.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HIVTestSetWidgetPrivate::HIVTestSetWidgetPrivate()
{
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
}

HIVTestSetWidget::HIVTestSetWidget(QWidget *parent) :
    HAbstractTestSetWidget(*new HIVTestSetWidgetPrivate, parent),
    ui(new Ui::HIVTestSetWidget)
{
    ui->setupUi(this);
    init();
}

HIVTestSetWidget::~HIVTestSetWidget()
{
    qDebug() << __func__;
    delete ui;
}

void HIVTestSetWidget::initialize(QVariantMap /*param*/)
{

}

QString HIVTestSetWidget::typeName()
{
    return "HIVTestSetWidget";
}

void HIVTestSetWidget::handleAction(HActionType action)
{
    Q_D(HIVTestSetWidget);
    if (!d->testState)
        return;
    if (action == ACT_SET_OUTPUT_CURRENT)
    {
        ui->doubleSpinBox_4->setValue(d->elecCurrent);
        d->model->addAction(ACT_GET_MEASURED_VOLTAGE);
    }
    if (action == ACT_GET_MEASURED_VOLTAGE)
    {
        d->elecCurrent += d->interval;
        if (d->elecCurrent <= d->elecTo)
        {
            d->testElec->setParam(OutputCurrent, d->elecCurrent);
            d->model->addAction(ACT_SET_OUTPUT_CURRENT);
        }
        else
            setTestState(false);
    }
}

bool HIVTestSetWidget::setTestState(bool b)
{
    Q_D(HIVTestSetWidget);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;
    ui->doubleSpinBox_1->setEnabled(!b);
    ui->doubleSpinBox_2->setEnabled(!b);
    ui->doubleSpinBox_3->setEnabled(!b);
    ui->doubleSpinBox_4->setEnabled(!b);
    if (b)
    {
        initParam();
        d->testElec->setData("[电源模式]", 1);
        d->testElec->setParam(OutputCurrent, d->elecCurrent);
        d->model->addAction(ACT_SET_SOURCE_MODE);
        d->model->addAction(ACT_SET_OUTPUT_CURRENT);
    }
    else
    {
        d->testElec->setData("[电源模式]", 0);
        d->model->addAction(ACT_SET_SOURCE_MODE);
    }
    return true;
}

void HIVTestSetWidget::initParam()
{
    Q_D(HIVTestSetWidget);
    d->elecFrom = ui->doubleSpinBox_1->value();
    d->elecTo = ui->doubleSpinBox_2->value();
    d->interval = ui->doubleSpinBox_3->value();
    if (d->elecFrom > d->elecTo)
        qSwap(d->elecFrom, d->elecTo);
    d->elecCurrent = d->elecFrom;
}

void HIVTestSetWidget::init()
{
    Q_D(HIVTestSetWidget);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_4);
    ui->doubleSpinBox_1->setValue(d->elecFrom);
    ui->doubleSpinBox_2->setValue(d->elecTo);
    ui->doubleSpinBox_3->setValue(d->interval);
    ui->doubleSpinBox_4->setValue(d->elecCurrent);
}

HE_GUI_END_NAMESPACE
