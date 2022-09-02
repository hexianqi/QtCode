#include "HGraphicsColorBoardItem_p.h"
#include "HDrawHelper.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>

HE_BEGIN_NAMESPACE

HGraphicsColorBoardItemPrivate::HGraphicsColorBoardItemPrivate()
{
    itemSize = QSizeF(200, 200);
    minimumSizeHint = QSizeF(50, 50);
}

HGraphicsColorBoardItem::HGraphicsColorBoardItem(QGraphicsItem *parent) :
    HGraphicsObject(*new HGraphicsColorBoardItemPrivate, parent)
{
    init();
}

HGraphicsColorBoardItem::HGraphicsColorBoardItem(HGraphicsColorBoardItemPrivate &p, QGraphicsItem *parent) :
    HGraphicsObject(p, parent)
{
}

HGraphicsColorBoardItem::~HGraphicsColorBoardItem()
{
}

int HGraphicsColorBoardItem::type() const
{
    return Type;
}

void HGraphicsColorBoardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        colorPick(event->pos());
    HGraphicsObject::mousePressEvent(event);
}

void HGraphicsColorBoardItem::init()
{
    Q_D(HGraphicsColorBoardItem);
    HGraphicsObject::init();
    buildGradient(d->value);
}

void HGraphicsColorBoardItem::drawContent(QPainter *painter, const QStyleOptionGraphicsItem */*option*/)
{
    Q_D(HGraphicsColorBoardItem);
    buildPixmap();
    painter->save();
    painter->drawPixmap(0, 0, d->boardPixmap);
    HDrawHelper::drawCrosshair(painter, toAbsolute(d->pos), 3, Qt::black);
    painter->restore();
}

void HGraphicsColorBoardItem::buildGradient(int value)
{
    Q_D(HGraphicsColorBoardItem);
    d->conicalGradient.setStops(QGradientStops());
    for (int i = 0; i < 360; i++)
        d->conicalGradient.setColorAt(i / 360.0, QColor::fromHsv(i, 255, value));
    d->conicalGradient.setColorAt(1, QColor::fromHsv(359, 255, value));

    d->radialGradient.setStops(QGradientStops());
    for (int i = 0; i < 100; i ++)
        d->radialGradient.setColorAt(i / 100.0, QColor::fromHsvF(0, 0, 1, 1 - i / 100.0));
    d->radialGradient.setColorAt(1, QColor::fromHsvF(0, 0, 1, 0));
}

void HGraphicsColorBoardItem::buildPixmap()
{
    Q_D(HGraphicsColorBoardItem);
    auto rect = boundingRect();
    auto size = rect.size().toSize();
    d->boardCenter = rect.center();
    d->boardRadius = qMin(rect.width(), rect.height()) / 2 - 2;
    d->conicalGradient.setCenter(d->boardCenter);
    d->radialGradient.setCenter(d->boardCenter);
    d->radialGradient.setRadius(d->boardRadius);
    d->radialGradient.setFocalPoint(d->boardCenter);

    auto image1 = QImage(size, QImage::Format_ARGB32);
    image1.fill(Qt::transparent);
    QPainter painter1;
    painter1.begin(&image1);
    painter1.setRenderHint(QPainter::Antialiasing, true);
    painter1.setBrush(d->conicalGradient);
    painter1.drawEllipse(d->boardCenter, d->boardRadius, d->boardRadius);
    painter1.end();

    auto image2 = QImage(size, QImage::Format_ARGB32);
    image2.fill(Qt::transparent);
    QPainter painter2;
    painter2.begin(&image2);
    painter2.setRenderHint(QPainter::Antialiasing, true);
    painter2.setBrush(d->radialGradient);
    painter2.drawEllipse(d->boardCenter, d->boardRadius, d->boardRadius);
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter2.drawImage(0, 0, image1);
    painter2.end();
    d->boardPixmap = QPixmap::fromImage(image2);
}

void HGraphicsColorBoardItem::colorPick(const QPointF &point)
{
    Q_D(HGraphicsColorBoardItem);
    if (!isInBoard(point))
        return;

    auto r = radius(point);
    auto h = hue(point);
    auto s = r / d->boardRadius;
    auto v = d->value / 255.0;
    d->pos = toRelative(point);
    emit colorPicked(QColor::fromHsvF(h, s, v));
    update();
}

bool HGraphicsColorBoardItem::isInBoard(const QPointF &point)
{
    Q_D(HGraphicsColorBoardItem);
    return radius(point) <= d->boardRadius;
}

double HGraphicsColorBoardItem::radius(const QPointF &point)
{
    Q_D(HGraphicsColorBoardItem);
    auto p = point - d->boardCenter;
    return sqrt(p.x() * p.x() + p.y() * p.y());
}

double HGraphicsColorBoardItem::hue(const QPointF &point)
{
    Q_D(HGraphicsColorBoardItem);
    auto x = d->boardCenter.x() - point.x();
    auto y = point.y() - d->boardCenter.y();
    auto h = qRadiansToDegrees(atan(qAbs(y / x)));
    if (x >= 0 && y >= 0)
        h = 180 + h;
    else if (x >= 0 && y < 0)
        h = 180 - h;
    else if (x < 0 && y >= 0)
        h = 360 - h;
    return h / 360.0;
}

QPointF HGraphicsColorBoardItem::toRelative(const QPointF &point)
{
    Q_D(HGraphicsColorBoardItem);
    auto p = point - d->boardCenter;
    return QPointF(p.x() / d->boardRadius, p.y() / d->boardRadius);
}

QPointF HGraphicsColorBoardItem::toAbsolute(const QPointF &point)
{
    Q_D(HGraphicsColorBoardItem);
    return QPointF(point.x() * d->boardRadius, point.y() * d->boardRadius) + d->boardCenter;
}

HE_END_NAMESPACE
