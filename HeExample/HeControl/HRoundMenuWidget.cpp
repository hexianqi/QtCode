#include "HRoundMenuWidget_p.h"
#include <QtCore/QTimer>
#include <QtGui/QtEvents>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HRoundMenuWidget::HRoundMenuWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HRoundMenuWidgetPrivate)
{
    auto list = QStringList() << ":/Resources/image/Add.png"
                              << ":/Resources/image/App.png"
                              << ":/Resources/image/Chat.png"
                              << ":/Resources/image/Delete.png"
                              << ":/Resources/image/find.png"
                              << ":/Resources/image/List.png";

    d_ptr->homePixmap.load(":/Resources/image/home.png");
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(40);
    connect(d_ptr->timer, &QTimer::timeout, this, &HRoundMenuWidget::onTimer);
    setPalette(Qt::white);
    setMouseTracking(true);
    setImages(list);
}

HRoundMenuWidget::~HRoundMenuWidget()
{
}

void HRoundMenuWidget::setImages(QStringList value)
{
    d_ptr->images.clear();
    d_ptr->menuRects.fill(QRect(), value.size());
    for (auto v : value)
        d_ptr->images << QPixmap(v);
    update();
}

void HRoundMenuWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRadialGradient radialGradient;
    d_ptr->length = std::min(width(), height());
    if (d_ptr->currentState == State::Shrink)
        d_ptr->radius = 0.33 * d_ptr->length / 1.2;
    d_ptr->homeRect = QRect(d_ptr->radius * 0.05, d_ptr->radius * 0.05, d_ptr->radius * 0.8, d_ptr->radius * 0.8);
    auto center = QPointF(d_ptr->radius * 0.2, d_ptr->radius * 0.2);
    radialGradient.setCenter(center);
    radialGradient.setRadius(d_ptr->radius * 1.2);
    radialGradient.setFocalPoint(center);
    radialGradient.setColorAt(0.0, QColor("#EAEAEA"));
    radialGradient.setColorAt(1.0, QColor("#AFAFAF"));

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.save();
    painter.setBrush(radialGradient);
    painter.setPen(QColor("#808080"));
    painter.drawEllipse(center, d_ptr->radius, d_ptr->radius);
    painter.restore();
    painter.drawPixmap(d_ptr->homeRect, d_ptr->homePixmap);

    if (d_ptr->currentState == State::Shrink)
        return;

    QPainterPath p1, p2;
    p1.addEllipse(center, d_ptr->outSideRadius, d_ptr->outSideRadius);
    p2.addEllipse(center, d_ptr->radius, d_ptr->radius);
    d_ptr->arcAreaPath = p1 - p2;
    painter.setBrush(QColor("#E2E2D0"));
    painter.setPen(Qt::transparent);
    painter.drawPath(d_ptr->arcAreaPath);

    auto cha = d_ptr->outSideRadius  - d_ptr->radius;
    auto x = 1.2 * d_ptr->radius + (cha - d_ptr->radius * 0.8) / 2;
    auto y = 0.2 * d_ptr->radius;
    auto imageRect = d_ptr->currentState == State::Popping ? QRect(x, y, cha * 0.6, cha * 0.6) : QRect(x, y, d_ptr->radius * 0.8, d_ptr->radius * 0.8);
    auto size = d_ptr->images.size();
    auto temp = QPoint(d_ptr->radius * 0.4, d_ptr->radius * 0.4);
    QTransform transform;
    for (int i = 0; i < size; i++)
    {
        auto angle = 360 / size * i + d_ptr->beforeOffset + d_ptr->currentOffset;
        painter.save();
        painter.rotate(angle);
        painter.drawPixmap(imageRect, d_ptr->images.at(i));
        painter.restore();

        transform.reset();
        transform.rotate(angle);
        auto point = transform.map(imageRect.center());
        d_ptr->menuRects[i] = QRect(point - temp, point + temp);
    }

    if (d_ptr->pressIndex >= 0)
    {
        painter.setBrush(QColor(0, 0, 0, 63));
        painter.drawEllipse(d_ptr->menuRects.at(d_ptr->pressIndex));
    }
}

