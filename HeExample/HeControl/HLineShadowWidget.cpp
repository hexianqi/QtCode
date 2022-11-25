#include "HLineShadowWidget_p.h"
#include <QtGui/QtEvents>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HLineShadowWidget::HLineShadowWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLineShadowWidgetPrivate)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

HLineShadowWidget::~HLineShadowWidget()
{
}

void HLineShadowWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto rect = this->rect();
    auto lines = QVector<QLine>() << QLine(rect.topLeft(), QPoint(0, d_ptr->lineLength))
                                  << QLine(rect.topLeft(), QPoint(d_ptr->lineLength, 0))
                                  << QLine(rect.topRight(), QPoint(rect.right() - d_ptr->lineLength, 0))
                                  << QLine(rect.topRight(), QPoint(rect.right(), d_ptr->lineLength))
                                  << QLine(rect.bottomLeft(), QPoint(0, rect.bottom() - d_ptr->lineLength))
                                  << QLine(rect.bottomLeft(), QPoint(d_ptr->lineLength, rect.bottom()))
                                  << QLine(rect.bottomRight(), QPoint(rect.right() - d_ptr->lineLength, rect.bottom()))
                                  << QLine(rect.bottomRight(), QPoint(rect.right(), rect.bottom() - d_ptr->lineLength));
    auto color1 = d_ptr->shadowColor;
    auto color2 = d_ptr->shadowColor;
    color1.setAlpha(20);
    color2.setAlpha(0);
    QLinearGradient linearGradient;
    linearGradient.setColorAt(0.4, color1);
    linearGradient.setColorAt(0.8, color2);

    painter.save();
    linearGradient.setStart(rect.left(), 0);
    linearGradient.setFinalStop(d_ptr->shadowLength, 0);
    painter.fillRect(rect.left(), rect.top(), d_ptr->shadowLength, rect.height(), linearGradient);
    linearGradient.setStart(rect.right(), 0);
    linearGradient.setFinalStop(rect.width() - d_ptr->shadowLength, 0);
    painter.fillRect(rect.width() - d_ptr->shadowLength, 0, d_ptr->shadowLength, rect.height(), linearGradient);
    linearGradient.setStart(0, rect.top());
    linearGradient.setFinalStop(0, d_ptr->shadowLength);
    painter.fillRect(rect.left(), rect.top(), rect.width(), d_ptr->shadowLength, linearGradient);
    linearGradient.setStart(0, rect.height());
    linearGradient.setFinalStop(0, rect.height() - d_ptr->shadowLength);
    painter.fillRect(0, rect.height() - d_ptr->shadowLength, rect.width(),d_ptr->shadowLength,linearGradient);
    painter.setPen(QPen(QColor("#164381"), 3));
    painter.drawRect(rect.adjusted(0, 0, -1, -1));
    painter.setPen(QPen(QColor("#49d9fe"), 5));
    painter.drawLines(lines);
    painter.restore();

    QWidget::paintEvent(event);
}

HE_END_NAMESPACE

