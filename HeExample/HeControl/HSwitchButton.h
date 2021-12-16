/***************************************************************************************************
**      2016-11-06  HSwitchButton 开关按钮控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86032-ds-1.html#tpc
**                  1:可设置开关按钮的样式 圆角矩形/内圆形/外圆形
**                  2:可设置选中和未选中时的背景颜色
**                  3:可设置选中和未选中时的滑块颜色
**                  4:可设置显示的文本
**                  5:可设置滑块离背景的间隔
**                  6:可设置圆角角度
**                  7:可设置是否显示动画过渡效果
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HSwitchButtonPrivate;

class HSwitchButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int rectRadius READ rectRadius WRITE setRectRadius)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    Q_PROPERTY(bool showText READ isShowText WRITE setShowText)
    Q_PROPERTY(bool showCircle READ isShowCircle WRITE setShowCircle)
    Q_PROPERTY(bool animationEnable READ isAnimationEnable WRITE setAnimationEnable)
    Q_PROPERTY(ButtonStyle buttonStyle READ buttonStyle WRITE setButtonStyle)

    Q_PROPERTY(QColor backgroundOff READ backgroundOff WRITE setBackgroundOff)
    Q_PROPERTY(QColor backgroundOn READ backgroundOn WRITE setBackgroundOn)
    Q_PROPERTY(QColor sliderColorOff READ sliderColorOff WRITE setSliderColorOff)
    Q_PROPERTY(QColor sliderColorOn READ sliderColorOn WRITE setSliderColorOn)
    Q_PROPERTY(QColor textColorOff READ textColorOff WRITE setTextColorOff)
    Q_PROPERTY(QColor textColorOn READ textColorOn WRITE setTextColorOn)

    Q_PROPERTY(QString textOff READ textOff WRITE setTextOff)
    Q_PROPERTY(QString textOn READ textOn WRITE setTextOn)

public:
    enum ButtonStyle
    {
        ButtonStyle_Rect = 0,       // 圆角矩形
        ButtonStyle_CircleIn = 1,   // 内圆形
        ButtonStyle_CircleOut = 2   // 外圆形
    };
    Q_ENUM(ButtonStyle)

public:
    explicit HSwitchButton(QWidget *parent = nullptr);
    ~HSwitchButton() override;

signals:
    void checkedChanged(bool checked);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int space() const;
    int rectRadius() const;
    bool isChecked() const;
    bool isShowText() const;
    bool isShowCircle() const;
    bool isAnimationEnable() const;
    ButtonStyle buttonStyle() const;
    QColor backgroundOff() const;
    QColor backgroundOn() const;
    QColor sliderColorOff() const;
    QColor sliderColorOn() const;
    QColor textColorOff() const;
    QColor textColorOn() const;
    QString textOff() const;
    QString textOn() const;

public slots:
    void setSpace(int value);
    void setRectRadius(int value);
    void setChecked(bool b);
    void setShowText(bool b);
    void setShowCircle(bool b);
    void setAnimationEnable(bool b);
    void setButtonStyle(ButtonStyle value);
    void setBackgroundOff(const QColor &value);
    void setBackgroundOn(const QColor &value);
    void setSliderColorOff(const QColor &value);
    void setSliderColorOn(const QColor &value);
    void setTextColorOff(const QColor &value);
    void setTextColorOn(const QColor &value);
    void setTextOff(const QString &value);
    void setTextOn(const QString &value);

protected:
    HSwitchButton(HSwitchButtonPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawText(QPainter *);
    void drawCircle(QPainter *);
    void drawSlider(QPainter *);

protected:
    QScopedPointer<HSwitchButtonPrivate> d_ptr;

private:
    void init();
    void startAnimation();
    int calcPos();
};

HE_END_NAMESPACE
