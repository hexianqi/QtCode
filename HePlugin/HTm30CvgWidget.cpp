#include "HTm30CvgWidget_p.h"
#include "HCartesianCoordinate.h"
#include "HPainterHelper.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>

HTm30CvgWidgetPrivate::HTm30CvgWidgetPrivate()
{
    square = true;
    drawGrid = false;
    drawRuler = false;
    cvg.load(":/image/cvg_background.png");
}

HTm30CvgWidget::HTm30CvgWidget(QWidget *parent) :
    HCartesianWidget(*new HTm30CvgWidgetPrivate, parent)
{
    init();
}

HTm30CvgWidget::~HTm30CvgWidget()
{
}

bool HTm30CvgWidget::isDrawBackground() const
{
    return true;
}

bool HTm30CvgWidget::isDrawEdge() const
{
    return true;
}

bool HTm30CvgWidget::isDrawLabel() const
{
    return true;
}

bool HTm30CvgWidget::isDrawCircle_10_20() const
{
    return true;
}

bool HTm30CvgWidget::isDrawVector() const
{
    return true;
}

bool HTm30CvgWidget::isDrawQuiver() const
{
    return true;
}

bool HTm30CvgWidget::isDrawValue() const
{
    return true;
}

bool HTm30CvgWidget::drawElse(QPainter *painter)
{
    HCartesianWidget::drawElse(painter);
    painter->setRenderHint(QPainter::Antialiasing, true);
    drawBackground(painter);
    drawEdge(painter);
    drawLabel(painter);
    drawCross(painter);
    drawCircle_10_20(painter);
    drawVector(painter);
    drawQuiver(painter);
    drawValue(painter);
    return true;
}

bool HTm30CvgWidget::drawBackground(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isDrawBackground() || !isValid())
        return false;

    auto target = d->plotArea.adjusted(1, 1, -1, -1);
    auto source = d->coordinate->mapToAxis(d->cvg.rect(), QRectF(-150, -150, 300, 300));
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->drawPixmap(target, d->cvg, source);
    painter->restore();
    return true;
}

bool HTm30CvgWidget::drawEdge(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isDrawEdge() || !isValid())
        return false;

    auto pen = QPen(QColor(128, 128, 128), 1, Qt::DashLine);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(pen);
    painter->drawLines(d->coordinate->mapToPosition(d->lineEdge, d->plotArea));
    painter->restore();
    return true;
}

bool HTm30CvgWidget::drawLabel(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isDrawLabel() || !isValid())
        return false;

    auto f = painter->font();
    f.setPointSize(10);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setFont(f);
    painter->setPen(QColor(64, 64, 64));
    for (int i = 0; i < 16; i++)
        painter->drawText(d->coordinate->mapToPosition(d->rectLabel[i], d->plotArea), Qt::AlignCenter, QString::number(i + 1));
    painter->restore();
    return true;
}

bool HTm30CvgWidget::drawCross(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isValid())
        return false;
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QColor(128, 128, 128));
    HPainterHelper::drawCrossCursor(painter, d->coordinate->mapToPosition(QPointF(0, 0), d->plotArea), 5);
    painter->restore();
    return true;
}

bool HTm30CvgWidget::drawCircle_10_20(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isDrawCircle_10_20() || !isValid())
        return false;

    auto r = QList<double>() << 0.8 << 0.9 << 1.1 << 1.2;
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QPen(Qt::white, 0.5));
    for (auto v : r)
    {
        auto rect = d->coordinate->mapToPosition(QRectF(-100 * v, -100 * v, 200 * v, 200 * v), d->plotArea);
        painter->drawEllipse(rect);
    }
    painter->drawText(d->coordinate->mapToPosition(QRectF(-10, -78, 20, 10), d->plotArea), Qt::AlignHCenter | Qt::AlignBottom, "-20%");
    painter->drawText(d->coordinate->mapToPosition(QRectF(-10, -132, 20, 10), d->plotArea), Qt::AlignHCenter | Qt::AlignTop, "+20%");
    painter->setPen(QPen(Qt::black, 1.25));
    painter->drawEllipse(d->coordinate->mapToPosition(QRectF(-100, -100, 200, 200), d->plotArea));
    painter->restore();
    return true;
}

bool HTm30CvgWidget::drawVector(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isDrawVector() || !isValid())
        return false;
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(QPen(Qt::red, 2));
    painter->drawPolygon(d->coordinate->mapToPosition(d->polyTest, d->plotArea));
    painter->restore();
    return true;
}

