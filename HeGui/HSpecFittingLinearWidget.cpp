#include "HSpecFittingLinearWidget_p.h"
#include "ui_HSpecFittingLinearWidget.h"
#include "HeData/HSpecFitting.h"
#include "HePlugin/HPluginHelper.h"
#include <QtGui/QValidator>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecFittingLinearWidget::HSpecFittingLinearWidget(QWidget *parent):
    HSpecFittingWidget(*new HSpecFittingLinearWidgetPrivate, parent),
    ui(new Ui::HSpecFittingLinearWidget)
{
    ui->setupUi(this);
    init();
}

HSpecFittingLinearWidget::~HSpecFittingLinearWidget()
{
    qDebug() << __func__;
    delete ui;
}

bool HSpecFittingLinearWidget::setTest(bool b)
{
    if (!HSpecFittingWidget::setTest(b))
        return false;
    ui->spinBox_1->setEnabled(!b);
    ui->spinBox_2->setEnabled(!b);
    ui->doubleSpinBox_1->setEnabled(!b);
    ui->doubleSpinBox_2->setEnabled(!b);
    return true;
}

bool HSpecFittingLinearWidget::initParam()
{
    Q_D(HSpecFittingLinearWidget);
    auto times = ui->spinBox_1->value();
    auto t1 = ui->doubleSpinBox_1->value();
    auto t2 = ui->doubleSpinBox_2->value();
    if (t1 > t2)
        qSwap(t1, t2);
    d->pel = ui->spinBox_2->value();
    d->points.clear();
    for (int i = 1; i <= times; i++)
        d->points << QPointF(0.0, t1 + (t2 - t1) * i / times);
    return true;
}

void HSpecFittingLinearWidget::saveData()
{
    Q_D(HSpecFittingLinearWidget);
    d->data->setData("[光谱拟合基准像元]", d->pel);
    d->data->setFittingPoints(d->points);
}

void HSpecFittingLinearWidget::showData()
{
    Q_D(HSpecFittingLinearWidget);
    auto integralTime = d->data->data("[光谱拟合积分时间范围]").toPointF();
    ui->doubleSpinBox_1->setValue(integralTime.x());
    ui->doubleSpinBox_2->setValue(integralTime.y());
    ui->spinBox_1->setValue(d->data->data("[光谱拟合取样次数]").toInt());
    ui->spinBox_2->setValue(d->data->data("[光谱拟合基准像元]").toInt());
}

void HSpecFittingLinearWidget::init()
{
    HPluginHelper::initWidget("[光谱拟合取样次数]", ui->spinBox_1);
    HPluginHelper::initWidget("[光谱像元]", ui->spinBox_2);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_2);
}

HE_GUI_END_NAMESPACE
