#include "HDetailWidget2100DC_p.h"
#include "ui_HDetailWidget2100DC.h"
#include "HeData/ITestData.h"

HDetailWidget2100DC::HDetailWidget2100DC(QWidget *parent) :
    HAbstractTestDetailWidget(*new HDetailWidget2100DCPrivate, parent),
    ui(new Ui::HDetailWidget2100DC)
{
    ui->setupUi(this);
    init();
}

HDetailWidget2100DC::~HDetailWidget2100DC()
{
    delete ui;
}

QString HDetailWidget2100DC::typeName()
{
    return "HDetailWidget2100DC";
}

void HDetailWidget2100DC::initHash()
{
    Q_D(HDetailWidget2100DC);
    d->lineEdits.insert("[实测电压]",           ui->lineEdit_004);
    d->lineEdits.insert("[实测电流]",           ui->lineEdit_014);
    d->lineEdits.insert("[电功率]",             ui->lineEdit_024);
    d->lineEdits.insert("[光谱光通量]",         ui->lineEdit_001);
    d->lineEdits.insert("[光功率]",             ui->lineEdit_002);
    d->lineEdits.insert("[光效率]",             ui->lineEdit_003);
    d->lineEdits.insert("[主波长]",             ui->lineEdit_011);
    d->lineEdits.insert("[峰值波长]",           ui->lineEdit_012);
    d->lineEdits.insert("[峰值带宽]",           ui->lineEdit_013);
    d->lineEdits.insert("[色坐标]",             ui->lineEdit_021);
    d->lineEdits.insert("[色坐标uvp]",          ui->lineEdit_022);
    d->lineEdits.insert("[Duv]",                ui->lineEdit_023);
    d->lineEdits.insert("[红色比]",             ui->lineEdit_031);
    d->lineEdits.insert("[绿色比]",             ui->lineEdit_032);
    d->lineEdits.insert("[蓝色比]",             ui->lineEdit_033);
    d->lineEdits.insert("[色温]",               ui->lineEdit_041);
    d->lineEdits.insert("[色纯度]",             ui->lineEdit_042);
    d->lineEdits.insert("[色容差]",             ui->lineEdit_043);
    d->lineEdits.insert("[显色指数Ra]",         ui->lineEdit_071);
    d->lineEdits.insert("[显色指数R9]",         ui->lineEdit_072);
    d->lineEdits.insert("[显色指数Rx]",         ui->lineEdit_073);
    d->lineEdits.insert("[TM30_Rf]",            ui->lineEdit_081);
    d->lineEdits.insert("[TM30_Rg]",            ui->lineEdit_082);
    d->lineEdits.insert("[光量子(380-780)]",    ui->lineEdit_051);
    d->lineEdits.insert("[光量子(400-700)]",    ui->lineEdit_052);
    d->lineEdits.insert("[光量子(700-800)]",    ui->lineEdit_053);
    d->lineEdits.insert("[光合光量子通量]",     ui->lineEdit_061);
    d->lineEdits.insert("[光合有效辐射通量]",   ui->lineEdit_062);
    d->lineEdits.insert("[光合光子通量效率]",   ui->lineEdit_063);
    d->lineEdits.insert("[荧光蓝光比]",         ui->lineEdit_054);
    d->lineEdits.insert("[荧光效能]",           ui->lineEdit_064);

}
