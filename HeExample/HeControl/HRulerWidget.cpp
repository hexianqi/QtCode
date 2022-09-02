#include "HRulerWidget_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HRulerWidgetPrivate::HRulerWidgetPrivate(Qt::Orientation orientation)
{
    this->orientation = orientation;
}

HRulerWidget::HRulerWidget(Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    d_ptr(new HRulerWidgetPrivate(orientation))
{
    init();
}

HRulerWidget::HRulerWidget(HRulerWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HRulerWidget::~HRulerWidget()
{
}

void HRulerWidget::setOffset(int value)
{
    if (d_ptr->offset == value)
        return;
    d_ptr->offset = value;
    update();
    return;
}

void HRulerWidget::setSlidingPos(int value)
{
    if (d_ptr->offset + value == d_ptr->slidingPos)
        return;
    d_ptr->slidingPos = d_ptr->offset + value;
    update();
    return;
}

void HRulerWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), d_ptr->background);
    painter.setPen(d_ptr->textColor);
    painter.setFont(d_ptr->font);
    if (d_ptr->orientation == Qt::Horizontal)
    {
        auto length = width() + d_ptr->offset;
        auto shortLine = height() * 0.75;
        auto middleLine = height() * 0.625;
        auto longLine = height() * 0.5;
        auto halfHeight = height() * 0.5;
        auto temp = 0;
        painter.translate(-d_ptr->offset, 0);
        for (int i = 0; i < length; i += 10)
        {
            if (temp % 10 == 0)
            {
                painter.drawLine(i, longLine, i, height());
                painter.drawText(i - 50, 0, 100, halfHeight, Qt::AlignCenter | Qt::TextWordWrap, QString::number(i));
            }
            else if(temp % 5 == 0)
                painter.drawLine(i, middleLine, i, height());
            else
                painter.drawLine(i, shortLine, i, height());
            temp++;
        }
    }
    else
    {
        auto length = height() + d_ptr->offset;
        auto shortLine = width() * 0.75;
        auto longLine = width() * 0.5;
        auto middleLine = width() * 0.625;
        auto harfWidth = width() / 2;
        auto temp = 0;
        painter.translate(0, -d_ptr->offset);
        for(int i = 0; i < length; i += 10)
        {
            if(temp % 10 == 0)
            {
                painter.drawLine(longLine, i, width(), i);
                painter.drawText(0, i - 50, harfWidth, 100, Qt::AlignCenter | Qt::TextWordWrap, QString::number(i));
            }
            else if(temp % 5 == 0)
                painter.drawLine(middleLine, i, width(), i);
            else
                painter.drawLine(shortLine, i, width(), i);
            temp++;
        }
    }
    painter.setPen(Qt::transparent);
    painter.setBrush(d_ptr->slidingColor);
    if (d_ptr->orientation == Qt::Horizontal)
        painter.drawRect(d_ptr->slidingPos - 1, 0, 3, height());
    else
        painter.drawRect(0, d_ptr->slidingPos - 1, width(), 3);
    painter.restore();
}

void HRulerWidget::init()
{
    d_ptr->orientation == Qt::Horizontal ? setFixedHeight(60) : setFixedWidth(100);
}

HE_END_NAMESPACE
