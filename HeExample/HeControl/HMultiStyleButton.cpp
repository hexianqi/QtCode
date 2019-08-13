#include "HMultiStyleButton_p.h"
#include "HMoveEventFilter.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_CONTROL_BEGIN_NAMESPACE

HMultiStyleButton::HMultiStyleButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HMultiStyleButtonPrivate)
{
    init();
}

HMultiStyleButton::HMultiStyleButton(HMultiStyleButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HMultiStyleButton::~HMultiStyleButton()
{
}

QSize HMultiStyleButton::sizeHint() const
{
    return QSize(100, 50);
}

QSize HMultiStyleButton::minimumSizeHint() const
{
    return QSize(20, 10);
}

QPixmap HMultiStyleButton::background() const
{
    return d_ptr->background;
}

int HMultiStyleButton::borderRadius() const
{
    return d_ptr->borderRadius;
}

int HMultiStyleButton::borderWidth() const
{
    return d_ptr->borderWidth;
}

QColor HMultiStyleButton::borderColor() const
{
    return d_ptr->borderColor;
}

QString HMultiStyleButton::text() const
{
    return d_ptr->text;
}

QFont HMultiStyleButton::textFont() const
{
    return d_ptr->textFont;
}

Qt::Alignment HMultiStyleButton::textAlign() const
{
    return d_ptr->textAlign;
}

QColor HMultiStyleButton::textColor() const
{
    return d_ptr->textColor;
}

bool HMultiStyleButton::isShowSuperText() const
{
    return d_ptr->showSuperText;
}

QString HMultiStyleButton::superText() const
{
    return d_ptr->superText;
}

QFont HMultiStyleButton::superTextFont() const
{
    return d_ptr->superTextFont;
}

Qt::Alignment HMultiStyleButton::superTextAlign() const
{
    return d_ptr->superTextAlign;
}

QColor HMultiStyleButton::superTextColor() const
{
    return d_ptr->superTextColor;
}

QColor HMultiStyleButton::normalColor() const
{
    return d_ptr->normalColor;
}

QColor HMultiStyleButton::pressedColor() const
{
    return d_ptr->pressedColor;
}

HMultiStyleButton::ColorMode HMultiStyleButton::colorMode() const
{
    return d_ptr->colorMode;
}

bool HMultiStyleButton::isMoveEnable() const
{
    return d_ptr->moveEnable;
}

void HMultiStyleButton::setBackground(const QPixmap &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HMultiStyleButton::setBorderRadius(int value)
{
    if (d_ptr->borderRadius == value)
        return;
    d_ptr->borderRadius = value;
    update();
}

void HMultiStyleButton::setBorderWidth(int value)
{
    if (d_ptr->borderWidth == value)
        return;
    d_ptr->borderWidth = value;
    update();
}

void HMultiStyleButton::setBorderColor(const QColor &value)
{
    if (d_ptr->borderColor == value)
        return;
    d_ptr->borderColor = value;
    update();
}

void HMultiStyleButton::setText(const QString &value)
{
    if (d_ptr->text == value)
        return;
    d_ptr->text = value;
    update();
}

void HMultiStyleButton::setTextFont(const QFont &value)
{
    if (d_ptr->textFont == value)
        return;
    d_ptr->textFont = value;
    update();
}

void HMultiStyleButton::setTextAlign(Qt::Alignment value)
{
    if (d_ptr->textAlign == value)
        return;
    d_ptr->textAlign = value;
    update();
}

void HMultiStyleButton::setTextColor(const QColor &value)
{
    if (d_ptr->textColor == value)
        return;
    d_ptr->textColor = value;
    update();
}

void HMultiStyleButton::setShowSuperText(bool b)
{
    if (d_ptr->showSuperText == b)
        return;
    d_ptr->showSuperText = b;
    update();
}

void HMultiStyleButton::setSuperText(const QString &value)
{
    if (d_ptr->superText == value)
        return;
    d_ptr->superText = value;
    update();
}

void HMultiStyleButton::setSuperTextFont(const QFont &value)
{
    if (d_ptr->superTextFont == value)
        return;
    d_ptr->superTextFont = value;
    update();
}

void HMultiStyleButton::setSuperTextAlign(Qt::Alignment value)
{
    if (d_ptr->superTextAlign == value)
        return;
    d_ptr->superTextAlign = value;
    update();
}

void HMultiStyleButton::setSuperTextColor(const QColor & value)
{
    if (d_ptr->superTextColor == value)
        return;
    d_ptr->superTextColor = value;
    update();
}

void HMultiStyleButton::setNormalColor(const QColor & value)
{
    if (d_ptr->normalColor == value)
        return;
    d_ptr->normalColor = value;
    update();
}

void HMultiStyleButton::setPressedColor(const QColor &value)
{
    if (d_ptr->pressedColor == value)
        return;
    d_ptr->pressedColor = value;
    update();
}

void HMultiStyleButton::setColorMode(ColorMode value)
{
    if (d_ptr->colorMode == value)
        return;
    d_ptr->colorMode = value;
    update();
}

void HMultiStyleButton::setMoveEnable(bool b)
{
    if (d_ptr->moveEnable == b)
        return;
    d_ptr->moveEnable = b;
    update();
}

bool HMultiStyleButton::eventFilter(QObject *watched, QEvent *event)
{
    if (isMoveEnable())
        d_ptr->filter->eventFilter(watched, event);
    return QWidget::eventFilter(watched, event);
}

void HMultiStyleButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        d_ptr->pressed = true;
        update();
        emit pressed();
    }
    QWidget::mousePressEvent(e);
}

void HMultiStyleButton::mouseReleaseEvent(QMouseEvent *e)
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

void HMultiStyleButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawText(&painter);
}

void HMultiStyleButton::drawBackground(QPainter *painter)
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

void HMultiStyleButton::drawText(QPainter *painter)
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

void HMultiStyleButton::init()
{
    d_ptr->textFont = font();
    d_ptr->superTextFont = font();
    d_ptr->filter = new HMoveEventFilter(this);
    installEventFilter(this);
}

HE_CONTROL_END_NAMESPACE
