#include "HTestSetWidget1000RGB_p.h"
#include "ui_HTestSetWidget1000RGB.h"
#include "HeData/ITestData.h"
#include "HeController/IModel.h"
#include "HePlugin/HPluginHelper.h"

HTestSetWidget1000RGBPrivate::HTestSetWidget1000RGBPrivate()
{
    crystalDatas.resize(5);
    crystalDatas[0].Id = 0;
    crystalDatas[0].sourceIo = QVector<int>() << 0 << 1 << 0 << 0 << 0;
    crystalDatas[1].Id = 0;
    crystalDatas[1].sourceIo = QVector<int>() << 0 << 0 << 1 << 0 << 0;
    crystalDatas[2].Id = 0;
    crystalDatas[2].sourceIo = QVector<int>() << 0 << 0 << 0 << 1 << 0;
    crystalDatas[3].Id = 0;
    crystalDatas[3].sourceIo = QVector<int>() << 0 << 0 << 0 << 0 << 1;
    crystalDatas[4].Id = 0;
    crystalDatas[4].sourceIo = QVector<int>() << 0 << 0 << 0 << 0 << 0;
}

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
    Q_D(HTestSetWidget1000RGB);
    switch(action)
    {
    case ACT_SET_OUTPUT_VOLTAGE:
        ui->doubleSpinBox_1->setValue(d->testData->data("[输出电压]").toDouble());
        break;
    case ACT_SET_REVERSE_VOLTAGE:
        ui->doubleSpinBox_2->setValue(d->testData->data("[反向电压]").toDouble());
        break;
    case ACT_SET_SOURCE_IO:
    case ACT_SET_OUTPUT_CURRENT:
    case ACT_SET_GEARS_OUTPUT_CURRENT:
    {
        auto io = d->testData->data("[电源开关]").value<QVector<int>>().at(0);
        ui->radioButton_11->setChecked(io == 0);
        ui->radioButton_11->setChecked(io == 1);
        ui->comboBox_12->setCurrentIndex(d->testData->data("[电流_档位]").toInt());
        ui->doubleSpinBox_21->setValue(d->testData->data("[输出电流-R]").toDouble());
        ui->doubleSpinBox_22->setValue(d->testData->data("[输出电流-G]").toDouble());
        ui->doubleSpinBox_23->setValue(d->testData->data("[输出电流-B]").toDouble());
        ui->doubleSpinBox_24->setValue(d->testData->data("[输出电流-W]").toDouble());
        break;
    }
    case ACT_SINGLE_TEST:
        emit resultChanged(action, true);
        if (!d->testState)
            break;
        if (setCrystalIndex(nextIndex(d->index)))
            d->model->addAction(ACT_SINGLE_TEST);
        else
            setTestState(false);
        break;
    case ACT_INTEGRATE_TEST:
        emit resultChanged(action, d->first);
        d->first = false;
        if (!d->testState)
            break;
        d->model->addAction(ACT_INTEGRATE_TEST, 100);
        break;
    default:
        break;
    }
}

bool HTestSetWidget1000RGB::setTestState(bool b)
{
    Q_D(HTestSetWidget1000RGB);
    if (!HAbstractTestSetWidget::setTestState(b))
        return false;

    if (b)
    {
        d->testData->handleOperation("<清空光谱采样缓存>");
        if (d->testMode == 0)
        {
            auto i = nextIndex(-1);
            if (!setCrystalIndex(i))
                return false;
            d->model->addAction(ACT_SINGLE_TEST);
        }
        else
        {
            d->first = true;
            setCrystalIndex(4);
            d->testData->setData("[预配置测试]", true);
            d->model->addAction(ACT_INTEGRATE_TEST);
        }
    }
    else
    {
        if (d->testMode >= 1)
            setTestData("[电源模式]", 0, ACT_SET_SOURCE_MODE, 200);
    }

    ui->groupBox->setEnabled(!b);
    ui->doubleSpinBox_1->setEnabled(!b);
    ui->doubleSpinBox_2->setEnabled(!b);
    ui->doubleSpinBox_3->setEnabled(!b);
    ui->doubleSpinBox_4->setEnabled(!b);
    ui->comboBox_1->setEnabled(!b);
    ui->pushButton_1->setEnabled(!b);
    ui->pushButton_2->setEnabled(!b);
    ui->pushButton_3->setEnabled(!b);
    ui->pushButton_4->setEnabled(!b);
    ui->pushButton_5->setEnabled(!b);
    return true;
}

void HTestSetWidget1000RGB::on_pushButton_1_clicked()
{
    setTestData("[输出电压]", ui->doubleSpinBox_1->value(), ACT_SET_OUTPUT_VOLTAGE);
}

void HTestSetWidget1000RGB::on_pushButton_2_clicked()
{
    setTestData("[反向电压]", ui->doubleSpinBox_2->value(), ACT_SET_REVERSE_VOLTAGE);
}

void HTestSetWidget1000RGB::on_pushButton_3_clicked()
{
    setTestData("[输出电流]", ui->doubleSpinBox_3->value(), ACT_SET_OUTPUT_CURRENT);
}

