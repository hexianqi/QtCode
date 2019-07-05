/***************************************************************************************************
**      2019-07-02  HMagicMouse 魔幻老鼠控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85664-ds-1.html#tpc
**                  本控件来源于qtdemo
**                  1:可设置身体+眼睛+眼珠+鼻子+尾巴的颜色
**                  2:可设置停留位置旋转角度
***************************************************************************************************/

#ifndef HMAGICMOUSE_H
#define HMAGICMOUSE_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HMagicMousePrivate;

class HMagicMouse : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double angle READ angle WRITE setAngle)
    Q_PROPERTY(QColor bodyColor READ bodyColor WRITE setBodyColor)
    Q_PROPERTY(QColor eyeColor READ eyeColor WRITE setEyeColor)
    Q_PROPERTY(QColor eyeballColor READ eyeballColor WRITE setEyeballColor)
    Q_PROPERTY(QColor noseColor READ noseColor WRITE setNoseColor)
    Q_PROPERTY(QColor earColor READ earColor WRITE setEarColor)
    Q_PROPERTY(QColor tailColor READ tailColor WRITE setTailColor)

public:
    explicit HMagicMouse(QWidget *parent = nullptr);
    ~HMagicMouse() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    double angle() const;
    QColor bodyColor() const;
    QColor eyeColor() const;
    QColor eyeballColor() const;
    QColor noseColor() const;
    QColor earColor() const;
    QColor tailColor() const;

public slots:
    void setAngle(double value);
    void setBodyColor(const QColor &value);
    void setEyeColor(const QColor &value);
    void setEyeballColor(const QColor &value);
    void setNoseColor(const QColor &value);
    void setEarColor(const QColor &value);
    void setTailColor(const QColor &value);

protected:
    HMagicMouse(HMagicMousePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBody(QPainter *);
    void drawEye(QPainter *);
    void drawEyeball(QPainter *);
    void drawNose(QPainter *);
    void drawEar(QPainter *);
    void drawTail(QPainter *);

protected:
    QScopedPointer<HMagicMousePrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HMAGICMOUSE_H
