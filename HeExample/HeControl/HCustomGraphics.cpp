#include "HCustomGraphics_p.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_BEGIN_NAMESPACE

HCustomGraphics::HCustomGraphics(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HCustomGraphicsPrivate)
{
    init();
}

HCustomGraphics::HCustomGraphics(HCustomGraphicsPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HCustomGraphics::~HCustomGraphics() = default;

QSize HCustomGraphics::sizeHint() const
{
    return {200, 100};
}

QSize HCustomGraphics::minimumSizeHint() const
{
    return {40, 20};
}

bool HCustomGraphics::isSelectDotVisible() const
{
    return d_ptr->selectDotVisible;
}

int HCustomGraphics::dotRadius() const
{
    return d_ptr->dotRadius;
}

int HCustomGraphics::lineWidth() const
{
    return d_ptr->lineWidth;
}

QColor HCustomGraphics::dotColor() const
{
    return d_ptr->dotColor;
}

QColor HCustomGraphics::lineColor() const
{
    return d_ptr->lineColor;
}

QColor HCustomGraphics::polygonColor() const
{
    return d_ptr->polygonColor;
}

QColor HCustomGraphics::selectColor() const
{
    return d_ptr->selectColor;
}

void HCustomGraphics::setSelectDotVisible(bool b)
{
    if (d_ptr->selectDotVisible == b)
        return;
    d_ptr->selectDotVisible = b;
    update();
}

void HCustomGraphics::setDotRadius(int value)
{
    if (d_ptr->dotRadius == value)
        return;
    d_ptr->dotRadius = value;
    update();
}

void HCustomGraphics::setLineWidth(int value)
{
    if (d_ptr->lineWidth == value)
        return;
    d_ptr->lineWidth = value;
    update();
}

void HCustomGraphics::setDotColor(const QColor &value)
{
    if (d_ptr->dotColor == value)
        return;
    d_ptr->dotColor = value;
    update();
}

void HCustomGraphics::setLineColor(const QColor &value)
{
    if (d_ptr->lineColor == value)
        return;
    d_ptr->lineColor = value;
    update();
}

void HCustomGraphics::setPolygonColor(const QColor &value)
{
    if (d_ptr->polygonColor == value)
        return;
    d_ptr->polygonColor = value;
    update();
}

void HCustomGraphics::setSelectColor(const QColor &value)
{
    if (d_ptr->selectColor == value)
        return;
    d_ptr->selectColor = value;
    update();
}

void HCustomGraphics::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    d_ptr->pressed = true;
    d_ptr->lastPoint = mapToGlobal(pos);

    // 连线模式下不选中
    if (!d_ptr->tempPoints.isEmpty())
        return;

    // 如果选中了,检测是否点到点上
    auto selectedPot = false;
    d_ptr->selectedPointIndex = -1;
    if (d_ptr->selectedIndex != -1)
    {
        auto poly = d_ptr->polygons.at(d_ptr->selectedIndex).first;
        for(int i = poly.size() - 1; i >= 0; i--)
        {
            if (calcLength(pos, poly[i]) <= 36)
            {
                selectedPot = true;
                d_ptr->selectedPointIndex = i;
                d_ptr->selectedPoint = poly[i];
                break;
            }
        }
    }
    // 当前选中了点则不用重绘
    if(selectedPot)
        return;
    // 判断是否选中一个
    d_ptr->selectedIndex = -1;
    for(int i = d_ptr->polygons.size() - 1; i >= 0; i--)
    {
        d_ptr->polygons[i].second = checkPoint(d_ptr->polygons[i].first, pos);
        if(d_ptr->polygons[i].second)
        {
            // 防止重叠部分
            if(d_ptr->selectedIndex == -1)
            {
                d_ptr->selectedIndex = i;
                d_ptr->selectedPolygon = d_ptr->polygons[i];
            }
            else
                d_ptr->polygons[i].second = false;
        }
    }
    update();
}

void HCustomGraphics::mouseMoveEvent(QMouseEvent *event)
{
    d_ptr->tempPoint = event->pos();
    if (d_ptr->pressed && d_ptr->selectedIndex != -1)
    {
        // 整体偏移坐标
        auto delta = mapToGlobal(d_ptr->tempPoint) - d_ptr->lastPoint;
        auto len = d_ptr->polygons.at(d_ptr->selectedIndex).first.size();
        if (d_ptr->selectedPointIndex != -1)
        {
            // 移动点
            d_ptr->polygons[d_ptr->selectedIndex].first[d_ptr->selectedPointIndex] = d_ptr->selectedPoint + delta;
        }
        else if(d_ptr->selectedIndex != -1)
        {
            // 移动面
            for(int i = 0; i < len; i++)
                d_ptr->polygons[d_ptr->selectedIndex].first[i] = d_ptr->selectedPolygon.first.at(i) + delta;
        }
    }
    update();
}

void HCustomGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标右键清空临时的
    if (event->button() == Qt::RightButton)
    {
        clearTemp();
        return;
    }

    // 检测再次点击与最后个点 - 还没写
    d_ptr->pressed = false;
    if (d_ptr->selectedIndex != -1)
        return;

    auto pos = event->pos();
    if (d_ptr->tempPoints.count() > 0)
    {
        if (calcLength(d_ptr->tempPoints.first(), pos) < 100)
        {
            // 完成一个多边形
            if (d_ptr->tempPoints.size() >= 3)
                d_ptr->polygons << qMakePair(d_ptr->tempPoints.toVector(), false);
            d_ptr->tempPoints.clear();
            this->update();
            return;
        }
    }
    d_ptr->tempPoints << pos;
    this->update();
}

void HCustomGraphics::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);
    // 绘制多边形
    drawPolygon(&painter);
    // 绘制点集合
    drawLines(&painter);
}

void HCustomGraphics::drawPolygon(QPainter *painter)
{
    painter->save();
    for (auto v : d_ptr->polygons)
    {
        painter->setPen(QPen(d_ptr->lineColor, d_ptr->lineWidth));
        v.second ? painter->setBrush(d_ptr->selectColor) : painter->setBrush(d_ptr->polygonColor);
        painter->drawPolygon(v.first.data(), v.first.size());

        if (d_ptr->selectDotVisible && v.second)
        {
            painter->setPen(Qt::NoPen);
            painter->setBrush(d_ptr->dotColor);
            for (auto p : v.first)
                painter->drawEllipse(p, d_ptr->dotRadius, d_ptr->dotRadius);
        }
    }
    painter->restore();
}

void HCustomGraphics::drawLines(QPainter *painter)
{
    auto count = d_ptr->tempPoints.count();
    if (count <= 0)
        return;

    painter->save();
    // 绘制点集合
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->dotColor);
    for(int i = 0; i < count; i++)
        painter->drawEllipse(d_ptr->tempPoints.at(i), d_ptr->dotRadius, d_ptr->dotRadius);
    // 绘制线条集合
    painter->setPen(QPen(d_ptr->lineColor, d_ptr->lineWidth));
    painter->setBrush(Qt::NoBrush);
    for(int i = 0; i < count - 1; i++)
        painter->drawLine(d_ptr->tempPoints.at(i), d_ptr->tempPoints.at(i + 1));
    // 绘制最后一条线条
    painter->drawLine(d_ptr->tempPoints.last(), d_ptr->tempPoint);
    painter->restore();
}

void HCustomGraphics::init()
{
    setMouseTracking(true);
    clearAll();
}

double HCustomGraphics::calcLength(const QPoint &p1, const QPoint &p2)
{
    return pow(p1.x() - p2.x(), 2.0) + pow(p1.y() - p2.y(), 2.0);
}

bool HCustomGraphics::checkPoint(const QVector<QPoint> &points, QPoint p)
{
    // 最少保证3个点
    auto count = points.size();
    if (count < 3)
        return false;

    int i, j;
    bool b = false;
    QList<int> vertx, verty;
    for(i = 0; i < count; i++)
    {
        vertx << points.at(i).x();
        verty << points.at(i).y();
    }
    // 核心算法,计算坐标是否在多边形内部
    for (i = 0, j = count - 1; i < count; j = i++)
    {
        bool b1 = (verty.at(i) > p.y()) != (verty.at(j) > p.y());
        bool b2 = (p.x() < (vertx.at(j) - vertx.at(i)) * (p.y() - verty.at(i)) / (verty.at(j) - verty.at(i)) + vertx.at(i));
        if (b1 && b2)
            b = !b;
    }
    return b;
}

void HCustomGraphics::clearTemp()
{
    d_ptr->tempPoints.clear();
}

void HCustomGraphics::clearAll()
{
    d_ptr->selectedPointIndex = -1;
    d_ptr->selectedIndex = -1;
    d_ptr->tempPoints.clear();
    d_ptr->polygons.clear();
}

HE_END_NAMESPACE
