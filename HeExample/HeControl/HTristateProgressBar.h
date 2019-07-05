/***************************************************************************************************
**      2019-07-03  HTristateProgressBar 三态进度条控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85615-ds-1.html#tpc
**                  1:可设置三种状态不同的值
**                  2:可设置三种状态不同的颜色
**                  3:可设置圆角角度
**                  4:可设置启用自动圆角
**                  5:可设置边框宽度+颜色
**                  6:可设置是否显示值或者百分比
**                  7:可设置字体自适应大小
**                  8:可设置背景颜色+文字颜色
**                  9:精准计算圆角角度,解决了QSS中border-radius当进度小于圆角角度出现方形的BUG
***************************************************************************************************/

#ifndef HTRISTATEPROGRESSBAR_H
#define HTRISTATEPROGRESSBAR_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HTristateProgressBarPrivate;

class HTristateProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value1 READ value1 WRITE setValue1)
    Q_PROPERTY(int value2 READ value2 WRITE setValue2)
    Q_PROPERTY(int value3 READ value3 WRITE setValue3)
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1)
    Q_PROPERTY(QColor color2 READ color2 WRITE setColor2)
    Q_PROPERTY(QColor color3 READ color3 WRITE setColor3)
    Q_PROPERTY(int radius READ radius WRITE setRadius)
    Q_PROPERTY(bool autoRadius READ isAutoRadius WRITE setAutoRadius)
    Q_PROPERTY(bool autoFont READ isAutoFont WRITE setAutoFont)
    Q_PROPERTY(bool showValue READ isShowValue WRITE setShowValue)
    Q_PROPERTY(bool showPercent READ isShowPercent WRITE setShowPercent)
    Q_PROPERTY(double borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

public:
    explicit HTristateProgressBar(QWidget *parent = nullptr);
    ~HTristateProgressBar() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int value1() const;
    int value2() const;
    int value3() const;
    QColor color1() const;
    QColor color2() const;
    QColor color3() const;
    int radius() const;
    bool isAutoRadius() const;
    bool isAutoFont() const;
    bool isShowValue() const;
    bool isShowPercent() const;
    double borderWidth() const;
    QColor background() const;
    QColor borderColor() const;
    QColor textColor() const;

public slots:
    void setValue1(int value);
    void setValue2(int value);
    void setValue3(int value);
    void setColor1(const QColor &value);
    void setColor2(const QColor &value);
    void setColor3(const QColor &value);
    void setRadius(int value);
    void setAutoRadius(bool b);
    void setAutoFont(bool b);
    void setShowValue(bool b);
    void setShowPercent(bool b);
    void setBorderWidth(double value);
    void setBackground(const QColor &value);
    void setBorderColor(const QColor &value);
    void setTextColor(const QColor &value);

protected:
    HTristateProgressBar(HTristateProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawValue(QPainter *);
    void drawBorder(QPainter *);

protected:
    QScopedPointer<HTristateProgressBarPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HTRISTATEPROGRESSBAR_H
