/***************************************************************************************************
**      2019-07-02  HButtonProgressBar  按钮进度条控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85669-ds-1.html#tpc
**                  1:可设置进度线条宽度+颜色
**                  2:可设置边框宽度+颜色
**                  3:可设置圆角角度+背景颜色
***************************************************************************************************/

#ifndef HBUTTONPROGRESSBAR_H
#define HBUTTONPROGRESSBAR_H

#include "HAbstractProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HButtonProgressBarPrivate;

class HButtonProgressBar : public HAbstractProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HButtonProgressBar)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)

public:
    explicit HButtonProgressBar(QWidget *parent = nullptr);
    ~HButtonProgressBar() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor background() const;
    int lineWidth() const;
    QColor lineColor() const;
    int borderWidth() const;
    int borderRadius() const;
    QColor borderColor() const;

public slots:
    void setBackground(const QColor &value);
    void setLineWidth(int value);
    void setLineColor(const QColor &value);
    void setBorderWidth(int value);
    void setBorderRadius(int value);
    void setBorderColor(const QColor &value);

protected:
    HButtonProgressBar(HButtonProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawProgress(QPainter *);

private:
    void init();
    void updateValue();
};

HE_CONTROL_END_NAMESPACE

#endif // HBUTTONPROGRESSBAR_H
