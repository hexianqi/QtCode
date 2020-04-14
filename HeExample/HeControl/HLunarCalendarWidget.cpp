#include "HLunarCalendarWidget_p.h"
#include "HIconFontFactory.h"
#include "HLunarCalendarInfo.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>

HE_CONTROL_BEGIN_NAMESPACE

HLunarCalendarWidgetPrivate::HLunarCalendarWidgetPrivate()
{
    date = QDate::currentDate();
    weekNameFormat = HLunarCalendarWidget::WeekNameFormat_Short;
    backgroundImage = ":/image/ludianwu/calendar_item_bk.png";
    selectType = HLunarCalendarItem::SelectType_Rect;
}

HLunarCalendarWidget::HLunarCalendarWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLunarCalendarWidgetPrivate)
{
    init();
}

HLunarCalendarWidget::HLunarCalendarWidget(HLunarCalendarWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HLunarCalendarWidget::~HLunarCalendarWidget() = default;

QSize HLunarCalendarWidget::sizeHint() const
{
    return {600, 500};
}

QSize HLunarCalendarWidget::minimumSizeHint() const
{
    return {200, 150};
}

QDate HLunarCalendarWidget::date() const
{
    return d_ptr->date;
}

HLunarCalendarWidget::WeekNameFormat HLunarCalendarWidget::weekNameFormat() const
{
    return d_ptr->weekNameFormat;
}

QColor HLunarCalendarWidget::weekTextColor() const
{
    return d_ptr->weekColor;
}

QColor HLunarCalendarWidget::weekBackground() const
{
    return d_ptr->weekBackground;
}

bool HLunarCalendarWidget::isShowLunar() const
{
    return d_ptr->showLunar;
}

QString HLunarCalendarWidget::backgroundImage() const
{
    return d_ptr->backgroundImage;
}

HLunarCalendarItem::SelectType HLunarCalendarWidget::selectType() const
{
    return d_ptr->selectType;
}

QColor HLunarCalendarWidget::borderColor() const
{
    return d_ptr->borderColor;
}

QColor HLunarCalendarWidget::weekColor() const
{
    return d_ptr->weekColor;
}

QColor HLunarCalendarWidget::superColor() const
{
    return d_ptr->superColor;
}

QColor HLunarCalendarWidget::lunarColor() const
{
    return d_ptr->lunarColor;
}

QColor HLunarCalendarWidget::currentTextColor() const
{
    return d_ptr->currentTextColor;
}

QColor HLunarCalendarWidget::otherTextColor() const
{
    return d_ptr->otherTextColor;
}

QColor HLunarCalendarWidget::selectTextColor() const
{
    return d_ptr->selectTextColor;
}

QColor HLunarCalendarWidget::hoverTextColor() const
{
    return d_ptr->hoverTextColor;
}

QColor HLunarCalendarWidget::currentLunarColor() const
{
    return d_ptr->currentLunarColor;
}

QColor HLunarCalendarWidget::otherLunarColor() const
{
    return d_ptr->otherLunarColor;
}

QColor HLunarCalendarWidget::selectLunarColor() const
{
    return d_ptr->selectLunarColor;
}

QColor HLunarCalendarWidget::hoverLunarColor() const
{
    return d_ptr->hoverLunarColor;
}

QColor HLunarCalendarWidget::currentBackground() const
{
    return d_ptr->currentBackground;
}

QColor HLunarCalendarWidget::otherBackground() const
{
    return d_ptr->otherBackground;
}

QColor HLunarCalendarWidget::selectBackground() const
{
    return d_ptr->selectBackground;
}

QColor HLunarCalendarWidget::hoverBackground() const
{
    return d_ptr->hoverBackground;
}

void HLunarCalendarWidget::setDate(const QDate &value)
{
    if (d_ptr->date == value)
        return;
    d_ptr->date = value;
    initDate();
}

void HLunarCalendarWidget::setWeekNameFormat(HLunarCalendarWidget::WeekNameFormat value)
{
    if (d_ptr->weekNameFormat == value)
        return;
    d_ptr->weekNameFormat = value;

    QStringList list;
    if (value == WeekNameFormat_Short)
        list << "日" << "一" << "二" << "三" << "四" << "五" << "六";
    else if (value == WeekNameFormat_Normal)
        list << "周日" << "周一" << "周二" << "周三" << "周四" << "周五" << "周六";
    else if (value == WeekNameFormat_Long)
        list << "星期天" << "星期一" << "星期二" << "星期三" << "星期四" << "星期五" << "星期六";
    else if (value == WeekNameFormat_En)
        list << "Sun" << "Mon" << "Tue" << "Wed" << "Thu" << "Fri" << "Sat";

    for (int i = 0; i < 7; i++)
        d_ptr->labelWeeks.at(i)->setText(list.at(i));
}

void HLunarCalendarWidget::setWeekTextColor(const QColor &value)
{
    if (d_ptr->weekTextColor == value)
        return;
    d_ptr->weekTextColor = value;
    initStyle();
}

void HLunarCalendarWidget::setWeekBackground(const QColor &value)
{
    if (d_ptr->weekBackground == value)
        return;
    d_ptr->weekBackground = value;
    initStyle();
}

void HLunarCalendarWidget::setShowLunar(bool b)
{
    if (d_ptr->showLunar == b)
        return;
    d_ptr->showLunar = b;
    initStyle();
}

void HLunarCalendarWidget::setBackgroundImage(const QString &value)
{
    if (d_ptr->backgroundImage == value)
        return;
    d_ptr->backgroundImage = value;
    initStyle();
}

void HLunarCalendarWidget::setSelectType(HLunarCalendarItem::SelectType value)
{
    if (d_ptr->selectType == value)
        return;
    d_ptr->selectType = value;
    initStyle();
}

void HLunarCalendarWidget::setBorderColor(const QColor &value)
{
    if (d_ptr->borderColor == value)
        return;
    d_ptr->borderColor = value;
    initStyle();
}

void HLunarCalendarWidget::setWeekColor(const QColor &value)
{
    if (d_ptr->weekColor == value)
        return;
    d_ptr->weekColor = value;
    initStyle();
}

void HLunarCalendarWidget::setSuperColor(const QColor &value)
{
    if (d_ptr->superColor == value)
        return;
    d_ptr->superColor = value;
    initStyle();
}

void HLunarCalendarWidget::setLunarColor(const QColor &value)
{
    if (d_ptr->lunarColor == value)
        return;
    d_ptr->lunarColor = value;
    initStyle();
}

void HLunarCalendarWidget::setCurrentTextColor(const QColor &value)
{
    if (d_ptr->currentTextColor == value)
        return;
    d_ptr->currentTextColor = value;
    initStyle();
}

void HLunarCalendarWidget::setOtherTextColor(const QColor &value)
{
    if (d_ptr->otherTextColor == value)
        return;
    d_ptr->otherTextColor = value;
    initStyle();
}

void HLunarCalendarWidget::setSelectTextColor(const QColor &value)
{
    if (d_ptr->selectTextColor == value)
        return;
    d_ptr->selectTextColor = value;
    initStyle();
}

void HLunarCalendarWidget::setHoverTextColor(const QColor &value)
{
    if (d_ptr->hoverTextColor == value)
        return;
    d_ptr->hoverTextColor = value;
    initStyle();
}

void HLunarCalendarWidget::setCurrentLunarColor(const QColor &value)
{
    if (d_ptr->currentLunarColor == value)
        return;
    d_ptr->currentLunarColor = value;
    initStyle();
}

void HLunarCalendarWidget::setOtherLunarColor(const QColor &value)
{
    if (d_ptr->otherLunarColor == value)
        return;
    d_ptr->otherLunarColor = value;
    initStyle();
}

void HLunarCalendarWidget::setSelectLunarColor(const QColor &value)
{
    if (d_ptr->selectLunarColor == value)
        return;
    d_ptr->selectLunarColor = value;
    initStyle();
}

void HLunarCalendarWidget::setHoverLunarColor(const QColor &value)
{
    if (d_ptr->hoverLunarColor == value)
        return;
    d_ptr->hoverLunarColor = value;
    initStyle();
}

void HLunarCalendarWidget::setCurrentBackground(const QColor &value)
{
    if (d_ptr->currentBackground == value)
        return;
    d_ptr->currentBackground = value;
    initStyle();
}

void HLunarCalendarWidget::setOtherBackground(const QColor &value)
{
    if (d_ptr->otherBackground == value)
        return;
    d_ptr->otherBackground = value;
    initStyle();
}

void HLunarCalendarWidget::setSelectBackground(const QColor &value)
{
    if (d_ptr->selectBackground == value)
        return;
    d_ptr->selectBackground = value;
    initStyle();
}

void HLunarCalendarWidget::setHoverBackground(const QColor &value)
{
    if (d_ptr->hoverBackground == value)
        return;
    d_ptr->hoverBackground = value;
    initStyle();
}

void HLunarCalendarWidget::showYearPrevious()
{
    if (d_ptr->date.year() <= 1901)
        return;
    dateChanged(d_ptr->date.year() - 1, d_ptr->date.month(), d_ptr->date.day());
}

void HLunarCalendarWidget::showYearNext()
{
    if (d_ptr->date.year() >= 2099)
        return;
    dateChanged(d_ptr->date.year() + 1, d_ptr->date.month(), d_ptr->date.day());
}

void HLunarCalendarWidget::showMonthPrevious()
{
    int year = d_ptr->date.year();
    int month = d_ptr->date.month();
    if (year <= 1901 && month == 1)
        return;

    month--;
    if (month < 1)
    {
        month = 12;
        year--;
    }
    dateChanged(year, month, d_ptr->date.day());
}

void HLunarCalendarWidget::showMonthNext()
{
    int year = d_ptr->date.year();
    int month = d_ptr->date.month();
    if (year >= 2099 && month == 12)
        return;

    month++;
    if (month > 12)
    {
        month = 1;
        year++;
    }
    dateChanged(year, month, d_ptr->date.day());
}

void HLunarCalendarWidget::showToday()
{
    setDate(QDate::currentDate());
}

void HLunarCalendarWidget::init()
{
    d_ptr->info = new HLunarCalendarInfo(this);
    auto factory = new HIconFontFactory(this);
    d_ptr->iconFont = factory->createFont("FontAwesome");
    initWidget();
    initStyle();
    initDate();
    setWeekNameFormat(WeekNameFormat_Long);
    setWindowTitle(tr("农历控件"));
}

void HLunarCalendarWidget::initWidget()
{
    auto top = new QWidget;
    top->setMinimumHeight(35);

    auto yearPrev = new QToolButton;
    yearPrev->setFixedWidth(35);
    yearPrev->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    yearPrev->setFont(d_ptr->iconFont);
    yearPrev->setText(QChar(0xf060));

    auto yearNext = new QToolButton;
    yearNext->setFixedWidth(35);
    yearNext->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    yearNext->setFont(d_ptr->iconFont);
    yearNext->setText(QChar(0xf061));

    auto monthPrev = new QToolButton;
    monthPrev->setFixedWidth(35);
    monthPrev->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    monthPrev->setFont(d_ptr->iconFont);
    monthPrev->setText(QChar(0xf060));

    auto monthNext = new QToolButton;
    monthNext->setFixedWidth(35);
    monthNext->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    monthNext->setFont(d_ptr->iconFont);
    monthNext->setText(QChar(0xf061));

    auto today = new QPushButton;
    today->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    today->setText(tr("今天"));

    d_ptr->comboBoxYear = new QComboBox;
    for (int i = 1901; i <= 2099; i++)
        d_ptr->comboBoxYear->addItem(tr("%1年").arg(i));

    d_ptr->comboBoxMonth = new QComboBox;
    for (int i = 1; i <= 12; i++)
        d_ptr->comboBoxMonth->addItem(tr("%1月").arg(i));

    auto layoutTop = new QHBoxLayout(top);
    layoutTop->setContentsMargins(0, 0, 0, 9);
    layoutTop->addWidget(yearPrev);
    layoutTop->addWidget(d_ptr->comboBoxYear);
    layoutTop->addWidget(yearNext);
    layoutTop->addSpacing(5);
    layoutTop->addWidget(monthPrev);
    layoutTop->addWidget(d_ptr->comboBoxMonth);
    layoutTop->addWidget(monthNext);
    layoutTop->addSpacing(5);
    layoutTop->addWidget(today);

    auto week = new QWidget;
    week->setMinimumHeight(30);

    auto layoutWeek = new QHBoxLayout(week);
    layoutWeek->setMargin(0);
    layoutWeek->setSpacing(0);
    for (int i = 0; i < 7; i++)
    {
        auto label = new QLabel;
        label->setAlignment(Qt::AlignCenter);
        layoutWeek->addWidget(label);
        d_ptr->labelWeeks << label;
    }

    auto body = new QWidget;
    body->setObjectName("widgetBody");

    auto layoutBody = new QGridLayout(body);
    layoutBody->setMargin(1);
    layoutBody->setHorizontalSpacing(0);
    layoutBody->setVerticalSpacing(0);

    for (int i = 0; i < 42; i++)
    {
        auto item = new HLunarCalendarItem;
        connect(item, &HLunarCalendarItem::clicked, this, &HLunarCalendarWidget::handleItemClicked);
        layoutBody->addWidget(item, i / 7, i % 7);
        d_ptr->dayItems << item;
    }

    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(top);
    layout->addWidget(week);
    layout->addWidget(body, 1);

    connect(yearPrev, &QToolButton::clicked, this, &HLunarCalendarWidget::showYearPrevious);
    connect(yearNext, &QToolButton::clicked, this, &HLunarCalendarWidget::showYearNext);
    connect(monthPrev, &QToolButton::clicked, this, &HLunarCalendarWidget::showMonthPrevious);
    connect(monthNext, &QToolButton::clicked, this, &HLunarCalendarWidget::showMonthNext);
    connect(today, &QPushButton::clicked, this, &HLunarCalendarWidget::showToday);
    connect(d_ptr->comboBoxYear, SIGNAL(currentIndexChanged(QString)), this, SLOT(handleYearChanged(QString)));
    connect(d_ptr->comboBoxMonth, SIGNAL(currentIndexChanged(QString)), this, SLOT(handleMonthChanged(QString)));
}

void HLunarCalendarWidget::initStyle()
{
    QString type = "SelectType_Rect";
    if (d_ptr->selectType == HLunarCalendarItem::SelectType_Circle)
        type = "SelectType_Circle";
    if (d_ptr->selectType == HLunarCalendarItem::SelectType_Triangle)
        type = "SelectType_Triangle";
    if (d_ptr->selectType == HLunarCalendarItem::SelectType_Image)
        type = "SelectType_Image";

    QStringList list;
    list << QString("QToolButton { padding:0px; background:none; border:none; border-radius:5px; }")
         << QString("QToolButton:hover { background:#16A085; color:#FFFFFF; }")
         << QString("QPushButton { background:#16A085; color:#FFFFFF; border-radius:5px; }")
         << QString("QLabel { background:%1; color:%2; }").arg(d_ptr->weekBackground.name(), d_ptr->weekTextColor.name())
         << QString("QWidget#widgetBody { border:1px solid %1; }").arg(d_ptr->borderColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-showLunar:%1; }").arg(d_ptr->showLunar)
         << QString("HeControl--HLunarCalendarItem { qproperty-backgroundImage:%1; }").arg(d_ptr->backgroundImage)
         << QString("HeControl--HLunarCalendarItem { qproperty-selectType:%1; }").arg(type)
         << QString("HeControl--HLunarCalendarItem { qproperty-borderColor:%1; }").arg(d_ptr->borderColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-weekColor:%1; }").arg(d_ptr->weekColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-superColor:%1; }").arg(d_ptr->superColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-lunarColor:%1; }").arg(d_ptr->lunarColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-currentTextColor:%1; }").arg(d_ptr->currentTextColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-otherTextColor:%1; }").arg(d_ptr->otherTextColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-selectTextColor:%1; }").arg(d_ptr->selectTextColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-hoverTextColor:%1; }").arg(d_ptr->hoverTextColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-currentLunarColor:%1; }").arg(d_ptr->currentLunarColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-otherLunarColor:%1; }").arg(d_ptr->otherLunarColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-selectLunarColor:%1; }").arg(d_ptr->selectLunarColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-hoverLunarColor:%1; }").arg(d_ptr->hoverLunarColor.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-currentBackground:%1; }").arg(d_ptr->currentBackground.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-otherBackground:%1; }").arg(d_ptr->otherBackground.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-selectBackground:%1; }").arg(d_ptr->selectBackground.name())
         << QString("HeControl--HLunarCalendarItem { qproperty-hoverBackground:%1; }").arg(d_ptr->hoverBackground.name());
    setStyleSheet(list.join("\n"));
}

