#include "HLunarCalendarItem_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HLunarCalendarItemPrivate::HLunarCalendarItemPrivate()
{
    backgroundImage = ":/image/ludianwu/calendar_item_bk.png";
    selectType = HLunarCalendarItem::SelectType_Rect;
    date = QDate::currentDate();
    dayType = HLunarCalendarItem::DayType_MonthCurrent;
}

HLunarCalendarItem::HLunarCalendarItem(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLunarCalendarItemPrivate)
{
}

HLunarCalendarItem::HLunarCalendarItem(HLunarCalendarItemPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}


HLunarCalendarItem::~HLunarCalendarItem()
{
}

QSize HLunarCalendarItem::sizeHint() const
{
    return QSize(100, 100);
}

QSize HLunarCalendarItem::minimumSizeHint() const
{
    return QSize(20, 20);
}

bool HLunarCalendarItem::isSelect() const
{
    return d_ptr->select;
}

bool HLunarCalendarItem::isShowLunar() const
{
    return d_ptr->showLunar;
}

QString HLunarCalendarItem::backgroundImage() const
{
    return d_ptr->backgroundImage;
}

HLunarCalendarItem::SelectType HLunarCalendarItem::selectType() const
{
    return d_ptr->selectType;
}

QDate HLunarCalendarItem::date() const
{
    return d_ptr->date;
}

QString HLunarCalendarItem::dunar() const
{
    return d_ptr->lunar;
}

HLunarCalendarItem::DayType HLunarCalendarItem::dayType() const
{
    return d_ptr->dayType;
}

QColor HLunarCalendarItem::borderColor() const
{
    return d_ptr->borderColor;
}

QColor HLunarCalendarItem::weekColor() const
{
    return d_ptr->weekColor;
}

QColor HLunarCalendarItem::superColor() const
{
    return d_ptr->superColor;
}

QColor HLunarCalendarItem::lunarColor() const
{
    return d_ptr->lunarColor;
}

QColor HLunarCalendarItem::currentTextColor() const
{
    return d_ptr->currentTextColor;
}

QColor HLunarCalendarItem::otherTextColor() const
{
    return d_ptr->otherTextColor;
}

QColor HLunarCalendarItem::selectTextColor() const
{
    return d_ptr->selectTextColor;
}

QColor HLunarCalendarItem::hoverTextColor() const
{
    return d_ptr->hoverTextColor;
}

QColor HLunarCalendarItem::currentLunarColor() const
{
    return d_ptr->currentLunarColor;
}

QColor HLunarCalendarItem::otherLunarColor() const
{
    return d_ptr->otherLunarColor;
}

QColor HLunarCalendarItem::selectLunarColor() const
{
    return d_ptr->selectLunarColor;
}

QColor HLunarCalendarItem::hoverLunarColor() const
{
    return d_ptr->hoverLunarColor;
}

QColor HLunarCalendarItem::currentBackground() const
{
    return d_ptr->currentBackground;
}

QColor HLunarCalendarItem::otherBackground() const
{
    return d_ptr->otherBackground;
}

QColor HLunarCalendarItem::selectBackground() const
{
    return d_ptr->selectBackground;
}

QColor HLunarCalendarItem::hoverBackground() const
{
    return d_ptr->hoverBackground;
}

void HLunarCalendarItem::setSelect(bool b)
{
    if (d_ptr->select == b)
        return;
    d_ptr->select = b;
    update();
}

void HLunarCalendarItem::setShowLunar(bool b)
{
    if (d_ptr->showLunar == b)
        return;
    d_ptr->showLunar = b;
    update();
}

void HLunarCalendarItem::setBackgroundImage(const QString &value)
{
    if (d_ptr->backgroundImage == value)
        return;
    d_ptr->backgroundImage = value;
    update();
}

void HLunarCalendarItem::setSelectType(HLunarCalendarItem::SelectType value)
{
    if (d_ptr->selectType == value)
        return;
    d_ptr->selectType = value;
    update();
}

void HLunarCalendarItem::setDate(const QDate &value)
{
    if (d_ptr->date == value)
        return;
    d_ptr->date = value;
    update();
}

void HLunarCalendarItem::setLunar(const QString &value)
{
    if (d_ptr->lunar == value)
        return;
    d_ptr->lunar = value;
    update();
}

