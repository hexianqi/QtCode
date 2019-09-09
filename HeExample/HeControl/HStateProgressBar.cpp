#include "HStateProgressBar_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HStateProgressBar::HStateProgressBar(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HStateProgressBarPrivate)
{
}

HStateProgressBar::HStateProgressBar(HStateProgressBarPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HStateProgressBar::~HStateProgressBar()
{
}

QSize HStateProgressBar::sizeHint() const
{
    return QSize(width(), width() / 5);
}

QSize HStateProgressBar::minimumSizeHint() const
{
    return QSize(125 * d_ptr->maximum, 25 * d_ptr->maximum);
}

QString HStateProgressBar::tip() const
{
    return d_ptr->tip;
}

HStateProgressBar::StateStyle HStateProgressBar::stateStyle() const
{
    return d_ptr->stateStyle;
}

QColor HStateProgressBar::barColor() const
{
    return d_ptr->barColor;
}

QColor HStateProgressBar::barBackground() const
{
    return d_ptr->barBackground;
}

QColor HStateProgressBar::noteColor() const
{
    return d_ptr->noteColor;
}

QColor HStateProgressBar::stateColor() const
{
    return d_ptr->stateColor;
}

QColor HStateProgressBar::tipColor() const
{
    return d_ptr->tipColor;
}

QColor HStateProgressBar::tipBackground() const
{
    return d_ptr->tipBackground;
}

void HStateProgressBar::setTip(const QString &value)
{
    if (d_ptr->tip == value)
        return;
    d_ptr->tip = value;
    update();
}

void HStateProgressBar::setNotes(const QStringList &value)
{
    if (d_ptr->notes == value)
        return;
    d_ptr->notes = value;
    update();
}

void HStateProgressBar::setStates(const QStringList &value)
{
    if (d_ptr->states == value)
        return;
    d_ptr->states = value;
    update();
}

void HStateProgressBar::setStateStyle(HStateProgressBar::StateStyle value)
{
    if (d_ptr->stateStyle == value)
        return;
    d_ptr->stateStyle = value;
    update();
}

void HStateProgressBar::setBarColor(const QColor &value)
{
    if (d_ptr->barColor == value)
        return;
    d_ptr->barColor = value;
    update();
}

void HStateProgressBar::setBarBackground(const QColor &value)
{
    if (d_ptr->barBackground == value)
        return;
    d_ptr->barBackground = value;
    update();
}

void HStateProgressBar::setNoteColor(const QColor &value)
{
    if (d_ptr->noteColor == value)
        return;
    d_ptr->noteColor = value;
    update();
}

void HStateProgressBar::setStateColor(const QColor &value)
{
    if (d_ptr->stateColor == value)
        return;
    d_ptr->stateColor = value;
    update();
}

void HStateProgressBar::setTipColor(const QColor &value)
{
    if (d_ptr->tipColor == value)
        return;
    d_ptr->tipColor = value;
    update();
}

void HStateProgressBar::setTipBackground(const QColor &value)
{
    if (d_ptr->tipBackground == value)
        return;
    d_ptr->tipBackground = value;
    update();
}

void HStateProgressBar::setValue(int value)
{
    if (value < 0 || value > d_ptr->maximum || value == d_ptr->value)
        return;
    d_ptr->value = value;
    update();
}

void HStateProgressBar::setMaximum(int value)
{
    if (value < 1 || value == d_ptr->maximum)
        return;
    d_ptr->maximum = value;
    if (d_ptr->value >= value)
        d_ptr->value = value - 1;
    update();
}

void HStateProgressBar::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    auto diameter = qMin(width()/(d_ptr->maximum * 5), height() * 2 / 9);

    d_ptr->bigRadius = diameter / 2;
    d_ptr->smallRadius = diameter * 2 / 5;
    d_ptr->lineWidth = width() / d_ptr->maximum;
    d_ptr->lineHeight = diameter / 5;
    d_ptr->innerLineHeight = diameter * 4 / 25;

    auto f = font();
    f.setPixelSize(d_ptr->bigRadius);
    painter.setFont(f);
    if (d_ptr->notes.isEmpty() && d_ptr->tip.isEmpty() && !d_ptr->states.isEmpty())
        painter.translate(d_ptr->lineWidth / 2, height() / 4);
    else
        painter.translate(d_ptr->lineWidth / 2, height() / 2);
    drawBackground(&painter);
    drawBarBackground(&painter);
    drawBar(&painter);
    drawBarNumber(&painter);
}

void HStateProgressBar::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::transparent);
    painter->drawRoundRect(rect(), 0, 0);
    painter->restore();
}

