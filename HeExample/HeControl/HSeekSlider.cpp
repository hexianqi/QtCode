#include "HSeekSlider_p.h"
#include "HControlHelper.h"
#include "HSeekStyle.h"
#include "HSeekPoints.h"
#include "HTimeTooltip.h"
#include <QtCore/QTimer>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QSequentialAnimationGroup>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HSeekSlider::HSeekSlider(Qt::Orientation orientation, bool classic, QWidget *parent) :
    QSlider(orientation, parent),
    d_ptr(new HSeekSliderPrivate)
{
    d_ptr->classic = classic;
    init();
}

HSeekSlider::~HSeekSlider()
{
    if (d_ptr->alternativeStyle)
        delete d_ptr->alternativeStyle;
    delete d_ptr->timeTooltip;
}

QSize HSeekSlider::sizeHint() const
{
    if (d_ptr->classic)
        return QSlider::sizeHint();
    return orientation() == Qt::Horizontal ? QSize(100, 18) : QSize( 18, 100 );
}

void HSeekSlider::setChapters(QList<HSeekPoint> value)
{
    d_ptr->chapters->setPoints(value);
}

// param pos Position, between 0 and 1. -1 disables the slider
// param legnth Duration time.
void HSeekSlider::setPosition(double pos, int length)
{
    if (qFuzzyCompare(pos, -1.0) || !d_ptr->seekable)
    {
        setEnabled(false);
        d_ptr->timeTooltip->hide();
        d_ptr->sliding = false;
        setValue(0);
        return;
    }

    setEnabled(true);

    if (!d_ptr->sliding)
    {
        setValue(pos * maximum());
        if (d_ptr->animationLoading != nullptr && pos >= 0.0 && d_ptr->animationLoading->state() != QAbstractAnimation::Stopped)
        {
            d_ptr->animationLoading->stop();
            d_ptr->loading = 0.0;
        }
    }
    d_ptr->inputLength = length;
}

void HSeekSlider::setSeekable(bool b)
{
    d_ptr->seekable = b;
}

void HSeekSlider::setBuffering(double value)
{
    if (value < d_ptr->buffering)
        d_ptr->bufferingStart = QTime::currentTime();
    d_ptr->buffering = value;
    if (d_ptr->buffering > 0.0 || isEnabled())
    {
        d_ptr->animationLoading->stop();
        d_ptr->startLoadingTimer->stop();
        d_ptr->loading = 0.0;
    }
    repaint();
}

void HSeekSlider::inputUpdated(bool b)
{
    if (!b)
    {
        d_ptr->animationLoading->stop();
        d_ptr->startLoadingTimer->stop();
        d_ptr->loading = 0.0;
        repaint();
    }
    else if (d_ptr->buffering == 0.0 && !isEnabled())
        d_ptr->startLoadingTimer->start();
}

void HSeekSlider::hideHandle()
{
    // If pause is called while not running Qt will complain
    if (d_ptr->animationOpacity->state() == QAbstractAnimation::Running)
        d_ptr->animationOpacity->pause();
    // Play the animation backward
    d_ptr->animationOpacity->setDirection(QAbstractAnimation::Backward);
    d_ptr->animationOpacity->start();
}

void HSeekSlider::paintEvent(QPaintEvent *event)
{
    if (d_ptr->alternativeStyle == nullptr)
        return QSlider::paintEvent(event);

    HSeekStyleOption option;
    option.initFrom(this);
    option.buffering = QTime::currentTime() > d_ptr->bufferingStart.addSecs(1) ? d_ptr->buffering : 0.0;
    option.length = d_ptr->inputLength;
    option.animate = d_ptr->animationOpacity->state() == QAbstractAnimation::Running || d_ptr->hideHandleTimer->isActive();
    option.opacity = d_ptr->opacity;
    option.loading = d_ptr->loading;
    option.sliderPosition = sliderPosition();
    option.sliderValue = value();
    option.maximum = maximum();
    option.minimum = minimum();
    for (auto point : d_ptr->chapters->points())
        option.points << point.time;
    QPainter painter(this);
    d_ptr->alternativeStyle->drawComplexControl(QStyle::CC_Slider, &option, &painter, this);
}

