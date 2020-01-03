#include "HScreenObject_p.h"
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

HE_CONTROL_BEGIN_NAMESPACE

HScreenObject::HScreenObject(QObject *parent) :
    QObject(parent),
    d_ptr(new HScreenObjectPrivate)
{
    init();
}

HScreenObject::HScreenObject(HScreenObjectPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    init();
}

HScreenObject::~HScreenObject()
{
}

HScreenObject::Status HScreenObject::status() const
{
    return d_ptr->status;
}

bool HScreenObject::isInArea(QPoint pos)
{
    return d_ptr->area.contains(pos);
}

void HScreenObject::setStatus(HScreenObject::Status value)
{
    d_ptr->status = value;
}

void HScreenObject::setStart(QPoint pos)
{
    d_ptr->startPos = pos;
}

void HScreenObject::setEnd(QPoint pos)
{
    d_ptr->endPos = pos;
    d_ptr->area = QRect(d_ptr->startPos, d_ptr->endPos).normalized();
}

void HScreenObject::move(QPoint pos)
{
    int l = d_ptr->area.left() + pos.x();
    int t = d_ptr->area.top() + pos.y();
    int r = d_ptr->area.right() + pos.x();
    int b = d_ptr->area.bottom() + pos.y();

    if (l < 0)
    {
        l = 0;
        r -= pos.x();
    }
    if (t < 0)
    {
        t = 0;
        b -= pos.y();
    }
    if (r > d_ptr->size.width())
    {
        r = d_ptr->size.width();
        l -= pos.x();
    }

    if (b > d_ptr->size.height())
    {
        b = d_ptr->size.height();
        t -= pos.y();
    }
    auto tl = QPoint(l, t);
    auto br = QPoint(r, b);
    d_ptr->area = QRect(tl, br);
    d_ptr->startPos = tl;
    d_ptr->endPos = br;
}

void HScreenObject::drawScreen(QPainter *painter)
{
    auto rect = d_ptr->area;
    painter->save();
    painter->setPen(QPen(Qt::green, 2, Qt::DotLine));
    painter->drawPixmap(0, 0, d_ptr->blurScreen);
    if (rect.width() * rect.height() != 0)
        painter->drawPixmap(rect, d_ptr->fullScreen.copy(rect));

    painter->drawRect(d_ptr->area);
    painter->setPen(QPen(Qt::yellow, 2, Qt::DotLine));
    painter->drawText(QRect(rect.left() + 2, rect.top() - 10, rect.width() - 4, 8),
                      Qt::AlignCenter,
                      tr("截图范围：(%1 , %2) - (%3 , %4)  图片大小：(%5 X %6)").arg(rect.left()).arg(rect.top()).arg(rect.right()).arg(rect.bottom()).arg(rect.width()).arg(rect.height()));
    painter->restore();
}

void HScreenObject::initScreen()
{
    setStart(QPoint(-1, -1));
    setEnd(QPoint(-1, -1));
    d_ptr->fullScreen = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(), 0, 0, d_ptr->size.width(), d_ptr->size.height());

    // 设置透明度实现模糊背景
    QPixmap pm(d_ptr->size);
    pm.fill(QColor(160, 160, 160, 128));
    d_ptr->blurScreen = QPixmap(d_ptr->fullScreen);
    QPainter p(&d_ptr->blurScreen);
    p.drawPixmap(0, 0, pm);
}

void HScreenObject::saveScreen(QString fileName)
{
    d_ptr->fullScreen.copy(d_ptr->area).save(fileName, "png");
}

void HScreenObject::saveFullScreen(QString fileName)
{
    d_ptr->fullScreen.save(fileName, "png");
}

void HScreenObject::init()
{
    d_ptr->size = QApplication::desktop()->size();
    d_ptr->status = Select;
    d_ptr->startPos = QPoint(-1, -1);
    d_ptr->endPos = QPoint(-1, -1);
}


HE_CONTROL_END_NAMESPACE
