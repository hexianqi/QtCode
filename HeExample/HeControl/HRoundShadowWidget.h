/***************************************************************************************************
**      2022-12-02  HRoundShadowWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HRoundShadowWidgetPrivate;

class HRoundShadowWidget : public QWidget
{
    Q_OBJECT

public:
    enum PressType
    {
        NoPressed,                 // 未按下
        PressedRight,              // 鼠标按下右侧
        PressedBottom,             // 鼠标按下下侧
        PressedRightBottom,        // 鼠标按下右下侧
        PressedButNotInPadding     // 按下但没在右、下、右下边缘
    };

public:
    explicit HRoundShadowWidget(QWidget *parent = nullptr);
    ~HRoundShadowWidget() override;

public:
    void setCenterWidgetLayout(QLayout * layout);

protected:
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

protected:
    QScopedPointer<HRoundShadowWidgetPrivate> d_ptr;

private:
    void setLayout(QLayout *);
    void updatePaddingRect();
};

HE_END_NAMESPACE

