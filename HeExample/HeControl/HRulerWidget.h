/***************************************************************************************************
**      2022-09-02  HRulerWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HRulerWidgetPrivate;

class HRulerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HRulerWidget(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~HRulerWidget() override;

public:
    void setOffset(int);
    void setSlidingPos(int);

protected:
    HRulerWidget(HRulerWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    virtual void init();

protected:
    QScopedPointer<HRulerWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
