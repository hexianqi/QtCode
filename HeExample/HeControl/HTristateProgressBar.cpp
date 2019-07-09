#include "HTristateProgressBar_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HTristateProgressBar::HTristateProgressBar(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTristateProgressBarPrivate)
{
}

HTristateProgressBar::HTristateProgressBar(HTristateProgressBarPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HTristateProgressBar::~HTristateProgressBar()
{
}

QSize HTristateProgressBar::sizeHint() const
{
    return QSize(300, 30);
}

QSize HTristateProgressBar::minimumSizeHint() const
{
    return QSize(60, 20);
}

int HTristateProgressBar::value1() const
{
    return d_ptr->value1;
}

int HTristateProgressBar::value2() const
{
    return d_ptr->value2;
}

int HTristateProgressBar::value3() const
{
    return d_ptr->value3;
}

QColor HTristateProgressBar::color1() const
{
    return d_ptr->color1;
}

QColor HTristateProgressBar::color2() const
{
    return d_ptr->color2;
}

QColor HTristateProgressBar::color3() const
{
    return d_ptr->color3;
}

int HTristateProgressBar::radius() const
{
    return d_ptr->radius;
}

bool HTristateProgressBar::isAutoRadius() const
{
    return d_ptr->autoRadius;
}

bool HTristateProgressBar::isAutoFont() const
{
    return d_ptr->autoFont;
}

bool HTristateProgressBar::isShowValue() const
{
    return d_ptr->showValue;
}

bool HTristateProgressBar::isShowPercent() const
{
    return d_ptr->showPercent;
}

double HTristateProgressBar::borderWidth() const
{
    return d_ptr->borderWidth;
}

QColor HTristateProgressBar::background() const
{
    return d_ptr->background;
}

QColor HTristateProgressBar::borderColor() const
{
    return d_ptr->borderColor;
}

QColor HTristateProgressBar::textColor() const
{
    return d_ptr->textColor;
}

void HTristateProgressBar::setValue1(int value)
{
    if (d_ptr->value1 == value)
        return;
    d_ptr->value1 = value;
    update();
}

void HTristateProgressBar::setValue2(int value)
{
    if (d_ptr->value2 == value)
        return;
    d_ptr->value2 = value;
    update();
}

void HTristateProgressBar::setValue3(int value)
{
    if (d_ptr->value3 == value)
        return;
    d_ptr->value3 = value;
    update();
}

void HTristateProgressBar::setColor1(const QColor &value)
{
    if (d_ptr->color1 == value)
        return;
    d_ptr->color1 = value;
    update();
}

void HTristateProgressBar::setColor2(const QColor &value)
{
    if (d_ptr->color2 == value)
        return;
    d_ptr->color2 = value;
    update();
}

void HTristateProgressBar::setColor3(const QColor &value)
{
    if (d_ptr->color3 == value)
        return;
    d_ptr->color3 = value;
    update();
}

void HTristateProgressBar::setRadius(int value)
{
    if (d_ptr->radius == value)
        return;
    d_ptr->radius = value;
    update();
}

void HTristateProgressBar::setAutoRadius(bool b)
{
    if (d_ptr->autoRadius == b)
        return;
    d_ptr->autoRadius = b;
    update();
}

void HTristateProgressBar::setAutoFont(bool b)
{
    if (d_ptr->autoFont == b)
        return;
    d_ptr->autoFont = b;
    update();
}

void HTristateProgressBar::setShowValue(bool b)
{
    if (d_ptr->showValue == b)
        return;
    d_ptr->showValue = b;
    update();
}

void HTristateProgressBar::setShowPercent(bool b)
{
    if (d_ptr->showPercent == b)
        return;
    d_ptr->showPercent = b;
    update();
}

void HTristateProgressBar::setBorderWidth(double value)
{
    if (qFuzzyCompare(d_ptr->borderWidth, value))
        return;
    d_ptr->borderWidth = value;
    update();
}

void HTristateProgressBar::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HTristateProgressBar::setBorderColor(const QColor &value)
{
    if (d_ptr->borderColor == value)
        return;
    d_ptr->borderColor = value;
    update();
}

void HTristateProgressBar::setTextColor(const QColor &value)
{
    if (d_ptr->textColor == value)
        return;
    d_ptr->textColor = value;
    update();
}

void HTristateProgressBar::paintEvent(QPaintEvent *)
{
    if (d_ptr->autoRadius)
        d_ptr->radius = height() / 2;
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawValue(&painter);
    drawBorder(&painter);
}

void HTristateProgressBar::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->background);
    painter->drawRoundedRect(this->rect(), d_ptr->radius, d_ptr->radius);
    painter->restore();
}

void HTristateProgressBar::drawValue(QPainter *painter)
{
    auto sum = d_ptr->value1 + d_ptr->value2 + d_ptr->value3;
    auto percent1 = 1.0 * d_ptr->value1 / sum;
    auto percent2 = 1.0 * d_ptr->value2 / sum;
    auto percent3 = 1.0 * d_ptr->value3 / sum;
    auto width1 = width() * percent1;
    auto width2 = width() * percent2;
    auto width3 = width() * percent3;
    auto rect1 = QRectF(0, 0, width1, height());
    auto rect2 = QRectF(width1, 0, width2, this->height());
    auto rect3 = QRectF(width1 + width2, 0, width3, this->height());
    auto path = QPainterPath();
    path.addRoundedRect(this->rect(), d_ptr->radius, d_ptr->radius);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setClipPath(path);
    painter->setBrush(d_ptr->color1);
    painter->drawRect(rect1);
    painter->setBrush(d_ptr->color2);
    painter->drawRect(rect2);
    painter->setBrush(d_ptr->color3);
    painter->drawRect(rect3);
    if (d_ptr->showValue)
    {
        if (d_ptr->autoFont)
        {
            auto f = font();
            f.setPointSizeF(qMin(width() * 0.15, height() * 0.9));
            painter->setFont(f);
        }

        QString text1 = QString::number(d_ptr->value1);
        QString text2 = QString::number(d_ptr->value2);
        QString text3 = QString::number(d_ptr->value3);
        if (d_ptr->showPercent)
        {
            text1 = QString("%1%").arg(percent1 * 100, 0, 'f', 0);
            text2 = QString("%1%").arg(percent2 * 100, 0, 'f', 0);
            text3 = QString("%1%").arg(percent3 * 100, 0, 'f', 0);
        }
        painter->setPen(d_ptr->textColor);
        painter->drawText(rect1, Qt::AlignCenter, text1);
        painter->drawText(rect2, Qt::AlignCenter, text2);
        painter->drawText(rect3, Qt::AlignCenter, text3);
    }
    painter->restore();
}

void HTristateProgressBar::drawBorder(QPainter *painter)
{
    painter->save();
    painter->setPen(d_ptr->borderWidth > 0 ? QPen(d_ptr->borderColor, d_ptr->borderWidth) : Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(this->rect(), d_ptr->radius, d_ptr->radius);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
