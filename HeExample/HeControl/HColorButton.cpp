#include "HColorButton_p.h"
#include "HMoveEventFilter.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_CONTROL_BEGIN_NAMESPACE

HColorButton::HColorButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HColorButtonPrivate)
{
    init();
}

HColorButton::HColorButton(HColorButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HColorButton::~HColorButton()
{
}

QSize HColorButton::sizeHint() const
{
    return QSize(100, 50);
}

QSize HColorButton::minimumSizeHint() const
{
    return QSize(20, 10);
}

QPixmap HColorButton::background() const
{
    return d_ptr->background;
}

int HColorButton::borderRadius() const
{
    return d_ptr->borderRadius;
}

int HColorButton::borderWidth() const
{
    return d_ptr->borderWidth;
}

QColor HColorButton::borderColor() const
{
    return d_ptr->borderColor;
}

QString HColorButton::text() const
{
    return d_ptr->text;
}

QFont HColorButton::textFont() const
{
    return d_ptr->textFont;
}

Qt::Alignment HColorButton::textAlign() const
{
    return d_ptr->textAlign;
}

QColor HColorButton::textColor() const
{
    return d_ptr->textColor;
}

bool HColorButton::isShowSuperText() const
{
    return d_ptr->showSuperText;
}

QString HColorButton::superText() const
{
    return d_ptr->superText;
}

QFont HColorButton::superTextFont() const
{
    return d_ptr->superTextFont;
}

Qt::Alignment HColorButton::superTextAlign() const
{
    return d_ptr->superTextAlign;
}

QColor HColorButton::superTextColor() const
{
    return d_ptr->superTextColor;
}

QColor HColorButton::normalColor() const
{
    return d_ptr->normalColor;
}

QColor HColorButton::pressedColor() const
{
    return d_ptr->pressedColor;
}

HColorButton::ColorMode HColorButton::colorMode() const
{
    return d_ptr->colorMode;
}

bool HColorButton::isMoveEnable() const
{
    return d_ptr->moveEnable;
}

void HColorButton::setBackground(const QPixmap &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HColorButton::setBorderRadius(int value)
{
    if (d_ptr->borderRadius == value)
        return;
    d_ptr->borderRadius = value;
    update();
}

void HColorButton::setBorderWidth(int value)
{
    if (d_ptr->borderWidth == value)
        return;
    d_ptr->borderWidth = value;
    update();
}

void HColorButton::setBorderColor(const QColor &value)
{
    if (d_ptr->borderColor == value)
        return;
    d_ptr->borderColor = value;
    update();
}

void HColorButton::setText(const QString &value)
{
    if (d_ptr->text == value)
        return;
    d_ptr->text = value;
    update();
}

void HColorButton::setTextFont(const QFont &value)
{
    if (d_ptr->textFont == value)
        return;
    d_ptr->textFont = value;
    update();
}

void HColorButton::setTextAlign(Qt::Alignment value)
{
    if (d_ptr->textAlign == value)
        return;
    d_ptr->textAlign = value;
    update();
}

void HColorButton::setTextColor(const QColor &value)
{
    if (d_ptr->textColor == value)
        return;
    d_ptr->textColor = value;
    update();
}

void HColorButton::setShowSuperText(bool b)
{
    if (d_ptr->showSuperText == b)
        return;
    d_ptr->showSuperText = b;
    update();
}

void HColorButton::setSuperText(const QString &value)
{
    if (d_ptr->superText == value)
        return;
    d_ptr->superText = value;
    update();
}

void HColorButton::setSuperTextFont(const QFont &value)
{
    if (d_ptr->superTextFont == value)
        return;
    d_ptr->superTextFont = value;
    update();
}

void HColorButton::setSuperTextAlign(Qt::Alignment value)
{
    if (d_ptr->superTextAlign == value)
        return;
    d_ptr->superTextAlign = value;
    update();
}

void HColorButton::setSuperTextColor(const QColor & value)
{
    if (d_ptr->superTextColor == value)
        return;
    d_ptr->superTextColor = value;
    update();
}

void HColorButton::setNormalColor(const QColor & value)
{
    if (d_ptr->normalColor == value)
        return;
    d_ptr->normalColor = value;
    update();
}

void HColorButton::setPressedColor(const QColor &value)
{
    if (d_ptr->pressedColor == value)
        return;
    d_ptr->pressedColor = value;
    update();
}

void HColorButton::setColorMode(ColorMode value)
{
    if (d_ptr->colorMode == value)
        return;
    d_ptr->colorMode = value;
    update();
}

void HColorButton::setMoveEnable(bool b)
{
    if (d_ptr->moveEnable == b)
        return;
    d_ptr->moveEnable = b;
    update();
}

bool HColorButton::eventFilter(QObject *watched, QEvent *event)
{
    if (isMoveEnable())
        d_ptr->filter->eventFilter(watched, event);
    return QWidget::eventFilter(watched, event);
}

void HColorButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        d_ptr->pressed = true;
        update();
        emit pressed();
    }
    QWidget::mousePressEvent(e);
}

void HColorButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && d_ptr->pressed)
    {
        d_ptr->pressed = false;
        update();
        emit released();
        emit clicked();
    }
    QWidget::mouseReleaseEvent(e);
}

void HColorButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawText(&painter);
}

void HColorButton::drawBackground(QPainter *painter)
{
    auto rect = QRect(d_ptr->borderWidth, d_ptr->borderWidth, width() - d_ptr->borderWidth * 2, height() - d_ptr->borderWidth * 2);
    painter->save();
    painter->setPen(QPen(d_ptr->borderColor, d_ptr->borderWidth));
    if (d_ptr->background.isNull())
    {
        if (d_ptr->colorMode == ColorMode_Normal)
            painter->setBrush(d_ptr->pressed ? d_ptr->pressedColor : d_ptr->normalColor);
        else if (d_ptr->colorMode == ColorMode_Replace)
        {
            auto gradient = QLinearGradient(QPoint(0, 0), QPoint(0, height()));
            gradient.setColorAt(0.0, d_ptr->pressed ? d_ptr->pressedColor : d_ptr->normalColor);
            gradient.setColorAt(0.49, d_ptr->pressed ? d_ptr->pressedColor : d_ptr->normalColor);
            gradient.setColorAt(0.50, d_ptr->pressed ? d_ptr->normalColor : d_ptr->pressedColor);
            gradient.setColorAt(1.0, d_ptr->pressed ? d_ptr->normalColor : d_ptr->pressedColor);
            painter->setBrush(gradient);
        }
        else if (d_ptr->colorMode == ColorMode_Shade)
        {
            auto gradient = QLinearGradient(QPoint(0, 0), QPoint(0, height()));
            gradient.setColorAt(0.0, d_ptr->pressed ? d_ptr->pressedColor : d_ptr->normalColor);
            gradient.setColorAt(1.0, d_ptr->pressed ? d_ptr->normalColor : d_ptr->pressedColor);
            painter->setBrush(gradient);
        }
        painter->drawRoundedRect(rect, d_ptr->borderRadius, d_ptr->borderRadius);
    }
    else
    {
        auto pixmap = d_ptr->background.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap((this->rect().width() - pixmap.width()) / 2, (this->rect().height() - pixmap.height()) / 2, pixmap);
    }
    painter->restore();
}

void HColorButton::drawText(QPainter *painter)
{
    if (!d_ptr->background.isNull())
        return;

    painter->save();
    if (d_ptr->showSuperText)
    {
        auto offset = 3;
        auto rect = QRect(d_ptr->borderWidth * offset, d_ptr->borderWidth, width() - d_ptr->borderWidth * offset * 2, height() - d_ptr->borderWidth * 2);
        painter->setPen(d_ptr->superTextColor);
        painter->setFont(d_ptr->superTextFont);
        painter->drawText(rect, QFlag(d_ptr->superTextAlign), d_ptr->superText);
    }

    auto offset = 5;
    auto rect = QRect(d_ptr->borderWidth * offset, d_ptr->borderWidth, width() - d_ptr->borderWidth * offset * 2, height() - d_ptr->borderWidth * 2);
    painter->setPen(d_ptr->textColor);
    painter->setFont(d_ptr->textFont);
    painter->drawText(rect, QFlag(d_ptr->textAlign), d_ptr->text);
    painter->restore();
}

void HColorButton::init()
{
    d_ptr->textFont = font();
    d_ptr->superTextFont = font();
    d_ptr->filter = new HMoveEventFilter(this);
    installEventFilter(this);
}

HE_CONTROL_END_NAMESPACE
