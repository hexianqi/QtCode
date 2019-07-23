#include "HSpecFittingPolynomWidget_p.h"
#include "ui_HSpecFittingPolynomWidget.h"
#include "HeData/HSpecFitting.h"
#include "HePlugin/HPluginHelper.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecFittingPolynomWidget::HSpecFittingPolynomWidget(QWidget *parent) :
    HSpecFittingWidget(*new HSpecFittingPolynomWidgetPrivate, parent),
    ui(new Ui::HSpecFittingPolynomWidget)
{
    ui->setupUi(this);
    init();
}

HSpecFittingPolynomWidget::~HSpecFittingPolynomWidget()
{
    delete ui;
}

bool HSpecFittingPolynomWidget::setTest(bool b)
{
    if (!HSpecFittingWidget::setTest(b))
        return false;
    ui->spinBox_1->setEnabled(!b);
    ui->spinBox_2->setEnabled(!b);
    ui->spinBox_3->setEnabled(!b);
    ui->doubleSpinBox_1->setEnabled(!b);
    ui->doubleSpinBox_2->setEnabled(!b);
    return true;
}

bool HSpecFittingPolynomWidget::initParam()
{
    Q_D(HSpecFittingPolynomWidget);
    auto times = ui->spinBox_1->value();
    auto t1 = ui->doubleSpinBox_1->value();
    auto t2 = ui->doubleSpinBox_2->value();
    if (t1 > t2)
        qSwap(t1, t2);
    d->integralTime = QPointF(t1, t2);
    d->pel = ui->spinBox_2->value();
    d->polyTime = ui->spinBox_3->value();
    d->points.clear();
    for (int i = 1; i <= times; i++)
        d->points << QPointF(0.0, t1 + (t2 - t1) * i / times);
    return true;
}

void HSpecFittingPolynomWidget::saveData()
{
    Q_D(HSpecFittingPolynomWidget);
    d->data->setData("[光谱拟合积分时间范围]", d->integralTime);d->data->setData("[光谱拟合基准像元]", d->pel);
    d->data->setData("[光谱拟合多项式项数]", d->polyTime);
    d->data->setFittingPoints(d->points);
}

void HSpecFittingPolynomWidget::showData()
{
    Q_D(HSpecFittingPolynomWidget);
    auto integralTime = d->data->data("[光谱拟合积分时间范围]").toPointF();
    ui->doubleSpinBox_1->setValue(integralTime.x());
    ui->doubleSpinBox_2->setValue(integralTime.y());
    ui->spinBox_1->setValue(d->data->data("[光谱拟合取样次数]").toInt());
    ui->spinBox_2->setValue(d->data->data("[光谱拟合基准像元]").toInt());
    ui->spinBox_3->setValue(d->data->data("[光谱拟合多项式项数]").toInt());
}

void HSpecFittingPolynomWidget::init()
{
    HPluginHelper::initWidget("[光谱拟合取样次数]", ui->spinBox_1);
    HPluginHelper::initWidget("[光谱像元]", ui->spinBox_2);
    HPluginHelper::initWidget("[光谱拟合多项式项数]", ui->spinBox_3);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_2);
}

HE_GUI_END_NAMESPACE
