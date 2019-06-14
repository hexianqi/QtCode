/***************************************************************************************************
**      2019-06-12  HBattery 电池电量控件。
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1：可设置电池电量，动态切换电池电量变化
**                  2：可设置电池电量警戒值
**                  3：可设置电池电量正常颜色和报警颜色
**                  4：可设置边框渐变颜色
**                  5：可设置电量变化时每次移动的步长
***************************************************************************************************/

#ifndef HBATTERY_H
#define HBATTERY_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HBatteryPrivate;

class HBattery : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(double alarmValue READ alarmValue WRITE setAlarmValue)
    Q_PROPERTY(double currentValue READ currentValue WRITE setCurrentValue)
    Q_PROPERTY(int duration READ duration WRITE setDuration)
    Q_PROPERTY(QColor borderColorStart READ borderColorStart WRITE setBorderColorStart)
    Q_PROPERTY(QColor borderColorEnd READ borderColorEnd WRITE setBorderColorEnd)
    Q_PROPERTY(QColor alarmColorStart READ alarmColorStart WRITE setAlarmColorStart)
    Q_PROPERTY(QColor alarmColorEnd READ alarmColorEnd WRITE setAlarmColorEnd)
    Q_PROPERTY(QColor normalColorStart READ normalColorStart WRITE setNormalColorStart)
    Q_PROPERTY(QColor normalColorEnd READ normalColorEnd WRITE setNormalColorEnd)

public:
    explicit HBattery(QWidget *parent = 0);
    ~HBattery() override;

signals:
    void valueChanged(double value);

public:
    void setRange(double minValue, double maxValue);
    void setMinValue(double value);
    void setMaxValue(double value);
    void setValue(double value);
    void setAlarmValue(double value);
    void setCurrentValue(double value);
    void setDuration(int value);
    void setBorderColorStart(QColor value);
    void setBorderColorEnd(QColor value);
    void setAlarmColorStart(QColor value);
    void setAlarmColorEnd(QColor value);
    void setNormalColorStart(QColor value);
    void setNormalColorEnd(QColor value);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    double minValue() const;
    double maxValue() const;
    double value() const;
    double alarmValue() const;
    double currentValue() const;
    double duration() const;
    QColor borderColorStart() const;
    QColor borderColorEnd() const;
    QColor alarmColorStart() const;
    QColor alarmColorEnd() const;
    QColor normalColorStart() const;
    QColor normalColorEnd() const;

protected:
    HBattery(HBatteryPrivate &, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HBatteryPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HBATTERY_H
