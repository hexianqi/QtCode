/***************************************************************************************************
**      2022-12-30  HSlideButtonGroup
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HSlideButtonGroupPrivate;

class HSlideButtonGroup : public QWidget
{
    Q_OBJECT

public:
    enum State
    {
        UnPressed,      // 未按下
        Extend,         // 正在伸长宽度
        IconShowing,    // 图标正在显示
        IconShowed,     // 图标已显示
        IconHiding,     // 图标正在隐藏
        Rreduce         // 正在缩短宽度
    };

public:
    explicit HSlideButtonGroup(QWidget *parent = nullptr);
    ~HSlideButtonGroup() override;

signals:
    void clicked(int index);

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void onTimer();

protected:
    QScopedPointer<HSlideButtonGroupPrivate> d_ptr;
};

HE_END_NAMESPACE

