#include "HCartesianCoordinate_p.h"
#include <QtCore/QLineF>
#include <QtGui/QPolygonF>

HCartesianCoordinate::HCartesianCoordinate(QObject *parent) :
    QObject(parent),
    d_ptr(new HCartesianCoordinatePrivate)
{
    setAxis(QRectF(0, 0, 1, 1), 5, 5);
}

HCartesianCoordinate::~HCartesianCoordinate() = default;

HCartesianCoordinate::HCartesianCoordinate(HCartesianCoordinatePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    setAxis(QRectF(0, 0, 1, 1), 5, 5);
}

QPointF HCartesianCoordinate::map(QPointF data, QRectF target, QRectF source)
{
    auto dx = target.width() / source.width();
    auto dy = target.height() / source.height();
    auto x = target.left() + (data.x() - source.left()) * dx;
    auto y = target.top() - (data.y() - source.bottom()) * dy;
    return {x, y};
}

QPolygonF HCartesianCoordinate::map(QPolygonF data, QRectF target, QRectF source)
{
    QPolygonF poly;
    auto dx = target.width() / source.width();
    auto dy = target.height() / source.height();
    for (int i = 0; i < data.size(); i++)
    {
        auto x = target.left() + (data[i].x() - source.left()) * dx;
        auto y = target.top() - (data[i].y() - source.bottom()) * dy;
        poly.append(QPointF(x, y));
    }
    return poly;
}

QLineF HCartesianCoordinate::map(QLineF data, QRectF target, QRectF source)
{
    auto dx = target.width() / source.width();
    auto dy = target.height() / source.height();
    auto x1 = target.left() + (data.x1() - source.left()) * dx;
    auto x2 = target.left() + (data.x2() - source.left()) * dx;
    auto y1 = target.top() - (data.y1() - source.bottom()) * dy;
    auto y2 = target.top() - (data.y2() - source.bottom()) * dy;
    return {x1, y1, x2, y2};
}

QVector<QLineF> HCartesianCoordinate::map(QVector<QLineF> data, QRectF target, QRectF source)
{
    QVector<QLineF> lines;
    auto dx = target.width() / source.width();
    auto dy = target.height() / source.height();
    for (int i = 0; i < data.size(); i++)
    {
        auto x1 = target.left() + (data[i].x1() - source.left()) * dx;
        auto x2 = target.left() + (data[i].x2() - source.left()) * dx;
        auto y1 = target.top() - (data[i].y1() - source.bottom()) * dy;
        auto y2 = target.top() - (data[i].y2() - source.bottom()) * dy;
        lines << QLineF(x1, y1, x2, y2);
    }
    return lines;
}

QRectF HCartesianCoordinate::map(QRectF data, QRectF target, QRectF source)
{
    auto dx = target.width() / source.width();
    auto dy = target.height() / source.height();
    auto x = target.left() + (data.left() - source.left()) * dx;
    auto y = target.top() - (data.bottom() - source.bottom()) * dy;
    return {x, y, data.width() * dx, data.height() * dy};
}

void HCartesianCoordinate::adjustAxis(double &min, double &max, int &tick)
{
    const int minTicks = 4;
    double grossStep,step;

    grossStep = (max - min) / minTicks;
    step = pow(10.0, floor(log10(grossStep)));

    if ( 5 * step < grossStep)
        step *= 5;
    else if (2 * step < grossStep)
        step *= 2;

    tick = int(ceil(max / step) - floor(min / step));
    if (tick < minTicks)
        tick = minTicks;
    min = floor(min / step) * step;
    max = ceil(max / step) * step;
}

void HCartesianCoordinate::setAxis(QRectF rect)
{
    setAxis(rect.left(), rect.right(), rect.top(), rect.bottom());
}

void HCartesianCoordinate::setAxis(QRectF rect, int tickX, int tickY)
{
    d_ptr->axis = rect;
    d_ptr->tickX = tickX;
    d_ptr->tickY = tickY;
}

void HCartesianCoordinate::setAxis(double minX, double maxX, double minY, double maxY, int tickX, int tickY)
{
    if (tickX <= 0)
        adjustAxis(minX, maxX, tickX);
    if (tickY <= 0)
        adjustAxis(minY, maxY, tickY);
    d_ptr->axis.setCoords(minX, minY, maxX, maxY);
    d_ptr->tickX = tickX;
    d_ptr->tickY = tickY;
}

QRectF HCartesianCoordinate::axis() const
{
    return d_ptr->axis;
}

int HCartesianCoordinate::tickX() const
{
    return d_ptr->tickX;
}

int HCartesianCoordinate::tickY() const
{
    return d_ptr->tickY;
}

double HCartesianCoordinate::spanX() const
{
    return d_ptr->axis.width();
}

double HCartesianCoordinate::spanY() const
{
    return d_ptr->axis.height();
}

QStringList HCartesianCoordinate::axisX()
{
    QStringList list;
    auto l = d_ptr->axis.left();
    auto d = spanX() / tickX();
    for (int i = 0; i <= tickX(); i++)
        list << QString("%1").arg(l + i * d);
    return list;
}

QStringList HCartesianCoordinate::axisY()
{
    QStringList list;
    auto t = d_ptr->axis.top();
    auto d = spanY() / tickY();
    for (int i = 0; i <= tickY(); i++)
        list << QString("%1").arg(t + i * d);
    return list;
}

QPointF HCartesianCoordinate::mapToPosition(QPointF value, const QRectF logic)
{
    return map(value, logic, d_ptr->axis);
}

QPolygonF HCartesianCoordinate::mapToPosition(QPolygonF value, QRectF logic)
{
    return map(std::move(value), logic, d_ptr->axis);
}

QLineF HCartesianCoordinate::mapToPosition(QLineF value, QRectF logic)
{
    return map(value, logic, d_ptr->axis);
}

QVector<QLineF> HCartesianCoordinate::mapToPosition(QVector<QLineF> value, QRectF logic)
{
    return map(value, logic, d_ptr->axis);
}

QRectF HCartesianCoordinate::mapToPosition(QRectF value, QRectF logic)
{
    return map(value, logic, d_ptr->axis);
}

QPointF HCartesianCoordinate::mapToValue(QPointF position, QRectF logic)
{
    return map(position, d_ptr->axis, logic);
}

QPolygonF HCartesianCoordinate::mapToValue(QPolygonF position, QRectF logic)
{
    return map(std::move(position), d_ptr->axis, logic);
}

QRectF HCartesianCoordinate::mapToValue(QRectF rect, QRectF logic)
{
    return map(rect, d_ptr->axis, logic);
}

QRectF HCartesianCoordinate::mapToAxis(QRectF data, QRectF axis)
{
    return map(d_ptr->axis, data, axis);
}