bool HTm30CvgWidget::drawQuiver(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isDrawQuiver() || !isValid())
        return false;
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    for (int i = 0; i < 16; i++)
    {
        painter->setPen(QPen(d->colorQuiver.at(i), 2));
        HPainterHelper::drawQuiver(painter, d->coordinate->mapToPosition(d->polyReference.at(i), d->plotArea), d->coordinate->mapToPosition(d->polyTest.at(i), d->plotArea));
    }
    painter->restore();
    return true;
}

bool HTm30CvgWidget::drawValue(QPainter *painter)
{
    Q_D(HTm30CvgWidget);
    if (!isDrawValue() || !isValid())
        return false;

    auto rect11 = QRectF(-140,  124, 60, 16);
    auto rect12 = QRectF(-140,  110, 60, 14);
    auto rect21 = QRectF(  80,  124, 60, 16);
    auto rect22 = QRectF(  80,  110, 60, 14);
    auto rect31 = QRectF(-140, -140, 60, 16);
    auto rect32 = QRectF(-140, -124, 60, 14);
    auto rect41 = QRectF(  80, -140, 60, 16);
    auto rect42 = QRectF(  80, -124, 60, 14);
    auto font1 = painter->font();
    auto font2 = painter->font();
    font1.setPointSize(15);
    font1.setBold(true);
    font2.setPointSize(13);
    font2.setItalic(true);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setPen(Qt::black);
    painter->setFont(font1);
    painter->drawText(d->coordinate->mapToPosition(rect11, d->plotArea), Qt::AlignVCenter | Qt::AlignLeft, QString::number(d->Rf, 'f', 0));
    painter->drawText(d->coordinate->mapToPosition(rect21, d->plotArea), Qt::AlignVCenter | Qt::AlignRight, QString::number(d->Rg, 'f', 0));
    painter->drawText(d->coordinate->mapToPosition(rect31, d->plotArea), Qt::AlignVCenter | Qt::AlignLeft, QString::number(d->Tc, 'f', 0));
    painter->drawText(d->coordinate->mapToPosition(rect41, d->plotArea), Qt::AlignVCenter | Qt::AlignRight, QString::number(d->Duv, 'f', 4));
    painter->setFont(font2);
    painter->drawText(d->coordinate->mapToPosition(rect12, d->plotArea), Qt::AlignVCenter | Qt::AlignLeft, "Rf");
    painter->drawText(d->coordinate->mapToPosition(rect22, d->plotArea), Qt::AlignVCenter | Qt::AlignRight, "Rg");
    painter->drawText(d->coordinate->mapToPosition(rect32, d->plotArea), Qt::AlignVCenter | Qt::AlignLeft, "CCT");
    painter->drawText(d->coordinate->mapToPosition(rect42, d->plotArea), Qt::AlignVCenter | Qt::AlignRight, "Duv");
    painter->restore();
    return true;
}

void HTm30CvgWidget::init()
{
    Q_D(HTm30CvgWidget);
    int i;
    double theta1, theta2;
    for (i = 0; i < 16; i++)
    {
        QRectF rect(0, 0, 20, 20);
        theta1 = qDegreesToRadians(i * 360 / 16.0);
        theta2 = qDegreesToRadians(i * 360 / 16.0 + 11.25);
        rect.moveCenter(QPointF(135 * cos(theta2), 135 * sin(theta2)));
        d->lineEdge << QLineF(10 * cos(theta1), 10 * sin(theta1), 150 * cos(theta1), 150 * sin(theta1));
        d->rectLabel << rect;
        d->polyTest << QPointF(50 * cos(theta2), 50 * sin(theta2));
        d->polyReference << QPointF(100 * cos(theta2), 100 * sin(theta2));
    }
    d->colorQuiver << QColor(230, 40, 40)
                   << QColor(231, 75, 75)
                   << QColor(251, 129, 46)
                   << QColor(255, 181, 41)
                   << QColor(203, 202, 70)
                   << QColor(126, 185, 76)
                   << QColor(65, 192, 109)
                   << QColor(0, 156, 124)
                   << QColor(22, 188, 176)
                   << QColor(0, 164, 191)
                   << QColor(0, 133, 195)
                   << QColor(59, 98, 170)
                   << QColor(69, 104, 174)
                   << QColor(106, 78, 133)
                   << QColor(157, 105, 161)
                   << QColor(167, 79, 129);
    setCoordinate(QRectF(-150, -150, 300, 300), 6, 6);
}
