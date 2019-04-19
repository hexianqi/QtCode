#include "HSpecSampleChartView_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeController/ITestSpec.h"
#include "HePlugin/HMarkerChartExtend.h"
#include "HePlugin/HSingleAxisChart.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QGraphicsSimpleTextItem>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecSampleChartViewPrivate::HSpecSampleChartViewPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    decimals = 0;
}

HSpecSampleChartView::HSpecSampleChartView(QWidget *parent) :
    HVernierChartView(*new HSpecSampleChartViewPrivate, nullptr, parent)
{
    init();
}

HSpecSampleChartView::~HSpecSampleChartView()
{
    qDebug() << __func__;
}

void HSpecSampleChartView::setEnablePeak(bool b)
{
    Q_D(HSpecSampleChartView);
    if (d->enablePeak == b)
        return;
    d->enablePeak = b;
}

void HSpecSampleChartView::refreshWidget()
{
    Q_D(HSpecSampleChartView);
    auto series = chart()->series();
    for (int i = 0; i < series.size(); i++)
    {
        auto s = qobject_cast<QXYSeries *>(series[i]);
        if (s == nullptr)
            continue;
        s->replace(d->testSpec->samplePoly(i));
    }
    refreshCenter();
}

void HSpecSampleChartView::refreshCenter()
{
    Q_D(HSpecSampleChartView);
    if (d->verniers.isEmpty())
        return;

    QStringList list;
    auto series = chart()->series();
    for (int i = 0; i < series.size(); i++)
    {
        if (!series[i]->isVisible())
            continue;
        auto p = d->testSpec->sampleMax(i, d->verniers.first(), d->verniers.last());
        list << QString(" Max%1(%2, %3) ").arg(i).arg(p.x()).arg(p.y());
    }
    d->textCenter->setText(QString("%1").arg(list.join('\t')));
}

void HSpecSampleChartView::refreshRight()
{
    Q_D(HSpecSampleChartView);
    if (d->verniers.isEmpty())
        return;

    QStringList list;
    for (auto v : d->verniers)
        list << QString("%1").arg(d->testSpec->pelsToWave(v), 0, 'f', 1);
    d->textRight->setText(QString("(%1)").arg(list.join(',')));
}

void HSpecSampleChartView::setVernier(QList<double> value)
{
    Q_D(HSpecSampleChartView);
    d->verniers = value;
    refreshRight();
    if (d->enablePeak)
        refreshCenter();
}

void HSpecSampleChartView::init()
{
    Q_D(HSpecSampleChartView);
    auto axisX = new QValueAxis;
    axisX->setLabelFormat("%d");
    axisX->setRange(0, 2100);
    axisX->setTickCount(6);
    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%d");
    axisY->setRange(0, 65535);
    axisY->setTickCount(6);
    auto chart = new HSingleAxisChart;
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    auto series1 = new QLineSeries();
    series1->setName(tr("原始曲线"));
    chart->addSeries(series1);
    auto series2 = new QLineSeries();
    series2->setName(tr("预处理曲线"));
    chart->addSeries(series2);
    auto marker = new HMarkerChartExtend(chart, this);
    marker->connectExtend();
    connect(this, &HSpecSampleChartView::vernierTextChanged, this, [=](QString text) { d->textLeft->setText(text); });
    connect(this, &HSpecSampleChartView::vernierValueChanged, this, &HSpecSampleChartView::setVernier);
    setChart(chart);
    setWindowTitle(tr("光谱采样曲线"));
    HVernierChartView::init();
}

HE_GUI_END_NAMESPACE

