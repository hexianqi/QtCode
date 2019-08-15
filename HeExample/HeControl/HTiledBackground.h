/***************************************************************************************************
**      2019-07-15  HTiledBackground 平铺背景控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85974-ds-1.html#tpc
**                  1:可设置交替背景颜色
**                  2:可设置大小
***************************************************************************************************/

#ifndef HTILEDBACKGROUND_H
#define HTILEDBACKGROUND_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HTiledBackgroundPrivate;

class HTiledBackground : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1)
    Q_PROPERTY(QColor color2 READ color2 WRITE setColor2)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(int size READ size WRITE setSize)

public:
    explicit HTiledBackground(QWidget *parent = nullptr);
    ~HTiledBackground() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor color1() const;
    QColor color2() const;
    int size() const;
    QPixmap pixmap() const;

public slots:
    void setColor1(const QColor &value);
    void setColor2(const QColor &value);
    void setSize(int value);
    void setPixmap(const QPixmap &value);

protected:
    HTiledBackground(HTiledBackgroundPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HTiledBackgroundPrivate> d_ptr;

private:
};

HE_CONTROL_END_NAMESPACE

#endif // HTILEDBACKGROUND_H


//protected:
//    void drawBg();
//


