#include "HButtonProgressBar_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_CONTROL_BEGIN_NAMESPACE

HButtonProgressBar::HButtonProgressBar(QWidget *parent) :
    HAbstractProgress(*new HButtonProgressBarPrivate, parent)
{
    init();
}

HButtonProgressBar::HButtonProgressBar(HButtonProgressBarPrivate &p, QWidget *parent) :
    HAbstractProgress(p, parent)
{
    init();
}

HButtonProgressBar::~HButtonProgressBar()
{
}

QSize HButtonProgressBar::sizeHint() const
{
    return QSize(200, 80);
}

QSize HButtonProgressBar::minimumSizeHint() const
{
    return QSize(20, 20);
}

QColor HButtonProgressBar::background() const
{
    Q_D(const HButtonProgressBar);
    return d->background;
}

int HButtonProgressBar::lineWidth() const
{
    Q_D(const HButtonProgressBar);
    return d->lineWidth;
}

QColor HButtonProgressBar::lineColor() const
{
    Q_D(const HButtonProgressBar);
    return d->lineColor;
}

int HButtonProgressBar::borderWidth() const
{
    Q_D(const HButtonProgressBar);
    return d->borderWidth;
}

int HButtonProgressBar::borderRadius() const
{
    Q_D(const HButtonProgressBar);
    return d->borderRadius;
}

QColor HButtonProgressBar::borderColor() const
{
    Q_D(const HButtonProgressBar);
    return d->borderColor;
}

void HButtonProgressBar::setBackground(const QColor &value)
{
    Q_D(HButtonProgressBar);
    if (d->background == value)
        return;
    d->background = value;
    update();
}

void HButtonProgressBar::setLineWidth(int value)
{
    Q_D(HButtonProgressBar);
    if (d->lineWidth == value)
        return;
    d->lineWidth = value;
    update();
}

void HButtonProgressBar::setLineColor(const QColor &value)
{
    Q_D(HButtonProgressBar);
    if (d->lineColor == value)
        return;
    d->lineColor = value;
    update();
}

void HButtonProgressBar::setBorderWidth(int value)
{
    Q_D(HButtonProgressBar);
    if (d->borderWidth == value)
        return;
    d->borderWidth = value;
    update();
}

void HButtonProgressBar::setBorderRadius(int value)
{
    Q_D(HButtonProgressBar);
    if (d->borderRadius == value)
        return;
    d->borderRadius = value;
    update();
}

void HButtonProgressBar::setBorderColor(const QColor &value)
{
    Q_D(HButtonProgressBar);
    if (d->borderColor == value)
        return;
    d->borderColor = value;
    update();
}

void HButtonProgressBar::resizeEvent(QResizeEvent *)
{
    Q_D(HButtonProgressBar);
    d->tempWidth = width();
}

void HButtonProgressBar::mousePressEvent(QMouseEvent *e)
{
    Q_D(HButtonProgressBar);
    if (e->button() == Qt::LeftButton && d->status != 1)
    {
        d->status = 0;
        d->timer->start();
    }
    return HAbstractProgress::mousePressEvent(e);
}

void HButtonProgressBar::paintEvent(QPaintEvent *)
{
    Q_D(HButtonProgressBar);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    if (d->status == 1)
        drawProgress(&painter);
    else
        drawBackground(&painter);
}

void HButtonProgressBar::drawBackground(QPainter *painter)
{
    Q_D(HButtonProgressBar);
    auto f = font();
    f.setPixelSize(qMin(width() * 0.35, height() * 0.9));
    auto pen = QPen(d->borderColor, d->borderWidth);
    auto rect = QRect(((width() - d->tempWidth) / 2) + d->borderWidth, d->borderWidth, d->tempWidth - d->borderWidth * 2, height() - d->borderWidth * 2);
    painter->save();
    painter->setPen(d->borderWidth > 0 ? pen : Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawRoundedRect(rect, d->borderRadius, d->borderRadius);
    painter->setFont(f);
    painter->setPen(d->lineColor);
    painter->drawText(rect, Qt::AlignCenter, d->status == 2 ? "完 成" : "开 始");
    painter->restore();
}

void HButtonProgressBar::drawProgress(QPainter *painter)
{
    Q_D(HButtonProgressBar);
    auto side = qMin(width(), height());
    auto radius = 99 - d->borderWidth;
    auto offset = radius - d->lineWidth - 5;
    auto pen1 = QPen(d->borderColor, d->borderWidth);
    auto pen2 = QPen(d->lineColor, d->lineWidth);
    auto f = font();
    f.setPixelSize(offset - 18);
    auto rectCircle = QRect(-radius, -radius, radius * 2, radius * 2);
    auto rectArc = QRectF(-offset, -offset, offset * 2, offset * 2);
    auto percent = toRatio(d->value) * 100;

    painter->save();
    painter->translate(width() / 2, height() / 2);
    painter->scale(side / 200.0, side / 200.0);
    painter->setPen(d->borderWidth > 0 ? pen1 : Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawEllipse(rectCircle);
    painter->setPen(pen2);
    painter->drawArc(rectArc, offset * 16, -3.6 * percent * 16);
    painter->setFont(f);
    painter->drawText(rectCircle, Qt::AlignCenter, QString("%1%").arg(percent, 0, 'f', 0));
    painter->restore();
}

void HButtonProgressBar::init()
{
    Q_D(HButtonProgressBar);
    d->timer = new QTimer(this);
    d->timer->setInterval(20);
    connect(d->timer, &QTimer::timeout, this, &HButtonProgressBar::updateValue);
}

void HButtonProgressBar::updateValue()
{
    Q_D(HButtonProgressBar);
    if (d->status == 0)
    {
        d->tempWidth -= 5;
        if (d->tempWidth < height() / 2)
        {
            d->tempWidth = height() / 2;
            d->value = d->minimum;
            d->status = 1;
        }
    }
    else if (d->status == 1)
    {
        d->value += range() / 100.0;
        if (d->value >= d->maximum)
        {
            d->value = d->maximum;
            d->status = 2;
        }
    }
    else if (d->status == 2)
    {
        d->tempWidth += 5;
        if (d->tempWidth >= width())
        {
            d->tempWidth = width();
            d->timer->stop();
        }
    }
    update();
}

HE_CONTROL_END_NAMESPACE
