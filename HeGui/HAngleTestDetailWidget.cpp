#include "HAngleTestDetailWidget_p.h"
#include "ui_HAngleTestDetailWidget.h"
#include "HeData/ITestData.h"

HE_BEGIN_NAMESPACE

HAngleTestDetailWidget::HAngleTestDetailWidget(QWidget *parent) :
    HAbstractTestDetailWidget(*new HAngleTestDetailWidgetPrivate, parent),
    ui(new Ui::HAngleTestDetailWidget)
{
    ui->setupUi(this);
    refreshWidget();
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

void HAngleTestDetailWidget::refreshWidget()
{
    Q_D(HAngleTestDetailWidget);
    ui->lineEdit_001->setText(d->testData->toString("[最大光强度角]"));
    ui->lineEdit_002->setText(d->testData->toString("[最大光强度]"));
    ui->lineEdit_003->setText(d->testData->toString("[法相光强度]"));
    ui->lineEdit_004->setText(d->testData->toString("[光强度]"));
    ui->lineEdit_011->setText(d->testData->toString("[左半光强度角]"));
    ui->lineEdit_012->setText(d->testData->toString("[右半光强度角]"));
    ui->lineEdit_013->setText(d->testData->toString("[半光强度夹角]"));
    ui->lineEdit_014->setText(d->testData->toString("[角度光通量]"));
    ui->lineEdit_021->setText(d->testData->toString("[左1/5光强度角]"));
    ui->lineEdit_022->setText(d->testData->toString("[右1/5光强度角]"));
    ui->lineEdit_023->setText(d->testData->toString("[1/5光强度夹角]"));
}

void HAngleTestDetailWidget::refreshData(QString)
{
    Q_D(HAngleTestDetailWidget);
    ui->lineEdit_004->setText(d->testData->toString("[光强度]"));
}

HE_END_NAMESPACE