void HSeekSlider::mouseMoveEvent(QMouseEvent *event)
{
    // handle mouserelease hijacking
    if ((event->buttons() & ~Qt::RightButton ) == Qt::NoButton)
        handleReleasedButton();

    if (!isEnabled())
        return event->accept();

    if (d_ptr->sliding)
    {
        setValue(valueFromPosition(event->x()));
        emit sliderMoved(value());
    }

    // Tooltip
    if (d_ptr->inputLength > 0)
    {
        int margin = handleLength();
        int posX = qBound(rect().left() + margin, event->x(), rect().right() - margin);

        QString text;
        if (orientation() == Qt::Horizontal ) /* TODO: vertical */
        {
            auto points = d_ptr->chapters->points();
            auto selected = -1;
            for (int i = 0 ; i < points.count() ; i++)
            {
                if (event->x() >=  margin + (size().width() - 2 * margin) * points.at(i).time / 1000000.0 / d_ptr->inputLength)
                    selected = i;
            }
            if (selected >= 0 && selected < points.size())
                text = points.at(selected).name;
        }

        QPoint target( event->globalX() - ( event->x() - posX ),
                      QWidget::mapToGlobal( QPoint( 0, 0 ) ).y() );
        if (size().width() > handleLength())
        {
            auto time = HControlHelper::secsToTime(d_ptr->inputLength * valueFromPosition(event->x()) / maximum());
            d_ptr->timeTooltip->setTip( target, time, text );
        }
    }
    event->accept();
}

void HSeekSlider::mousePressEvent(QMouseEvent *event)
{
    if (!isEnabled() || (event->button() != Qt::LeftButton && event->button() != Qt::MidButton))
        return QSlider::mousePressEvent(event);

    d_ptr->jumping = false;

    // handle chapter clicks
    auto width = size().width();
    auto points = d_ptr->chapters->points();
    if (points.size() > 0 && d_ptr->inputLength && width)
    {
        if (orientation() == Qt::Horizontal ) /* TODO: vertical */
        {
            if (event->y() < 3 || event->y() > size().height() - 3)
            {
                auto selected = -1;
                auto startsnonzero = points.at(0).time > 0;
                auto min_diff = width + 1;
                for (int i = 0; i < points.count(); i++)
                {
                    int diff_x = fabs(width * points.at(i).time / 1000000.0 / d_ptr->inputLength - event->x());
                    if (diff_x < min_diff)
                    {
                        min_diff = diff_x;
                        selected = i + (startsnonzero ? 1 : 0);
                    }
                    else
                        break;
                }
                if (selected && min_diff < 4) // max 4px around mark
                {
                    emit chapterChanged(selected);
                    event->accept();
                    d_ptr->jumping = true;
                    return;
                }
            }
        }
    }

    d_ptr->sliding = true;
    setValue(valueFromPosition(event->x()));
    emit sliderMoved(value());
    event->accept();
}

void HSeekSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::RightButton)
        handleReleasedButton();
    else
        QSlider::mouseReleaseEvent(event);
}

void HSeekSlider::enterEvent(QEvent *)
{
    d_ptr->hideHandleTimer->stop();
    if ( isEnabled() && d_ptr->animationOpacity->direction() != QAbstractAnimation::Forward)
    {
        // If pause is called while not running Qt will complain */
        if (d_ptr->animationOpacity->state() == QAbstractAnimation::Running)
            d_ptr->animationOpacity->pause();
        d_ptr->animationOpacity->setDirection( QAbstractAnimation::Forward);
        d_ptr->animationOpacity->start();
    }
    // Don't show the tooltip if the slider is disabled or a menu is open
    if( isEnabled() && d_ptr->inputLength > 0 && !qApp->activePopupWidget())
        d_ptr->timeTooltip->show();
}

void HSeekSlider::leaveEvent(QEvent *)
{
    d_ptr->hideHandleTimer->start();
    // Hide the tooltip
    //   - if the mouse leave the slider rect (Note: it can still be over the tooltip!)
    //   - if another window is on the way of the cursor
    if (!rect().contains(mapFromGlobal(QCursor::pos())) || (!isActiveWindow() && !d_ptr->timeTooltip->isActiveWindow()))
        d_ptr->timeTooltip->hide();
}

void HSeekSlider::hideEvent(QHideEvent *)
{
    d_ptr->timeTooltip->hide();
}

bool HSeekSlider::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == d_ptr->timeTooltip)
    {
        if (event->type() == QEvent::MouseMove)
        {
            auto e = static_cast<QMouseEvent*>(event);
            if (rect().contains(mapFromGlobal(e->globalPos())))
                return false;
        }
        if (event->type() == QEvent::Leave || event->type() == QEvent::MouseMove)
            d_ptr->timeTooltip->hide();
        return false;
    }
    return QSlider::eventFilter(watched, event);
}

void HSeekSlider::setHandleOpacity(double value)
{
    if (qFuzzyCompare(d_ptr->opacity, value))
        return;
    d_ptr->opacity = value;
    update();
}

void HSeekSlider::setLoading(double value)
{
    if (qFuzzyCompare(d_ptr->loading, value))
        return;
    d_ptr->loading = value;
    update();
}

