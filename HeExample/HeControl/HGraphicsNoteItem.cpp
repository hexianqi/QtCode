#include "HGraphicsNoteItem_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>

HE_BEGIN_NAMESPACE

HGraphicsNoteItemPrivate::HGraphicsNoteItemPrivate()
{
    itemSize = QSizeF(160, 200);
    minimumSizeHint = QSizeF(160, 200);
    buttonRects.resize(2);
}

HGraphicsNoteItem::HGraphicsNoteItem(QGraphicsItem *parent) :
    HGraphicsObject(*new HGraphicsNoteItemPrivate, parent)
{
    init();
}

HGraphicsNoteItem::HGraphicsNoteItem(HGraphicsNoteItemPrivate &p, QGraphicsItem *parent) :
    HGraphicsObject(p, parent)
{
}

HGraphicsNoteItem::~HGraphicsNoteItem()
{
}

int HGraphicsNoteItem::type() const
{
    return Type;
}

void HGraphicsNoteItem::setTitle(const QString &value)
{
    Q_D(HGraphicsNoteItem);
    if (d->title == value)
        return;
    d->title = value;
    update();
}

void HGraphicsNoteItem::setContent(const QStringList &value)
{
    Q_D(HGraphicsNoteItem);
    if (d->content == value)
        return;
    d->content = value;
    update();
}

void HGraphicsNoteItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGraphicsNoteItem);
    if (event->button() == Qt::LeftButton)
    {
        int i;
        auto pos = event->pos();
        for (i = 0; i < d->buttonRects.size(); i++)
        {
            if (d->buttonRects[i].contains(pos))
            {
                buttonPressed(i);
                break;
            }
        }
        for (i = 0; i < d->textRects.size(); i++)
        {
            if (d->textRects[i].contains(pos))
            {
                textPressed(i);
                break;
            }
        }
    }
    HGraphicsObject::mousePressEvent(event);
}

void HGraphicsNoteItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGraphicsNoteItem);
    if (event->button() == Qt::LeftButton)
    {
        if (d->pressButtonIndex != -1)
        {
            d->pressButtonIndex = -1;
            update();
        }
        if (d->pressTextIndex != -1)
        {
            d->pressTextIndex = -1;
            update();
        }
    }
    HGraphicsObject::mouseReleaseEvent(event);
}

void HGraphicsNoteItem::drawContent(QPainter *painter, const QStyleOptionGraphicsItem */*option*/)
{
    Q_D(HGraphicsNoteItem);

    auto rect = boundingRect();
    auto titleHeight = rect.height() * 0.15;
    auto contentHeight = rect.height() * 0.65;
    auto titleRect = QRectF(15, 0, rect.width() - 30, titleHeight);
    auto textHeight = 40;
    d->currentPaintSize = contentHeight / textHeight;
    d->fullPage = d->content.size() / d->currentPaintSize;
    d->currentPage = d->showContentIndex / d->currentPaintSize;
    if (d->showContentIndex % d->currentPaintSize != 0)
        d->currentPage++;
    d->textRects.clear();

    painter->save();
    // 边框
    painter->drawRoundRect(rect.adjusted(5, 5, -5, -5));
    // 标题
    QFont font = painter->font();
    font.setPixelSize(24);
    painter->setFont(font);
    painter->setPen(QColor("#333333"));
    painter->drawText(titleRect, Qt::AlignCenter, d->title);
    painter->setPen(QPen(QColor("#555555"), 2));
    painter->drawLine(titleRect.bottomLeft(), titleRect.bottomRight());
    // 内容
    font.setPixelSize(20);
    painter->setFont(font);
    painter->setPen(QColor("#888888"));
    for (int i = d->showContentIndex, j = 0; i < d->content.size() && j < d->currentPaintSize; i++, j++)
    {
        auto textRect = QRectF(15, titleHeight + j * textHeight, rect.width() - 30, textHeight);
        painter->drawText(textRect, Qt::AlignCenter, d->content[i]);
        painter->drawLine(textRect.bottomLeft(), textRect.bottomRight());
        d->textRects << textRect;
    }
    // 按钮
    d->buttonRects[0].setRect(rect.width() * 0.20, rect.height() * 0.85, rect.width() * 0.15, rect.height() * 0.1);
    d->buttonRects[1].setRect(rect.width() * 0.65, rect.height() * 0.85, rect.width() * 0.15, rect.height() * 0.1);
    painter->setPen(QColor("#888888"));
    painter->drawRoundRect(d->buttonRects[0], 30, 30);
    painter->drawRoundRect(d->buttonRects[1], 30, 30);
    painter->setPen(QColor("#555555"));
    painter->drawText(d->buttonRects[0], Qt::AlignCenter, "<<");
    painter->drawText(d->buttonRects[1], Qt::AlignCenter, ">>");
    // 焦点
    if (d->pressButtonIndex == 0 || d->pressButtonIndex == 1)
    {
        painter->setBrush(QColor("#3F000000"));
        painter->setPen(Qt::transparent);
        painter->drawRoundRect(d->buttonRects[d->pressButtonIndex], 30, 30);
    }
    if (d->pressTextIndex != -1)
    {
        painter->setBrush(QColor("#3F000000"));
        painter->setPen(Qt::transparent);
        painter->drawRect(d->textRects[d->pressTextIndex]);
    }

    painter->restore();
}

void HGraphicsNoteItem::buttonPressed(int index)
{
    Q_D(HGraphicsNoteItem);

    d->pressButtonIndex = index;
    if (index == 0)
    {
        if (d->currentPage == 0)
            return;
        d->currentPage--;
        d->showContentIndex -= d->currentPaintSize;
    }
    else if (index == 1)
    {
        if (d->currentPage == d->fullPage)
            return;
        d->currentPage++;
        d->showContentIndex += d->currentPaintSize;
    }
    else
        return;

    d->showContentIndex = qBound(0, d->showContentIndex, d->content.size() - 1);
    update();
}

void HGraphicsNoteItem::textPressed(int index)
{
    Q_D(HGraphicsNoteItem);
    d->pressTextIndex = index;
    update();
}

HE_END_NAMESPACE
