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

HTimelineWidget::~HTimelineWidget()
{
}

void HTimelineWidget::addInfo(QDate data, QString info)
{
    d_ptr->infos.insert(data, info);
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
        auto date = it.key();
        if (date.year() != year)
        {
            y += 30;
            year = date.year();
            drawBigCircle(&painter, x, y);

            auto font = painter.font();
            font.setPixelSize(30);
            font.setBold(true);
            painter.save();
            painter.setFont(font);
            painter.drawText(0, y - 20, width() * 0.25, 40, Qt::AlignRight | Qt::AlignVCenter, QString::number(year));
            painter.restore();
            y += 70;
        }
        drawSmallCircle(&painter, x, y);

        {
            painter.save();
            auto font = painter.font();
            font.setPixelSize(16);
            painter.setFont(font);
            painter.drawText(0, y - 20, width() * 0.20, 40, Qt::AlignRight | Qt::AlignVCenter, QString("%1").arg(QString::number(date.day()), 2, QChar{'0'}));
            painter.restore();
        }

        {
            painter.save();
            auto font = painter.font();
            font.setPixelSize(12);
            painter.setFont(font);
            painter.drawText(width() * 0.20 + 10, y - 20, width() * 0.05, 40, Qt::AlignRight | Qt::AlignVCenter, QString("%1月").arg(QString::number(date.month()), 2, QChar{'0'}));
            painter.restore();
        }

        {
            painter.save();
            auto font = painter.font();
            font.setPixelSize(14);
            painter.setFont(font);
            painter.drawText(x + 30, y - 20, width() * 0.7 - 30, 40, Qt::AlignLeft | Qt::AlignVCenter, it.value());
            painter.restore();
        }

        y += 40;
    }

}

void HTimelineWidget::drawBigCircle(QPainter *painter, int x, int y)
{
    auto radiu = 20;
    auto boundingRect = QRect(-radiu, -radiu, radiu * 2, radiu * 2);
    auto linearGradient = QLinearGradient(boundingRect.topLeft(), boundingRect.bottomRight());
    linearGradient.setColorAt(0.0, QColor("#7FDA8B"));
    linearGradient.setColorAt(1.0, QColor("#17B721"));

    painter->save();
    painter->translate(x, y);
    painter->setPen(Qt::transparent);
    painter->setBrush(linearGradient);
    painter->drawEllipse(boundingRect);
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect.adjusted(3, 3, -3, -3));
    painter->setPen(QPen(QBrush(linearGradient), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));//渐变线
    painter->drawLine(QPoint(0, 0), QPoint(0, -8));
    painter->drawLine(QPoint(0, 0), QPoint(8, 0));
    painter->restore();
}

void HTimelineWidget::drawSmallCircle(QPainter *painter, int x, int y)
{
    auto radiu = 6;
    auto boundingRect = QRect(-radiu, -radiu, radiu * 2, radiu * 2);
    auto linearGradient = QLinearGradient(boundingRect.topLeft(), boundingRect.bottomRight());
    linearGradient.setColorAt(0.0, QColor("#7FDA8B"));
    linearGradient.setColorAt(1.0, QColor("#17B721"));

    painter->save();
    painter->translate(x, y);
    painter->setPen(QPen(QBrush(linearGradient), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));//渐变线
    painter->setBrush(linearGradient);
    painter->drawEllipse(boundingRect);
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect.adjusted(1, 1, -1, -1));
    painter->restore();
}

HE_END_NAMESPACE