void HStateProgressBar::drawBarBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->barBackground);
    for (int i = 0; i < d_ptr->maximum; i++)
    {
        painter->drawEllipse(QPointF(i * d_ptr->lineWidth, 0), d_ptr->bigRadius, d_ptr->bigRadius);
        if (i > 0)
            painter->drawRect((i-1) * d_ptr->lineWidth, -d_ptr->lineHeight / 2, d_ptr->lineWidth, d_ptr->lineHeight);
        drawNote(painter, i, d_ptr->barBackground);
        drawState(painter, i, d_ptr->barBackground);
    }
    painter->restore();
}

void HStateProgressBar::drawBar(QPainter *painter)
{
    if (d_ptr->value < 1)
        return;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->barColor);
    for (int i = 0; i < d_ptr->value; i++)
    {
        painter->drawEllipse(QPointF(i*d_ptr->lineWidth, 0), d_ptr->smallRadius, d_ptr->smallRadius);
        if (i == d_ptr->value - 1)
        {
            if (d_ptr->value != d_ptr->maximum)
                painter->drawRect(i * d_ptr->lineWidth, -d_ptr->innerLineHeight / 2,  d_ptr->lineWidth / 2, d_ptr->innerLineHeight);
        }
        else
            painter->drawRect( i * d_ptr->lineWidth, -d_ptr->innerLineHeight / 2,  d_ptr->lineWidth, d_ptr->innerLineHeight);

        drawNote(painter, i, d_ptr->noteColor);
        drawState(painter, i, d_ptr->stateColor);
    }
    drawTip(painter, d_ptr->value - 1);
    painter->restore();
}

void HStateProgressBar::drawBarNumber(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    for (int i = 0; i < d_ptr->maximum; i++)
    {
        if (d_ptr->stateStyle == StateStyle_NACK || i >= d_ptr->value)
            painter->drawText(QRectF(i * d_ptr->lineWidth - d_ptr->bigRadius, -d_ptr->bigRadius, 2 * d_ptr->bigRadius, 2 * d_ptr->bigRadius), Qt::AlignCenter, QString::number(i+1));
        else
        {
            painter->setPen(QPen(Qt::white, 2));
            auto center = QPointF(i*d_ptr->lineWidth, 0);
            auto p1 = QPointF(center.x(), center.y() + d_ptr->smallRadius / 3);
            auto p2 = QPointF(center.x() - d_ptr->smallRadius / 3, center.y());
            auto p3 = QPointF(center.x() + d_ptr->smallRadius / 2, center.y() - d_ptr->smallRadius / 3);
            painter->drawLine(p1, p2);
            painter->drawLine(p1, p3);
        }
    }
    painter->restore();
}

void HStateProgressBar::drawNote(QPainter *painter, int index, const QColor &color)
{
    if (index < 0 || index>= d_ptr->notes.count())
        return;

    auto textWidth = painter->fontMetrics().width(d_ptr->notes[index]);
    painter->save();
    painter->setPen(color);
    painter->drawText(QRectF(-textWidth * 0.75 + index * d_ptr->lineWidth, -d_ptr->bigRadius * 4, textWidth * 1.5, d_ptr->bigRadius * 2), Qt::AlignCenter, d_ptr->notes[index]);
    painter->restore();
}

void HStateProgressBar::drawState(QPainter *painter, int index, const QColor &color)
{
    if (index < 0 || index>= d_ptr->states.count())
        return;

    auto textWidth = painter->fontMetrics().width(d_ptr->states[index]);
    painter->save();
    painter->setPen(color);
    painter->drawText(QRectF(-textWidth * 0.75 + index * d_ptr->lineWidth, d_ptr->bigRadius * 1.5, textWidth * 1.5, d_ptr->bigRadius * 2), Qt::AlignCenter, d_ptr->states[index]);
    painter->restore();
}

void HStateProgressBar::drawTip(QPainter *painter, int index)
{
    if ((d_ptr->notes.isEmpty() || index >= d_ptr->notes.count() || d_ptr->notes[index].isEmpty()) && d_ptr->tip.isEmpty())
        return;

    auto tip = index < d_ptr->notes.count() ? d_ptr->notes[index] : d_ptr->tip;
    auto f = font();
    f.setBold(true);
    auto textWidth = painter->fontMetrics().width(tip);
    textWidth = qMax(textWidth, d_ptr->bigRadius * 2);
    auto rect = QRectF(index * d_ptr->lineWidth - textWidth, -d_ptr->bigRadius * 4, textWidth * 2, d_ptr->bigRadius * 2);
    auto poly = QPolygonF() << QPointF(index * d_ptr->lineWidth, -d_ptr->bigRadius * 1.5)
                            << QPointF(index * d_ptr->lineWidth - d_ptr->bigRadius * 0.5, -2 * d_ptr->bigRadius)
                            << QPointF(index * d_ptr->lineWidth + d_ptr->bigRadius * 0.5, -2 * d_ptr->bigRadius);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->tipBackground);
    painter->drawRoundedRect(rect, d_ptr->bigRadius * 0.5, d_ptr->bigRadius * 0.5);
    painter->drawPolygon(poly);
    painter->setPen(d_ptr->tipColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, tip);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
