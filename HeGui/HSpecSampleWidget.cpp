#include "HSpecSampleWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestSpec.h"
#include "HePlugin/HPluginHelper.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QLabel>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HSpecSampleWidgetPrivate::HSpecSampleWidgetPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    decimals = 0;
    curveVisibles << true << true;
}

HSpecSampleWidget::HSpecSampleWidget(QWidget *parent) :
    HVernierWidget(*new HSpecSampleWidgetPrivate, parent)
{
    init();
}

HSpecSampleWidget::~HSpecSampleWidget()
{
    qDebug() << __func__;
}

void HSpecSampleWidget::setEnablePeak(bool b)
{
    Q_D(HSpecSampleWidget);
    if (d->enablePeak == b)
        return;
    d->enablePeak = b;
}

void HSpecSampleWidget::refreshWidget()
{
    Q_D(HSpecSampleWidget);
    for (int i = 0; i < d->curveVisibles.size(); i++)
    {
        if (d->curveVisibles[i])
            addPolygon(i, d->testSpec->samplePoly(i));
        else
            removePolygon(i);
    }
    refreshCenter();
}

void HSpecSampleWidget::refreshCenter()
{
    Q_D(HSpecSampleWidget);
    if (d->verniers.isEmpty())
        return;

    QStringList list;
    for (int i = 0; i < d->curveVisibles.size(); i++)
    {
        if (!d->curveVisibles[i])
            continue;
        auto p = d->testSpec->sampleMax(i, d->verniers.first(), d->verniers.last());
        list << QString(" Max%1(%2, %3) ").arg(i).arg(p.x()).arg(p.y());
    }
    d->labelCenter->setText(QString("%1").arg(list.join('\t')));
}

void HSpecSampleWidget::refreshRight()
{
    Q_D(HSpecSampleWidget);
    if (d->verniers.isEmpty())
        return;

    QStringList list;
    for (auto v : d->verniers)
        list << QString("%1").arg(d->testSpec->pelsToWave(v), 0, 'f', 1);
    d->labelRight->setText(QString("(%1)").arg(list.join(',')));
}

void HSpecSampleWidget::setCurve1Visible(bool b)
{
    Q_D(HSpecSampleWidget);
    d->curveVisibles[0] = b;
    refreshWidget();
}

void HSpecSampleWidget::setCurve2Visible(bool b)
{
    Q_D(HSpecSampleWidget);
    d->curveVisibles[1] = b;
    refreshWidget();
}

void HSpecSampleWidget::setVernier(const QList<double> &value)
{
    Q_D(HSpecSampleWidget);
    d->verniers = value;
    refreshRight();
    if (d->enablePeak)
        refreshCenter();
}

void HSpecSampleWidget::init()
{
    Q_D(HSpecSampleWidget);
    auto curve1 = new QAction(tr("原始曲线"), this);
    curve1->setCheckable(true);
    curve1->setChecked(d->curveVisibles[0]);
    auto curve2 = new QAction(tr("预处理曲线"), this);
    curve2->setCheckable(true);
    curve2->setChecked(d->curveVisibles[1]);
    HPluginHelper::addSeparator(this);
    addAction(curve1);
    addAction(curve2);
    connect(curve1, &QAction::triggered, this, &HSpecSampleWidget::setCurve1Visible);
    connect(curve2, &QAction::triggered, this, &HSpecSampleWidget::setCurve2Visible);
    connect(this, &HSpecSampleWidget::vernierTextChanged, d->labelLeft, &QLabel::setText);
    connect(this, &HSpecSampleWidget::vernierValueChanged, this, &HSpecSampleWidget::setVernier);
    setCoordinate(QRectF(0, 0, 2100, 65535), 5, 5);
    setWindowTitle(tr("光谱采样曲线"));
}

HE_GUI_END_NAMESPACE
