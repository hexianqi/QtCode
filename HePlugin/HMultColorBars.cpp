#include "HMultColorBars_p.h"

HMultColorBarsPrivate::HMultColorBarsPrivate()
{
    labelFont = QFont(QLatin1String("sans serif"), 12);
}

HMultColorBars::HMultColorBars(QCPAxis *keyAxis, QCPAxis *valueAxis) :
    QCPBars(keyAxis, valueAxis),
    d_ptr(new HMultColorBarsPrivate)
{
}

HMultColorBars::HMultColorBars(HMultColorBarsPrivate &p, QCPAxis *keyAxis, QCPAxis *valueAxis) :
    QCPBars(keyAxis, valueAxis),
    d_ptr(&p)
{
}

HMultColorBars::~HMultColorBars()
{
}

bool HMultColorBars::labelVisible() const
{
    return d_ptr->labelVisible;
}

Qt::Alignment HMultColorBars::labelAligment() const
{
    return d_ptr->labelAlignment;
}

double HMultColorBars::labelSpace() const
{
    return d_ptr->labelSpace;
}

QFont HMultColorBars::labelFont() const
{
    return d_ptr->labelFont;
}

void HMultColorBars::setLabelVisible(bool b)
{
    if (d_ptr->labelVisible == b)
        return;
    d_ptr->labelVisible = b;
}

void HMultColorBars::setLabelAlignment(Qt::Alignment value)
{
    if (d_ptr->labelAlignment == value)
        return;
    d_ptr->labelAlignment = value;
}

void HMultColorBars::setLabelSpace(double value)
{
    if (d_ptr->labelSpace == value)
        return;
    d_ptr->labelSpace = value;
}

void HMultColorBars::setLabelFont(const QFont &value)
{
    if (d_ptr->labelFont == value)
        return;
    d_ptr->labelFont = value;
}

void HMultColorBars::draw(QCPPainter *painter)
{
    if (!mKeyAxis || !mValueAxis)
    {
        qDebug() << Q_FUNC_INFO << "invalid key or value axis";
        return;
    }
    if (mDataContainer->isEmpty())
        return;

    for (auto it = mDataContainer->begin(); it != mDataContainer->end(); ++it)
    {
        auto rect = getBarRect(it->key, it->value);
        auto text = QString::number(it->value, 'g', 2);
        painter->setBrush(mBrush);
        painter->setPen(mPen);
        applyDefaultAntialiasingHint(painter);
        painter->drawPolygon(rect);
        drawLabel(painter, text, rect);
    }
}

void HMultColorBars::drawLabel(QCPPainter *painter, QString text, QRectF barRect)
{
    if (!d_ptr->labelVisible)
        return;

    painter->save();
    painter->setFont(d_ptr->labelFont);                                                                                 // 设置字体
    QRectF textRect = painter->fontMetrics().boundingRect(0, 0, 0, 0, Qt::TextDontClip | d_ptr->labelAlignment, text);  // 计算文字所占用的大小

    if (mKeyAxis.data()->orientation() == Qt::Horizontal)                                   // 当key轴为水平轴的时候
    {
        if (mKeyAxis.data()->axisType() == QCPAxis::atTop)                                  // 上轴，移动文字到柱状图下面
            textRect.moveTopLeft(barRect.bottomLeft() + QPointF(0, d_ptr->labelSpace));
        else                                                                                // 下轴，移动文字到柱状图上面
            textRect.moveBottomLeft(barRect.topLeft() - QPointF(0, d_ptr->labelSpace));
        textRect.setWidth(barRect.width());
        painter->drawText(textRect, Qt::TextDontClip | d_ptr->labelAlignment, text);
    }
    else                                                                                    // 当key轴为竖直轴的时候
    {
        if (mKeyAxis.data()->axisType() == QCPAxis::atLeft)                                 // 左轴，移动文字到柱状图右边
            textRect.moveTopLeft(barRect.topRight() + QPointF(d_ptr->labelSpace, 0));
        else                                                                                // 右轴，移动文字到柱状图左边
            textRect.moveTopRight(barRect.topLeft() - QPointF(d_ptr->labelSpace, 0));
        textRect.setHeight(barRect.height());
        painter->drawText(textRect, Qt::TextDontClip | d_ptr->labelAlignment, text);
    }
    painter->restore();
}




