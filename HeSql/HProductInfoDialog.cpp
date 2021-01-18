#include "HProductInfoDialog_p.h"
#include "ui_HProductInfoDialog.h"
#include "IProductInfo.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HProductInfoDialog::HProductInfoDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HProductInfoDialogPrivate),
    ui(new Ui::HProductInfoDialog)
{
    ui->setupUi(this);
    init();
}

HProductInfoDialog::~HProductInfoDialog()
{
    qDebug() << __func__;
    delete ui;
}

void HProductInfoDialog::setData(IProductInfo *p)
{
    d_ptr->data = p;
    showData();
}

void HProductInfoDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

void HProductInfoDialog::showData()
{
    ui->lineEdit_01->setText(d_ptr->data->data("Manufacturer").toString());
    ui->lineEdit_02->setText(d_ptr->data->data("ProductName").toString());
    ui->lineEdit_03->setText(d_ptr->data->data("ProductModel").toString());
    ui->lineEdit_04->setText(d_ptr->data->data("TestInstitute").toString());
    ui->lineEdit_05->setText(d_ptr->data->data("Tester").toString());
    ui->spinBox_01->setValue(d_ptr->data->data("SampleNumber").toInt());
    ui->doubleSpinBox_01->setValue(d_ptr->data->data("Temperature").toDouble());
    ui->doubleSpinBox_02->setValue(d_ptr->data->data("Humidity").toDouble());
    ui->checkBox_01->setChecked(d_ptr->data->data("Editable").toBool());
    ui->checkBox_02->setChecked(d_ptr->data->data("Increase").toBool());
    ui->checkBox_03->setChecked(d_ptr->data->data("Enable").toBool());
}

void HProductInfoDialog::saveData()
{
    d_ptr->data->setData("Manufacturer", ui->lineEdit_01->text());
    d_ptr->data->setData("ProductName", ui->lineEdit_02->text());
    d_ptr->data->setData("ProductModel", ui->lineEdit_03->text());
    d_ptr->data->setData("TestInstitute", ui->lineEdit_04->text());
    d_ptr->data->setData("Tester", ui->lineEdit_05->text());
    d_ptr->data->setData("SampleNumber", ui->spinBox_01->value());
    d_ptr->data->setData("Temperature", ui->doubleSpinBox_01->value());
    d_ptr->data->setData("Humidity", ui->doubleSpinBox_02->value());
    d_ptr->data->setData("Editable", ui->checkBox_01->isChecked());
    d_ptr->data->setData("Increase", ui->checkBox_02->isChecked());
    d_ptr->data->setData("Enable", ui->checkBox_03->isChecked());
}

void HProductInfoDialog::init()
{
    HPluginHelper::initWidget("[样品编号]", ui->spinBox_01);
    HPluginHelper::initWidget("[环境温度]", ui->doubleSpinBox_01);
    HPluginHelper::initWidget("[环境湿度]", ui->doubleSpinBox_02);
}

HE_SQL_END_NAMESPACE
