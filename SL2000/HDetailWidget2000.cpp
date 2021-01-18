#include "HDetailWidget2000_p.h"
#include "ui_HDetailWidget2000.h"
#include "HeData/ITestData.h"
#include <QtCore/QDebug>

HDetailWidget2000::HDetailWidget2000(QWidget *parent) :
    HAbstractTestDetailWidget(*new HDetailWidget2000Private, parent),
    ui(new Ui::HDetailWidget2000)
{
    ui->setupUi(this);
    refreshWidget();
}

HDetailWidget2000::~HDetailWidget2000()
{
    qDebug() << __func__;
    delete ui;
}

void HDetailWidget2000::initialize(QVariantMap /*param*/)
{

}

QString HDetailWidget2000::typeName()
{
    return "HDetailWidget2000";
}

void HDetailWidget2000::refreshWidget()
{
    Q_D(HDetailWidget2000);
    ui->lineEdit_001->setText(d->testData->toString("[主波长]"));
    ui->lineEdit_002->setText(d->testData->toString("[峰值波长]"));
    ui->lineEdit_003->setText(d->testData->toString("[峰值带宽]"));
    ui->lineEdit_004->setText(d->testData->toString("[光谱光通量]"));
    ui->lineEdit_011->setText(d->testData->toString("[色坐标]"));
    ui->lineEdit_012->setText(d->testData->toString("[色坐标uvp]"));
    ui->lineEdit_013->setText(d->testData->toString("[Duv]"));
    ui->lineEdit_014->setText(d->testData->toString("[光功率]"));
    ui->lineEdit_021->setText(d->testData->toString("[红色比]"));
    ui->lineEdit_022->setText(d->testData->toString("[绿色比]"));
    ui->lineEdit_023->setText(d->testData->toString("[蓝色比]"));    
    ui->lineEdit_031->setText(d->testData->toString("[色温]"));
    ui->lineEdit_032->setText(d->testData->toString("[色纯度]"));
    ui->lineEdit_033->setText(d->testData->toString("[色容差]"));
    ui->lineEdit_041->setText(d->testData->toString("[显色指数Ra]"));
    ui->lineEdit_042->setText(d->testData->toString("[显色指数Rx]"));
}
