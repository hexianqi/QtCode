#include "HTestSetWidget1000RGB.h"
#include "ui_HTestSetWidget1000RGB.h"

HTestSetWidget1000RGB::HTestSetWidget1000RGB(QWidget *parent) :
    HAbstractTestSetWidget(parent),
    ui(new Ui::HTestSetWidget1000RGB)
{
    ui->setupUi(this);
    init();
}

HTestSetWidget1000RGB::~HTestSetWidget1000RGB()
{
    delete ui;
}

QString HTestSetWidget1000RGB::typeName()
{
    return "HTestSetWidget1000RGB";
}

void HTestSetWidget1000RGB::handleAction(HActionType action)
{
//    Q_D(HTestSetWidget1000A);
//    bool adjust = false;
//    switch(action)
//    {
//    case ACT_SET_INTEGRAL_TIME:
//        ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
//        break;
//    case ACT_SET_OUTPUT_VOLTAGE:
//        ui->doubleSpinBox_2->setValue(d->testData->data("[输出电压]").toDouble());
//        break;
//    case ACT_SET_OUTPUT_CURRENT:
//        ui->doubleSpinBox_3->setValue(d->testData->data("[输出电流]").toDouble());
//        break;
//    case ACT_SET_REVERSE_VOLTAGE:
//        ui->doubleSpinBox_4->setValue(d->testData->data("[反向电压]").toDouble());
//        break;
//    case ACT_SET_GEARS_OUTPUT_CURRENT:
//        ui->comboBox_2->setCurrentIndex(d->testData->data("[输出电流_档位]").toInt());
//        break;
//    case ACT_SET_LUMINOUS_GEARS:
//        if (ui->comboBox_3->isEnabled() && !d->autoLuminousGears)
//            ui->comboBox_3->setCurrentIndex(d->testData->data("[光档位]").toInt() + 1);
//        break;
//    case ACT_QUERY_STATE_TRIGGER:
//        if (!d->testState)
//            break;
//        if (d->testData->data("[触发状态]").toInt() != 1)
//            d->model->addAction(ACT_QUERY_STATE_TRIGGER, 50);
//        else
//            d->model->addAction(ACT_SINGLE_TEST, 100);
//        break;
//    case ACT_SINGLE_TEST:
//        adjust = adjustIntegralTime();
//        adjust = adjustLuminousGears() || adjust;
//        if (adjust)
//        {
//            d->model->addAction(ACT_SINGLE_TEST);
//            break;
//        }
//        emit resultChanged(action, true);
//        if (!d->testState)
//            break;
//        if (d->testMode == 4)
//            d->model->addAction(ACT_QUERY_STATE_TRIGGER);
//        else
//            setTestState(false);
//        break;
//    case ACT_INTEGRATE_TEST:
//        emit resultChanged(action, d->testMode == 3 || d->first);
//        d->first = false;
//        if (!d->testState)
//            break;
//        adjustIntegralTime();
//        adjustLuminousGears();
//        if (d->testMode == 1 || d->testMode == 2)
//            d->model->addAction(ACT_INTEGRATE_TEST, 100);
//        break;
//    default:
//        break;
//    }
}

bool HTestSetWidget1000RGB::setTestState(bool b)
{
//    Q_D(HTestSetWidget1000A);
//    if (!HAbstractTestSetWidget::setTestState(b))
//        return false;

//    if (b)
//    {
//        d->first = true;
//        d->testData->handleOperation("<清空光谱采样缓存>");
//        if (d->testMode == 0)
//        {
//            d->model->addAction(ACT_SINGLE_TEST);
//        }
//        else if (d->testMode == 4)
//        {
//            d->model->addAction(ACT_QUERY_STATE_TRIGGER);
//        }
//        else
//        {
//            d->testData->setData("[预配置测试]", true);
//            if (d->testMode == 1)
//            {
//                d->model->addAction(ACT_INTEGRATE_TEST);
//            }
//            if (d->testMode == 2)
//            {
//                auto t = ui->timeEdit_1->time();
//                d->model->addAction(ACT_INTEGRATE_TEST);
//                d->timerContinue->start((t.hour() * 3600 + t.minute() * 60 + t.second()) * 1000);
//            }
//            if (d->testMode == 3)
//            {
//                d->timerInterval->start(ui->spinBox_1->value() * 1000);
//            }
//        }
//    }
//    else
//    {
//        if (d->testMode >= 1 && d->testMode <= 3)
//        {
//            d->timerContinue->stop();
//            d->timerInterval->stop();
//            setTestData("[电源模式]", 0, ACT_SET_SOURCE_MODE, 200);
//        }
//    }
//    ui->comboBox_1->setEnabled(!b);
//    ui->comboBox_2->setEnabled(!b);
//    return true;
}

void HTestSetWidget1000RGB::init()
{
    Q_D(HTestSetWidget1000RGB);
//    int i;
//    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
//    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_2);
//    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
//    HPluginHelper::initWidget("[反向电压]", ui->doubleSpinBox_4);
//    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  反复测试  ") << tr("  持续测试  ") << tr("  间隔测试  "));// << tr("  分选测试  "));
//    for (i = 0; i < d->testData->data("[输出电流_档位数]").toInt(); i++)
//        ui->comboBox_2->addItem(tr("  %1档  ").arg(i+1));
//    ui->comboBox_3->addItem(tr("  自动  "));
//    for (i = 0; i < d->testData->data("[光档位数]").toInt(); i++)
//        ui->comboBox_3->addItem(tr("  %1档  ").arg(i+1));
//    d->timerContinue = new QTimer(this);
//    d->timerInterval = new QTimer(this);

//    connect(ui->doubleSpinBox_1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[积分时间]", value, ACT_SET_INTEGRAL_TIME); });
//    connect(ui->doubleSpinBox_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[输出电压]", value, ACT_SET_OUTPUT_VOLTAGE); });
//    connect(ui->doubleSpinBox_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[输出电流]", value, ACT_SET_OUTPUT_CURRENT); });
//    connect(ui->doubleSpinBox_4, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[反向电压]", value, ACT_SET_REVERSE_VOLTAGE); });
//    connect(ui->comboBox_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTestSetWidget1000A::setTestMode);
//    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTestSetWidget1000A::setCurrentGears);
//    connect(ui->comboBox_3, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTestSetWidget1000A::setLuminousGears);
//    connect(d->timerContinue, &QTimer::timeout, this, [=] { setTestState(false); });
//    connect(d->timerInterval, &QTimer::timeout, this, [=] { d->model->addAction(ACT_INTEGRATE_TEST); });
}
