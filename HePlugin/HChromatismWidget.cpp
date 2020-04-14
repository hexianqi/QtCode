#include "HChromatismWidget_p.h"
#include "HCartesianCoordinate.h"
#include "HeAlgorithm/HMath.h"
#include <QtCore/QVariant>
#include <QtGui/QPainter>


HE_ALGORITHM_USE_NAMESPACE

HChromatismWidgetPrivate::HChromatismWidgetPrivate()
{
    fontTitle.setPointSize(12);
    fontTitle.setWeight(QFont::Bold);
    fontBody.setPointSize(12);
    fontBody.setWeight(QFont::Bold);
    pointFocus = QPointF(0.0, 0.0);
    pointCenter = QPointF(0.5, 0.5);
}

HChromatismWidget::HChromatismWidget(QWidget *parent) :
    HCartesianWidget(*new HChromatismWidgetPrivate, parent)
{
    init();
}

void HChromatismWidget::setData(const QVariantMap &value)
{
    Q_D(HChromatismWidget);
    if (value.contains("[标题]"))
        d->title = value.value("[标题]").toString();
    if (value.contains("[标准Sdcm]"))
        d->sdcmStd = value.value("[标准Sdcm]").toDouble();
    if (value.contains("[中心点]"))
        d->pointCenter = value.value("[中心点]").toPointF();
    if (value.contains("[旋转角]"))
        d->theta = value.value("[旋转角]").toDouble();
    if (value.contains("[轴A]"))
        d->axisA = value.value("[轴A]").toDouble();
    if (value.contains("[轴B]"))
        d->axisB = value.value("[轴B]").toDouble();
    if (value.contains("[测试点]"))
        d->pointFocus = value.value("[测试点]").toPointF();
    if (value.contains("[测试Sdcm]"))
        d->sdcmFocus = value.value("[测试Sdcm]").toDouble();
    auto poly = HMath::calcEllipse(d->pointCenter, d->sdcmStd, d->theta, d->axisA, d->axisB);
    fixCoordinate(d->pointCenter, poly);
    addPolygon(0, poly, true);
}

void HChromatismWidget::setColorPointFocus(const QColor &value)
{
    Q_D(HChromatismWidget);
    if (d->colorPointFocus == value)
        return;
    d->colorPointFocus = value;
    refreshPixmap();
}

void HChromatismWidget::setColorTitle(const QColor &value)
{
    Q_D(HChromatismWidget);
    if (d->colorTitle == value)
        return;
    d->colorTitle = value;
    refreshPixmap();
}

void HChromatismWidget::setColorBody(const QColor &value)
{
    Q_D(HChromatismWidget);
    if (d->colorBody == value)
        return;
    d->colorBody = value;
    refreshPixmap();
}

void HChromatismWidget::setFontTitle(const QFont &value)
{
    Q_D(HChromatismWidget);
    if (d->fontTitle == value)
        return;
    d->fontTitle = value;
    refreshPixmap();
}

void HChromatismWidget::setFontBody(const QFont &value)
{
    Q_D(HChromatismWidget);
    if (d->fontTitle == value)
        return;
    d->fontTitle = value;
    refreshPixmap();
}

QColor HChromatismWidget::colorPointFocus()
{
    Q_D(HChromatismWidget);
    return d->colorPointFocus;
}

QColor HChromatismWidget::colorTitle()
{
    Q_D(HChromatismWidget);
    return d->colorTitle;
}

QColor HChromatismWidget::colorBody()
{
    Q_D(HChromatismWidget);
    return d->colorBody;
}

QFont HChromatismWidget::fontTitle()
{
    Q_D(HChromatismWidget);
    return d->fontTitle;
}

QFont HChromatismWidget::fontBody()
{
    Q_D(HChromatismWidget);
    return d->fontBody;
}

bool HChromatismWidget::drawElse(QPainter *painter)
{
    HCartesianWidget::drawElse(painter);
    drawPointFocus(painter);
    drawPointCenter(painter);
    drawDescription(painter);
    return true;
}

bool HChromatismWidget::drawPointFocus(QPainter *painter)
{
    Q_D(HChromatismWidget);
    if (!isValid())
        return false;

    auto p = d->coordinate->mapToPosition(d->pointFocus, d->plotArea);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QPen(d->colorPointFocus, 2));
    painter->drawLine(QLineF(p.x(), p.y() - 3, p.x(), p.y() + 3));
    painter->drawLine(QLineF(p.x() - 3, p.y(), p.x() + 3, p.y()));
    painter->restore();
    return true;
}

bool HChromatismWidget::drawPointCenter(QPainter *painter)
{
    Q_D(HChromatismWidget);
    if (!isValid())
        return false;

    auto p = d->coordinate->mapToPosition(d->pointCenter, d->plotArea);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawEllipse(p, 2.0, 2.0);
    painter->restore();
    return true;
}

bool HChromatismWidget::drawDescription(QPainter *painter)
{
    Q_D(HChromatismWidget);
    if (!isValid())
        return false;

    auto body = tr("%1 SDCM\t\t\r\n(%2, %3)").arg(d->sdcmFocus, 0, 'f', 1).arg(d->pointFocus.x(), 0, 'f', 4).arg(d->pointFocus.y(), 0, 'f', 4);
    auto footer = tr("标准 %1 SDCM \n 目标值x=%2,y=%3").arg(d->sdcmStd, 0, 'f', 1).arg(d->pointCenter.x(), 0, 'f', 3).arg(d->pointCenter.y(), 0, 'f', 3);

    painter->save();
    painter->setPen(d->colorBody);
    painter->setFont(d->fontBody);
    painter->drawText(d->plotArea.adjusted(25, 25, -25, -25), Qt::AlignRight | Qt::AlignTop | Qt::TextWordWrap, body);
    painter->setPen(d->colorTitle);
    painter->setFont(d->fontTitle);
    painter->drawText(QRectF(d->plotArea.left(), 5, d->plotArea.width(), d->plotArea.top() - 15), Qt::AlignBottom | Qt::AlignHCenter, d->title);
    painter->drawText(QRectF(d->plotArea.left(), d->plotArea.bottom() + 20, d->plotArea.width(), 50), Qt::AlignTop | Qt::AlignHCenter, footer);
    painter->restore();
    return true;
}

void HChromatismWidget::init()
{
    Q_D(HChromatismWidget);
    d->margins.setBottom(80);
    d->margins.setTop(60);
    setCoordinate(QRectF(0, 0, 1, 1), 5, 5);
}

void HChromatismWidget::fixCoordinate(QPointF center, QPolygonF poly)
{
    auto x1 = center.x();
    auto x2 = center.x();
    auto y1 = center.y();
    auto y2 = center.y();
    for (auto p : poly)
    {
        x1 = qMin(x1, p.x());
        x2 = qMax(x2, p.x());
        y1 = qMin(y1, p.y());
        y2 = qMax(y2, p.y());
    }
    x1 = int((x1 - 0.005) * 500) / 500.0;
    x2 = int((x2 + 0.005) * 500) / 500.0;
    y1 = int((y1 - 0.005) * 500) / 500.0;
    y2 = int((y2 + 0.005) * 500) / 500.0;
    setCoordinate(QRectF(QPointF(x1, y1), QPointF(x2, y2)), 5, 5);
}
