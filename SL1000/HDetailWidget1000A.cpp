#include "HDetailWidget1000A_p.h"
#include "ui_HDetailWidget1000A.h"
#include "HeData/ITestData.h"

HDetailWidget1000A::HDetailWidget1000A(QWidget *parent) :
    HAbstractTestDetailWidget(*new HDetailWidget1000APrivate, parent),
    ui(new Ui::HDetailWidget1000A)
{
    ui->setupUi(this);
    refreshWidget();
}

HDetailWidget1000A::~HDetailWidget1000A()
{
    delete ui;
}

QString HDetailWidget1000A::typeName()
{
    return "HDetailWidget1000A";
}

void HDetailWidget1000A::refreshWidget()
{
    Q_D(HDetailWidget1000A);
    ui->lineEdit_001->setText(d->testData->toString("[主波长]"));
    ui->lineEdit_002->setText(d->testData->toString("[峰值波长]"));
    ui->lineEdit_003->setText(d->testData->toString("[峰值带宽]"));
    ui->lineEdit_004->setText(d->testData->toString("[光强度]"));
    ui->lineEdit_011->setText(d->testData->toString("[色坐标]"));
    ui->lineEdit_012->setText(d->testData->toString("[色坐标uvp]"));
    ui->lineEdit_013->setText(d->testData->toString("[Duv]"));
    ui->lineEdit_014->setText(d->testData->toString("[光通量]"));
    ui->lineEdit_021->setText(d->testData->toString("[红色比]"));
    ui->lineEdit_022->setText(d->testData->toString("[绿色比]"));
    ui->lineEdit_023->setText(d->testData->toString("[蓝色比]"));
    ui->lineEdit_024->setText(d->testData->toString("[光功率]"));
    ui->lineEdit_031->setText(d->testData->toString("[色温]"));
    ui->lineEdit_032->setText(d->testData->toString("[色纯度]"));
    ui->lineEdit_033->setText(d->testData->toString("[色容差]"));
    ui->lineEdit_034->setText(d->testData->toString("[光效率]"));
    ui->lineEdit_041->setText(d->testData->toString("[显色指数Ra]"));
    ui->lineEdit_042->setText(d->testData->toString("[显色指数R9]"));
    ui->lineEdit_043->setText(d->testData->toString("[显色指数Rx]"));
    ui->lineEdit_051->setText(d->testData->toString("[实测电压]"));
    ui->lineEdit_052->setText(d->testData->toString("[实测电流]"));
    ui->lineEdit_053->setText(d->testData->toString("[反向漏流]"));
    ui->lineEdit_054->setText(d->testData->toString("[电功率]"));
    ui->lineEdit_061->setText(d->testData->toString("[光量子(380-780)]"));
    ui->lineEdit_062->setText(d->testData->toString("[光量子(400-700)]"));
    ui->lineEdit_063->setText(d->testData->toString("[光量子(700-800)]"));
    ui->lineEdit_064->setText(d->testData->toString("[荧光蓝光比]"));
    ui->lineEdit_071->setText(d->testData->toString("[光合光量子通量]"));
    ui->lineEdit_072->setText(d->testData->toString("[光合有效辐射通量]"));
    ui->lineEdit_073->setText(d->testData->toString("[光合光子通量效率]"));
    ui->lineEdit_074->setText(d->testData->toString("[荧光效能]"));
    ui->lineEdit_081->setText(d->testData->toString("[TM30_Rf]"));
    ui->lineEdit_082->setText(d->testData->toString("[TM30_Rg]"));
}
