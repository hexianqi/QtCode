#include "HIrregularPopupWidget_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HIrregularPopupWidget::HIrregularPopupWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HIrregularPopupWidgetPrivate)
{
    setPalette(Qt::white);

    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);
    effect->setBlurRadius(25);
    effect->setColor(Qt::black);
    setGraphicsEffect(effect);

    auto font = this->font();
    font.setPixelSize(20);
    setFont(font);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

HIrregularPopupWidget::~HIrregularPopupWidget()
{
}

QSize HIrregularPopupWidget::sizeHint() const
{
    if (d_ptr->text.isEmpty())
        return QSize(200, 100);

    auto size = fontMetrics().size(Qt::AlignCenter, d_ptr->text);
    auto width = size.width() + 30;
    auto height = size.height() + 30;
    if (d_ptr->sharpPosition == Left || d_ptr->sharpPosition == Right)
        width += d_ptr->SharpWidth;
    if (d_ptr->sharpPosition == Top || d_ptr->sharpPosition == Bottom)
        height += d_ptr->SharpHeight;
    return QSize(width, height);
}

void HIrregularPopupWidget::setText(const QString &value)
{
    if (d_ptr->text == value)
        return;
    d_ptr->text = value;
    update();
}

void HIrregularPopupWidget::setSharpPosition(SharpPosition value)
{
    if (d_ptr->sharpPosition == value)
        return;
    d_ptr->sharpPosition = value;
    update();
}

void HIrregularPopupWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPainterPath path;
    QPolygonF polygon;
    QRect centerRect = this->rect();

    switch (d_ptr->sharpPosition)
    {
    case Left:
        polygon.append(QPointF(d_ptr->SharpWidth, (height() - d_ptr->SharpHeight) / 2));
        polygon.append(QPointF(0, height() / 2));
        polygon.append(QPointF(d_ptr->SharpWidth, (height() + d_ptr->SharpHeight) / 2));
        centerRect.adjust(d_ptr->SharpWidth, 0, 0, 0);
        break;
    case Right:
        polygon.append(QPointF(width() - d_ptr->SharpWidth, (height() - d_ptr->SharpHeight) / 2));
        polygon.append(QPointF(width(), height() / 2));
        polygon.append(QPointF(width() - d_ptr->SharpWidth, (height() + d_ptr->SharpHeight) / 2));
        centerRect.adjust(0, 0, -d_ptr->SharpWidth, 0);
        break;
    case Top:
        polygon.append(QPointF((width() - d_ptr->SharpWidth) / 2, d_ptr->SharpHeight));
        polygon.append(QPointF(width() / 2, 0));
        polygon.append(QPointF((width() + d_ptr->SharpWidth) / 2, d_ptr->SharpHeight));
        centerRect.adjust(0, d_ptr->SharpHeight, 0, 0);
        break;
    case Bottom:
        polygon.append(QPointF((width() - d_ptr->SharpWidth) / 2, height() - d_ptr->SharpHeight));
        polygon.append(QPointF(width() / 2, height()));
        polygon.append(QPointF((width() + d_ptr->SharpWidth) / 2, height() - d_ptr->SharpHeight));
        centerRect.adjust(0, 0, 0, -d_ptr->SharpHeight);
        break;
    }
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillRect(rect(), Qt::transparent);
    painter.setBrush(d_ptr->backgroundColor);
    painter.setPen(Qt::transparent);
    painter.drawPolygon(polygon);
    painter.drawRoundedRect(centerRect, 6, 6);
    path.addPolygon(polygon);
    path.addRoundedRect(centerRect, 6, 6);
    painter.setClipPath(path);
    painter.setPen(Qt::white);
    painter.drawText(centerRect,Qt::AlignCenter | Qt::TextWordWrap, d_ptr->text);
}

HE_END_NAMESPACE

