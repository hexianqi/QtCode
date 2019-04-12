#include "HVernierWidget_p.h"
#include "HCartesianCoordinate.h"
#include "HVernierTracking.h"
#include <QLabel>
#include <QGridLayout>

HVernierWidgetPrivate::HVernierWidgetPrivate(HVernierWidget *q) :
    HCartesianWidgetPrivate(q)
{
    halfSide = true;
}

HVernierWidget::HVernierWidget(QWidget *parent)
    : HCartesianWidget(*new HVernierWidgetPrivate(this), parent)
{
    init();
}

HVernierWidget::HVernierWidget(HVernierWidgetPrivate &p, QWidget *parent)
    : HCartesianWidget(p, parent)
{
    init();
}

HVernierWidget::~HVernierWidget()
{
}

void HVernierWidget::setDecimals(int value)
{
    Q_D(HVernierWidget);
    if (d->decimals == value)
        return;
    d->decimals = value;
    updataVernier();
}

void HVernierWidget::updataVernier()
{
    Q_D(HVernierWidget);
    auto rect = (d->plotArea.width() < 0.1 || d->plotArea.height() < 0.1) ? QRectF(0, 0, 1, 1) : d->plotArea;
    auto verniers = d->coordinate->mapToValue(d->tracking->verniers(), rect);
    if (verniers.size() < 1)
        return;

    double value;
    QVector<double> values;
    QStringList list;
    for (auto p : verniers)
    {
        value = d->tracking->orientation() == Qt::Vertical ? p.x() : p.y();
        values << value;
        list << QString("%1").arg(value, 0, 'f', d->decimals);
    }
    emit vernierValueChanged(values);
    emit vernierTextChanged(QString("(%1)").arg(list.join(',')));
}

HVernierTracking *HVernierWidget::tracking()
{
    Q_D(HVernierWidget);
    return d->tracking;
}

QLabel *HVernierWidget::labelLeft()
{
    Q_D(HVernierWidget);
    return d->labelLeft;
}

QLabel *HVernierWidget::labelCenter()
{
    Q_D(HVernierWidget);
    return d->labelCenter;
}

QLabel *HVernierWidget::labelRight()
{
    Q_D(HVernierWidget);
    return d->labelRight;
}

int HVernierWidget::decimals()
{
    Q_D(HVernierWidget);
    return d->decimals;
}

void HVernierWidget::paintEvent(QPaintEvent *e)
{
    Q_D(HVernierWidget);
    d->tracking->paintEvent(e);
    HCartesianWidget::paintEvent(e);
}

void HVernierWidget::mousePressEvent(QMouseEvent *e)
{
    Q_D(HVernierWidget);
    if (d->tracking->mousePressEvent(e))
        return;
    HCartesianWidget::mousePressEvent(e);
}

void HVernierWidget::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HVernierWidget);
    if (d->tracking->mouseMoveEvent(e))
        return;
    HCartesianWidget::mouseMoveEvent(e);
}

void HVernierWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HVernierWidget);
    if (d->tracking->mouseReleaseEvent(e))
        return;
    HCartesianWidget::mouseReleaseEvent(e);
}

void HVernierWidget::handleCoordinateChanged(HCartesianCoordinate *p)
{
    HCartesianWidget::handleCoordinateChanged(p);
    updataVernier();
}

void HVernierWidget::handlePlotAreaChanged(QRectF value)
{
    Q_D(HVernierWidget);
    auto h = fontMetrics().height();
    d->tracking->setValidRegion(value);
    d->layoutLabel->setGeometry(QRectF(value.left() + 15, value.top() - h - 5, value.width() - 30, h).toRect());
    updataVernier();
}

void HVernierWidget::handleOrientationChanged()
{
    update();
    updataVernier();
}

void HVernierWidget::handleVernierPosChanged(QPointF pos)
{
    Q_D(HVernierWidget);
    if (d->tracking->orientation() == Qt::Vertical)
        update(QRectF(pos.x(), d->plotArea.top(), 1, d->plotArea.height()).toRect());
    else
        update(QRectF(d->plotArea.left(), pos.y(), d->plotArea.width(), 1).toRect());
    updataVernier();
}

void HVernierWidget::handleVernierSizeChanged()
{
    update();
    updataVernier();
}

void HVernierWidget::init()
{
    Q_D(HVernierWidget);
    d->tracking = new HVernierTracking(Qt::Vertical, this);
    d->tracking->resizeVernier(2);
    d->labelLeft = new QLabel(this);
    d->labelLeft->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    d->labelCenter = new QLabel(this);
    d->labelCenter->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
    d->labelRight = new QLabel(this);
    d->labelRight->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    d->layoutLabel = new QGridLayout;
    d->layoutLabel->addWidget(d->labelLeft, 0, 0);
    d->layoutLabel->addWidget(d->labelCenter, 0, 1);
    d->layoutLabel->addWidget(d->labelRight, 0, 2);
    connect(this, &HVernierWidget::plotAreaChanged, this, &HVernierWidget::handlePlotAreaChanged);
    connect(d->tracking, &HVernierTracking::orientationChanged, this, &HVernierWidget::handleOrientationChanged);
    connect(d->tracking, &HVernierTracking::vernierPosChanged, this, &HVernierWidget::handleVernierPosChanged);
    connect(d->tracking, &HVernierTracking::vernierSizeChanged, this, &HVernierWidget::handleVernierSizeChanged);
}
