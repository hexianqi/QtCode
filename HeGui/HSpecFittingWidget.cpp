#include "HSpecFittingWidget_p.h"
#include "HeData/HSpecFitting.h"
#include "HeCore/HAppContext.h"
#include "HeController/IModel.h"
#include "HeController/ITestSpec.h"
#include <QMessageBox>
#include <QProgressDialog>

HE_GUI_BEGIN_NAMESPACE

HSpecFittingWidgetPrivate::HSpecFittingWidgetPrivate(HSpecFitting *d)
{
    data = d;
    model = HAppContext::getContextPointer<IModel>("IModel");
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecFittingWidget::HSpecFittingWidget(HSpecFitting *data, QWidget *parent)
    : QWidget(parent)
    , d_ptr(new HSpecFittingWidgetPrivate(data))
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
}

void HSpecFittingWidget::restoreDefault()
{
    d_ptr->data->restoreDefault();
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
        d_ptr->progressDialog->cancel();
        setTest(false);
        QMessageBox::warning(this, tr("提示"), tr("采样溢出!"), QMessageBox::Yes);
        return;
    }

    if (!d_ptr->testSpec->data("[采样帧溢出状态]").toBool())
        return;

    d_ptr->points[d_ptr->curTimes++].setX(d_ptr->testSpec->sample(1, d_ptr->pel));
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
        d_ptr->curTimes = 0;
        d_ptr->progressDialog->setRange(0, d_ptr->points.size());
        d_ptr->progressDialog->setValue(0);
        d_ptr->testSpec->setIntegralTime(d_ptr->points.first().y());
        d_ptr->model->addAction(ACT_SET_INTEGRAL_TIME);
    }
    d_ptr->testSpec->setFitting(b);
    d_ptr->testState = b;
    emit testStateChanged(b);
    return true;
}

void HSpecFittingWidget::init()
{
    d_ptr->progressDialog = new QProgressDialog(this);
    connect(d_ptr->progressDialog, &QProgressDialog::cancel, this, [=]{ setTest(false); });
}

HE_GUI_END_NAMESPACE
