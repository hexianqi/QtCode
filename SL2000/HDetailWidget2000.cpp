#include "HDetailWidget2000_p.h"
#include "ui_HDetailWidget2000.h"
#include "HeData/ITestData.h"

HDetailWidget2000::HDetailWidget2000(QWidget *parent) :
    HAbstractTestDetailWidget(*new HDetailWidget2000Private, parent),
    ui(new Ui::HDetailWidget2000)
{
    ui->setupUi(this);
    init();
}

HDetailWidget2000::~HDetailWidget2000()
{
    delete ui;
}

QString HDetailWidget2000::typeName()
{
    return "HDetailWidget2000";
}

void HDetailWidget2000::initHash()
{
    Q_D(HDetailWidget2000);
    d->lineEdits.insert("[光谱光通量]", ui->lineEdit_004);
    d->lineEdits.insert("[光功率]",     ui->lineEdit_014);
    d->lineEdits.insert("[主波长]",     ui->lineEdit_001);
    d->lineEdits.insert("[峰值波长]",   ui->lineEdit_002);
    d->lineEdits.insert("[峰值带宽]",   ui->lineEdit_003);
    d->lineEdits.insert("[色坐标]",     ui->lineEdit_011);
    d->lineEdits.insert("[色坐标uvp]",  ui->lineEdit_012);
    d->lineEdits.insert("[Duv]",        ui->lineEdit_013);
    d->lineEdits.insert("[红色比]",     ui->lineEdit_021);
    d->lineEdits.insert("[绿色比]",     ui->lineEdit_022);
    d->lineEdits.insert("[蓝色比]",     ui->lineEdit_023);
    d->lineEdits.insert("[色温]",       ui->lineEdit_031);
    d->lineEdits.insert("[色纯度]",     ui->lineEdit_032);
    d->lineEdits.insert("[色容差]",     ui->lineEdit_033);
    d->lineEdits.insert("[显色指数Ra]", ui->lineEdit_041);
    d->lineEdits.insert("[显色指数Rx]", ui->lineEdit_042);
}
