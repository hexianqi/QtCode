#include "HChatWidget_p.h"
#include <QtGui/QtEvents>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HChatInfo::HChatInfo(QString userName, QString message) :
    userName(userName),
    message(message)
{
}

HChatWidget::HChatWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HChatWidgetPrivate)
{
    setMinimumWidth(300);
}

HChatWidget::HChatWidget(HChatWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    setMinimumWidth(300);
}

HChatWidget::~HChatWidget()
{
}

void HChatWidget::setUserName(QString value)
{
    d_ptr->userName = value;
}

void HChatWidget::addPixmap(QString userName, QPixmap pixmap)
{
    d_ptr->heads.insert(userName, pixmap);
}

void HChatWidget::addPixmap(QString userName, QString fileName)
{
    QPixmap pixmap;
    if (pixmap.load(fileName))
        addPixmap(userName, pixmap);
}

void HChatWidget::addChart(QString userName, QString message)
{
    d_ptr->chats.append(HChatInfo(userName, message));
}

void HChatWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect pixmapRect;
    QRectF textRect;
    QColor background;
    auto drawHeight = 10;
    auto rect = event->rect();
    auto width = rect.width();
    auto font = painter.font();
    font.setPixelSize(24);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setFont(font);
    painter.fillRect(rect, QColor("#F5F5F5"));
    painter.setPen(QColor("#2f2f2f"));
    for (auto info : d_ptr->chats)
    {
        QPainterPath path;
        if (info.userName == d_ptr->userName)
        {
            pixmapRect = QRect(width - 42, drawHeight, 32, 32);
            background = QColor("#2EC100");
            textRect = painter.boundingRect(QRectF(width * 0.4, drawHeight, width * 0.6 - 42 - 30, 30), Qt::AlignRight | Qt::AlignVCenter | Qt::TextWordWrap, info.message);
            if (textRect.top()  < drawHeight)
                textRect.moveTopLeft(QPointF(textRect.left(), drawHeight));
            auto areaRect = textRect.adjusted(-3, -3, 3, 3);
            auto point = areaRect.topRight() + QPointF(0,6);
            auto polygon = QPolygonF() << point << point +  QPointF(20, 8) << point + QPointF(0, 18);
            path.addRoundedRect(areaRect, 6, 6);
            path.addPolygon(polygon);

        }
        else
        {
            pixmapRect = QRect(10, drawHeight, 32, 32);
            background = Qt::white;
            textRect = painter.boundingRect(QRectF(72, drawHeight, width * 0.6 - 72, 30), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, info.message);
            if (textRect.top() < drawHeight)
                textRect.moveTopLeft(QPointF(textRect.left(), drawHeight));
            auto areaRect = textRect.adjusted(-3, -3, 3, 3);
            auto point = areaRect.topLeft() + QPointF(0, 6);
            auto polygon = QPolygonF() << point << point -  QPointF(20, 8) << point + QPointF(0, 18);
            path.addRoundedRect(areaRect, 6, 6);
            path.addPolygon(polygon);
        }

        painter.drawPixmap(pixmapRect, d_ptr->heads[info.userName]);
        painter.fillPath(path, background);
        painter.drawText(textRect, info.message);
        drawHeight = textRect.bottom() + 20;
    }

    QWidget::paintEvent(event);
}

HE_END_NAMESPACE