void HSeekSlider::updatePos()
{
    emit sliderDragged(1.0 * value() / maximum());
}

int HSeekSlider::handleLength()
{
    if (d_ptr->handleLength < 1)
    {
        QStyleOptionSlider option;
        initStyleOption(&option);
        d_ptr->handleLength = style()->pixelMetric(QStyle::PM_SliderLength, &option);
    }
    return d_ptr->handleLength;
}

int HSeekSlider::valueFromPosition(int pos)
{
    return QStyle::sliderValueFromPosition(minimum(), maximum(), pos - handleLength() / 2, width() - handleLength(), false);
}

void HSeekSlider::handleReleasedButton()
{
    if (!d_ptr->sliding && !d_ptr->jumping)
        return;
    d_ptr->sliding = false;
    auto seek = d_ptr->seekLimitTimer->isActive();
    d_ptr->seekLimitTimer->stop();
    if (d_ptr->jumping)
    {
        d_ptr->jumping = false;
        return;
    }
    if (seek && isEnabled())
        updatePos();
}

void HSeekSlider::init()
{
    setRange(0, 10000);
    setSingleStep(2);
    setPageStep(10);
    setMouseTracking(true);
    setTracking(true);
    setFocusPolicy(Qt::NoFocus);
    setMinimumHeight(18);
    setPosition(-1.0, 0);
//    secstotimestr( psz_length, 0 );

    d_ptr->seekLimitTimer = new QTimer(this);
    d_ptr->seekLimitTimer->setSingleShot(true);
    d_ptr->hideHandleTimer = new QTimer(this);
    d_ptr->hideHandleTimer->setSingleShot(true);
    d_ptr->hideHandleTimer->setInterval(2000);
    d_ptr->startLoadingTimer = new QTimer(this);
    d_ptr->startLoadingTimer->setSingleShot(true);
    d_ptr->startLoadingTimer->setInterval(500);
    d_ptr->timeTooltip = new HTimeTooltip;
    d_ptr->timeTooltip->setMouseTracking(true);
    d_ptr->timeTooltip->installEventFilter(this);
    d_ptr->chapters = new HSeekPoints(this);
    if (d_ptr->classic)
    {
        d_ptr->alternativeStyle = new HSeekStyle;
        setStyle(d_ptr->alternativeStyle);
    }

    d_ptr->animationOpacity = new QPropertyAnimation(this);
    d_ptr->animationOpacity->setTargetObject(this);
    d_ptr->animationOpacity->setDuration(300);
    d_ptr->animationOpacity->setStartValue(0.0);
    d_ptr->animationOpacity->setEndValue(1.0);
    auto loadingIn = new QPropertyAnimation(this);
    loadingIn->setTargetObject(this);
    loadingIn->setDuration(2000);
    loadingIn->setStartValue(0.0);
    loadingIn->setEndValue(1.0);
    loadingIn->setEasingCurve(QEasingCurve::OutBounce);
    auto loadingOut = new QPropertyAnimation(this);
    loadingOut->setTargetObject(this);
    loadingOut->setDuration(2000);
    loadingOut->setStartValue(1.0);
    loadingOut->setEndValue(0.0);
    loadingOut->setEasingCurve(QEasingCurve::OutBounce);
    d_ptr->animationLoading = new QSequentialAnimationGroup( this );
    d_ptr->animationLoading->addAnimation(loadingIn);
    d_ptr->animationLoading->addAnimation(loadingOut);
    d_ptr->animationLoading->setLoopCount(-1);

//    CONNECT( MainInputManager::getInstance(), inputChanged( bool ), this , inputUpdated( bool ) );
    connect(this, &HSeekSlider::sliderMoved, this, [=] { if (d_ptr->sliding && !d_ptr->seekLimitTimer->isActive()) d_ptr->seekLimitTimer->start(150); });
    connect(d_ptr->seekLimitTimer, &QTimer::timeout, this, &HSeekSlider::updatePos);
    connect(d_ptr->hideHandleTimer, &QTimer::timeout, this, &HSeekSlider::hideHandle);
    connect(d_ptr->startLoadingTimer, &QTimer::timeout, this, [&] { d_ptr->animationLoading->start(); });
    connect(d_ptr->animationOpacity, &QPropertyAnimation::valueChanged, this, [=](QVariant value) { setHandleOpacity(value.toDouble()); });
    connect(loadingIn, &QPropertyAnimation::valueChanged, this, [=](QVariant value) { setLoading(value.toDouble()); });
    connect(loadingOut, &QPropertyAnimation::valueChanged, this, [=](QVariant value) { setLoading(value.toDouble()); });
}

HE_CONTROL_END_NAMESPACE
