/***************************************************************************************************
**      2019-06-19  HColorProgressBar 带颜色进度条控件。
***************************************************************************************************/

#ifndef HCOLORPROGRESSBAR_H
#define HCOLORPROGRESSBAR_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HColorProgressBarPrivate;

class HColorProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(QColor barBackground READ barBackground WRITE setBarBackground)
    Q_PROPERTY(QColor barSplitLineColor READ barSplitLineColor WRITE setBarSplitLineColor)
    Q_PROPERTY(QColor BarColor READ barColor WRITE setBarColor)
    Q_PROPERTY(int decimal READ decimal WRITE setDecimal)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int barSplitLineStep READ barSplitLineStep WRITE setBarSplitLineStep)
    Q_PROPERTY(bool showBarSplitLine READ isShowBarSplitLine WRITE setShowBarSplitLine)

public:
    explicit HColorProgressBar(QWidget *parent = nullptr);
    ~HColorProgressBar() override;

signals:
    void valueChanged(double value);

public slots:
    void setRange(double minimum, double maximum);
    void setMinimum(double value);
    void setMaximum(double value);
    void setValue(double value);
    void setBarBackground(const QColor &value);
    void setBarSplitLineColor(const QColor &value);
    void setBarColor(const QColor &value);
    void setDecimal(int value);
    void setSpace(int value);
    void setBarSplitLineStep(int value);
    void setShowBarSplitLine(bool value);

public:
    QSize sizeHint() const override;
    double minimum() const;
    double maximum() const;
    double value() const;
    QColor barBackground() const;
    QColor barSplitLineColor() const;
    QColor barColor() const;
    int decimal() const;
    int space() const;
    int barSplitLineStep() const;
    bool isShowBarSplitLine() const;

protected:
    HColorProgressBar(HColorProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawBar(QPainter *);
    void drarBarSplitLine(QPainter *);
    void drawText(QPainter *);

protected:
    QScopedPointer<HColorProgressBarPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORPROGRESSBAR_H