void HTestSetWidget1000RGB::on_pushButton_4_clicked()
{
    Q_D(HTestSetWidget1000RGB);
    auto value = ui->doubleSpinBox_4->value();
    ui->doubleSpinBox_11->setValue(value);
    ui->doubleSpinBox_12->setValue(value);
    ui->doubleSpinBox_13->setValue(value);
    ui->doubleSpinBox_14->setValue(value);
    ui->doubleSpinBox_15->setValue(value);
    d->crystalDatas[0].IntegralTime = value;
    d->crystalDatas[1].IntegralTime = value;
    d->crystalDatas[2].IntegralTime = value;
    d->crystalDatas[3].IntegralTime = value;
    d->crystalDatas[4].IntegralTime = value;
    setTestData("[积分时间]", value, ACT_SET_INTEGRAL_TIME);
}

void HTestSetWidget1000RGB::on_pushButton_5_clicked()
{
    setTestMode(ui->comboBox_1->currentIndex());
}

void HTestSetWidget1000RGB::on_pushButton_11_clicked()
{
    Q_D(HTestSetWidget1000RGB);
    auto io = ui->radioButton_11->isChecked() ? 0 : 1;
    auto current = QVector<double>() << ui->doubleSpinBox_21->value() << ui->doubleSpinBox_22->value() << ui->doubleSpinBox_23->value() << ui->doubleSpinBox_24->value() ;
    d->crystalDatas[0].enable = ui->checkBox_11->isChecked();
    d->crystalDatas[0].IntegralTime = ui->doubleSpinBox_11->value();
    d->crystalDatas[0].sourceIo[0] = io;
    d->crystalDatas[1].enable = ui->checkBox_12->isChecked();
    d->crystalDatas[1].IntegralTime = ui->doubleSpinBox_12->value();
    d->crystalDatas[1].sourceIo[0] = io;
    d->crystalDatas[2].enable = ui->checkBox_13->isChecked();
    d->crystalDatas[2].IntegralTime = ui->doubleSpinBox_13->value();
    d->crystalDatas[2].sourceIo[0] = io;
    d->crystalDatas[3].enable = ui->checkBox_14->isChecked();
    d->crystalDatas[3].IntegralTime = ui->doubleSpinBox_14->value();
    d->crystalDatas[3].sourceIo[0] = io;
    d->crystalDatas[4].enable = ui->checkBox_15->isChecked();
    d->crystalDatas[4].IntegralTime = ui->doubleSpinBox_15->value();
    d->crystalDatas[4].sourceIo[0] = io;
    d->crystalDatas[4].sourceIo[1] = ui->checkBox_11->isChecked() ? 1 : 0;
    d->crystalDatas[4].sourceIo[2] = ui->checkBox_12->isChecked() ? 1 : 0;
    d->crystalDatas[4].sourceIo[3] = ui->checkBox_13->isChecked() ? 1 : 0;
    d->crystalDatas[4].sourceIo[4] = ui->checkBox_14->isChecked() ? 1 : 0;
    d->testData->setData("[电流_档位]", ui->comboBox_12->currentIndex());
    d->testData->setData("[电源开关]", QVariant::fromValue(d->crystalDatas[4].sourceIo));
    d->testData->setData("[输出电流-RGBW]", QVariant::fromValue(current));
    d->model->addAction(ACT_SET_GEARS_OUTPUT_CURRENT);
}

int HTestSetWidget1000RGB::nextIndex(int i)
{
    Q_D(HTestSetWidget1000RGB);
    i++;
    for (; i < 5; i++)
    {
        if (d->crystalDatas.at(i).enable)
            return i;
    }
    return -1;
}

bool HTestSetWidget1000RGB::setCrystalIndex(int i)
{
    Q_D(HTestSetWidget1000RGB);
    if (i < 0 || i > 5)
        return false;
    d->index = i;
    d->testData->setData("[TypeId]", d->crystalDatas[i].Id);
    setTestData("[积分时间]", d->crystalDatas.at(i).IntegralTime, ACT_SET_INTEGRAL_TIME);
    setTestData("[电源开关]", QVariant::fromValue(d->crystalDatas[i].sourceIo), ACT_SET_SOURCE_IO);
    return true;
}

void HTestSetWidget1000RGB::init()
{
    Q_D(HTestSetWidget1000RGB);
    HPluginHelper::initWidget("[输出电压]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[反向电压]", ui->doubleSpinBox_2);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_3);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_4);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_11);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_12);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_13);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_14);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_15);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_21);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_22);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_23);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_24);
    HPluginHelper::initWidget("[输出电流]", ui->doubleSpinBox_25);
    ui->comboBox_1->addItems(QStringList() << tr("  单次测试  ") << tr("  综合测试  "));
    for (int i = 0; i < d->testData->data("[输出电流_档位数]").toInt(); i++)
        ui->comboBox_12->addItem(tr("  %1档  ").arg(i+1));
}
