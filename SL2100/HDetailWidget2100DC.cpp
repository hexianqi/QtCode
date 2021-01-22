#include "HDetailWidget2100DC_p.h"
#include "ui_HDetailWidget2100DC.h"
#include "HeData/ITestData.h"
#include <QtCore/QDebug>

HDetailWidget2100DC::HDetailWidget2100DC(QWidget *parent) :
    HAbstractTestDetailWidget(*new HDetailWidget2100DCPrivate, parent),
    ui(new Ui::HDetailWidget2100DC)
{
    ui->setupUi(this);
    refreshWidget();
}

HDetailWidget2100DC::~HDetailWidget2100DC()
{
    qDebug() << __func__;
    delete ui;
}

void HDetailWidget2100DC::initialize(QVariantMap /*param*/)
{

}

QString HDetailWidget2100DC::typeName()
{
    return "HDetailWidget2100DC";
}

void HDetailWidget2100DC::refreshWidget()
{
    Q_D(HDetailWidget2100DC);
    ui->lineEdit_01->setText(d->testData->toString("[实测电压]"));
    ui->lineEdit_02->setText(d->testData->toString("[实测电流]"));
    ui->lineEdit_03->setText(d->testData->toString("[电功率]"));
    ui->lineEdit_11->setText(d->testData->toString("[光谱光通量]"));
    ui->lineEdit_12->setText(d->testData->toString("[光功率]"));
    ui->lineEdit_13->setText(d->testData->toString("[光效率]"));
    ui->lineEdit_21->setText(d->testData->toString("[主波长]"));
    ui->lineEdit_22->setText(d->testData->toString("[峰值波长]"));
    ui->lineEdit_23->setText(d->testData->toString("[峰值带宽]"));
    ui->lineEdit_31->setText(d->testData->toString("[色坐标]"));
    ui->lineEdit_32->setText(d->testData->toString("[色坐标uvp]"));
    ui->lineEdit_33->setText(d->testData->toString("[Duv]"));
    ui->lineEdit_41->setText(d->testData->toString("[红色比]"));
    ui->lineEdit_42->setText(d->testData->toString("[绿色比]"));
    ui->lineEdit_43->setText(d->testData->toString("[蓝色比]"));
    ui->lineEdit_51->setText(d->testData->toString("[色温]"));
    ui->lineEdit_52->setText(d->testData->toString("[色纯度]"));
    ui->lineEdit_53->setText(d->testData->toString("[色容差]"));
    ui->lineEdit_61->setText(d->testData->toString("[显色指数Ra]"));
    ui->lineEdit_62->setText(d->testData->toString("[显色指数R9]"));
    ui->lineEdit_71->setText(d->testData->toString("[显色指数Rx]"));
}