void HLunarCalendarItem::setDayType(DayType value)
{
    if (d_ptr->dayType == value)
        return;
    d_ptr->dayType = value;
    update();
}

void HLunarCalendarItem::setBorderColor(const QColor &value)
{
    if (d_ptr->borderColor == value)
        return;
    d_ptr->borderColor = value;
    update();
}

void HLunarCalendarItem::setWeekColor(const QColor &value)
{
    if (d_ptr->weekColor == value)
        return;
    d_ptr->weekColor = value;
    update();
}

void HLunarCalendarItem::setSuperColor(const QColor &value)
{
    if (d_ptr->superColor == value)
        return;
    d_ptr->superColor = value;
    update();
}

void HLunarCalendarItem::setLunarColor(const QColor &value)
{
    if (d_ptr->lunarColor == value)
        return;
    d_ptr->lunarColor = value;
    update();
}

void HLunarCalendarItem::setCurrentTextColor(const QColor &value)
{
    if (d_ptr->currentTextColor == value)
        return;
    d_ptr->currentTextColor = value;
    update();
}

void HLunarCalendarItem::setOtherTextColor(const QColor &value)
{
    if (d_ptr->otherTextColor == value)
        return;
    d_ptr->otherTextColor = value;
    update();
}

void HLunarCalendarItem::setSelectTextColor(const QColor &value)
{
    if (d_ptr->selectTextColor == value)
        return;
    d_ptr->selectTextColor = value;
    update();
}

void HLunarCalendarItem::setHoverTextColor(const QColor &value)
{
    if (d_ptr->hoverTextColor == value)
        return;
    d_ptr->hoverTextColor = value;
    update();
}

void HLunarCalendarItem::setCurrentLunarColor(const QColor &value)
{
    if (d_ptr->currentLunarColor == value)
        return;
    d_ptr->currentLunarColor = value;
    update();
}

void HLunarCalendarItem::setOtherLunarColor(const QColor &value)
{
    if (d_ptr->otherLunarColor == value)
        return;
    d_ptr->otherLunarColor = value;
    update();
}

void HLunarCalendarItem::setSelectLunarColor(const QColor &value)
{
    if (d_ptr->selectLunarColor == value)
        return;
    d_ptr->selectLunarColor = value;
    update();
}

void HLunarCalendarItem::setHoverLunarColor(const QColor &value)
{
    if (d_ptr->hoverLunarColor == value)
        return;
    d_ptr->hoverLunarColor = value;
    update();
}

void HLunarCalendarItem::setCurrentBackground(const QColor &value)
{
    if (d_ptr->currentBackground == value)
        return;
    d_ptr->currentBackground = value;
    update();
}

void HLunarCalendarItem::setOtherBackground(const QColor &value)
{
    if (d_ptr->otherBackground == value)
        return;
    d_ptr->otherBackground = value;
    update();
}

void HLunarCalendarItem::setSelectBackground(const QColor &value)
{
    if (d_ptr->selectBackground == value)
        return;
    d_ptr->selectBackground = value;
    update();
}

void HLunarCalendarItem::setHoverBackground(const QColor &value)
{
    if (d_ptr->hoverBackground == value)
        return;
    d_ptr->hoverBackground = value;
    update();
}

void HLunarCalendarItem::enterEvent(QEvent *)
{
    d_ptr->hover = true;
    update();
}

void HLunarCalendarItem::leaveEvent(QEvent *)
{
    d_ptr->hover = false;
    update();
}

void HLunarCalendarItem::mousePressEvent(QMouseEvent *)
{
    d_ptr->pressed = true;
    update();
    emit clicked(d_ptr->date, d_ptr->dayType);
}

void HLunarCalendarItem::mouseReleaseEvent(QMouseEvent *)
{
    d_ptr->pressed = false;
    update();
}

void HLunarCalendarItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    // 绘制背景和边框
    drawBackground(&painter);
    // 绘制状态
    drawState(&painter);
    // 绘制日期
    drawDay(&painter);
    // 绘制农历信息
    drawLunar(&painter);
}

