#include "HSlideButtonGroup_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

HE_BEGIN_NAMESPACE

const int normalStatusSize = 60;
const int iconSize = 28;                                    // 图标宽度
const int iconShowY = (normalStatusSize - iconSize) / 2;    // 图标显示最终位置的Y值
const int iconHideY = normalStatusSize + 10;                // 图标隐藏最终位置的Y值

HSlideButtonGroup::HSlideButtonGroup(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSlideButtonGroupPrivate)
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(40);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(d_ptr->timer, &QTimer::timeout, this, &HSlideButtonGroup::onTimer);


    d_ptr->images << QPixmap(":/Resources/image/like1.png")
                  << QPixmap(":/Resources/image/like2.png")
                  << QPixmap(":/Resources/image/coin1.png")
                  << QPixmap(":/Resources/image/coin2.png")
                  << QPixmap(":/Resources/image/star1.png")
                  << QPixmap(":/Resources/image/star2.png");

    for (int i = 0; i < d_ptr->images.size() / 2; i++)
        d_ptr->rects << QRect(normalStatusSize + i * (normalStatusSize - 10) + (normalStatusSize - 10 - iconSize) / 2, iconHideY, iconSize, iconSize);
}

HSlideButtonGroup::~HSlideButtonGroup()
{
}

QSize HSlideButtonGroup::sizeHint() const
{
    if (d_ptr->state == UnPressed)
        return QSize(normalStatusSize, normalStatusSize);
    return QSize(normalStatusSize + d_ptr->widthChangeValue, normalStatusSize);
}

void HSlideButtonGroup::paintEvent(QPaintEvent *)
{
    auto radiu = normalStatusSize / 2 - 6;
    auto lineWidth = radiu / 3.0;
    auto roundedRect = rect().adjusted(5, 5, -5, -5);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(roundedRect, normalStatusSize / 2, normalStatusSize / 2);
    painter.setClipPath(path);
    painter.fillRect(rect(), Qt::white);
    painter.setPen(QPen(QColor(0x22a74c), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRoundedRect(roundedRect, normalStatusSize / 2, normalStatusSize / 2);
    painter.save();
    painter.drawRoundedRect(roundedRect, normalStatusSize / 2, normalStatusSize / 2);
    painter.translate(QPoint(normalStatusSize / 2,normalStatusSize / 2));


    if (d_ptr->state == Extend ||
        d_ptr->state == IconShowing ||
        d_ptr->state == IconShowed ||
        d_ptr->state == IconHiding ||
        d_ptr->state == Rreduce)
    {
        painter.rotate(d_ptr->angle);
    }

    painter.drawLine(-lineWidth, 0, lineWidth, 0);
    painter.drawLine(0, -lineWidth, 0, lineWidth);
    painter.restore();

    if (d_ptr->state == IconShowing ||
        d_ptr->state == IconShowed ||
        d_ptr->state == IconHiding)
    {
        for (int i = 0; i < d_ptr->rects.size(); i++)
            painter.drawPixmap(d_ptr->rects.at(i), d_ptr->images.at(i * 2));
    }

    if (d_ptr->state == IconShowed && d_ptr->index != -1)
        painter.drawPixmap(d_ptr->rects.at(d_ptr->index), d_ptr->images.at(d_ptr->index * 2 + 1));
}

void HSlideButtonGroup::mousePressEvent(QMouseEvent *event)
{
    if (d_ptr->state == UnPressed)
    {
        d_ptr->state = Extend;
        d_ptr->widthChangeValue = 0;
        d_ptr->angle = 0;
        d_ptr->timer->start();
    }
    else if(d_ptr->state == IconShowed)
    {
        auto pos = event->pos();
        for (int i = 0; i < d_ptr->rects.size(); i++)
        {
            if (d_ptr->rects.at(i).contains(pos))
            {
                d_ptr->index = i;
                break;
            }
        }
        if (d_ptr->index != -1)
        {
            update();
            emit clicked(d_ptr->index);
        }
        else
        {
            if (QRect(10, 10, normalStatusSize - 20, normalStatusSize - 20).contains(pos))
            {
                d_ptr->state = IconHiding;
                d_ptr->timer->start();
            }
        }
    }
}

void HSlideButtonGroup::mouseReleaseEvent(QMouseEvent *)
{
    if (d_ptr->state == IconShowed)
    {
        if (d_ptr->index != -1)
        {
            d_ptr->index = -1;
            update();
        }
    }
}

void HSlideButtonGroup::onTimer()
{
    if (d_ptr->state == Extend)
    {
        auto inLayout = testAttribute(Qt::WA_LaidOut); // 控件是否在布局中
        if (inLayout)
            setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed); // Minimum：sizeHint() 提供的大小为最小大小，可拉伸（布局中）

        d_ptr->angle += 5;
        auto temp = (d_ptr->images.size() / 2 * (normalStatusSize - 10));

        d_ptr->widthChangeValue += (temp / 10);
        if (d_ptr->widthChangeValue > temp)
            d_ptr->state = IconShowing;

        if (!inLayout)
            adjustSize(); // 控件不在布局中时调整大小（不在布局中）
        update();

        if (inLayout)
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    else if (d_ptr->state == IconShowing)
    {
        auto isCenter = true;
        for (int i = 0; i < d_ptr->rects.size(); i++)
        {
            auto rect = d_ptr->rects[i];
            auto y = rect.y();
            if (y == iconShowY)
                continue;
            isCenter = false;
            y -= 7;
            if (y < iconShowY)
                rect.moveTopLeft(QPoint(rect.x(), iconShowY));
            else
                rect.moveTop(y);
            d_ptr->rects[i] = rect;
            break;
        }
        if (isCenter)
        {
            d_ptr->state = IconShowed;
            d_ptr->timer->stop();
        }
        update();
    }
    else if (d_ptr->state == IconHiding)
    {
        auto isHide = true;
        for(int i = d_ptr->rects.size() - 1; i >= 0; i--)
        {
            auto rect = d_ptr->rects[i];
            auto y = rect.y();
            if (y == iconHideY)
                continue;
            isHide = false;
            y += 7;

            if(y >= iconHideY)
                rect.moveTopLeft(QPoint(rect.x(),iconHideY));
            else
                rect.moveTop(y);
            d_ptr->rects[i] = rect;
            break;
        }
        if (isHide)
            d_ptr->state = Rreduce;
        update();
    }
    else if (d_ptr->state == Rreduce)
    {
        auto isLayout = testAttribute(Qt::WA_LaidOut);
        if (isLayout)
            setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

        d_ptr->angle -= 5;
        auto temp = (d_ptr->images.size() / 2 * (normalStatusSize - 10));

        d_ptr->widthChangeValue -= (temp / 10);
        if (d_ptr->widthChangeValue <= 0)
        {
            d_ptr->state = UnPressed;
            d_ptr->timer->stop();
        }

        if(!isLayout)
            adjustSize(); // 控件不在布局中时调整大小（不在布局中）
        update();

        if(isLayout)
            setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    }
}

HE_END_NAMESPACE
