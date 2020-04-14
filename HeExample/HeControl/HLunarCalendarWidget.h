/***************************************************************************************************
**      2017-11-17  HLunarCalendarWidget 农历控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:可设置边框/周末/角标/农历节日颜色
**                  2:可设置当前月/其他月/选中日期/悬停日期文字颜色
**                  3:可设置当前月/其他月/选中日期/悬停日期农历文字颜色
**                  4:可设置当前月/其他月/选中日期/悬停日期背景颜色
**                  5:可设置四种选中背景模式（矩形背景、圆形背景、图片背景、带三角标）
**                  6:可直接切换到上一年/下一年/上一月/下一月/转到今天
**                  7:可设置是否显示农历信息,不显示则当做正常的日历使用
**                  8:支持1901年-2099年范围
***************************************************************************************************/

#ifndef HLUNARCALENDARWIDGET_H
#define HLUNARCALENDARWIDGET_H

#include "HLunarCalendarItem.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLunarCalendarWidgetPrivate;

class HLunarCalendarWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDate date                                   READ date WRITE setDate)

    Q_PROPERTY(WeekNameFormat weekNameFormat                READ weekNameFormat     WRITE setWeekNameFormat)
    Q_PROPERTY(QColor weekTextColor                         READ weekTextColor      WRITE setWeekTextColor)
    Q_PROPERTY(QColor weekBackground                        READ weekBackground     WRITE setWeekBackground)

    Q_PROPERTY(bool showLunar                               READ isShowLunar        WRITE setShowLunar)
    Q_PROPERTY(QString backgroundImage                      READ backgroundImage    WRITE setBackgroundImage)
    Q_PROPERTY(HLunarCalendarItem::SelectType selectType    READ selectType         WRITE setSelectType)

    Q_PROPERTY(QColor borderColor                           READ borderColor        WRITE setBorderColor)
    Q_PROPERTY(QColor weekColor                             READ weekColor          WRITE setWeekColor)
    Q_PROPERTY(QColor superColor                            READ superColor         WRITE setSuperColor)
    Q_PROPERTY(QColor lunarColor                            READ lunarColor         WRITE setLunarColor)

    Q_PROPERTY(QColor currentTextColor                      READ currentTextColor   WRITE setCurrentTextColor)
    Q_PROPERTY(QColor otherTextColor                        READ otherTextColor     WRITE setOtherTextColor)
    Q_PROPERTY(QColor selectTextColor                       READ selectTextColor    WRITE setSelectTextColor)
    Q_PROPERTY(QColor hoverTextColor                        READ hoverTextColor     WRITE setHoverTextColor)

    Q_PROPERTY(QColor currentLunarColor                     READ currentLunarColor  WRITE setCurrentLunarColor)
    Q_PROPERTY(QColor otherLunarColor                       READ otherLunarColor    WRITE setOtherLunarColor)
    Q_PROPERTY(QColor selectLunarColor                      READ selectLunarColor   WRITE setSelectLunarColor)
    Q_PROPERTY(QColor hoverLunarColor                       READ hoverLunarColor    WRITE setHoverLunarColor)

    Q_PROPERTY(QColor currentBackground                     READ currentBackground  WRITE setCurrentBackground)
    Q_PROPERTY(QColor otherBackground                       READ otherBackground    WRITE setOtherBackground)
    Q_PROPERTY(QColor selectBackground                      READ selectBackground   WRITE setSelectBackground)
    Q_PROPERTY(QColor hoverBackground                       READ hoverBackground    WRITE setHoverBackground)

public:
    enum WeekNameFormat
    {
        WeekNameFormat_Short = 0,   // 短名称
        WeekNameFormat_Normal = 1,  // 普通名称
        WeekNameFormat_Long = 2,    // 长名称
        WeekNameFormat_En = 3       // 英文名称
    };
    Q_ENUM(WeekNameFormat)

public:
    explicit HLunarCalendarWidget(QWidget *parent = nullptr);
    ~HLunarCalendarWidget() override;

signals:
    void clicked(const QDate &date);
    void selectionChanged();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QDate date() const;
    WeekNameFormat weekNameFormat() const;
    QColor weekTextColor() const;
    QColor weekBackground() const;
    bool isShowLunar() const;
    QString backgroundImage() const;
    HLunarCalendarItem::SelectType selectType() const;
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
    void setDate(const QDate &value);
    void setWeekNameFormat(WeekNameFormat value);
    void setWeekTextColor(const QColor &value);
    void setWeekBackground(const QColor &value);
    void setShowLunar(bool b);
    void setBackgroundImage(const QString &value);
    void setSelectType(HLunarCalendarItem::SelectType value);
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
    void showYearPrevious();
    void showYearNext();
    void showMonthPrevious();
    void showMonthNext();
    void showToday();

protected:
    HLunarCalendarWidget(HLunarCalendarWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HLunarCalendarWidgetPrivate> d_ptr;

private:
    void init();
    void initWidget();
    void initStyle();
    void initDate();

private slots:
    void handleYearChanged(const QString &);
    void handleMonthChanged(const QString &);
    void handleItemClicked(const QDate &, const HLunarCalendarItem::DayType &);
    void dayChanged(const QDate &);
    void dateChanged(int year, int month, int day);
};

HE_CONTROL_END_NAMESPACE

#endif // HLUNARCALENDARWIDGET_H
