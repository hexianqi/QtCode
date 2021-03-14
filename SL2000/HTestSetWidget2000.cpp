#include "HTestSetWidget2000_p.h"
#include "ui_HTestSetWidget2000.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HTestSetWidget2000::HTestSetWidget2000(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget2000Private, parent),
    ui(new Ui::HTestSetWidget2000)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget2000::~HTestSetWidget2000()
{
    qDebug() << __func__;
    delete ui;
}

void HTestSetWidget2000::initialize(QVariantMap /*param*/)
{

}

QString HTestSetWidget2000::typeName()
{
    return "HTestSetWidget2000";
}

void HTestSetWidget2000::handleAction(HActionType action)
{
    Q_D(HTestSetWidget2000);
    bool append = false;
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_GET_SPECTRUM:
        append = !adjustIntegralTime() && d->testMode == 0;
        emit resultChanged(action, append);
        if (!d->testState)
            break;
        if (append || (d->testMode == 2 && d->testData->data("[光谱采样溢出状态]").toInt() == 0))
        {
            setTestState(false);
            break;
        }
        d->model->addAction(ACT_GET_SPECTRUM, 10);
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
        d->testData->handleOperation("<清空光谱采样缓存>");
        d->model->addAction(ACT_GET_SPECTRUM);
    }
    ui->comboBox_1->setEnabled(!b);
    return true;
}

void HTestSetWidget2000::on_doubleSpinBox_1_editingFinished()
{
    Q_D(HTestSetWidget2000);
    auto value = ui->doubleSpinBox_1->value();
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidget2000::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidget2000);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidget2000::on_comboBox_1_currentIndexChanged(int value)
{
    setTestMode(value);
}

bool HTestSetWidget2000::adjustIntegralTime()
{
    Q_D(HTestSetWidget2000);
    if (!d->autoIntegralTime)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HTestSetWidget2000::init()
{
    Q_D(HTestSetWidget2000);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  ") << tr("  捕获测试  "));
}
