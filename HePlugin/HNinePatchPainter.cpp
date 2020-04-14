#include "HNinePatchPainter_p.h"
#include <QtGui/QPainter>

// 根据九宫格 4 边的宽度把 rect 按九宫格分割为 9 个 rect: 左、左上、上、右上、右、右下、下、左下、中间
QList<QRect> calculateNinePatchRects(const QRect &rect, const QMargins &margins)
{
    int l = margins.left();
    int r = margins.right();
    int t = margins.top();
    int b = margins.bottom();
    int x = rect.x();
    int y = rect.y();
    int w = rect.width() - l - r;   // 中间部分的宽
    int h = rect.height() - t - b;  // 中间部分的高

    return QList<QRect>() << QRect(x, y + t, l, h)
                          << QRect(x, y, l, t)
                          << QRect(x + l, y, w, t)
                          << QRect(x + l + w, y, r, t)
                          << QRect(x + l + w, y + t, r, h)
                          << QRect(x + l + w, y + t + h, r, b)
                          << QRect(x + l, y + t + h, w, b)
                          << QRect(x, y + t + h, l, b)
                          << QRect(x + l, y + t, w, h);
}

QPixmap scalePixmap(const QPixmap &pixmap, const QSize &size)
{
    // 缩放时忽略图片的高宽比，使用平滑缩放的效果
    return pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

HNinePatchPainter::HNinePatchPainter() :
    d_ptr(new HNinePatchPainterPrivate)
{
}

HNinePatchPainter::HNinePatchPainter(HNinePatchPainterPrivate &p) :
    d_ptr(&p)
{
}

HNinePatchPainter::~HNinePatchPainter() = default;

void HNinePatchPainter::setMargins(QMargins value)
{
    if (d_ptr->margins == value)
        return;
    d_ptr->margins = value;
    d_ptr->rebuildPixmap = true;
}

void HNinePatchPainter::setMargins(int left, int top, int right, int bottom)
{
    setMargins(QMargins(left, top, right, bottom));
}

void HNinePatchPainter::setStretchHorizontal(bool b)
{
    if (d_ptr->stretchHorizontal == b)
        return;
    d_ptr->stretchHorizontal = b;
}

void HNinePatchPainter::setStretchVertical(bool b)
{
    if (d_ptr->stretchVertical == b)
        return;
    d_ptr->stretchVertical = b;
}

void HNinePatchPainter::setBackground(const QPixmap &value)
{
    d_ptr->background = value;
    d_ptr->rebuildPixmap = true;
}

void HNinePatchPainter::draw(QPainter *painter, const QRect &rect)
{
    rebuildPixmapIfNeeded();
    auto rects = calculateNinePatchRects(rect, d_ptr->margins);
    // 绘制 4 个角
    painter->drawPixmap(rects.at(1), d_ptr->topLeftPixmap);
    painter->drawPixmap(rects.at(3), d_ptr->topRightPixmap);
    painter->drawPixmap(rects.at(5), d_ptr->bottomRightPixmap);
    painter->drawPixmap(rects.at(7), d_ptr->bottomLeftPixmap);
    // 绘制左右边
    if (d_ptr->stretchHorizontal)
    {
        // 水平拉伸
        painter->drawPixmap(rects.at(0), scalePixmap(d_ptr->leftPixmap, rects.at(0).size()));
        painter->drawPixmap(rects.at(4), scalePixmap(d_ptr->leftPixmap, rects.at(4).size()));
    }
    else
    {
        // 水平平铺
        painter->drawTiledPixmap(rects.at(0), d_ptr->leftPixmap);
        painter->drawTiledPixmap(rects.at(4), d_ptr->rightPixmap);
    }
    // 绘制上下边
    if (d_ptr->stretchVertical)
    {
        // 垂直拉伸
        painter->drawPixmap(rects.at(2), scalePixmap(d_ptr->topPixmap, rects.at(2).size()));
        painter->drawPixmap(rects.at(6), scalePixmap(d_ptr->bottomPixmap, rects.at(6).size()));
    }
    else
    {
        // 垂直平铺
        painter->drawTiledPixmap(rects.at(2), d_ptr->topPixmap);
        painter->drawTiledPixmap(rects.at(6), d_ptr->bottomPixmap);
    }
    // 绘制中间部分
    int pmw = d_ptr->centerPixmap.width();
    int pmh = d_ptr->centerPixmap.height();
    int crw = rects.at(8).width();
    int crh = rects.at(8).height();
    if (d_ptr->stretchHorizontal && d_ptr->stretchVertical)
    {
        // 水平和垂直都拉伸
        painter->drawPixmap(rects.at(8), scalePixmap(d_ptr->centerPixmap, rects.at(8).size()));
    }
    else if (d_ptr->stretchHorizontal && !d_ptr->stretchVertical)
    {
        // 水平拉伸，垂直平铺
        if (crh % pmh != 0)
            pmh = pmh * crh / (crh + pmh);
        auto pixmap = scalePixmap(d_ptr->centerPixmap, QSize(crw, pmh));
        painter->drawTiledPixmap(rects.at(8), pixmap);
    }
    else if (!d_ptr->stretchHorizontal && d_ptr->stretchVertical)
    {
        // 水平平铺，垂直拉伸
        if (crw % pmw != 0)
            pmw = pmw * crw / (crw + pmw);
        auto pixmap = scalePixmap(d_ptr->centerPixmap, QSize(pmw, crh));
        painter->drawTiledPixmap(rects.at(8), pixmap);
    }
    else
    {
        // 水平和垂直都平铺
        painter->drawTiledPixmap(rects.at(8), d_ptr->centerPixmap);
    }
}

void HNinePatchPainter::rebuildPixmapIfNeeded()
{
    if (!d_ptr->rebuildPixmap)
        return;

    auto rects = calculateNinePatchRects(d_ptr->background.rect(), d_ptr->margins);
    d_ptr->leftPixmap        = d_ptr->background.copy(rects.at(0));
    d_ptr->topLeftPixmap     = d_ptr->background.copy(rects.at(1));
    d_ptr->topPixmap         = d_ptr->background.copy(rects.at(2));
    d_ptr->topRightPixmap    = d_ptr->background.copy(rects.at(3));
    d_ptr->rightPixmap       = d_ptr->background.copy(rects.at(4));
    d_ptr->bottomRightPixmap = d_ptr->background.copy(rects.at(5));
    d_ptr->bottomPixmap      = d_ptr->background.copy(rects.at(6));
    d_ptr->bottomLeftPixmap  = d_ptr->background.copy(rects.at(7));
    d_ptr->centerPixmap      = d_ptr->background.copy(rects.at(8));
    d_ptr->rebuildPixmap = false;
}
