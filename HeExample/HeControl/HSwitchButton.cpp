#include "HSwitchButton_p.h"
#include "HDrawHelper.h"
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_CONTROL_BEGIN_NAMESPACE

HSwitchButton::HSwitchButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSwitchButtonPrivate)
{
    init();
}

HSwitchButton::HSwitchButton(HSwitchButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HSwitchButton::~HSwitchButton()
{
}

QSize HSwitchButton::sizeHint() const
{
    return QSize(60, 30);
}

QSize HSwitchButton::minimumSizeHint() const
{
    return QSize(20, 20);
}

int HSwitchButton::space() const
{
    return d_ptr->space;
}

int HSwitchButton::rectRadius() const
{
    return d_ptr->rectRadius;
}

bool HSwitchButton::isChecked() const
{
    return d_ptr->checked;
}

bool HSwitchButton::isShowText() const
{
    return d_ptr->showText;
}

bool HSwitchButton::isShowCircle() const
{
    return d_ptr->showCircle;
}

bool HSwitchButton::isAnimationEnable() const
{
    return d_ptr->animationEnable;
}

HSwitchButton::ButtonStyle HSwitchButton::buttonStyle() const
{
    return d_ptr->buttonStyle;
}

QColor HSwitchButton::backgroundOff() const
{
    return d_ptr->backgroundOff;
}

QColor HSwitchButton::backgroundOn() const
{
    return d_ptr->backgroundOn;
}

QColor HSwitchButton::sliderColorOff() const
{
    return d_ptr->sliderColorOff;
}

QColor HSwitchButton::sliderColorOn() const
{
    return d_ptr->sliderColorOn;
}

QColor HSwitchButton::textColorOff() const
{
    return d_ptr->textColorOff;
}

QColor HSwitchButton::textColorOn() const
{
    return d_ptr->textColorOn;
}

QString HSwitchButton::textOff() const
{
    return d_ptr->textOff;
}

QString HSwitchButton::textOn() const
{
    return d_ptr->textOn;
}

void HSwitchButton::setSpace(int value)
{
    if (d_ptr->space == value)
        return;
    d_ptr->space = value;
    d_ptr->pos = isChecked() ? calcPos() : 0;
    update();
}

void HSwitchButton::setRectRadius(int value)
{
    if (d_ptr->rectRadius == value)
        return;
    d_ptr->rectRadius = value;
    update();
}

void HSwitchButton::setChecked(bool b)
{
    if (d_ptr->checked == b)
        return;
    d_ptr->checked = b;
    startAnimation();
}

void HSwitchButton::setShowText(bool b)
{
    if (d_ptr->showText == b)
        return;
    d_ptr->showText = b;
    update();
}

void HSwitchButton::setShowCircle(bool b)
{
    if (d_ptr->showCircle == b)
        return;
    d_ptr->showCircle = b;
    update();
}

void HSwitchButton::setAnimationEnable(bool b)
{
    if (d_ptr->animationEnable == b)
        return;
    d_ptr->animationEnable = b;
}

void HSwitchButton::setButtonStyle(ButtonStyle value)
{
    if (d_ptr->buttonStyle == value)
        return;
    d_ptr->buttonStyle = value;
    update();
}

void HSwitchButton::setBackgroundOff(const QColor &value)
{
    if (d_ptr->backgroundOff == value)
        return;
    d_ptr->backgroundOff = value;
    update();
}

void HSwitchButton::setBackgroundOn(const QColor &value)
{
    if (d_ptr->backgroundOn == value)
        return;
    d_ptr->backgroundOn = value;
    update();
}

void HSwitchButton::setSliderColorOff(const QColor &value)
{
    if (d_ptr->sliderColorOff == value)
        return;
    d_ptr->sliderColorOff = value;
    update();
}

void HSwitchButton::setSliderColorOn(const QColor &value)
{
    if (d_ptr->sliderColorOn == value)
        return;
    d_ptr->sliderColorOn = value;
    update();
}

void HSwitchButton::setTextColorOff(const QColor &value)
{
    if (d_ptr->textColorOff == value)
        return;
    d_ptr->textColorOff = value;
    update();
}

void HSwitchButton::setTextColorOn(const QColor &value)
{
    if (d_ptr->textColorOn == value)
        return;
    d_ptr->textColorOn = value;
    update();
}

void HSwitchButton::setTextOff(const QString &value)
{
    if (d_ptr->textOff == value)
        return;
    d_ptr->textOff = value;
    update();
}

void HSwitchButton::setTextOn(const QString &value)
{
    if (d_ptr->textOn == value)
        return;
    d_ptr->textOn = value;
    update();
}

void HSwitchButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        setChecked(!isChecked());
    QWidget::mousePressEvent(e);
}

void HSwitchButton::resizeEvent(QResizeEvent *e)
{
    d_ptr->pos = isChecked() ? calcPos() : 0;
    return QWidget::resizeEvent(e);
}

void HSwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawText(&painter);
    drawCircle(&painter);
    drawSlider(&painter);
}

