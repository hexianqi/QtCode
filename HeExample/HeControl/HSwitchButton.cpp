#include "HSwitchButton_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HSwitchButton::HSwitchButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSwitchButtonPrivate)
{
}

HSwitchButton::HSwitchButton(HSwitchButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HSwitchButton::~HSwitchButton()
{
}

QSize HSwitchButton::sizeHint() const
{

}

int HSwitchButton::space() const
{
    return m_space;
}

int HSwitchButton::rectRadius() const
{
    return m_rectRadius;
}

bool HSwitchButton::isChecked() const
{
    return m_checked;
}

bool HSwitchButton::isShowText() const
{
    return m_showText;
}

bool HSwitchButton::isShowCircle() const
{
    return m_showCircle;
}

bool HSwitchButton::isAnimation() const
{
    return m_animation;
}

HSwitchButton::ButtonStyle HSwitchButton::buttonStyle() const
{
    return m_buttonStyle;
}

QColor HSwitchButton::backgroundOff() const
{
    return m_backgroundOff;
}

QColor HSwitchButton::backgroundOn() const
{
    return m_backgroundOn;
}

QColor HSwitchButton::sliderColorOff() const
{
    return m_sliderColorOff;
}

QColor HSwitchButton::sliderColorOn() const
{
    return m_sliderColorOn;
}

QColor HSwitchButton::textColorOff() const
{
    return m_textColorOff;
}

QColor HSwitchButton::textColorOn() const
{
    return m_textColorOn;
}

QString HSwitchButton::textOff() const
{
    return m_textOff;
}

QString HSwitchButton::textOn() const
{
    return m_textOn;
}

void HSwitchButton::setSpace(int value)
{
    m_space = value;
}

void HSwitchButton::setRectRadius(int value)
{
    m_rectRadius = rectRadius;
}

void HSwitchButton::setChecked(bool b)
{
    m_checked = b;
}

void HSwitchButton::setShowText(bool b)
{
    m_showText = showText;
}

void HSwitchButton::setShowCircle(bool b)
{
    m_showCircle = b;
}

void HSwitchButton::setAnimation(bool b)
{
    m_animation = animation;
}

void HSwitchButton::setButtonStyle(ButtonStyle value)
{
    m_buttonStyle = value;
}

void HSwitchButton::setBackgroundOff(const QColor &value)
{
    m_backgroundOff = backgroundOff;
}

void HSwitchButton::setBackgroundOn(const QColor &value)
{
    m_backgroundOn = value;
}

void HSwitchButton::setSliderColorOff(const QColor &value)
{
    m_sliderColorOff = sliderColorOff;
}

void HSwitchButton::setSliderColorOn(const QColor &value)
{
    m_sliderColorOn = sliderColorOn;
}

void HSwitchButton::setTextColorOff(const QColor &value)
{
    m_textColorOff = value;
}

void HSwitchButton::setTextColorOn(const QColor &value)
{
    m_textColorOn = textColorOn;
}

void HSwitchButton::setTextOff(const QString &value)
{
    m_textOff = textOff;
}

void HSwitchButton::setTextOn(const QString &value)
{
    m_textOn = value;
}

void HSwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
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


    if (buttonStyle() == ButtonStyle_CircleIn)
    {
        auto rect = QRect(0, 0, width(), height());
        auto side = qMin(rect.width(), rect.height());
        QPainterPath path1, path2, path3;
        path1.addEllipse(rect.x(), rect.y(), side, side);
        path2.addEllipse(rect.width() - side, rect.y(), side, side);
        path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, rect.height());
        painter->drawPath(path3 + path1 + path2);
    }
    else if (buttonStyle() == ButtonStyle_CircleOut)
        painter->drawRoundedRect(height() / 2, space(), width() - height(), height() - space() * 2, rectRadius(), rectRadius());
    else if (buttonStyle() == ButtonStyle_Rect)
        painter->drawRoundedRect(rect(), rectRadius(), rectRadius());




    painter->restore();



    //    if (buttonStyle == ButtonStyle_Rect || buttonStyle == ButtonStyle_CircleIn) {
    //        //绘制文本和小圆,互斥
    //        if (showText) {
    //            int sliderWidth = qMin(width(), height()) - space * 2;
    //            if (buttonStyle == ButtonStyle_Rect) {
    //                sliderWidth = width() / 2 - 5;
    //            } else if (buttonStyle == ButtonStyle_CircleIn) {
    //                sliderWidth -= 5;
    //            }

    //            if (checked) {
    //                QRect textRect(0, 0, width() - sliderWidth, height());
    //                painter->setPen(textColorOn);
    //                painter->drawText(textRect, Qt::AlignCenter, textOn);
    //            } else {
    //                QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
    //                painter->setPen(textColorOff);
    //                painter->drawText(textRect, Qt::AlignCenter, textOff);
    //            }
    //        } else if (showCircle) {
    //            int side = qMin(width(), height()) / 2;
    //            int y = (height() - side) / 2;

    //            if (checked) {
    //                QRect circleRect(side / 2, y, side, side);
    //                QPen pen(textColorOn, 2);
    //                painter->setPen(pen);
    //                painter->setBrush(Qt::NoBrush);
    //                painter->drawEllipse(circleRect);
    //            } else {
    //                QRect circleRect(width() - (side * 1.5), y, side, side);
    //                QPen pen(textColorOff, 2);
    //                painter->setPen(pen);
    //                painter->setBrush(Qt::NoBrush);
    //                painter->drawEllipse(circleRect);
    //            }
    //        }
    //    }



}

