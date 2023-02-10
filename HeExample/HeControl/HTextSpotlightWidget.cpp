#include "HTextSpotlightWidget_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HTextSpotlightWidget::HTextSpotlightWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTextSpotlightWidgetPrivate)
{
    d_ptr->timer = new QTimer(this);
    d_ptr->text = "黄河之水天上来，奔流到海不复回";
    auto font = this->font();
    font.setPixelSize(40);
    font.setBold(true);
    setFont(font);

    connect(d_ptr->timer, &QTimer::timeout, this, &HTextSpotlightWidget::onTimer);
    d_ptr->timer->start(40);
}

HTextSpotlightWidget::~HTextSpotlightWidget()
{
}

void HTextSpotlightWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setFont(this->font());

    painter.save();
    painter.setPen(QColor("#574E54"));
    painter.drawText(rect(), Qt::AlignCenter | Qt::TextWordWrap, d_ptr->text);
    painter.restore();

    d_ptr->textRect = painter.boundingRect(rect(), Qt::AlignCenter | Qt::TextWordWrap, d_ptr->text);
    auto pos = d_ptr->textRect.topLeft() + QPoint(d_ptr->changeValue, 0);

    QPainterPath path;
    path.addEllipse(pos.x(), pos.y() + d_ptr->textRect.height() / 2, 50, 50);
    painter.setClipPath(path);

    auto tempRect = path.boundingRect();
    QLinearGradient linearGradient(tempRect.topRight(),tempRect.bottomLeft());
    linearGradient.setColorAt(0.0, Qt::magenta);
    linearGradient.setColorAt(0.2, Qt::darkYellow);
    linearGradient.setColorAt(0.4, Qt::green);
    linearGradient.setColorAt(0.6, Qt::red);
    linearGradient.setColorAt(0.8, Qt::darkRed);
    linearGradient.setColorAt(1.0, Qt::blue);
    painter.setBrush(Qt::transparent);
    painter.setPen(QPen(QBrush(linearGradient), 3));
    painter.drawText(rect(), Qt::AlignCenter | Qt::TextWordWrap, d_ptr->text);
}

void HTextSpotlightWidget::onTimer()
{
    if (d_ptr->runDirectionIsRight)
    {
        d_ptr->changeValue += 15;
        if (d_ptr->changeValue >= d_ptr->textRect.width())
            d_ptr->runDirectionIsRight = false;
    }
    else
    {
        d_ptr->changeValue -= 15;
        if (d_ptr->changeValue <= 0)
            d_ptr->runDirectionIsRight = true;
    }
    update();
}

HE_END_NAMESPACE
