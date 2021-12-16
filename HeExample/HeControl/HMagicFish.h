/***************************************************************************************************
**      2018-07-15  HMagicFish 魔幻鱼控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85674-ds-1.html#tpc
**                  绘制原理 https://www.jianshu.com/p/3dd3d1524851
**                  1:可设置鱼头+鱼身+鱼鳍+鱼尾的颜色
**                  2:可设置鱼头+鱼身+鱼鳍+鱼尾的比例
**                  3:可设置基准颜色,作为所有统一颜色
**                  4:可设置鱼鳍是否摆动
**                  5:可设置鱼的停留位置旋转角度
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HMagicFishPrivate;

class HMagicFish : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor)
    Q_PROPERTY(QColor headColor READ headColor WRITE setHeadColor)
    Q_PROPERTY(QColor bodyColor READ bodyColor WRITE setBodyColor)
    Q_PROPERTY(QColor finColor READ finColor WRITE setFinColor)
    Q_PROPERTY(QColor tailColor READ tailColor WRITE setTailColor)
    Q_PROPERTY(bool finMoveEnable READ isFinMoveEnable WRITE setFinMoveEnable)
    Q_PROPERTY(int speed READ speed WRITE setSpeed)
    Q_PROPERTY(double wave READ wave WRITE setWave)
    Q_PROPERTY(double angle READ angle WRITE setAngle)

public:
    explicit HMagicFish(QWidget *parent = nullptr);
    ~HMagicFish() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor baseColor() const;
    QColor headColor() const;
    QColor bodyColor() const;
    QColor finColor() const;
    QColor tailColor() const;
    bool isFinMoveEnable() const;
    int speed() const;
    double wave() const;
    double angle() const;
    double getLength() const;

public slots:
    void setBaseColor(const QColor &value);
    void setHeadColor(const QColor &value);
    void setBodyColor(const QColor &value);
    void setFinColor(const QColor &value);
    void setTailColor(const QColor &value);
    void setFinMoveEnable(bool b);
    void setSpeed(int value);
    void setWave(double value);
    void setAngle(double value);
    void setLength(double value);

protected:
    HMagicFish(HMagicFishPrivate &p, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawHead(QPainter *);
    void drawBody(QPainter *, const QPointF &pos, double angle);
    void drawFin(QPainter *, const QPointF &pos, double angle, bool left);
    void drawTail(QPainter *, const QPointF &pos, double angle);
    void drawTail1(QPainter *, const QPointF &pos, double angle);
    void drawTail2(QPainter *, const QPointF &pos, double angle);
    QPointF calcPoint(const QPointF &pos, double len, double angle);
    double calcWaveRadians(double value);

protected:
    QScopedPointer<HMagicFishPrivate> d_ptr;

private:
    void init();
    void updateValue();
};

HE_END_NAMESPACE
