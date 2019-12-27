/***************************************************************************************************
**      2019-12-27  HLunarCalendarItem
***************************************************************************************************/

#ifndef HLUNARCALENDARITEM_H
#define HLUNARCALENDARITEM_H

#include "HControlGlobal.h"
#include <QtCore/QDate>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HLunarCalendarItemPrivate;

class HLunarCalendarItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool select READ isSelect WRITE setSelect)
    Q_PROPERTY(bool showLunar READ isShowLunar WRITE setShowLunar)
    Q_PROPERTY(QString backgroundImage READ backgroundImage WRITE setBackgroundImage)
    Q_PROPERTY(SelectType selectType READ selectType WRITE setSelectType)

    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(QString lunar READ dunar WRITE setLunar)
    Q_PROPERTY(DayType dayType READ dayType WRITE setDayType)

    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor weekColor READ weekColor WRITE setWeekColor)
    Q_PROPERTY(QColor superColor READ superColor WRITE setSuperColor)
    Q_PROPERTY(QColor lunarColor READ lunarColor WRITE setLunarColor)

    Q_PROPERTY(QColor currentTextColor READ currentTextColor WRITE setCurrentTextColor)
    Q_PROPERTY(QColor otherTextColor READ otherTextColor WRITE setOtherTextColor)
    Q_PROPERTY(QColor selectTextColor READ selectTextColor WRITE setSelectTextColor)
    Q_PROPERTY(QColor hoverTextColor READ hoverTextColor WRITE setHoverTextColor)

    Q_PROPERTY(QColor currentLunarColor READ currentLunarColor WRITE setCurrentLunarColor)
    Q_PROPERTY(QColor otherLunarColor READ otherLunarColor WRITE setOtherLunarColor)
    Q_PROPERTY(QColor selectLunarColor READ selectLunarColor WRITE setSelectLunarColor)
    Q_PROPERTY(QColor hoverLunarColor READ hoverLunarColor WRITE setHoverLunarColor)

    Q_PROPERTY(QColor currentBackground READ currentBackground WRITE setCurrentBackground)
    Q_PROPERTY(QColor otherBackground READ otherBackground WRITE setOtherBackground)
    Q_PROPERTY(QColor selectBackground READ selectBackground WRITE setSelectBackground)
    Q_PROPERTY(QColor hoverBackgroundColor READ hoverBackground WRITE setHoverBackground)

public:
    enum DayType
    {
        DayType_MonthPre = 0,       //上月剩余天数
        DayType_MonthNext = 1,      //下个月的天数
        DayType_MonthCurrent = 2,   //当月天数
        DayType_WeekEnd = 3         //周末
    };
    Q_ENUM(DayType)

    enum SelectType
    {
        SelectType_Rect = 0,        //矩形背景
        SelectType_Circle = 1,      //圆形背景
        SelectType_Triangle = 2,    //带三角标
        SelectType_Image = 3        //图片背景
    };
    Q_ENUM(SelectType)

public:
    explicit HLunarCalendarItem(QWidget *parent = nullptr);
    ~HLunarCalendarItem() override;

signals:
    void clicked(const QDate &date, const DayType &dayType);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool isSelect() const;
    bool isShowLunar() const;
    QString backgroundImage() const;
    SelectType selectType() const;
    QDate date() const;
    QString dunar() const;
    DayType dayType() const;
    QColor borderColor() const;
    QColor weekColor() const;
    QColor superColor() const;
    QColor lunarColor() const;
    QColor currentTextColor() const;
    QColor otherTextColor() const;
    QColor selectTextColor() const;
    QColor hoverTextColor() const;
    QColor currentLunarColor() const;
    QColor otherLunarColor() const;
    QColor selectLunarColor() const;
    QColor hoverLunarColor() const;
    QColor currentBackground() const;
    QColor otherBackground() const;
    QColor selectBackground() const;
    QColor hoverBackground() const;

public slots:
    void setSelect(bool b);
    void setShowLunar(bool b);
    void setBackgroundImage(const QString &value);
    void setSelectType(SelectType value);
    void setDate(const QDate &value);
    void setLunar(const QString &value);
    void setDayType(DayType value);
    void setBorderColor(const QColor &value);
    void setWeekColor(const QColor &value);
    void setSuperColor(const QColor &value);
    void setLunarColor(const QColor &value);
    void setCurrentTextColor(const QColor &value);
    void setOtherTextColor(const QColor &value);
    void setSelectTextColor(const QColor &value);
    void setHoverTextColor(const QColor &value);
    void setCurrentLunarColor(const QColor &value);
    void setOtherLunarColor(const QColor &value);
    void setSelectLunarColor(const QColor &value);
    void setHoverLunarColor(const QColor &value);
    void setCurrentBackground(const QColor &value);
    void setOtherBackground(const QColor &value);
    void setSelectBackground(const QColor &value);
    void setHoverBackground(const QColor &value);

protected:
    HLunarCalendarItem(HLunarCalendarItemPrivate &p, QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawState(QPainter *);
    void drawCurrent(QPainter *, const QColor &);
    void drawDay(QPainter *);
    void drawLunar(QPainter *);

protected:
    QScopedPointer<HLunarCalendarItemPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HLUNARCALENDARITEM_H
