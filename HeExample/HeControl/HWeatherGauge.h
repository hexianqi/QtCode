/***************************************************************************************************
**      2019-04-23  HWeatherGauge 天气仪表盘控件
**                  1:可设置两种值,比如温度+湿度
**                  2:可设置两种值的背景颜色+文字颜色
**                  3:可设置零度值左侧右侧两种颜色
**                  4:可设置圆的起始角度和结束角度
**                  5:可设置10种天气,晴天+雨天+阴天+大风等
**                  6:可设置各种其他颜色
**                  7:可设置是否启用动画显示进度
***************************************************************************************************/

#pragma once

#include "HCircleGauge.h"

HE_BEGIN_NAMESPACE

class HWeatherGaugePrivate;

class HWeatherGauge : public HCircleGauge
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HWeatherGauge)
    Q_PROPERTY(WeatherType weatherType READ weatherType WRITE setWeatherType)
    Q_PROPERTY(QColor negativeColor READ negativeColor WRITE setNegativeColor)
    Q_PROPERTY(QColor positiveColor READ positiveColor WRITE setPositiveColor)
    Q_PROPERTY(QColor negativeTextColor READ negativeTextColor WRITE setNegativeTextColor)
    Q_PROPERTY(QColor positiveTextColor READ positiveTextColor WRITE setPositiveTextColor)
    Q_PROPERTY(QColor negativePixmapColor READ negativePixmapColor WRITE setNegativePixmapColor)
    Q_PROPERTY(QColor positivePixmapColor READ positivePixmapColor WRITE setPositivePixmapColor)
    Q_PROPERTY(double outerValue READ outerValue WRITE setOuterValue)
    Q_PROPERTY(double outerMinimum READ outerMinimum WRITE setOuterMinimum)
    Q_PROPERTY(double outerMaximum READ outerMaximum WRITE setOuterMaximum)
    Q_PROPERTY(int outerAngleStart READ outerAngleStart WRITE setOuterAngleStart)
    Q_PROPERTY(int outerAngleEnd READ outerAngleEnd WRITE setOuterAngleEnd)
    Q_PROPERTY(QColor outerRingBackground READ outerRingBackground WRITE setOuterRingBackground)
    Q_PROPERTY(QColor outerRingColor READ outerRingColor WRITE setOuterRingColor)
    Q_PROPERTY(QColor outerTextColor READ outerTextColor WRITE setOuterTextColor)

public:
    enum WeatherType
    {
        WeatherType_Sun = 0,            // 晴
        WeatherType_Rain = 1,           // 雨
        WeatherType_Snow = 2,           // 雪
        WeatherType_Cloud = 3,          // 多云
        WeatherType_Wind = 4,           // 风
        WeatherType_SnowRain = 5,       // 雪雨
        WeatherType_Hail = 6,           // 冰雹
        WeatherType_Thunderstorm = 7,   // 雷雨
        WeatherType_Fog = 8,            // 雾
        WeatherType_PartlyCloudy = 9    // 局部多云
    };

public:
    explicit HWeatherGauge(QWidget *parent = nullptr);

public:
    WeatherType weatherType() const;
    QColor negativeColor() const;
    QColor positiveColor() const;
    QColor negativeTextColor() const;
    QColor positiveTextColor() const;
    QColor negativePixmapColor() const;
    QColor positivePixmapColor() const;
    double outerValue() const;
    double outerMinimum() const;
    double outerMaximum() const;
    int outerAngleStart() const;
    int outerAngleEnd() const;
    QColor outerRingBackground() const;
    QColor outerRingColor() const;
    QColor outerTextColor() const;

public slots:
    void setWeatherType(WeatherType value);
    void setNegativeColor(const QColor &);
    void setPositiveColor(const QColor &);
    void setNegativeTextColor(const QColor &);
    void setPositiveTextColor(const QColor &);
    void setNegativePixmapColor(const QColor &);
    void setPositivePixmapColor(const QColor &);
    void setOuterRange(double minimum, double maximum);
    void setOuterMinimum(double value);
    void setOuterMaximum(double value);
    void setOuterValue(double value);
    void setOuterAngleStart(int value);
    void setOuterAngleEnd(int value);
    void setOuterRingBackground(const QColor &);
    void setOuterRingColor(const QColor &);
    void setOuterTextColor(const QColor &);

protected:
    HWeatherGauge(HWeatherGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawProgress(QPainter *, int radius) override;
    void drawValue(QPainter *, int radius) override;
    void drawPixmap(QPainter *);

private:
    void init();

};

HE_END_NAMESPACE
