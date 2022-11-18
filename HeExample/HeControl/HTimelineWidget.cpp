#include "HTimelineWidget_p.h"
#include <QtCore/QDate>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HTimelineWidget::HTimelineWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTimelineWidgetPrivate)
{
    setPalette(Qt::white);
}

HTimelineWidget::HTimelineWidget(HTimelineWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    setPalette(Qt::white);
}

void HTimelineWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    auto x = static_cast<int>(width() * 0.3);
    auto y = 20;
    auto year = -1;

    painter.save();
    painter.setPen(QPen(QColor("#4CCB5E"), 2));
    painter.drawLine(x, 0, x, height());
    painter.restore();

    for (auto it = d_ptr->infos.begin(); it != d_ptr->infos.end(); it++)
    {
        if (it.key().year() != year)
        {
            y += 30;
            year = it.key().year();
            drawYearCircle(&painter, x, y);

            auto font = painter.font();
            font.setPixelSize(30);
            font.setBold(true);
            painter.save();
            painter.setFont(font);
            painter.drawText(0, y-20, width() * 0.25, 40, Qt::AlignRight | Qt::AlignVCenter, QString::number(year));
            painter.restore();
            y += 70;
        }
        drawSmallCircle(&painter,drawCircleShapeX,y);

        {
            painter.save();
            auto font = painter.font();
            font.setPixelSize(16);
            painter.setFont(font);
            QRect dayTextRect(0,y-20,static_cast<int>(rect.width() * 0.20),40);
            painter.drawText(dayTextRect,Qt::AlignRight | Qt::AlignVCenter,
                             QString("%1").arg(QString::number(item.first.day()),2,QChar{'0'}));
            painter.restore();
        }

        {
            painter.save();
            auto font = painter.font();
            font.setPixelSize(12);
            painter.setFont(font);
            QRect monthTextRect(static_cast<int>(rect.width() * 0.20) + 10,y - 20,
                                static_cast<int>(rect.width() * 0.05),40);
            painter.drawText(monthTextRect,Qt::AlignRight | Qt::AlignVCenter,
                             QString("%1月").arg(QString::number(item.first.month()),2,QChar{'0'}));
            painter.restore();
        }

        {
            painter.save();
            auto font = painter.font();
            font.setPixelSize(14);
            painter.setFont(font);
            QRect infoTextRect(drawCircleShapeX + 30,y-20,
                               static_cast<int>(rect.width() * 0.7 - 30),40);
            painter.drawText(infoTextRect,Qt::AlignLeft | Qt::AlignVCenter,item.second);
            painter.restore();
        }

        y += 40;
    }

}

HTimelineWidget::~HTimelineWidget()
{
}

void HTimelineWidget::addInfo(QDate data, QString info)
{
    d_ptr->infos.insert(data, info);
}

HE_END_NAMESPACE


#include "timelinecontrolswidget.h"
#include <QPainter>
#include <QPaintEvent>

TimelineControlsWidget::TimelineControlsWidget(QWidget *parent)
    : QWidget(parent)
{
    setPalette(Qt::white);

    infoList << std::make_pair<QDate,QString>(QDate(2021,10,1),"国庆节放假");
    infoList << std::make_pair<QDate,QString>(QDate(2021,8,1),"建党百年，伟大征程");
    infoList << std::make_pair<QDate,QString>(QDate(2021,5,1),"劳动节放假");
    infoList << std::make_pair<QDate,QString>(QDate(2021,3,8),"妇女节，女士放假，男士未放假");
    infoList << std::make_pair<QDate,QString>(QDate(2020,11,11),"购物节");
    infoList << std::make_pair<QDate,QString>(QDate(2020,12,26),"圣诞节");
    infoList << std::make_pair<QDate,QString>(QDate(2020,4,1),"愚人节");
    infoList << std::make_pair<QDate,QString>(QDate(2020,1,20),"新冠疫情开始爆发");
    infoList << std::make_pair<QDate,QString>(QDate(2019,10,1),"东风17、东风41亮相");
}

TimelineControlsWidget::~TimelineControlsWidget()
{

}

void TimelineControlsWidget::drawYearCircle(QPainter * painter,int x, int y)
{
    auto radiu = 20;
    QRect boundingRect = QRect(-radiu,-radiu,radiu * 2,radiu * 2);

    painter->save();
    painter->translate(x,y);

    QLinearGradient linearGradient(boundingRect.topLeft(),boundingRect.bottomRight());
    linearGradient.setColorAt(0.0,QColor("#7FDA8B"));
    linearGradient.setColorAt(1.0,QColor("#17B721"));

    //    linearGradient.setColorAt(0.0,Qt::green);
    //    linearGradient.setColorAt(1.0,Qt::blue);

    painter->setBrush(linearGradient);
    painter->setPen(Qt::transparent);

    painter->drawEllipse(boundingRect);

    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect.adjusted(3,3,-3,-3));

    painter->setPen(QPen(QBrush(linearGradient), 5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));//渐变线
    painter->drawLine(QPoint(0,0),QPoint(0,-8));
    painter->drawLine(QPoint(0,0),QPoint(8,0));

    painter->restore();
}

void TimelineControlsWidget::drawSmallCircle(QPainter * painter, int x, int y)
{
    auto radiu = 6;
    QRect boundingRect = QRect(-radiu,-radiu,radiu * 2,radiu * 2);

    painter->save();
    painter->translate(x,y);

    QLinearGradient linearGradient(boundingRect.topLeft(),boundingRect.bottomRight());
    linearGradient.setColorAt(0.0,QColor("#7FDA8B"));
    linearGradient.setColorAt(1.0,QColor("#17B721"));

    painter->setBrush(linearGradient);
    painter->setPen(QPen(QBrush(linearGradient), 3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));//渐变线

    painter->drawEllipse(boundingRect);

    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect.adjusted(1,1,-1,-1));
    painter->restore();
}

void TimelineControlsWidget::paintEvent(QPaintEvent *event)
{

}
