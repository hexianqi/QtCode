#include "HSpecSampleWidget_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeController/ITestSpec.h"
#include "HePlugin/HPluginHelper.h"
#include <QAction>
#include <QLabel>

HE_GUI_BEGIN_NAMESPACE

HSpecSampleWidgetPrivate::HSpecSampleWidgetPrivate(HSpecSampleWidget *q) :
    HVernierWidgetPrivate(q)
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    curveVisibles.append(true);
    curveVisibles.append(true);
}

HSpecSampleWidget::HSpecSampleWidget(QWidget *parent) :
    HVernierWidget(*new HSpecSampleWidgetPrivate(this), parent)
{
    init();
}

HSpecSampleWidget::~HSpecSampleWidget()
{
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
    refreshLabelCenter();
}

void HSpecSampleWidget::refreshLabelCenter()
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
    d->labelCenter->setText(QString("(%1)").arg(list.join('\t')));
}

void HSpecSampleWidget::refreshLabelRight()
{
    Q_D(HSpecSampleWidget);
    if (d->verniers.isEmpty())
        return;

    QStringList list;
    for (auto v : d->verniers)
        list << QString(" %1").arg(d->testSpec->pelsToWave(v), 0, 'f', 1);
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

void HSpecSampleWidget::setVernier(QVector<double> value)
{
    Q_D(HSpecSampleWidget);
    d->verniers = value;
    refreshLabelRight();
    if (d->enablePeak)
        refreshLabelCenter();
}

void HSpecSampleWidget::init()
{
    Q_D(HSpecSampleWidget);
    d->actionCurve1 = new QAction(tr("原始曲线"), this);
    d->actionCurve1->setCheckable(true);
    d->actionCurve1->setChecked(d->curveVisibles[0]);
    d->actionCurve2 = new QAction(tr("预处理曲线"), this);
    d->actionCurve2->setCheckable(true);
    d->actionCurve2->setChecked(d->curveVisibles[1]);

    setDecimals(0);
    setCoordinate(QRectF(0, 0, 2100, 65535), 5, 5);
    HPluginHelper::addSeparator(this);
    addAction(d->actionCurve1);
    addAction(d->actionCurve2);
    connect(d->actionCurve1, &QAction::toggled, this, &HSpecSampleWidget::setCurve1Visible);
    connect(d->actionCurve2, &QAction::toggled, this, &HSpecSampleWidget::setCurve2Visible);
    connect(this, &HSpecSampleWidget::vernierTextChanged, d->labelLeft, &QLabel::setText);
    connect(this, &HSpecSampleWidget::vernierValueChanged, this, &HSpecSampleWidget::setVernier);
    setWindowTitle(tr("光谱采样曲线"));
}

HE_GUI_END_NAMESPACE