void HSwitchButton::drawBackground(QPainter *painter)
{
    auto color = isChecked() ? backgroundOn() : backgroundOff();
    if (!isEnabled())
        color.setAlpha(60);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);

    auto side = qMin(width() / 2, height());
    auto y = rect().center().y() - side / 2;
    if (buttonStyle() == ButtonStyle_CircleIn)
    {
        QPainterPath path1, path2, path3;
        path1.addEllipse(0, y, side, side);
        path2.addEllipse(width() - side, y, side, side);
        path3.addRect(side / 2, y, width() - side, side);
        painter->drawPath(path3 + path1 + path2);
    }
    else if (buttonStyle() == ButtonStyle_CircleOut)
        painter->drawRoundedRect(side / 2, y + space(), width() - side, side - space() * 2, rectRadius(), rectRadius());
    else if (buttonStyle() == ButtonStyle_Rect)
        painter->drawRoundedRect(rect(), rectRadius(), rectRadius());

    painter->restore();
}

void HSwitchButton::drawText(QPainter *painter)
{
    if (!isShowText())
        return;
    if (buttonStyle() != ButtonStyle_Rect && buttonStyle() != ButtonStyle_CircleIn)
        return;

    auto x = buttonStyle() == ButtonStyle_Rect ? width() / 2 : qMin(width() / 2, height()) - space() * 2 ;
    auto text = textOn().length() > textOff().length() ? textOn() : textOff();
    auto f = HDrawHelper::adjustFontSize(painter, text, x);
    painter->save();
    painter->setFont(f);
    if (isChecked())
    {
        painter->setPen(textColorOn());
        painter->drawText(QRect(0, 0, width() - x, height()), Qt::AlignCenter, textOn());
    }
    else
    {
        painter->setPen(textColorOff());
        painter->drawText(QRect(x, 0, width() - x, height()), Qt::AlignCenter, textOff());
    }
    painter->restore();
}

void HSwitchButton::drawCircle(QPainter *painter)
{
    if (!isShowCircle())
        return;
    if (buttonStyle() != ButtonStyle_Rect && buttonStyle() != ButtonStyle_CircleIn)
        return;

    auto side = qMin(width() / 2, height()) / 2;
    auto y = rect().center().y() - side / 2;
    painter->save();
    if (isChecked())
    {
        painter->setPen(QPen(textColorOn(), 2));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(QRectF(side * 0.5, y, side, side));
    }
    else
    {
        painter->setPen(QPen(textColorOff(), 2));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(QRectF(width() - side * 1.5, y, side, side));
    }
    painter->restore();
}

void HSwitchButton::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(isChecked() ? sliderColorOn() : sliderColorOff());
    if (buttonStyle() == ButtonStyle_CircleIn)
    {
        auto side = qMin(width() / 2, height()) - space() * 2;
        auto y = rect().center().y() - side / 2;
        painter->drawEllipse(d_ptr->pos + space(), y, side, side);
    }
    else if (buttonStyle() == ButtonStyle_CircleOut)
    {
        auto side = qMin(width() / 2, height());
        auto y = rect().center().y() - side / 2;
        auto rect = QRect(d_ptr->pos, y, side, side);
        auto color1 = (isChecked() ? Qt::white : backgroundOff());
        auto color2 = (isChecked() ? sliderColorOn() : sliderColorOff());
        auto gradient = QRadialGradient(rect.center(), side / 2);
        gradient.setColorAt(0.0, isChecked() ? color1 : color2);
        gradient.setColorAt(0.5, isChecked() ? color1 : color2);
        gradient.setColorAt(0.6, isChecked() ? color2 : color1);
        gradient.setColorAt(1.0, isChecked() ? color2 : color1);
        painter->setBrush(gradient);
        painter->drawEllipse(rect);
    }
    else if (buttonStyle() == ButtonStyle_Rect)
    {
        painter->drawRoundedRect(d_ptr->pos + space(), space(), width() / 2 - space() * 2 , height() - space() * 2, rectRadius(), rectRadius());
    }
    painter->restore();
}

void HSwitchButton::init()
{
    d_ptr->animation = new QPropertyAnimation(this);
    d_ptr->animation->setTargetObject(this);
    d_ptr->animation->setEasingCurve(QEasingCurve::Linear);
    connect(d_ptr->animation, &QPropertyAnimation::valueChanged, this, [=](QVariant value) { d_ptr->pos = value.toInt();  update();});
}

void HSwitchButton::startAnimation()
{
    auto pos = calcPos();
    auto start = isChecked() ? 0 : pos;
    auto end = isChecked() ? pos : 0;
    if (isAnimationEnable())
    {
        d_ptr->animation->setStartValue(start);
        d_ptr->animation->setEndValue(end);
        d_ptr->animation->start();
    }
    else
    {
        d_ptr->pos = end;
        update();
    }
}

int HSwitchButton::calcPos()
{
    if (buttonStyle() == ButtonStyle_Rect)
        return width() / 2;
    if (buttonStyle() == ButtonStyle_CircleIn || buttonStyle() == ButtonStyle_CircleOut)
        return width() - qMin(width() / 2, height());
    return 0;
}

HE_CONTROL_END_NAMESPACE
