/***************************************************************************************************
**      2017-10-21  HPanelItem 面板区域控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86054-ds-1.html#tpc
**                  1:可设置标题栏文字/高度/字体/对齐方式/颜色
**                  2:可设置边框宽度/边框圆角角度/边框颜色
**                  3:可设置报警颜色切换间隔/报警加深颜色/报警普通颜色
**                  4:可设置启用状态和禁用状态时文字和边框颜色
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