HE_CONTROL_END_NAMESPACE


//void SwitchButton::drawBg(QPainter *painter)
//{
//    painter->save();
//    painter->setPen(Qt::NoPen);

//    QColor bgColor = checked ? bgColorOn : bgColorOff;
//    if (!isEnabled()) {
//        bgColor.setAlpha(60);
//    }

//    painter->setBrush(bgColor);

//    if (buttonStyle == ButtonStyle_Rect) {
//        painter->drawRoundedRect(rect(), rectRadius, rectRadius);
//    } else if (buttonStyle == ButtonStyle_CircleIn) {
//        QRect rect(0, 0, width(), height());
//        //半径为高度的一半
//        int side = qMin(rect.width(), rect.height());

//        //左侧圆
//        QPainterPath path1;
//        path1.addEllipse(rect.x(), rect.y(), side, side);
//        //右侧圆
//        QPainterPath path2;
//        path2.addEllipse(rect.width() - side, rect.y(), side, side);
//        //中间矩形
//        QPainterPath path3;
//        path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, rect.height());

//        QPainterPath path;
//        path = path3 + path1 + path2;
//        painter->drawPath(path);
//    } else if (buttonStyle == ButtonStyle_CircleOut) {
//        QRect rect(height() / 2, space, width() - height(), height() - space * 2);
//        painter->drawRoundedRect(rect, rectRadius, rectRadius);
//    }

//    if (buttonStyle == ButtonStyle_Rect || buttonStyle == ButtonStyle_CircleIn) {
//        //绘制文本和小圆,互斥
//        if (showText) {
//            int sliderWidth = qMin(width(), height()) - space * 2;
//            if (buttonStyle == ButtonStyle_Rect) {
//                sliderWidth = width() / 2 - 5;
//            } else if (buttonStyle == ButtonStyle_CircleIn) {
//                sliderWidth -= 5;
//            }

//            if (checked) {
//                QRect textRect(0, 0, width() - sliderWidth, height());
//                painter->setPen(textColorOn);
//                painter->drawText(textRect, Qt::AlignCenter, textOn);
//            } else {
//                QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
//                painter->setPen(textColorOff);
//                painter->drawText(textRect, Qt::AlignCenter, textOff);
//            }
//        } else if (showCircle) {
//            int side = qMin(width(), height()) / 2;
//            int y = (height() - side) / 2;

//            if (checked) {
//                QRect circleRect(side / 2, y, side, side);
//                QPen pen(textColorOn, 2);
//                painter->setPen(pen);
//                painter->setBrush(Qt::NoBrush);
//                painter->drawEllipse(circleRect);
//            } else {
//                QRect circleRect(width() - (side * 1.5), y, side, side);
//                QPen pen(textColorOff, 2);
//                painter->setPen(pen);
//                painter->setBrush(Qt::NoBrush);
//                painter->drawEllipse(circleRect);
//            }
//        }
//    }

//    painter->restore();
//}

//void SwitchButton::drawSlider(QPainter *painter)
//{
//    painter->save();
//    painter->setPen(Qt::NoPen);

//    if (!checked) {
//        painter->setBrush(sliderColorOff);
//    } else {
//        painter->setBrush(sliderColorOn);
//    }

//    if (buttonStyle == ButtonStyle_Rect) {
//        int sliderWidth = width() / 2 - space * 2;
//        int sliderHeight = height() - space * 2;
//        QRect sliderRect(startX + space, space, sliderWidth , sliderHeight);
//        painter->drawRoundedRect(sliderRect, rectRadius, rectRadius);
//    } else if (buttonStyle == ButtonStyle_CircleIn) {
//        QRect rect(0, 0, width(), height());
//        int sliderWidth = qMin(rect.width(), rect.height()) - space * 2;
//        QRect sliderRect(startX + space, space, sliderWidth, sliderWidth);
//        painter->drawEllipse(sliderRect);
//    } else if (buttonStyle == ButtonStyle_CircleOut) {
//        int sliderWidth = this->height();
//        QRect sliderRect(startX, 0, sliderWidth, sliderWidth);

//        QColor color1 = (checked ? Qt::white : bgColorOff);
//        QColor color2 = (checked ? sliderColorOn : sliderColorOff);

//        QRadialGradient radialGradient(sliderRect.center(), sliderWidth / 2);
//        radialGradient.setColorAt(0, checked ? color1 : color2);
//        radialGradient.setColorAt(0.5, checked ? color1 : color2);
//        radialGradient.setColorAt(0.6, checked ? color2 : color1);
//        radialGradient.setColorAt(1.0, checked ? color2 : color1);
//        painter->setBrush(radialGradient);

//        painter->drawEllipse(sliderRect);
//    }

//    painter->restore();
//}