void HLunarCalendarWidget::initDate()
{
    auto year = d_ptr->date.year();
    auto month = d_ptr->date.month();
    auto week = d_ptr->info->firstDayOfWeek(year, month);
    auto countDay = d_ptr->info->monthDays(year, month);
    auto countDayPre = d_ptr->info->monthDays(month == 1 ? year - 1 : year, month == 1 ? 12 : month - 1);

    d_ptr->comboBoxClicked = true;
    d_ptr->comboBoxYear->setCurrentText(tr("%1年").arg(year));
    d_ptr->comboBoxMonth->setCurrentText(tr("%1月").arg(month));
    d_ptr->comboBoxClicked = false;

    // 如果上月天数上月刚好一周则另外处理
    int startPre, endPre, startNext, endNext, index, tempYear, tempMonth, tempDay;
    if (week == 0)
    {
        startPre = 0;
        endPre = 7;
        startNext = 0;
        endNext = 42 - (countDay + 7);
    }
    else
    {
        startPre = 0;
        endPre = week;
        startNext = week + countDay;
        endNext = 42;
    }

    // 纠正1月份前面部分偏差,1月份前面部分是上一年12月份
    tempYear = year;
    tempMonth = month - 1;
    if (tempMonth < 1)
    {
        tempYear--;
        tempMonth = 12;
    }
    // 显示上月天数
    for (int i = startPre; i < endPre; i++)
    {
        index = i;
        tempDay = countDayPre - endPre + i + 1;

        QDate date(tempYear, tempMonth, tempDay);
        auto lunar = d_ptr->info->lunarDay(tempYear, tempMonth, tempDay);
        d_ptr->dayItems.at(index)->setDate(date, lunar, HLunarCalendarItem::DayType_MonthPre);
    }

    // 纠正12月份后面部分偏差,12月份后面部分是下一年1月份
    tempYear = year;
    tempMonth = month + 1;
    if (tempMonth > 12)
    {
        tempYear++;
        tempMonth = 1;
    }
    // 显示下月天数
    for (int i = startNext; i < endNext; i++)
    {
        index = 42 - endNext + i;
        tempDay = i - startNext + 1;

        QDate date(tempYear, tempMonth, tempDay);
        auto lunar = d_ptr->info->lunarDay(tempYear, tempMonth, tempDay);
        d_ptr->dayItems.at(index)->setDate(date, lunar, HLunarCalendarItem::DayType_MonthNext);
    }

    // 重新置为当前年月
    tempYear = year;
    tempMonth = month;
    // 显示当前月
    for (int i = week; i < (countDay + week); i++)
    {
        index = week == 0 ? (i + 7) : i;
        tempDay = i - week + 1;

        QDate date(tempYear, tempMonth, tempDay);
        auto lunar = d_ptr->info->lunarDay(tempYear, tempMonth, tempDay);
        d_ptr->dayItems.at(index)->setDate(date, lunar, ((i % 7) == 0 || (i % 7) == 6) ? HLunarCalendarItem::DayType_WeekEnd : HLunarCalendarItem::DayType_MonthCurrent);
    }

    dayChanged(d_ptr->date);
}

