#include "HTrendTestSetWidget_p.h"
#include "ui_HTrendTestSetWidget.h"
#include "HeController/IModel.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QTimer>

HE_BEGIN_NAMESPACE

HTrendTestSetWidget::HTrendTestSetWidget(QWidget *parent) :
    HAbstractTestSetWidget(*new HTrendTestSetWidgetPrivate, parent),
    ui(new Ui::HTrendTestSetWidget)
{
    ui->setupUi(this);
    init();
}

HTrendTestSetWidget::~HTrendTestSetWidget()
{
    delete ui;
}

QString HTrendTestSetWidget::typeName()
{
    return "HTrendTestSetWidget";
}

void HTrendTestSetWidget::handleAction(HActionType action)
{
    Q_D(HTrendTestSetWidget);
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
    case ACT_SET_GEARS_OUTPUT_CURRENT:
        ui->comboBox_1->setCurrentIndex(d->testData->data("[输出电流_档位]").toInt());
        break;
    case ACT_SET_LUMINOUS_GEARS:
        ui->comboBox_2->setCurrentIndex(d->testData->data("[光档位]").toInt());
        break;
    case ACT_INTEGRATE_TEST:
        emit resultChanged(action, d->first);
        d->first = false;
        break;
    default:
        break;
    }
}

bool HTrendTestSetWidget::setTestState(bool b)
{
    Q_D(HTrendTestSetWidget);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;
    if (b)
    {
        auto time = ui->timeEdit_1->time();
        auto interval = ui->spinBox_1->value();
        setData("[测量间隔]", interval);
        setTestData("[电源模式]", 1, ACT_SET_SOURCE_MODE);
        d->first = true;
        d->testData->handleOperation("<清空光谱采样缓存>");
        d->timerInterval->start(interval * 1000);
        d->timerContinue->start((time.hour() * 3600 + time.minute() * 60 + time.second()) * 1000);
    }
    else
    {
        d->timerContinue->stop();
        d->timerInterval->stop();
        setTestData("[电源模式]", 0, ACT_SET_SOURCE_MODE, 200);
    }
    ui->doubleSpinBox_1->setEnabled(!b);
    ui->doubleSpinBox_2->setEnabled(!b);
    ui->doubleSpinBox_3->setEnabled(!b);
    ui->comboBox_1->setEnabled(!b);
    ui->comboBox_2->setEnabled(!b);
    ui->timeEdit_1->setEnabled(!b);
    ui->spinBox_1->setEnabled(!b);
    return true;
}

void HTrendTestSetWidget::setCurrentGears(int value)
{
    setTestData("[输出电流_档位]", value, ACT_SET_GEARS_OUTPUT_CURRENT);
    setTestData("[实测电流_档位]", value, ACT_SET_GEARS_MEASURED_CURRENT);
}

void HTrendTestSetWidget::init()
{
    Q_D(HTrendTestSetWidget);
    int i;
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    for (i = 0; i < d->testData->data("[输出电流_档位数]").toInt(); i++)
        ui->comboBox_1->addItem(tr("  %1档  ").arg(i+1));
    for (i = 0; i < d->testData->data("[光档位数]").toInt(); i++)
        ui->comboBox_2->addItem(tr("  %1档  ").arg(i+1));
    ui->doubleSpinBox_1->setValue(d->testData->data("[积分时间]").toDouble());
    ui->doubleSpinBox_2->setValue(d->testData->data("[输出电压]").toDouble());
    ui->doubleSpinBox_3->setValue(d->testData->data("[输出电流]").toDouble());
    ui->comboBox_1->setCurrentIndex(d->testData->data("[输出电流_档位]").toInt());
    ui->comboBox_2->setCurrentIndex(d->testData->data("[光档位]").toInt());
    d->timerContinue = new QTimer(this);
    d->timerInterval = new QTimer(this);

    connect(ui->doubleSpinBox_1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[积分时间]", value, ACT_SET_INTEGRAL_TIME); });
    connect(ui->doubleSpinBox_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[输出电压]", value, ACT_SET_OUTPUT_VOLTAGE); });
    connect(ui->doubleSpinBox_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=] (double value) { setTestData("[输出电流]", value, ACT_SET_OUTPUT_CURRENT); });
    connect(ui->comboBox_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HTrendTestSetWidget::setCurrentGears);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=] (int value) { setTestData("[光档位]", value, ACT_SET_LUMINOUS_GEARS); });
    connect(d->timerContinue, &QTimer::timeout, this, [=] { setTestState(false); });
    connect(d->timerInterval, &QTimer::timeout, this, [=] { d->model->addAction(ACT_INTEGRATE_TEST); });
    setData("[测量间隔]", 1);
}

HE_END_NAMESPACE
