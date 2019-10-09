/***************************************************************************************************
**      2017-10-21  HPanelItem 面板区域控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86054-ds-1.html#tpc
**                  1:可设置标题栏文字/高度/字体/对齐方式/颜色
**                  2:可设置边框宽度/边框圆角角度/边框颜色
**                  3:可设置报警颜色切换间隔/报警加深颜色/报警普通颜色
**                  4:可设置启用状态和禁用状态时文字和边框颜色
***************************************************************************************************/

#ifndef HPANELITEM_H
#define HPANELITEM_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HPanelItemPrivate;

class HPanelItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor borderDisableColor READ borderDisableColor WRITE setBorderDisableColor)

    Q_PROPERTY(int titleHeight READ titleHeight WRITE setTitleHeight)
    Q_PROPERTY(QString titleText READ titleText WRITE setTitleText)
    Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont)
    Q_PROPERTY(Qt::Alignment titleAlignment READ titleAlignment WRITE setTitleAlignment)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)
    Q_PROPERTY(QColor titleDisableColor READ titleDisableColor WRITE setTitleDisableColor)

    Q_PROPERTY(bool alarm READ isAlarm WRITE setAlarm)
    Q_PROPERTY(int alarmInterval READ alarmInterval WRITE setAlarmInterval)
    Q_PROPERTY(QColor alarmTextColor READ alarmTextColor WRITE setAlarmTextColor)
    Q_PROPERTY(QColor alarmDarkColor READ alarmDarkColor WRITE setAlarmDarkColor)
    Q_PROPERTY(QColor alarmNormalColor READ alarmNormalColor WRITE setAlarmNormalColor)

public:
    explicit HPanelItem(QWidget *parent = nullptr);
    ~HPanelItem() override;

public:
    //    QSize sizeHint()                const;
    //    QSize minimumSizeHint()         const;

    int borderWidth() const;
    int borderRadius() const;
    QColor borderColor() const;
    QColor borderDisableColor() const;
    int titleHeight() const;
    QString titleText() const;
    QFont titleFont() const;
    Qt::Alignment titleAlignment() const;
    QColor titleColor() const;
    QColor titleDisableColor() const;
    bool isAlarm() const;
    int alarmInterval() const;
    QColor alarmTextColor() const;
    QColor alarmDarkColor() const;
    QColor alarmNormalColor() const;

public slots:
    void setBorderWidth(int value);
    void setBorderRadius(int value);
    void setBorderColor(const QColor &value);
    void setBorderDisableColor(const QColor &value);
    void setTitleHeight(int value);
    void setTitleText(const QString &value);
    void setTitleFont(const QFont &value);
    void setTitleAlignment(Qt::Alignment value);
    void setTitleColor(const QColor &value);
    void setTitleDisableColor(const QColor &value);
    void setAlarm(bool b);
    void setAlarmInterval(int value);
    void setAlarmTextColor(const QColor &value);
    void setAlarmDarkColor(const QColor &value);
    void setAlarmNormalColor(const QColor &value);

protected:
    HPanelItem(HPanelItemPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBorder(QPainter *);
    void drawTitle(QPainter *);
    QColor currentBorderColor();
    QColor currentTitleColor();

protected:
    QScopedPointer<HPanelItemPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HPANELITEM_H

//private:
//    int titleHeight;                //标题高度
//    QString titleText;              //标题文字
//    QFont titleFont;                //标题字体
//    Alignment titleAlignment;       //标题对齐方式
//    QColor titleColor;              //标题颜色
//    QColor titleDisableColor;       //禁用状态下文字颜色

//    int borderWidth;                //边框宽度
//    int borderRadius;               //边框圆角角度
//    QColor borderColor;             //边框颜色
//    QColor borderDisableColor;      //禁用状态下边框颜色

//    int alarmInterval;              //报警切换间隔
//    QColor alarmTextColor;          //报警文字颜色
//    QColor alarmDarkColor;          //报警加深颜色
//    QColor alarmNormalColor;        //报警普通颜色

//    bool isAlarm;                   //是否报警
//    bool isEnable;                  //是否启用

//    bool isDark;                    //是否加深
//    QColor tempColor;               //临时颜色
//    QTimer *timer;                  //报警切换定时器

//public:
//    int getTitleHeight()            const;
//    QString getTitleText()          const;
//    QFont getTitleFont()            const;
//    Alignment getTitleAlignment()   const;
//    QColor getTitleColor()          const;
//    QColor getTitleDisableColor()   const;

//    int getBorderWidth()            const;
//    int getBorderRadius()           const;
//    QColor getBorderColor()         const;
//    QColor getBorderDisableColor()  const;

//    int getAlarmInterval()          const;
//    QColor getAlarmTextColor()      const;
//    QColor getAlarmDarkColor()      const;
//    QColor getAlarmNormalColor()    const;

//    bool getIsAlarm()               const;
//    bool getIsEnable()              const;


//private slots:
//    void checkAlarm();

//public Q_SLOTS:
//    //设置报警状态
//    void setAlarm(bool alarm);
//    //设置启用状态
//    void setEnable(bool enable);

//    //设置标题栏高度
//    void setTitleHeight(int titleHeight);
//    //设置标题文字
//    void setTitleText(const QString &titleText);
//    //设置标题字体
//    void setTitleFont(const QFont &titleFont);
//    //设置标题文字对齐方式
//    void setTitleAlignment(const Alignment &titleAlignment);
//    //设置标题文字颜色
//    void setTitleColor(const QColor &titleColor);
//    //设置禁用状态下标题文字颜色
//    void setTitleDisableColor(const QColor &titleDisableColor);

//    //设置边框宽度
//    void setBorderWidth(int borderWidth);
//    //设置边框圆角角度
//    void setBorderRadius(int borderRadius);
//    //设置边框颜色
//    void setBorderColor(const QColor &borderColor);
//    //设置禁用状态下边框颜色
//    void setBorderDisableColor(const QColor &borderDisableColor);

//    //设置报警切换间隔
//    void setAlarmInterval(int alarmInterval);
//    //设置报警文字颜色
//    void setAlarmTextColor(const QColor &alarmTextColor);
//    //设置报警加深颜色
//    void setAlarmDarkColor(const QColor &alarmDarkColor);
//    //设置报警普通颜色
//    void setAlarmNormalColor(const QColor &alarmNormalColor);

//};

//#endif // PANELFRAME_H
