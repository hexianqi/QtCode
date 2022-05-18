#include "HAngleTestDetailWidget_p.h"
#include "ui_HAngleTestDetailWidget.h"

HE_BEGIN_NAMESPACE

HAngleTestDetailWidget::HAngleTestDetailWidget(QWidget *parent) :
    HAbstractTestDetailWidget(*new HAngleTestDetailWidgetPrivate, parent),
    ui(new Ui::HAngleTestDetailWidget)
{
    ui->setupUi(this);
    init();
    setWindowTitle(tr("光强角度分布数据"));
}

HAngleTestDetailWidget::~HAngleTestDetailWidget()
{
    delete ui;
}

QString HAngleTestDetailWidget::typeName()
{
    return "HAngleTestDetailWidget";
}

void HAngleTestDetailWidget::initHash()
{
    Q_D(HAngleTestDetailWidget);
    d->lineEdits.insert("[实测电压]",        ui->lineEdit_014);
    d->lineEdits.insert("[最大光强度角]",    ui->lineEdit_001);
    d->lineEdits.insert("[最大光强度]",      ui->lineEdit_002);
    d->lineEdits.insert("[法向光强度]",      ui->lineEdit_003);
    d->lineEdits.insert("[光强度]",          ui->lineEdit_004);
    d->lineEdits.insert("[角度光通量]",      ui->lineEdit_024);
    d->lineEdits.insert("[左半光强度角]",    ui->lineEdit_011);
    d->lineEdits.insert("[右半光强度角]",    ui->lineEdit_012);
    d->lineEdits.insert("[半光强度夹角]",    ui->lineEdit_013);
    d->lineEdits.insert("[左1/5光强度角]",   ui->lineEdit_021);
    d->lineEdits.insert("[右1/5光强度角]",   ui->lineEdit_022);
    d->lineEdits.insert("[1/5光强度夹角]",   ui->lineEdit_023);
}

HE_END_NAMESPACE
