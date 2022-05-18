#include "HLedWidget_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtWidgets/qdrawutil.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleOptionFrame>

HE_BEGIN_NAMESPACE

HLedWidget::HLedWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLedWidgetPrivate)
{
    init();
}

HLedWidget::HLedWidget(HLedWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HLedWidget::~HLedWidget() = default;

QSize HLedWidget::sizeHint() const
{
    if (d_ptr->shapeStyle == ShapeStyle_Circular)
        return QSize(25, 25).expandedTo(QApplication::globalStrut());
    return QSize(25, 15).expandedTo(QApplication::globalStrut());
}

int HLedWidget::heightForWidth(int value) const
{
    if (d_ptr->shapeStyle == ShapeStyle_Circular)
        return -1;
    return value;
}

QColor HLedWidget::color() const
{
    return d_ptr->color;
}

bool HLedWidget::isChecked() const
{
    return d_ptr->checked;
}

HLedWidget::ShapeStyle HLedWidget::shapeStyle() const
{
    return d_ptr->shapeStyle;
}

int HLedWidget::frameWidth() const
{
    return d_ptr->frameWidth;
}

bool HLedWidget::isAnimated() const
{
    return  d_ptr->timer->isActive();
}

int HLedWidget::interval() const
{
    return d_ptr->timer->interval();
}

void HLedWidget::setColor(const QColor &value)
{
    if (d_ptr->color == value)
        return;
    d_ptr->color = value;
    emit colorChanged(value);
    update();
}

void HLedWidget::setChecked(bool b)
{
    if (d_ptr->checked == b)
        return;
    d_ptr->checked = b;
    emit toggled(b);
    update();
}

void HLedWidget::setShapeStyle(ShapeStyle value)
{
    if (d_ptr->shapeStyle == value)
        return;
    d_ptr->shapeStyle = value;
    updateGeometry();
    update();
}

void HLedWidget::setFrameWidth(int value)
{
    if (d_ptr->frameWidth == value)
        return;
    d_ptr->frameWidth = value;
    update();
}

void HLedWidget::setAnimated(bool b)
{
    if (d_ptr->timer->isActive() == b)
        return;
    if (b)
        d_ptr->timer->start();
    else
        d_ptr->timer->stop();
}

void HLedWidget::setInterval(int value)
{
    if (d_ptr->timer->interval() == value)
        return;
    d_ptr->timer->setInterval(value);
}

void HLedWidget::toggle()
{
    setChecked(!isChecked());
}

void HLedWidget::blink()
{
    if (isAnimated())
        return;
    setChecked(true);
    QTimer::singleShot(100, this, &HLedWidget::toggle);
}

void HLedWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void HLedWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    auto color = isChecked() ? d_ptr->color : palette().background().color();
    if (d_ptr->shapeStyle == ShapeStyle_Circular)
    {
        auto side = qMin(width(), height());
        auto gradient = QRadialGradient(rect().center(), side * 0.45, rect().center() - QPointF(side * 0.1, side * 0.1));
        gradient.setColorAt(0.0, palette().color(QPalette::Light));
        gradient.setColorAt(0.75, color);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(gradient);
        painter.setPen(QPen(palette().color(QPalette::Foreground), d_ptr->frameWidth));
        painter.drawEllipse(rect().adjusted((width() - side) / 2 + d_ptr->frameWidth, (height() - side) / 2 + d_ptr->frameWidth, -(width() - side) / 2 - d_ptr->frameWidth, -(height() - side) / 2 - d_ptr->frameWidth));
    }
    else
    {
        QStyleOptionFrame option;
        option.initFrom(this);
        option.lineWidth = d_ptr->frameWidth;
        option.midLineWidth = d_ptr->frameWidth;
        if (d_ptr->shapeStyle == ShapeStyle_RectangularRaised)
            option.state |= QStyle::State_Raised;
        else if (d_ptr->shapeStyle == ShapeStyle_RectangularSunken)
            option.state |= QStyle::State_Sunken;
        auto brush = QBrush(color);
        if (d_ptr->shapeStyle == ShapeStyle_RectangularPlain)
            qDrawPlainRect(&painter, option.rect, option.palette.foreground().color(), d_ptr->frameWidth, &brush);
        else
            qDrawShadePanel(&painter, option.rect, option.palette, d_ptr->shapeStyle == ShapeStyle_RectangularSunken, d_ptr->frameWidth, &brush);
    }
}

void HLedWidget::init()
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(1000);
    connect(d_ptr->timer, &QTimer::timeout, this, &HLedWidget::toggle);
    auto policy = QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
    setWindowIcon(QIcon(":/image/ww/led.png"));
}

HE_END_NAMESPACE
