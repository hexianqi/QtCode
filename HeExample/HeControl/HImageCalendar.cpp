#include "HImageCalendar_p.h"
#include "HLunarCalendarInfo.h"
#include <QtCore/QDate>
#include <QtGui/QPainter>
#include <QtWidgets/QActionGroup>

HE_CONTROL_BEGIN_NAMESPACE

HImageCalendar::HImageCalendar(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HImageCalendarPrivate)
{
    init();
}

HImageCalendar::HImageCalendar(HImageCalendarPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HImageCalendar::~HImageCalendar() = default;

QSize HImageCalendar::sizeHint() const
{
    return {140, 158};
}

QSize HImageCalendar::minimumSizeHint() const
{
    return {140, 158};
}

HImageCalendar::CalendarStyle HImageCalendar::calendarStyle() const
{
    return d_ptr->calendarStyle;
}

void HImageCalendar::setCalendarStyle(CalendarStyle value)
{
    if (d_ptr->calendarStyle == value)
        return;
    d_ptr->calendarStyle = value;
    update();
}

void HImageCalendar::paintEvent(QPaintEvent *)
{
    // 居中绘制图片
    auto image = createImage();
    auto x = rect().center().x() - image.width() / 2;
    auto y = rect().center().y() - image.height() / 2;
    QPainter painter(this);
    painter.drawImage(QPointF(x, y), image);
}

QImage HImageCalendar::createImage()
{
    auto yearMonth = QDate::currentDate().toString("yyyy年 MM月");
    auto week = QDate::currentDate().toString("dddd");
    auto day = QDate::currentDate().toString("dd");
    auto lunar = d_ptr->lunar->lunarYearMonthDay(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());
    auto image =  QImage(140, 158, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::TextAntialiasing);
    painter.drawImage(0, 0, QImage(d_ptr->images.value(d_ptr->calendarStyle)));
    painter.setPen(QColor(250, 250, 250));
    painter.setFont(QFont("Microsoft Yahei", 9));
    painter.drawText(QRect(10, 26, 140 - 20, 20), Qt::AlignCenter, yearMonth);
    painter.drawText(QRect(10, 106, 140 - 20, 20), Qt::AlignCenter, week);
    painter.setFont(QFont("Microsoft Yahei", 8));
    painter.drawText(QRect(10, 124, 140 - 20, 20), Qt::AlignCenter, lunar);
    painter.setFont(QFont("Arial", 45));
    painter.setPen(QColor(50, 50, 50));
    painter.drawText(QRect(12, 40, 140 - 20, 80), Qt::AlignCenter, day);
    painter.setPen(QColor(250, 250, 250));
    painter.drawText(QRect(10, 38, 140 - 20, 80), Qt::AlignCenter, day);
    return image;
}

void HImageCalendar::changeStyle(QAction *p)
{
    if (p == nullptr)
        return;
    setCalendarStyle(static_cast<CalendarStyle>(p->data().toInt()));
}

void HImageCalendar::init()
{
    d_ptr->lunar = new HLunarCalendarInfo(this);
    d_ptr->images.insert(CalendarStyle_Yellow,    ":/image/ludianwu/calendar_yellow.png");
    d_ptr->images.insert(CalendarStyle_Blue,      ":/image/ludianwu/calendar_blue.png");
    d_ptr->images.insert(CalendarStyle_Brown,     ":/image/ludianwu/calendar_brown.png");
    d_ptr->images.insert(CalendarStyle_Gray,      ":/image/ludianwu/calendar_gray.png");
    d_ptr->images.insert(CalendarStyle_Purple,    ":/image/ludianwu/calendar_purple.png");
    d_ptr->images.insert(CalendarStyle_Red,       ":/image/ludianwu/calendar_red.png");
    QMap<CalendarStyle, QString> alias;
    alias.insert(CalendarStyle_Yellow,    tr("黄色风格"));
    alias.insert(CalendarStyle_Blue,      tr("蓝色风格"));
    alias.insert(CalendarStyle_Brown,     tr("褐色风格"));
    alias.insert(CalendarStyle_Gray,      tr("灰色风格"));
    alias.insert(CalendarStyle_Purple,    tr("紫色风格"));
    alias.insert(CalendarStyle_Red,       tr("红色风格"));
    auto group = new QActionGroup(this);
    for (auto it = alias.begin(); it != alias.end(); it++)
    {
        auto action = group->addAction(it.value());
        action->setCheckable(true);
        action->setData(it.key());
    }
    addActions(group->actions());
    connect(group, &QActionGroup::triggered, this, &HImageCalendar::changeStyle);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    group->actions().at(0)->setChecked(true);
    changeStyle(group->actions().at(0));
    setFont(QFont("Microsoft Yahei", 9));
    setWindowTitle(tr("日历"));
}

HE_CONTROL_END_NAMESPACE
