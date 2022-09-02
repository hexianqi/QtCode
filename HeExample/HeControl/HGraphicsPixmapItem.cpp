#include "HGraphicsPixmapItem_p.h"
#include "HGraphicsHelper.h"
#include <QtGui/QMovie>
#include <QtGui/QPainter>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStyleOptionGraphicsItem>

HE_BEGIN_NAMESPACE

HGraphicsPixmapItemPrivate::HGraphicsPixmapItemPrivate()
{
    itemSize = QSizeF(128, 128);
}

HGraphicsPixmapItem::HGraphicsPixmapItem(QGraphicsItem *parent) :
    HGraphicsObject(*new HGraphicsPixmapItemPrivate, parent)
{
    init();
}

HGraphicsPixmapItem::HGraphicsPixmapItem(HGraphicsPixmapItemPrivate &p, QGraphicsItem *parent) :
    HGraphicsObject(p, parent)
{
}

HGraphicsPixmapItem::~HGraphicsPixmapItem()
{
}

int HGraphicsPixmapItem::type() const
{
    return Type;
}

QString HGraphicsPixmapItem::title() const
{
    Q_D(const HGraphicsPixmapItem);
    return d->title;
}

QPixmap HGraphicsPixmapItem::pixmap() const
{
    Q_D(const HGraphicsPixmapItem);
    return d->pixmap;
}

QColor HGraphicsPixmapItem::textColor() const
{
    Q_D(const HGraphicsPixmapItem);
    return d->textColor;
}

void HGraphicsPixmapItem::setTitle(const QString &value)
{
    Q_D(HGraphicsPixmapItem);
    if (d->title == value)
        return;
    d->title = value;
    update();
}

void HGraphicsPixmapItem::setPixmap(const QPixmap &value)
{
    Q_D(HGraphicsPixmapItem);
    if (d->pixmap == value)
        return;
    d->pixmap = value;
    update();
}

void HGraphicsPixmapItem::setTextColor(const QColor &value)
{
    Q_D(HGraphicsPixmapItem);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HGraphicsPixmapItem::init()
{
    Q_D(HGraphicsPixmapItem);
    HGraphicsObject::init();
    d->movie = new QMovie(this);
    connect(d->movie, &QMovie::frameChanged, [=] { setPixmap(d->movie->currentPixmap()); });
}

void HGraphicsPixmapItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto action = menu.addAction(tr("设置图片"));
    connect(action, &QAction::triggered, this, &HGraphicsPixmapItem::openFile);
    menu.exec(event->screenPos());
}

void HGraphicsPixmapItem::drawContent(QPainter *painter, const QStyleOptionGraphicsItem */*option*/)
{
    Q_D(HGraphicsPixmapItem);
    auto rect = boundingRect().toRect();
    painter->save();

    if (!d->pixmap.isNull())
        painter->drawPixmap(rect, d->pixmap);

    if (!d->title.isEmpty())
    {
        auto textRect = QRectF(0, 0, rect.width(), 30);
        textRect.moveTo(QPoint(0, static_cast<int>((rect.height() - 30) / 2)));
        auto font = painter->font();
        font.setPixelSize(24);
        painter->setPen(QPen(d->textColor, 2, Qt::SolidLine));
        painter->setFont(font);
        painter->drawText(textRect, Qt::AlignCenter, d->title);
    }
    painter->restore();
}

void HGraphicsPixmapItem::openFile()
{
    Q_D(HGraphicsPixmapItem);
    auto fileName = QFileDialog::getOpenFileName(nullptr, tr("设置图片"), QString(), "*.png *.jpg *.gif");
    if (fileName.isEmpty() || d->fileName == fileName)
        return;

    QSignalBlocker blocker(d->movie);
    d->movie->stop();

    QPixmap pixmap(fileName);
    if (pixmap.width() >= scene()->width() || pixmap.height() >= scene()->height())
    {
        QMessageBox::information(nullptr, tr("错误"), tr("图片尺寸大于视图尺寸"));
        return;
    }

    QFileInfo info(fileName);
    if (info.suffix() == "gif")
    {
        d->movie->setFileName(fileName);
        d->movie->start();
    }
    d->fileName = fileName;

    setPixmap(pixmap);
}

HE_END_NAMESPACE

