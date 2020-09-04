/***************************************************************************************************
**      2020-08-31  HSoundSlider 语音滑块。
**                  参考VLC-3.0.9.2
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QAbstractSlider>

HE_CONTROL_BEGIN_NAMESPACE

class HSoundSliderPrivate;

class HSoundSlider : public QAbstractSlider
{
    Q_OBJECT

public:
    explicit HSoundSlider(QWidget *parent = nullptr);
    ~HSoundSlider() override;

public:
    void setMuted(bool);
    void setColors(QList<QColor>);

protected:
    HSoundSlider(HSoundSliderPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void wheelEvent(QWheelEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

protected:
    void init();
    void rebuildIfNeeded();
    void handleReleasedButton();
    void setPos(int x);
    QColor desaturate(QColor);

protected:
    QScopedPointer<HSoundSliderPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

