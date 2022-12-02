/***************************************************************************************************
**      2022-12-01  HRoundMenuWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HRoundMenuWidgetPrivate;

class HRoundMenuWidget : public QWidget
{
    Q_OBJECT

public:
    enum State
    {
        Shrink,
        Popped,
        Popping
    };

public:
    explicit HRoundMenuWidget(QWidget *parent = nullptr);
    ~HRoundMenuWidget() override;

public:
    void setImages(QStringList);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void onTimer();

protected:
    QScopedPointer<HRoundMenuWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

