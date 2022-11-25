#include "HColorSelectionRing_p.h"
#include <QtCore/QtMath>
#include <QtGui/QtEvents>
#include <QtGui/QPainter>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

HE_BEGIN_NAMESPACE

HColorSelectionRing::HColorSelectionRing(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HColorSelectionRingPrivate)
{
    setPalette(Qt::white);
    setMinimumSize(150, 150);
    for (int i = 0; i < 360; i++)
        d_ptr->conicalGradient.setColorAt(i / 360.0, QColor::fromHsv(i, 255, 255));
    d_ptr->conicalGradient.setColorAt(1, QColor::fromHsv(359, 255, 255));
}

HColorSelectionRing::~HColorSelectionRing()
{
}

void HColorSelectionRing::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPainterPath path1, path2;
    auto radius = std::min(width(), height()) * 0.4;
    auto radians = qDegreesToRadians(d_ptr->ballAngle);
    auto ballPos = QPointF(cos(radians) * radius * 0.9, sin(radians) * radius * 0.9);
    auto selectColor = getColorInWidget(ballPos.toPoint() + rect().center());
    path1.addEllipse(QPoint(0, 0), radius, radius);
    path2.addEllipse(QPoint(0, 0), radius * 0.8, radius * 0.8);

    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::transparent);
    painter.translate(rect().center());
    painter.setPen(Qt::NoPen);
    painter.setBrush(d_ptr->conicalGradient);
    painter.drawPath(path1 - path2);
    painter.setPen(QColor("#128bf1"));
    painter.drawEllipse(ballPos, radius * 0.2, radius * 0.2);
    painter.setBrush(selectColor);
    painter.setPen(Qt::transparent);
    painter.drawEllipse(QPointF(0, 0), radius * 0.6, radius * 0.6);
    painter.restore();
}

void HColorSelectionRing::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto pos = event->pos() - rect().center();
        d_ptr->ballAngle = qRadiansToDegrees(atan2(pos.y(), pos.x()));
        d_ptr->isPressed = true;
        update();
    }
    QWidget::mousePressEvent(event);
}

void HColorSelectionRing::mouseReleaseEvent(QMouseEvent *event)
{
    if (d_ptr->isPressed)
        d_ptr->isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

void HColorSelectionRing::mouseMoveEvent(QMouseEvent *event)
{
    if (d_ptr->isPressed)
    {
        auto pos = event->pos() - rect().center();
        d_ptr->ballAngle = qRadiansToDegrees(atan2(pos.y(), pos.x()));
        update();
    }
    return QWidget::mouseMoveEvent(event);
}

void HColorSelectionRing::showEvent(QShowEvent *event)
{
    update();
    QWidget::showEvent(event);
}

QColor HColorSelectionRing::getColorInWidget(const QPoint &pos)
{
    static QScreen *screen = QGuiApplication::screenAt(pos);
    if (!screen)
        screen = QGuiApplication::primaryScreen();
    auto gpos = mapToGlobal(pos);
    return screen->grabWindow(0, gpos.x(), gpos.y(), 1, 1).toImage().pixel(0, 0);
}

HE_END_NAMESPACE

