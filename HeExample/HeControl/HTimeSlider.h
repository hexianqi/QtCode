/***************************************************************************************************
**      2022-11-17  HTimeSlider
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HTimeSliderPrivate;

class HTimeSlider : public QWidget
{
    Q_OBJECT

public:
    explicit HTimeSlider(QWidget *parent = nullptr);
    ~HTimeSlider() override;

public:
    void setSec(int);

protected:
    HTimeSlider(HTimeSliderPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void init();
    QString digitalToTime(int sec);

protected:
    QScopedPointer<HTimeSliderPrivate> d_ptr;
};

HE_END_NAMESPACE
