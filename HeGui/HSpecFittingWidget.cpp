#include "HSpecFittingWidget_p.h"
#include "ui_HSpecFittingWidget.h"
#include "HeCore/HAppContext.h"
#include "HeData/HSpecFitting.h"
#include "HePlugin/HPluginHelper.h"
#include "HeController/IModel.h"
#include "HeData/ITestSpec.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressDialog>

HE_BEGIN_NAMESPACE

HSpecFittingWidgetPrivate::HSpecFittingWidgetPrivate()
{
    model = HAppContext::getContextPointer<IModel>("IModel");
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecFittingWidget::HSpecFittingWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSpecFittingWidgetPrivate),
    ui(new Ui::HSpecFittingWidget)
{
    ui->setupUi(this);
    init();
}

HSpecFittingWidget::~HSpecFittingWidget()
{
    delete ui;
}

QPolygonF HSpecFittingWidget::points()
{
    return d_ptr->data->points();
}

QPolygonF HSpecFittingWidget::curve()
{
    return d_ptr->data->curve(1);
}

void HSpecFittingWidget::setData(HSpecFitting *p)
{
    d_ptr->data = p;
    showData();
}

void HSpecFittingWidget::clearData()
{
    d_ptr->data->clear();
    showData();
}

bool HSpecFittingWidget::setTestState(bool b)
{
    if (d_ptr->testState == b)
        return false;

    if (b)
    {
        auto times = ui->spinBox_1->value();
        auto t1 = ui->doubleSpinBox_1->value();
        auto t2 = ui->doubleSpinBox_2->value();
        if (t1 > t2)
            qSwap(t1, t2);
        d_ptr->integralTime = QPointF(t1, t2);
        d_ptr->pel = ui->spinBox_2->value();
        d_ptr->polyTime = ui->spinBox_3->value();
        d_ptr->points.clear();
        for (int i = 1; i <= times; i++)
            d_ptr->points << QPointF(0.0, t1 + (t2 - t1) * i / times);
        d_ptr->curTimes = 0;
        d_ptr->progressDialog->setRange(0, d_ptr->points.size());
        d_ptr->progressDialog->setValue(0);
        d_ptr->testSpec->setData("[积分时间]", d_ptr->points.first().y());
        d_ptr->model->addAction(ACT_SET_INTEGRAL_TIME);
    }
    d_ptr->testSpec->setFitting(!b);
    d_ptr->testState = b;
    ui->spinBox_1->setEnabled(!b);
    ui->spinBox_2->setEnabled(!b);
    ui->spinBox_3->setEnabled(!b);
    ui->doubleSpinBox_1->setEnabled(!b);
    ui->doubleSpinBox_2->setEnabled(!b);
    ui->checkBox_1->setEnabled(!b);
    emit stateChanged(b);
    return true;
}

void HSpecFittingWidget::handleAction(HActionType action)
{
    if (!d_ptr->testState || action != ACT_GET_SPECTRUM)
        return;

    if (d_ptr->testSpec->data("[光谱采样溢出状态]").toInt() != 0)
    {
        cancel(tr("光谱采样数据溢出!"));
        return;
    }

    if (d_ptr->testSpec->data("[光谱采样帧溢出状态]").toInt() < 0)
        return;

    auto sample = d_ptr->testSpec->sample(1, d_ptr->pel);
    d_ptr->points[d_ptr->curTimes].setX(sample);
    d_ptr->curTimes += 1;
    d_ptr->progressDialog->setValue(d_ptr->curTimes);
    if (d_ptr->curTimes < d_ptr->points.size())
    {
        d_ptr->testSpec->setData("[积分时间]", d_ptr->points[d_ptr->curTimes].y());
        d_ptr->model->addAction(ACT_SET_INTEGRAL_TIME);
        return;
    }

    saveData();
    setTestState(false);
    showData();
    emit fittingFinished();
    QMessageBox::information(this, tr("提示"), tr("拟合完成！"), QMessageBox::Yes);
}

void HSpecFittingWidget::init()
{
    d_ptr->progressDialog = new QProgressDialog(tr("正在采样...."), tr("取消"), 0, 100, this);
    d_ptr->progressDialog->reset();
    HPluginHelper::initWidget("[光谱拟合取样次数]", ui->spinBox_1);
    HPluginHelper::initWidget("[光谱像元]", ui->spinBox_2);
    HPluginHelper::initWidget("[线性多项式项数]", ui->spinBox_3);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_1);
    HPluginHelper::initWidget("[积分时间]", ui->doubleSpinBox_2);
    connect(d_ptr->progressDialog, &QProgressDialog::canceled, this, [=]{ setTestState(false); });
    setWindowTitle(tr("光谱拟合"));
}

void HSpecFittingWidget::cancel(const QString &text)
{
    d_ptr->progressDialog->cancel();
    setTestState(false);
    QMessageBox::warning(this, tr("提示"), text, QMessageBox::Yes);
}

void HSpecFittingWidget::saveData()
{
    int i;
    double temp, max = 0.0;
    QPolygonF points;
    for (auto point : d_ptr->points)
    {
        temp = point.x() / point.y();
        if (temp > max)
            max = temp;
        points << QPointF(point.x(), temp);
    }
    for (i = 0; i < points.size(); i++)
        points[i].setY(points[i].y() / max);
    d_ptr->data->setData("[光谱拟合积分时间范围]", d_ptr->integralTime);
    d_ptr->data->setData("[光谱拟合基准像元]", d_ptr->pel);
    d_ptr->data->setData("[线性多项式项数]", d_ptr->polyTime);
    d_ptr->data->setData("[线性策略]", ui->checkBox_1->isChecked() ? "HPolynomStrategy" : "HPlineStrategy");
    d_ptr->data->setPoints(points);
}

void HSpecFittingWidget::showData()
{
    auto integralTime = d_ptr->data->data("[光谱拟合积分时间范围]").toPointF();
    ui->doubleSpinBox_1->setValue(integralTime.x());
    ui->doubleSpinBox_2->setValue(integralTime.y());
    ui->spinBox_1->setValue(d_ptr->data->data("[光谱拟合取样次数]").toInt());
    ui->spinBox_2->setValue(d_ptr->data->data("[光谱拟合基准像元]").toInt());
    ui->spinBox_3->setValue(d_ptr->data->data("[线性多项式项数]").toInt());
    ui->checkBox_1->setChecked(d_ptr->data->data("[线性策略]").toString() == "HPolynomStrategy");
}

HE_END_NAMESPACE