void HRoundMenuWidget::resizeEvent(QResizeEvent *event)
{
    d_ptr->currentState = State::Shrink;
    update();
    QWidget::resizeEvent(event);
}

void HRoundMenuWidget::mousePressEvent(QMouseEvent *event)
{
    auto region = QRegion(d_ptr->homeRect, QRegion::Ellipse);
    auto pos = event->pos();
    if (region.contains(pos))
    {
        if (d_ptr->currentState == State::Shrink)
        {
            d_ptr->lastState = State::Shrink;
            d_ptr->radius = 0.5 * d_ptr->length / 1.2;
            d_ptr->outSideRadius = d_ptr->radius;
            d_ptr->currentState = State::Popping;
        }
        else if (d_ptr->currentState == State::Popped)
        {
            d_ptr->lastState = State::Popped;
            d_ptr->radius = 0.33 * d_ptr->length / 1.2;
            d_ptr->currentState = State::Popping;
        }
        d_ptr->timer->start();
    }
    else
    {
        d_ptr->pressIndex = -1;
        if (d_ptr->currentState == State::Popped)
        {
            for (int i = 0; i < d_ptr->menuRects.size(); i++)
            {
                if (d_ptr->menuRects.at(i).contains(pos))
                {
                    d_ptr->pressIndex = i;
                    break;
                }
            }

            if (d_ptr->pressIndex == -1)
            {
                if (d_ptr->arcAreaPath.contains(pos))
                {
                    d_ptr->pressPos = pos;
                    setCursor(Qt::OpenHandCursor);
                }
            }
        }
    }
    update();

    QWidget::mousePressEvent(event);
}

void HRoundMenuWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (d_ptr->currentState == State::Popped)
    {
        d_ptr->pressIndex = -1;
        d_ptr->pressPos = QPoint(0, 0);
        d_ptr->beforeOffset += d_ptr->currentOffset;
        d_ptr->currentOffset = 0;
        setCursor(Qt::ArrowCursor);
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void HRoundMenuWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    auto region = QRegion(d_ptr->homeRect, QRegion::Ellipse);
    auto mouseInAbtnZone = false;

    if (region.contains(pos))
    {
        mouseInAbtnZone = true;
    }
    else if(d_ptr->currentState == State::Popped)
    {
        for(auto rect : d_ptr->menuRects)
        {
            region = QRegion(rect, QRegion::Ellipse);
            if (region.contains(pos))
            {
                mouseInAbtnZone = true;
                break;
            }
        }
    }

    if (d_ptr->pressPos.isNull())
    {
        setCursor(mouseInAbtnZone ? Qt::PointingHandCursor : Qt::ArrowCursor);
    }
    else
    {
        auto line1 = QLineF(d_ptr->radius * 0.2, d_ptr->radius * 0.2, d_ptr->pressPos.x(), d_ptr->pressPos.y());
        auto line2 = QLineF(d_ptr->radius * 0.2, d_ptr->radius * 0.2, pos.x(), pos.y());
        d_ptr->currentOffset = line2.angleTo(line1);
        if (d_ptr->currentOffset > 200 && pos.x() > 0 && pos.y() > 0)
            d_ptr->currentOffset -= 360;
        setCursor(Qt::OpenHandCursor);
        update();
    }

    QWidget::mouseMoveEvent(event);
}

void HRoundMenuWidget::onTimer()
{
    if (d_ptr->currentState != State::Popping)
        return;
    if (d_ptr->lastState == State::Shrink)
    {
        d_ptr->outSideRadius += d_ptr->length * 0.1;
        if (d_ptr->outSideRadius >= d_ptr->length - d_ptr->radius * 0.2)
        {
            d_ptr->timer->stop();
            d_ptr->currentState = State::Popped;
            d_ptr->outSideRadius = d_ptr->length - d_ptr->radius * 0.2;
        }
    }
    else if(d_ptr->lastState == State::Popped)
    {
        d_ptr->outSideRadius -= d_ptr->length * 0.1;
        if (d_ptr->outSideRadius < d_ptr->radius)
        {
            d_ptr->timer->stop();
            d_ptr->currentState = State::Shrink;
            d_ptr->outSideRadius = d_ptr->radius;
        }
    }
    update();
}

HE_END_NAMESPACE
