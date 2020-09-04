#include "HSoundSlider_p.h"
#include "HDrawHelper.h"
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QApplication>

HE_CONTROL_BEGIN_NAMESPACE

HSoundSlider::HSoundSlider(QWidget *parent) :
    QAbstractSlider(parent),
    d_ptr(new HSoundSliderPrivate)
{
    init();
}

HSoundSlider::HSoundSlider(HSoundSliderPrivate &p, QWidget *parent) :
    QAbstractSlider(parent),
    d_ptr(&p)
{
    init();
}

HSoundSlider::~HSoundSlider()
{
}

void HSoundSlider::setMuted(bool b)
{
    if (d_ptr->muted == b)
        return;
    d_ptr->muted = b;
    update();
}

void HSoundSlider::setColors(QList<QColor> value)
{
    if (d_ptr->colors == value)
        return;
    d_ptr->colors = value;
    d_ptr->rebuild = true;
    update();
}

void HSoundSlider::paintEvent(QPaintEvent *)
{
    rebuildIfNeeded();

    auto pixmap = d_ptr->muted ? &d_ptr->progress2 : &d_ptr->progress1;
    auto scale = 1.0 * pixmap->width() / width();
    auto offsetDst = int(((width() - (d_ptr->paddingRight + d_ptr->paddingLeft)) * value() + 100) / maximum()) + d_ptr->paddingLeft;
    auto offsetSrc = int(((pixmap->width() - (d_ptr->paddingRight + d_ptr->paddingLeft) * scale) * value() + 100) / maximum() + d_ptr->paddingLeft * scale);

    QPainter painter(this);
    painter.drawPixmap(0, 0, offsetDst, height(), *pixmap, 0, 0, offsetSrc, pixmap->height());
    painter.drawPixmap(rect(), d_ptr->outside, d_ptr->outside.rect());
    painter.setPen(d_ptr->foreground );
    painter.setFont(d_ptr->font);
    painter.drawText(0, 0, 34, 15, Qt::AlignRight | Qt::AlignVCenter, QString::number(value()) + '%');
}

void HSoundSlider::wheelEvent(QWheelEvent *event)
{
    int newvalue = value() + event->delta() * singleStep() / (8 * 15);
    setValue(qBound(minimum(), newvalue , maximum()));
    emit sliderReleased();
    emit sliderMoved(value());
}

void HSoundSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::RightButton)
    {
        d_ptr->sliding = true;
        d_ptr->oldvalue = value();
        emit sliderPressed();
        setPos(event->x());
        emit sliderMoved(value());
    }
}

void HSoundSlider::mouseMoveEvent(QMouseEvent *event)
{
    // handle mouserelease hijacking
    if (d_ptr->sliding && (event->buttons() & ~Qt::RightButton ) == Qt::NoButton)
        handleReleasedButton();

    if (d_ptr->sliding)
    {
        QRect rect(d_ptr->paddingLeft - 15, -1, width() - d_ptr->paddingRight + 15 * 2 , width() + 5);
        if (!rect.contains(event->pos()))
        { /* We are outside */
            if (!d_ptr->mouseOutside)
                setValue(d_ptr->oldvalue);
            d_ptr->mouseOutside = true;
        }
        else
        { /* We are inside */
            d_ptr->mouseOutside = false;
            setPos(event->x());
            emit sliderMoved(value());
        }
    }
    else
    {
        int i = ((event->x() - d_ptr->paddingLeft) * maximum()) / (width() - (d_ptr->paddingLeft + d_ptr->paddingRight));
        i = qBound(0, i, maximum());
        setToolTip(QString("%1  %").arg(i));
    }
}

void HSoundSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::RightButton)
        handleReleasedButton();
    else
        QAbstractSlider::mouseReleaseEvent(event);
}

void HSoundSlider::init()
{
    setRange(0, 125);
    setMouseTracking(true);
    setFixedSize(85, 26);
    d_ptr->mask = HDrawHelper::loadSvgToPixmap(":/image/svg/volume-slider-inside.svg", size()).createHeuristicMask();
    d_ptr->outside = HDrawHelper::loadSvgToPixmap(":/image/svg/volume-slider-outside.svg", size());
    d_ptr->background = palette().color(QPalette::Active, QPalette::Window);
    d_ptr->foreground = palette().color(QPalette::Active, QPalette::WindowText);
    d_ptr->foreground.setHsv(d_ptr->foreground.hue(), (d_ptr->background.saturation() + d_ptr->foreground.saturation()) / 2, (d_ptr->background.value() + d_ptr->foreground.value()) / 2);
    d_ptr->font.setPointSize(7);
    d_ptr->colors << QColor(0, 255, 0) <<  QColor(255, 170, 0) << QColor(255, 0, 0) << QColor(255, 255, 255);
}

void HSoundSlider::rebuildIfNeeded()
{
    if (!d_ptr->rebuild)
        return;
    d_ptr->rebuild = false;

    auto mid = 100.0 / maximum();
    QLinearGradient gradient1(d_ptr->paddingLeft, 2, width() - d_ptr->paddingRight, 2);
    QLinearGradient gradient2(d_ptr->paddingLeft, 2, width() - d_ptr->paddingRight, 2);
    gradient1.setColorAt(0.0, d_ptr->colors.at(0));
    gradient1.setColorAt(mid - 0.05, d_ptr->colors.at(1));
    gradient1.setColorAt(mid + 0.05, d_ptr->colors.at(2));
    gradient1.setColorAt(1.0, d_ptr->colors.at(3));
    gradient2.setColorAt(0.0, desaturate(d_ptr->colors.at(0)));
    gradient2.setColorAt(mid - 0.05, desaturate(d_ptr->colors.at(1)));
    gradient2.setColorAt(mid + 0.05, desaturate(d_ptr->colors.at(2)));
    gradient2.setColorAt(1.0, desaturate(d_ptr->colors.at(3)));

    d_ptr->progress1 = QPixmap(d_ptr->outside.size());
    d_ptr->progress2 = QPixmap(d_ptr->outside.size());
    d_ptr->progress1.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());
    d_ptr->progress2.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());
    QPainter painter;
    painter.begin(&d_ptr->progress1);
    painter.setPen( Qt::NoPen );
    painter.setBrush(gradient1);
    painter.drawRect(d_ptr->progress1.rect());
    painter.end();
    painter.begin(&d_ptr->progress2);
    painter.setPen(Qt::NoPen );
    painter.setBrush(gradient2);
    painter.drawRect(d_ptr->progress2.rect());
    painter.end();
    d_ptr->progress1.setMask(d_ptr->mask);
    d_ptr->progress2.setMask(d_ptr->mask);
}

void HSoundSlider::handleReleasedButton()
{
    if (!d_ptr->mouseOutside && value() != d_ptr->oldvalue)
    {
        emit sliderReleased();
        setValue(value());
        emit sliderMoved( value() );
    }
    d_ptr->sliding = false;
    d_ptr->mouseOutside = false;
}

void HSoundSlider::setPos(int x)
{
    setValue((x - d_ptr->paddingLeft) * maximum() / (width() - (d_ptr->paddingLeft + d_ptr->paddingRight)));
}

QColor HSoundSlider::desaturate(QColor c)
{
    c.setHslF(c.hueF(), 0.2, 0.5, 1.0);
    return c;
}

HE_CONTROL_END_NAMESPACE
