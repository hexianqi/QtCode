/***************************************************************************************************
**      2019-06-19  HColorProgressBar 带颜色进度条控件。
***************************************************************************************************/

#ifndef HCOLORPROGRESSBAR_H
#define HCOLORPROGRESSBAR_H

#include "HAbstractProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HColorProgressBarPrivate;

class HColorProgressBar : public HAbstractProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HColorProgressBar)
    Q_PROPERTY(QColor barBackground READ barBackground WRITE setBarBackground)
    Q_PROPERTY(QColor barSplitLineColor READ barSplitLineColor WRITE setBarSplitLineColor)
    Q_PROPERTY(QColor BarColor READ barColor WRITE setBarColor)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int barSplitLineStep READ barSplitLineStep WRITE setBarSplitLineStep)
    Q_PROPERTY(bool showBarSplitLine READ isShowBarSplitLine WRITE setShowBarSplitLine)

public:
    explicit HColorProgressBar(QWidget *parent = nullptr);
    ~HColorProgressBar() override;

public:
    QSize sizeHint() const override;
    QColor barBackground() const;
    QColor barSplitLineColor() const;
    QColor barColor() const;
    int space() const;
    int barSplitLineStep() const;
    bool isShowBarSplitLine() const;

public slots:
    void setBarBackground(const QColor &value);
    void setBarSplitLineColor(const QColor &value);
    void setBarColor(const QColor &value);
    void setSpace(int value);
    void setBarSplitLineStep(int value);
    void setShowBarSplitLine(bool value);

protected:
    HColorProgressBar(HColorProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawBar(QPainter *);
    void drarBarSplitLine(QPainter *);
    void drawText(QPainter *);
};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORPROGRESSBAR_H
