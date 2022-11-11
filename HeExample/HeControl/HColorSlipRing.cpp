#include "HColorSlipRing_p.h"
#include <QtCore/QtMath>
#include <QtGui/QtEvents>
#include <QtGui/QPainter>
#include <QtGui/QGradient>

HE_BEGIN_NAMESPACE

HColorSlipRing::HColorSlipRing(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HColorSlipRingPrivate)
{
    setMinimumSize(300, 300);
}

HColorSlipRing::~HColorSlipRing()
{
}

void HColorSlipRing::paintEvent(QPaintEvent *event)
{
    int i;
    double lastValue;
    int splitIndex = -1;
    QPainterPath path, unselectedPath;
    QList<QPointF> centers;
    QList<QPolygonF> polygons;
    QPainter painter(this);
    QConicalGradient gradient;

    auto rect = event->rect();
    auto centerPoint = rect.center();
    auto miniSize = qMin(rect.width(), rect.height());
    auto radiusBig = (miniSize - 80) / 2;
    auto radiusSmall = qMax(radiusBig / 4 * 3, 40);
    auto radiusBall = radiusSmall - 30;
    gradient.setCenter(centerPoint);
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(0.25, Qt::blue);
    gradient.setColorAt(1, Qt::green);

    for (i = 133; i <= 405; i += 15)
    {
        auto pos1 = calcPos(i, radiusSmall);
        auto pos2 = calcPos(i + 3, radiusSmall);
        auto pos3 = calcPos(i, radiusBig);
        auto pos4 = calcPos(i + 3, radiusBig);

        auto poly = QPolygonF() << pos1 << pos2 << pos4 << pos3 << pos1;
        polygons << poly;
        centers << QLineF(pos1, pos2).center();
    }

    if (d_ptr->isPressed)
    {
        auto point = d_ptr->pressPos - centerPoint;
        d_ptr->ballAngle = qRadiansToDegrees(atan2(point.y(), point.x()));
        if (d_ptr->ballAngle < 133 && point.x() < 0 && point.y() > 0)
            d_ptr->ballAngle = 133;
        if (d_ptr->ballAngle > 45 && point.x() > 0)
            d_ptr->ballAngle = 45;
    }
    auto ballPos = calcPos(d_ptr->ballAngle, radiusBall);

    for (i = 0; i < centers.size(); i++)
    {
        auto point = ballPos - centers.at(i);
        auto distance = sqrt(pow(point.x(), 2) + pow(point.y(), 2));
        if (i > 0 && distance >= lastValue && distance < miniSize * 0.33)
        {
            splitIndex = i - 1;
            break;
        }
        else
            lastValue = distance;
    }
    if (splitIndex == -1)
        splitIndex = centers.size() - 1;

    path.addEllipse(ballPos, 20, 20);
    for (i = 0; i < polygons.size(); i++)
    {
        if (i <= splitIndex)
            path.addPolygon(polygons.at(i));
        else
            unselectedPath.addPolygon(polygons.at(i));
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::transparent);
    painter.translate(centerPoint);
    painter.setBrush(gradient);
    painter.drawPath(path);
    painter.setBrush(Qt::darkGray);
    painter.drawPath(unselectedPath);
}

void HColorSlipRing::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        d_ptr->pressPos = event->pos();
        d_ptr->isPressed = true;
        update();
    }
    QWidget::mousePressEvent(event);
}

void HColorSlipRing::mouseReleaseEvent(QMouseEvent *event)
{
    if (d_ptr->isPressed)
    {
        d_ptr->isPressed = false;
        update();
    }
    QWidget::mousePressEvent(event);
}

void HColorSlipRing::mouseMoveEvent(QMouseEvent *event)
{
    if (d_ptr->isPressed)
    {
        d_ptr->pressPos = event->pos();
        update();
    }
    QWidget::mouseMoveEvent(event);
}

QPointF HColorSlipRing::calcPos(double angle, int radius)
{
    auto radians = qDegreesToRadians(angle);
    return QPointF(cos(radians) * radius, sin(radians) * radius);
}

HE_END_NAMESPACE