void HLunarCalendarWidget::handleYearChanged(const QString &value)
{
    if (d_ptr->comboBoxClicked)
        return;
    dateChanged(value.midRef(0, value.length() - 1).toInt(), d_ptr->date.month(), d_ptr->date.day());
}

void HLunarCalendarWidget::handleMonthChanged(const QString &value)
{
    if (d_ptr->comboBoxClicked)
        return;
    dateChanged(d_ptr->date.year(), value.midRef(0, value.length() - 1).toInt(), d_ptr->date.day());
}

void HLunarCalendarWidget::handleItemClicked(const QDate &date, const HLunarCalendarItem::DayType &type)
{
    if (type == HLunarCalendarItem::DayType_MonthPre)
        showMonthPrevious();
    else if (type == HLunarCalendarItem::DayType_MonthNext)
        showMonthNext();
    else
    {
        d_ptr->date = date;
        dayChanged(date);
    }
}

void HLunarCalendarWidget::dayChanged(const QDate &date)
{
    auto day = date.day();
    auto week = d_ptr->info->firstDayOfWeek(date.year(), date.month());

    // 选中当前日期,其他日期恢复,这里还有优化空间,比方说类似单选框机制
    for (int i = 0; i < 42; i++)
    {
        // 当月第一天是星期天要另外计算
        auto index = week == 0 ? day + 6 : day + week - 1;
        d_ptr->dayItems.at(i)->setSelect(i == index);
    }

    emit clicked(date);
    emit selectionChanged();
}

void HLunarCalendarWidget::dateChanged(int year, int month, int day)
{
    // 如果原有天大于28则设置为1，防止出错
    setDate(QDate(year, month, day > 28 ? 1 : day));
}

HE_CONTROL_END_NAMESPACE
