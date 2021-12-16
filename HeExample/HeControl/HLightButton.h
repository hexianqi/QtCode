/***************************************************************************************************
**      2016-10-16  HLightButton 高亮发光按钮控件。
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:可设置文本,居中显示
**                  2:可设置文本颜色
**                  3:可设置外边框渐变颜色
**                  4:可设置里边框渐变颜色
**                  5:可设置背景色
**                  6:可设置是否在容器中可移动,当成一个对象使用
**                  7:可设置是否显示矩形
**                  8:可设置报警颜色+非报警颜色
**                  9:可控制启动报警和停止报警,报警时闪烁
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HLightButtonPrivate;

class HLightButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text                 READ text                   WRITE setText)
    Q_PROPERTY(QColor textColor             READ textColor              WRITE setTextColor)
    Q_PROPERTY(QColor alarmColor            READ alarmColor             WRITE setAlarmColor)
    Q_PROPERTY(QColor normalColor           READ normalColor            WRITE setNormalColor)
    Q_PROPERTY(QColor borderOutColorStart   READ borderOutColorStart    WRITE setBorderOutColorStart)
    Q_PROPERTY(QColor borderOutColorEnd     READ borderOutColorEnd      WRITE setBorderOutColorEnd)
    Q_PROPERTY(QColor borderInColorStart    READ borderInColorStart     WRITE setBorderInColorStart)
    Q_PROPERTY(QColor borderInColorEnd      READ borderInColorEnd       WRITE setBorderInColorEnd)
    Q_PROPERTY(QColor background            READ background             WRITE setBackground)
    Q_PROPERTY(QColor overlayColor          READ overlayColor           WRITE setOverlayColor)
    Q_PROPERTY(bool moveEnable              READ isMoveEnable           WRITE setMoveEnable)
    Q_PROPERTY(bool showRect                READ isShowRect             WRITE setShowRect)
    Q_PROPERTY(bool showOverlay             READ isShowOverlay          WRITE setShowOverlay)

public:
    explicit HLightButton(QWidget *parent = nullptr);
    ~HLightButton() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QString text() const;
    QColor textColor() const;
    QColor alarmColor() const;
    QColor normalColor() const;
    QColor borderOutColorStart() const;
    QColor borderOutColorEnd() const;
    QColor borderInColorStart() const;
    QColor borderInColorEnd() const;
    QColor background() const;
    QColor overlayColor() const;
    bool isMoveEnable() const;
    bool isShowRect() const;
    bool isShowOverlay() const;

public slots:
    void setText(const QString &value);
    void setTextColor(const QColor &value);
    void setAlarmColor(const QColor &value);
    void setNormalColor(const QColor &value);
    void setBorderOutColorStart(const QColor &value);
    void setBorderOutColorEnd(const QColor &value);
    void setBorderInColorStart(const QColor &value);
    void setBorderInColorEnd(const QColor &value);
    void setBackground(const QColor &value);
    void setOverlayColor(const QColor &value);
    void setMoveEnable(bool b);
    void setShowRect(bool b);
    void setShowOverlay(bool b);
    void startAlarm();
    void stopAlarm();
    void alarm();

protected:
    HLightButton(HLightButtonPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawRect(QPainter *);
    void drawBorderOut(QPainter *);
    void drawBorderIn(QPainter *);
    void drawBackground(QPainter *);
    void drawText(QPainter *);

protected:
    QScopedPointer<HLightButtonPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
