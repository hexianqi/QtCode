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

#ifndef HWEATHERGAUGE_H
#define HWEATHERGAUGE_H

#include "HCircleGauge.h"

HE_CONTROL_BEGIN_NAMESPACE

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
    ~HWeatherGauge() override;

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
    void setNegativeColor(const QColor &value);
    void setPositiveColor(const QColor &value);
    void setNegativeTextColor(const QColor &value);
    void setPositiveTextColor(const QColor &value);
    void setNegativePixmapColor(const QColor &value);
    void setPositivePixmapColor(const QColor &value);
    void setOuterRange(double minimum, double maximum);
    void setOuterMinimum(double value);
    void setOuterMaximum(double value);
    void setOuterValue(double value);    
    void setOuterAngleStart(int value);
    void setOuterAngleEnd(int value);
    void setOuterRingBackground(const QColor &value);
    void setOuterRingColor(const QColor &value);
    void setOuterTextColor(const QColor &value);

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

HE_CONTROL_END_NAMESPACE

#endif // HWEATHERGAUGE_H





//private slots:
//    void updateOuterValue();            //更新外圈数值
//    void updateInnerValue();            //更新内圈数值

//    int precision;                      //精确度,小数点后几位

//    QColor centerPixMapNegativeColor;   //中心图片颜色
//    QColor centerPixMapPositiveColor;   //中心图片颜色
//    QString centerSvgPath;              //当前svg图片路径
//    WeatherType weatherType;            //天气类型

//    QColor outerValueTextColor;         //外环值文本颜色
//    QColor innerNegativeValueTextColor; //内环正值文本颜色
//    QColor innerPositiveValueTextColor; //内环负值文本颜色

//    //将svg文件中的xml数据颜色替换
//    void setColor(QDomElement elem, QString strtagname, QString strattr, QString strattrval);
//    QString rgb2HexStr(const QColor &color);

//public:
//    double getOuterMinValue()               const;
//    double getOuterMaxValue()               const;
//    double getOuterValue()                  const;
//    int getOuterStartAngle()                const;
//    int getOuterEndAngle()                  const;

//    QColor getOuterRingBgColor()            const;
//    QColor getOuterRingColor()              const;

//    double getInnerMaxValue()               const;
//    double getInnerMinValue()               const;
//    double getInnerValue()                  const;
//    int getInnerStartAngle()                const;
//    int getInnerEndAngle()                  const;

//    QColor getInnerRingBgColor()            const;
//    QColor getInnerNegativeColor()          const;
//    QColor getInnerPositiveColor()          const;

//    int getInnerScaleMajor()                const;
//    int getInnerScaleMinor()                const;
//    QColor getInnerScaleColor()             const;
//    QColor getInnerScaleNumColor()          const;

//    bool getAnimation()                     const;
//    double getAnimationStep()               const;

//    WeatherType getWeatherType()            const;

//    QColor getCenterPixMapNegativeColor()   const;
//    QColor getCenterPixMapPositiveColor()   const;

//    QColor getOuterValueTextColor()         const;
//    QColor getInnerNegativeValueTextColor() const;
//    QColor getInnerPositiveValueTextColor() const;

//    QSize sizeHint()                        const;
//    QSize minimumSizeHint()                 const;

//public Q_SLOTS:
//    void setWeatherType(WeatherType &type);

//    //设置范围值
//    void setOuterRange(double minValue, double maxValue);
//    //设置外环最大最小值
//    void setOuterMinValue(double value);
//    void setOuterMaxValue(double value);

//    //设置外环值
//    void setOuterValue(double value);
//    //设置外环开始旋转角度
//    void setOuterStartAngle(int startAngle);
//    //设置外环结束旋转角度
//    void setOuterEndAngle(int endAngle);
//    //设置外环背景色
//    void setOuterRingBgColor(const QColor &color);
//    //设置外环进度色
//    void setOuterRingColor(const QColor &color);

//    //设置范围值
//    void setInnerRange(double minValue, double maxValue);
//    void setInnerMinValue(double value);
//    void setInnerMaxValue(double value);
//    void setInnerValue(double value);
//    void setInnerStartAngle(int startAngle);
//    void setInnerEndAngle(int endAngle);

//    void setInnerRingBgColor(const QColor &color);
//    void setInnerNegativeColor(const QColor &color);
//    void setInnerPositiveColor(const QColor &color);

//    void setInnerScaleMajor(int value);
//    void setInnerScaleMinor(int value);
//    void setInnerScaleColor(const QColor &color);
//    void setInnerScaleNumColor(const QColor &color);

//    //设置中心图标颜色
//    void setCenterPixMapNegativeColor(const QColor &color);
//    void setCenterPixMapPositiveColor(const QColor &color);

//    void setOuterValueTextColor(const QColor &color);
//    void setInnerNegativeValueTextColor(const QColor &color);
//    void setInnerPositiveValueTextColor(const QColor &color);

//    //设置是否启用动画显示
//    void setAnimation(bool animation);
//    //设置动画显示的步长
//    void setAnimationStep(double animationStep);

//Q_SIGNALS:
//    void valueChanged(double value);
//};

//#endif // GAUGEWEATHER_H