void HLunarCalendarItem::drawBackground(QPainter *painter)
{
    auto color = d_ptr->dayType == DayType_MonthPre || d_ptr->dayType == DayType_MonthNext ? d_ptr->otherBackground : d_ptr->currentBackground;
    painter->save();
    painter->setPen(d_ptr->borderColor);
    painter->setBrush(color);
    painter->drawRect(rect());
    painter->restore();
}

void HLunarCalendarItem::drawState(QPainter *painter)
{
    if (d_ptr->select)
        drawCurrent(painter, d_ptr->selectBackground);
    else if (d_ptr->hover)
        drawCurrent(painter, d_ptr->hoverBackground);
}

void HLunarCalendarItem::drawCurrent(QPainter *painter, const QColor &color)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);

    if (d_ptr->selectType == SelectType_Rect)
    {
        painter->drawRect(rect());
    }
    if (d_ptr->selectType == SelectType_Circle)
    {
        int radius = side / 2 - 3;
        painter->drawEllipse(QPointF(width / 2, height / 2), radius, radius);
    }
    if (d_ptr->selectType == SelectType_Triangle)
    {
        int radius = side / 3;
        QPolygon pts;
        pts.setPoints(3, 1, 1, radius, 1, 1, radius);
        painter->drawRect(rect());
        painter->setBrush(d_ptr->superColor);
        painter->drawConvexPolygon(pts);
    }
    if (d_ptr->selectType == SelectType_Image)
    {
        QImage img(d_ptr->backgroundImage);
        if (!img.isNull())
        {
            img = img.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            int x = (width - img.width()) / 2;
            int y = (height - img.height()) / 2;
            painter->drawImage(x, y, img);
        }
    }

    painter->restore();
}

void HLunarCalendarItem::drawDay(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    auto color = d_ptr->currentTextColor;
    auto font = this->font();

    if (d_ptr->select)
        color = d_ptr->selectTextColor;
    else if (d_ptr->hover)
        color = d_ptr->hoverTextColor;
    else if (d_ptr->dayType == DayType_MonthPre || d_ptr->dayType == DayType_MonthNext)
        color = d_ptr->otherTextColor;
    else if (d_ptr->dayType == DayType_WeekEnd)
        color = d_ptr->weekColor;

    painter->save();
    painter->setPen(color);
    if (d_ptr->showLunar)
    {
        font.setPixelSize(side / 2.7);
        painter->setFont(font);
        painter->drawText(QRectF(0, 0, width, height / 1.7), Qt::AlignHCenter | Qt::AlignBottom, QString::number(d_ptr->date.day()));
    }
    else
    {
        font.setPixelSize(side / 2);
        painter->setFont(font);
        painter->drawText(QRect(0, 0, width, height), Qt::AlignCenter, QString::number(d_ptr->date.day()));
    }
    painter->restore();
}

void HLunarCalendarItem::drawLunar(QPainter *painter)
{
    if (!d_ptr->showLunar || d_ptr->lunar.isEmpty())
        return;

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    auto color = d_ptr->currentLunarColor;
    auto font = this->font();
    font.setPixelSize(side / 5);
    auto listDayName = QStringList() << "*" << "初一" << "初二" << "初三" << "初四" << "初五" << "初六" << "初七" << "初八" << "初九" << "初十"
                                     << "十一" << "十二" << "十三" << "十四" << "十五" << "十六" << "十七" << "十八" << "十九" << "二十"
                                     << "廿一" << "廿二" << "廿三" << "廿四" << "廿五" << "廿六" << "廿七" << "廿八" << "廿九" << "三十";
    if (d_ptr->select)
        color = d_ptr->selectLunarColor;
    else if (d_ptr->hover)
        color = d_ptr->hoverLunarColor;
    else if (!listDayName.contains(d_ptr->lunar) && d_ptr->dayType != DayType_MonthPre && d_ptr->dayType != DayType_MonthNext)
        color = d_ptr->lunarColor;
    else if (d_ptr->dayType == DayType_MonthPre || d_ptr->dayType == DayType_MonthNext)
        color = d_ptr->otherLunarColor;

    painter->save();
    painter->setPen(color);
    painter->setFont(font);
    painter->drawText(QRect(0, height / 2, width, height / 2), Qt::AlignCenter, d_ptr->lunar);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
