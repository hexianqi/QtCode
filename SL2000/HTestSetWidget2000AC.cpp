#include "HTestSetWidget2000AC_p.h"
#include "ui_HTestSetWidget2000AC.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QTimer>

HTestSetWidget2000AC::HTestSetWidget2000AC(QWidget *parent) :
    HAbstractTestSetWidget(*new HTestSetWidget2000ACPrivate, parent),
    ui(new Ui::HTestSetWidget2000AC)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget2000AC::~HTestSetWidget2000AC()
{
    delete ui;
}

QString HTestSetWidget2000AC::typeName()
{
    return "HTestSetWidget2000AC";
}

void HTestSetWidget2000AC::handleAction(HActionType action)
{
    Q_D(HTestSetWidget2000AC);
    switch(action)
    {
    case ACT_SET_INTEGRAL_TIME:
        ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
        break;
    case ACT_GET_SPECTRUM_ELEC:
        emit resultChanged(action, false);
        if (!d->testState)
            break;
        adjustIntegralTime();
        d->model->addAction(ACT_GET_SPECTRUM_ELEC, 100);
        break;
    default:
        break;
    }
}

bool HTestSetWidget2000AC::setTestState(bool b)
{
    Q_D(HTestSetWidget2000AC);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;

    if (b)
    {
        d->testData->handleOperation("<清空光谱采样缓存>");
        d->model->addAction(ACT_GET_SPECTRUM_ELEC);
        if (d->testMode == 1)
        {
            auto t = ui->timeEdit->time();
            d->timerContinue->start((t.hour() * 3600 + t.minute() * 60 + t.second()) * 1000);
        }
    }
    else
    {
        d->timerContinue->stop();
    }
    return true;
}

void HTestSetWidget2000AC::on_doubleSpinBox_1_valueChanged(double value)
{
    Q_D(HTestSetWidget2000AC);
    if (qFuzzyCompare(value, d->testData->data("[积分时间]").toDouble()))
        return;
    d->testData->setData("[积分时间]", value);
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidget2000AC::on_checkBox_1_clicked(bool b)
{
    Q_D(HTestSetWidget2000AC);
    if (d->autoIntegralTime == b)
        return;
    d->autoIntegralTime = b;
    ui->checkBox_1->setChecked(b);
    ui->doubleSpinBox_1->setEnabled(!b);
}

void HTestSetWidget2000AC::on_comboBox_1_currentIndexChanged(int value)
{
    setTestMode(value);
}

bool HTestSetWidget2000AC::adjustIntegralTime()
{
    Q_D(HTestSetWidget2000AC);
    if (!d->autoIntegralTime)
        return false;
    if (!d->testData->handleOperation("<匹配积分时间>").toBool())
        return false;
    d->model->addAction(ACT_SET_INTEGRAL_TIME);
    return true;
}

void HTestSetWidget2000AC::init()
{
    Q_D(HTestSetWidget2000AC);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->comboBox_1->addItems(QStringList() << tr("  反复测试  ") << tr("  持续测试  "));
    d->timerContinue = new QTimer(this);
    connect(d->timerContinue, &QTimer::timeout, this, [=] { setTestState(false); });
}
