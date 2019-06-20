/***************************************************************************************************
**      2019-06-17  HLedNumber LED数字控件
**                  http://www.qtcn.org/bbs/read-htm-tid-63464.html
**                  1：可设置当前数字
**                  2：可设置各种颜色
***************************************************************************************************/

#ifndef HLEDNUMBER_H
#define HLEDNUMBER_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HLedNumberPrivate;

class HLedNumber : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int number READ number WRITE setNumber)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int padding READ padding WRITE setPadding)
    Q_PROPERTY(int radius READ radius WRITE setRadius)
    Q_PROPERTY(QColor backgroundStart READ backgroundStart WRITE setBackgroundStart)
    Q_PROPERTY(QColor backgroundEnd READ backgroundEnd WRITE setBackgroundEnd)
    Q_PROPERTY(QColor numberBackgroundStart READ numberBackgroundStart WRITE setNumberBackgroundStart)
    Q_PROPERTY(QColor numberBackgroundEnd READ numberBackgroundEnd WRITE setNumberBackgroundEnd)
    Q_PROPERTY(QColor numberColorStart READ numberColorStart WRITE setNumberColorStart)
    Q_PROPERTY(QColor numberColorEnd READ numberColorEnd WRITE setNumberColorEnd)

public:
    explicit HLedNumber(QWidget *parent = nullptr);
    ~HLedNumber() override;

public:
    void setNumber(int value);
    void setSpace(int value);
    void setPadding(int value);
    void setRadius(int value);
    void setBackgroundStart(const QColor &value);
    void setBackgroundEnd(const QColor &value);
    void setNumberBackgroundStart(const QColor &value);
    void setNumberBackgroundEnd(const QColor &value);
    void setNumberColorStart(const QColor &value);
    void setNumberColorEnd(const QColor &value);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int number() const;
    int space() const;
    int padding() const;
    int radius() const;
    QColor backgroundStart() const;
    QColor backgroundEnd() const;
    QColor numberBackgroundStart() const;
    QColor numberBackgroundEnd() const;
    QColor numberColorStart() const;
    QColor numberColorEnd() const;

protected:
    HLedNumber(HLedNumberPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawNumberBackground(QPainter *);
    void drawNumber(QPainter *);

protected:
    QScopedPointer<HLedNumberPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HLEDNUMBER_H
