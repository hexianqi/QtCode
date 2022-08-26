#include "HGraphicsPixmapItem_p.h"
#include "HGraphicsHelper.h"
#include <QtGui/QPainter>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStyleOptionGraphicsItem>

HE_BEGIN_NAMESPACE

HGraphicsPixmapItem::HGraphicsPixmapItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    d_ptr(new HGraphicsPixmapItemPrivate)
{
    init();
}

HGraphicsPixmapItem::HGraphicsPixmapItem(HGraphicsPixmapItemPrivate &p, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    d_ptr(&p)
{
}

HGraphicsPixmapItem::~HGraphicsPixmapItem()
{
    init();
}

int HGraphicsPixmapItem::type() const
{
    return Type;
}

QString HGraphicsPixmapItem::title() const
{
    return d_ptr->title;
}

QPixmap HGraphicsPixmapItem::pixmap() const
{
    return d_ptr->pixmap;
}

QColor HGraphicsPixmapItem::textColor() const
{
    return d_ptr->textColor;
}

void HGraphicsPixmapItem::setTitle(const QString &value)
{
    if (d_ptr->title == value)
        return;
    d_ptr->title = value;
    update();
}

void HGraphicsPixmapItem::setPixmap(const QPixmap &value)
{
    if (d_ptr->pixmap == value)
        return;
    d_ptr->pixmap = value;
    d_ptr->itemSize = d_ptr->pixmap.size();
    update();
}

void HGraphicsPixmapItem::setTextColor(const QColor &value)
{
    if (d_ptr->textColor == value)
        return;
    d_ptr->textColor = value;
    update();
}

QRectF HGraphicsPixmapItem::boundingRect() const
{
    return  QRectF(0, 0, d_ptr->itemSize.width() + 10, d_ptr->itemSize.height() + 10);
}

QVariant HGraphicsPixmapItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ((change == ItemPositionChange || change == ItemPositionHasChanged) && scene())
    {
        auto pos = HGraphicsHelper::fixByScene(this, value);
        if (pos.isValid())
            return pos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void HGraphicsPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    auto rect = boundingRect();
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawRect(rect);
        setZValue(2);
    }
    else
    {
        setZValue(1);
        painter->fillRect(rect, QBrush(Qt::transparent));
    }

    if (!d_ptr->pixmap.isNull())
        painter->drawPixmap(rect.toRect(), d_ptr->pixmap);

    if (!d_ptr->title.isEmpty())
    {
        auto textRect = QRectF(0, 0, rect.width(), 30);
        textRect.moveTo(QPoint(0, static_cast<int>((rect.height() - 30) / 2)));
        auto font = painter->font();
        font.setPixelSize(24);
        painter->setPen(QPen(d_ptr->textColor, 2, Qt::SolidLine));
        painter->setFont(font);
        painter->drawText(textRect, Qt::AlignCenter, d_ptr->title);
    }

    if (option->state & QStyle::State_Selected)
    {
        auto w = int(rect.width());
        auto h = int(rect.height());
        painter->setPen(Qt::red);
        for (auto p : d_ptr->resizePos)
            painter->drawLine(w - p, h, w, h - p);
    }

    painter->restore();
}

void HGraphicsPixmapItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto action = menu.addAction(tr("设置图片"));
    connect(action, &QAction::triggered, this, &HGraphicsPixmapItem::openPixmap);
    menu.exec(event->screenPos());
}

void HGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (isInResizeArea(event->pos()))
            d_ptr->resizing = true;
    }
    return QGraphicsObject::mousePressEvent(event);
}

void HGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (d_ptr->resizing)
    {
        auto w = event->pos().x();
        auto h = event->pos().y();
        if (w > 0)
            d_ptr->itemSize.setWidth(w);
        if (h > 0)
            d_ptr->itemSize.setHeight(h);
        prepareGeometryChange();
    }
    else
        QGraphicsObject::mouseMoveEvent(event);
}

void HGraphicsPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && d_ptr->resizing)
        d_ptr->resizing = false;
    QGraphicsObject::mouseReleaseEvent(event);
}

void HGraphicsPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (d_ptr->resizing || (isInResizeArea(event->pos()) && isSelected()))
        setCursor(Qt::SizeFDiagCursor);
    else
        setCursor(Qt::ArrowCursor);
    QGraphicsObject::hoverMoveEvent(event);
}

void HGraphicsPixmapItem::init()
{
    setAcceptHoverEvents(true);
    setFlags(ItemIsMovable | ItemSendsScenePositionChanges | ItemIsSelectable | ItemIsFocusable);
}

void HGraphicsPixmapItem::openPixmap()
{
    auto fileName = QFileDialog::getOpenFileName(nullptr, tr("设置图片"), QString(), "*.png *.jpg");
    if (fileName.isEmpty())
        return;

    QPixmap pixmap(fileName);
    if (pixmap.width() >= scene()->width() || pixmap.height() >= scene()->height())
    {
        QMessageBox::information(nullptr, tr("错误"), tr("图片尺寸大于视图尺寸"));
        return;
    }
    setPixmap(pixmap);
}

bool HGraphicsPixmapItem::isInResizeArea(const QPointF &pos)
{
    return (pos.x() - d_ptr->itemSize.width() + d_ptr->resizePos[0]) > (d_ptr->itemSize.height() - pos.y());
}

HE_END_NAMESPACE
