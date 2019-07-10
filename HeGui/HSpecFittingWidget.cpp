#include "HSpecFittingWidget_p.h"
#include "HeData/HSpecFitting.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeData/ITestSpec.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressDialog>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecFittingWidgetPrivate::HSpecFittingWidgetPrivate()
{
    model = HAppContext::getContextPointer<IModel>("IModel");
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecFittingWidget::HSpecFittingWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new HSpecFittingWidgetPrivate)
{
    init();
}

HSpecFittingWidget::HSpecFittingWidget(HSpecFittingWidgetPrivate &p, QWidget *parent)
    : QWidget(parent)
    , d_ptr(&p)
{
    init();
}

HSpecFittingWidget::~HSpecFittingWidget()
{
    qDebug() << __func__;
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

QPolygonF HSpecFittingWidget::fittingPoints()
{
    return d_ptr->data->fittingPoints();
}

void HSpecFittingWidget::handleAction(HActionType action)
{
    if (!d_ptr->testState || action != ACT_GET_SPECTRUM)
        return;

    if (d_ptr->testSpec->data("[采样溢出状态]").toInt() != 0)
    {
        cancel(tr("采样数据溢出!"));
        return;
    }

    if (d_ptr->testSpec->data("[采样帧溢出状态]").toInt() < 0)
        return;

    auto sample = d_ptr->testSpec->sample(1, d_ptr->pel);
//    if (sample < d_ptr->lastSample)
//    {
//        cancel(tr("采样数据不对（积分时间：%1ms）!").arg(d_ptr->points[d_ptr->curTimes].y()));
//        return;
//    }
//    d_ptr->lastSample = sample;
    d_ptr->points[d_ptr->curTimes].setX(sample);
    d_ptr->curTimes += 1;
    d_ptr->progressDialog->setValue(d_ptr->curTimes);
    if (d_ptr->curTimes < d_ptr->points.size())
    {
        d_ptr->testSpec->setIntegralTime(d_ptr->points[d_ptr->curTimes].y());
        d_ptr->model->addAction(ACT_SET_INTEGRAL_TIME);
        return;
    }

    saveData();
    setTest(false);
    showData();
    emit fittingFinished();
    QMessageBox::information(this, tr("提示"), tr("拟合完成！"), QMessageBox::Yes);
}

bool HSpecFittingWidget::setTest(bool b)
{
    if (d_ptr->testState == b)
        return false;
    if (b)
    {
        if (!initParam())
            return false;
        d_ptr->lastSample = 0.0;
        d_ptr->curTimes = 0;        
        d_ptr->progressDialog->setRange(0, d_ptr->points.size());
        d_ptr->progressDialog->setValue(0);
        d_ptr->testSpec->setIntegralTime(d_ptr->points.first().y());
        d_ptr->model->addAction(ACT_SET_INTEGRAL_TIME);
        qDebug() << "HSpecFittingWidget";
    }
    d_ptr->testSpec->setFitting(!b);
    d_ptr->testState = b;
    emit testStateChanged(b);
    return true;
}

void HSpecFittingWidget::cancel(QString text)
{
    d_ptr->progressDialog->cancel();
    setTest(false);
    QMessageBox::warning(this, tr("提示"), text, QMessageBox::Yes);
}

void HSpecFittingWidget::init()
{
    d_ptr->progressDialog = new QProgressDialog(tr("正在采样...."), tr("取消"), 0, 100, this);
    d_ptr->progressDialog->reset();
    connect(d_ptr->progressDialog, &QProgressDialog::canceled, this, [=]{ setTest(false); });
    setWindowTitle(tr("光谱拟合"));
}

HE_GUI_END_NAMESPACE
