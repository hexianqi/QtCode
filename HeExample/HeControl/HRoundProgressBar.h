/***************************************************************************************************
**      2019-06-25  HRoundProgressBar 圆形进度条。
***************************************************************************************************/

#ifndef HROUNDPROGRESSBAR_H
#define HROUNDPROGRESSBAR_H

#include "HAbstractProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HRoundProgressBarPrivate;

class HRoundProgressBar : public HAbstractProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HRoundProgressBar)
    Q_PROPERTY(BarStyle barStyle READ barStyle WRITE setBarStyle)
    Q_PROPERTY(bool reverse READ isReverse WRITE setReverse)
    Q_PROPERTY(int angleStart READ angleStart WRITE setAngleStart)
    Q_PROPERTY(bool drawExcircle READ isDrawExcircle WRITE setDrawExcircle)
    Q_PROPERTY(bool drawDataCircle READ isDrawDataCircle WRITE setDrawDataCircle)
    Q_PROPERTY(bool drawInnerCircle READ isDrawInnerCircle WRITE setDrawInnerCircle)
    Q_PROPERTY(bool drawText READ isDrawText WRITE setDrawText)
    Q_PROPERTY(QString format READ format WRITE setFormat)
    Q_PROPERTY(double excircleWidth READ excircleWidth WRITE setExcircleWidth)
    Q_PROPERTY(double dataCircleWidth READ dataCircleWidth WRITE setDataCircleWidth)

public:
    enum BarStyle
    {
        BarStyle_Donut, // 圆环
        BarStyle_Pie,   // 饼状
        BarStyle_Line,  // 线条
    };

public:
    explicit HRoundProgressBar(QWidget *parent = nullptr);
    ~HRoundProgressBar() override;

public:
    BarStyle barStyle() const;
    bool isReverse() const;
    int angleStart() const;
    bool isDrawExcircle() const;
    bool isDrawDataCircle() const;
    bool isDrawInnerCircle() const;
    bool isDrawText() const;
    QString format() const;
    double excircleWidth() const;
    double dataCircleWidth() const;

public slots:
    void setBarStyle(BarStyle value);
    void setReverse(bool b);
    void setAngleStart(int value);
    void setDrawExcircle(bool b);
    void setDrawDataCircle(bool b);
    void setDrawInnerCircle(bool b);
    void setDrawText(bool b);
    void setFormat(QString value);
    void setExcircleWidth(double value);
    void setDataCircleWidth(double value);
    void setDataColors(const QGradientStops &value);

protected:
    HRoundProgressBar(HRoundProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    QImage createImage();
    void drawExcircle(QPainter *);
    void drawDataCircle(QPainter *);
    void drawInnerCircle(QPainter *);
    void drawText(QPainter *);
    void rebuildDataBrushIfNeeded();
    QString valueToText(double value);
};

HE_CONTROL_END_NAMESPACE

#endif // HROUNDPROGRESSBAR_H
