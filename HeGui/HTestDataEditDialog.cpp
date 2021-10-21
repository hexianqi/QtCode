#include "HTestDataEditDialog_p.h"
#include "ui_HTestDataEditDialog.h"
#include "HeData/ITestData.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HTestDataEditDialog::HTestDataEditDialog(QWidget *parent) :
    HAbstractTestDataEditDialog(*new HTestDataEditDialogPrivate, parent),
    ui(new Ui::HTestDataEditDialog)
{
    ui->setupUi(this);
    init();
}

HTestDataEditDialog::~HTestDataEditDialog()
{
    qDebug() << __func__;
    delete ui;
}

QString HTestDataEditDialog::typeName()
{
    return "HTestDataEditDialog";
}

void HTestDataEditDialog::showData()
{
    Q_D(HTestDataEditDialog);
    auto data = d->data();
    ui->lineEdit_01->setText(data->data("[制造厂商]").toString());
    ui->lineEdit_02->setText(data->data("[产品名称]").toString());
    ui->lineEdit_03->setText(data->data("[产品型号]").toString());
    ui->lineEdit_05->setText(data->data("[测试员]").toString());
    ui->lineEdit_06->setText(data->data("[备注]").toString());
    ui->spinBox_01->setValue(data->data("[样品编号]").toInt());
    ui->doubleSpinBox_01->setValue(data->data("[环境温度]").toDouble());
    ui->doubleSpinBox_02->setValue(data->data("[环境湿度]").toDouble());
}

void HTestDataEditDialog::saveData()
{
    Q_D(HTestDataEditDialog);
    if (d->data0 != nullptr)
    {
        d->data0->setData("[制造厂商]", ui->lineEdit_01->text());
        d->data0->setData("[产品名称]", ui->lineEdit_02->text());
        d->data0->setData("[产品型号]", ui->lineEdit_03->text());
        d->data0->setData("[测试员]", ui->lineEdit_05->text());
        d->data0->setData("[备注]", ui->lineEdit_06->text());
        d->data0->setData("[样品编号]", ui->spinBox_01->value());
        d->data0->setData("[环境温度]", ui->doubleSpinBox_01->value());
        d->data0->setData("[环境湿度]", ui->doubleSpinBox_02->value());
    }
    if (d->data1 != nullptr)
    {
        d->data1->setData("[制造厂商]", ui->lineEdit_01->text());
        d->data1->setData("[产品名称]", ui->lineEdit_02->text());
        d->data1->setData("[产品型号]", ui->lineEdit_03->text());
        d->data1->setData("[测试员]", ui->lineEdit_05->text());
        d->data1->setData("[备注]", ui->lineEdit_06->text());
        d->data1->setData("[样品编号]", ui->spinBox_01->value());
        d->data1->setData("[环境温度]", ui->doubleSpinBox_01->value());
        d->data1->setData("[环境湿度]", ui->doubleSpinBox_02->value());
    }
}

void HTestDataEditDialog::init()
{
    HPluginHelper::initWidget("[样品编号]", ui->spinBox_01);
    HPluginHelper::initWidget("[环境温度]", ui->doubleSpinBox_01);
    HPluginHelper::initWidget("[环境湿度]", ui->doubleSpinBox_02);
    setWindowTitle(tr("产品信息编辑"));
    showData();
}

HE_GUI_END_NAMESPACE
